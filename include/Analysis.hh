/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include <typeinfo>
#include <mutex>
#include <thread>
#define INFORMATION

#include "File.hh"
#include "Reader.hh"
#include "AnalysisBase.hh"
#include "Debug.hh"

namespace boca
{

template<typename Tagger>
class First
{
public:
    First(Reader<Tagger>& reader, Stage stage, Tag tag) :
        reader_(reader) {
        Info();
        stage_ = stage;
        tag_ = tag;
    }
    Stage stage()  {
        Info();
        return stage_;
    }
    Tag tag()  {
        Info();
        return tag_;
    }
    Reader<Tagger>& reader()  {
        Info();
        return reader_;
    }
private:
    Reader<Tagger>& reader_;
    Stage stage_;
    Tag tag_;
};

template<typename Tagger>
class Second
{
public:
    Second(First<Tagger>& first, File& file, TFile& export_file) :
        first_(first),
        export_file_(export_file),
        file_(file) {
        Info();
    }
    First<Tagger>& first()  {
        Info();
        return first_;
    }
    File& file()  {
        Info();
        return file_;
    }
    TFile& export_file()  {
        Info();
        return export_file_;
    }
private:
    First<Tagger>& first_;
    File& file_;
    TFile& export_file_;
};

template<typename Tagger>
class BranchWriter
{

public:
    BranchWriter(Second<Tagger>& second, Tagger& tagger) :
        second_(second) {
        Info();
        tree_writer_ = exroot::TreeWriter(&(second.export_file()), second.file().Title().c_str());
        SetTreeBranch(tagger);
        tree_branch_ = tree_writer_.NewBranch(tagger.WeightBranchName().c_str(), InfoBranch::Class());
    }

    void SetTreeBranch(Tagger& tagger) {
        Info();
        switch (second().first().stage()) {
        case Stage::trainer : tagger.SetTreeBranch(tree_writer(), second().first().stage());
            break;
        case Stage::reader : second().first().reader().SetTreeBranch(tree_writer(), second().first().stage());
            break;
        }
    }

    void set_object_sum(long object_sum) {
        Info();
        std::lock_guard<std::mutex> guard1(object_sum_mutex);
        object_sum_ = object_sum;
    }
    void Write() {
        Error();
        if (object_sum()) tree_writer().Write();
    }

    Second<Tagger>& second()  {
        Info();
        return second_;
    }

    exroot::TreeBranch& tree_branch() {
        Info();
        return *tree_branch_;
    }

    exroot::TreeWriter& tree_writer() {
        Error();
        return tree_writer_;
    }

    long& object_sum() {
        Info();
        return object_sum_;
    }

private:

    exroot::TreeBranch* tree_branch_;
    std::mutex tree_branch_mutex;

    exroot::TreeWriter tree_writer_;
    std::mutex tree_writer_mutex;

    long object_sum_ = 0;
    std::mutex object_sum_mutex;

    Second<Tagger>& second_;
    std::mutex second_mutex;

};

template<typename Tagger>
class Third
{
public:
    Third(Second<Tagger>& second, BranchWriter<Tagger>& tree_writer, Tagger tagger, int entry) :
        second_(second),
        tree_writer_(tree_writer),
        tagger_(tagger) {
        Info();
        entry_ = entry;
        Initialize();
    }

    void Initialize() {
        Error();
        std::lock_guard<std::mutex> second_guard(second_mutex);
        clones_arrays_ = ClonesArrays(second().file().source());
        tree_reader_ = second().file().TreeReader();
        clones_arrays_.UseBranches(tree_reader_);
//         InfoBranch info_branch = FillInfoBranch(second().file());
    }

    InfoBranch FillInfoBranch(boca::File const& file)  {
        Error();
        InfoBranch info_branch;
        info_branch.Crosssection = file.crosssection() / fb;
        info_branch.CrosssectionError = file.crosssection_error() / fb;
        info_branch.Mass = file.mass() / GeV;
        info_branch.Name = file.nice_name();
        return info_branch;
    }

    ClonesArrays const& clones_arrays()  {
        Info();
        return clones_arrays_;
    }

    exroot::TreeReader& tree_reader() {
        Info();
        return tree_reader_;
    }


    InfoBranch& info_branch() {
        Info();
        return info_branch_;
    }

    long& event_number() {
        Info();
        return event_number_;
    }

    Range range(long max) {
        return Range(FirstEntry(max), GetEntries());
    }

    long FirstEntry(long max)  {
        Info();
        long entry = 0;
        std::lock_guard<std::mutex> guard1(second_mutex);
        if (second().first().stage() == Stage::reader) entry = std::min(GetEntries(), max) / 2;  // TODO fix corner cases
        return entry;
    }

    long GetEntries() {
        Info();
        return tree_reader().GetEntries();
    }


    bool SaveEntry(int object_number) {
        Info();
        std::lock_guard<std::mutex> guard2(event_number_mutex);
        std::lock_guard<std::mutex> guard3(inf_branch_mutex);
        info_branch().EventNumber = event_number();
        std::lock_guard<std::mutex> guard5(tree_writer_mutex);
        static_cast<InfoBranch&>(*branch_writer().tree_branch().NewEntry()) = info_branch();
        Error();
        branch_writer().tree_writer().Fill();
        branch_writer().tree_writer().Clear();
        return object_number;
    }

    void ReadEntry() {
        Info();
        std::lock_guard<std::mutex> guard2(event_number_mutex);
        ++event_number();
        tree_reader().ReadEntry(entry_);
    }

    Tagger& tagger() {
        Info();
        return tagger_;
    }

    Second<Tagger>& second()  {
        Info();
        return second_;
    }

    BranchWriter<Tagger>& branch_writer() {
        Error();
        return tree_writer_;
    }

    int entry_;
private:

    ClonesArrays clones_arrays_;
    exroot::TreeReader tree_reader_;

    InfoBranch info_branch_;
    std::mutex inf_branch_mutex;


    Second<Tagger>& second_;
    std::mutex second_mutex;

    long event_number_ = 0;
    std::mutex event_number_mutex;

    BranchWriter<Tagger>& tree_writer_;
    std::mutex tree_writer_mutex;

    Tagger tagger_;
};

/**
 * @brief provides main analysis loops and logic.
 * @details This class has to be subclassed for each analysis.
 * The subclasses have to be instantiated with a Tagger as template argument.
 * Subclasses should be templated classes.
 * @author Jan Hajer
 * @copyright Copyright (C) 2015 Jan Hajer
 * @date 2015
 * @license GPL 3
 *
 */
template<typename Tagger>
class Analysis : public AnalysisBase
{

public:

    /**
     * @brief Main analysis loop which has to be called by main.cpp
     *
     */
    void AnalysisLoop(Stage stage) final {
        Info();
        Reader<Tagger> reader(stage);
        for (auto const & tag : std::vector<Tag> {Tag::signal, Tag::background}) FirstLoop({reader, stage, tag});
    }

protected:


    template<typename Class>
    bool TaggerIs() const {
        Info();
        return typeid(tagger_).hash_code() == typeid(Class).hash_code();
    }

private:

    void FirstLoop(First<Tagger> first) {
        Info();
        TFile export_file(tagger().ExportFileName(first.stage(), first.tag()).c_str(), "Recreate");
        ClearFiles();
        SetFiles(first.tag(), first.stage());
        for (auto & file : this->Files(first.tag())) SecondLoop( {first, file, export_file});
    }

    /**
     * @brief Analysis performed on each file
     *
     */
    void SecondLoop(Second<Tagger> second) {
        Info();
        BranchWriter<Tagger> branch_writer(second, tagger_);
        std::vector<std::thread> threads;
        for (auto core : Range(1)) threads.emplace_back(std::thread([&, core] {ThirdLoop({second, branch_writer, tagger_, core});}));
        for (auto & thread : threads) if (thread.joinable()) thread.join();
        branch_writer.Write();
    }

    void ThirdLoop(Third<Tagger> third) {
        Info();
        int object_sum = 0;
        while (object_sum < 1000 && third.entry_ < third.GetEntries()) {
            object_sum += FourthLoop(third);
            Error(third.entry_, object_sum);
        }
        third.branch_writer().set_object_sum(object_sum);
        Error("ended");
    }

    /**
     * @brief Checks for PreCuts and saves the results of each analysis.
     *
     */
    int FourthLoop(Third<Tagger>& third) const {
        Error();
        ++third.entry_;
        third.ReadEntry();
        Event event(third.clones_arrays(), third.second().file().source());
        if (!PassPreCut(event, third.second().first().tag())) return 0;
        return third.SaveEntry(Switch(event, third.second().first(), third.tagger()));
    }

    /**
     * @brief Starts the analysis on each Event
     *
     * @return int number of safed objects
     */
    int Switch(Event const& event, First<Tagger>& first, Tagger& tagger) const {
        Info();
        switch (first.stage()) {
        case Stage::trainer : return tagger.Train(event, pre_cuts(), first.tag());
        case Stage::reader : return first.reader().Bdt(event, pre_cuts());
        default : return 0;
        }
    }



    /**
     * @brief getter for Tagger
     *
     * @return boca::Tagger&
     */
    Tagger& tagger() final {
        Info();
        return tagger_;
    }

    /**
     * @brief getter for Tagger
     *
     * @return const boca::Tagger&
     */
    Tagger const& tagger() const final {
        Info();
        return tagger_;
    }

    /**
     * @brief Tagger template
     *
     */
    Tagger tagger_;

};

}









