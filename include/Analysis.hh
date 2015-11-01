/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include <typeinfo>
#include <mutex>
#include <thread>
// #define INFORMATION

#include "File.hh"
#include "Reader.hh"
#include "AnalysisBase.hh"
#include "Debug.hh"

namespace boca
{

class First
{
public:
    First(Stage stage, Tag tag) {
        Info0;
        stage_ = stage;
        tag_ = tag;
    }
    Stage stage() const {
        Info0;
        return stage_;
    }
    Tag tag() const {
        Info0;
        return tag_;
    }
private:
    Stage stage_;
    Tag tag_;
};

class Second
{
public:
    Second(First& first, File& file, TFile& export_file) :
        first_(first),
        export_file_(export_file),
        file_(file) {
        Info0;
    }
    First const& first() const {
        Info0;
        return first_;
    }
    File const& file() const {
        Info0;
        return file_;
    }
    TFile& export_file() {
        Info0;
        return export_file_;
    }
private:
    First& first_;
    File& file_;
    TFile& export_file_;
};

template<typename Tagger>
class BranchWriter
{

public:
    BranchWriter(Second& second, Tagger& tagger) :
        second_(second),
        tagger_(tagger),
        reader_(Reader<Tagger>(second.first().stage())),
        tree_writer_(exroot::TreeWriter(&(second.export_file()), second.file().Title().c_str())) {
        Info0;
        Initialize();
    }

    void Initialize() {
        Info0;
        tree_branch_ = tree_writer_.NewBranch(tagger_.WeightBranchName().c_str(), InfoBranch::Class());
        std::lock_guard<std::mutex> second_guard(second_mutex_);
        std::lock_guard<std::mutex> tree_writer_guard(tree_writer_mutex_);
        switch (second().first().stage()) {
        case Stage::trainer : tagger_.SetTreeBranch(tree_writer(), second().first().stage());
            break;
        case Stage::reader : reader_.SetTreeBranch(tree_writer(), second().first().stage());
            break;
        }
    }

    void Write() {
      Info0;
        std::lock_guard<std::mutex> object_sum_guard(object_sum_mutex_);
        std::lock_guard<std::mutex> tree_writer_guard(tree_writer_mutex_);
        if (object_sum()) tree_writer().Write();
    }

    Second& second()  {
        Info0;
        return second_;
    }

    exroot::TreeBranch& tree_branch() {
        Info0;
        return *tree_branch_;
    }

    exroot::TreeWriter& tree_writer() {
      Info0;
        return tree_writer_;
    }

    long& object_sum() {
        Info0;
        return object_sum_;
    }

    void Increment() {
        std::lock_guard<std::mutex> object_sum_guard(object_sum_mutex_);
        ++object_sum_;
    }

    void Increment(int number) {
        std::lock_guard<std::mutex> object_sum_guard(object_sum_mutex_);
        object_sum_ += number;
        Error(object_sum());
    }

    Reader<Tagger> reader() const {
        return reader_;
    }

    Tagger tagger() const {
        return tagger_;
    }

    std::mutex& tagger_mutex() {
        return tagger_mutex_;
    }

    std::mutex& reader_mutex() {
        return reader_mutex_;
    }

    std::mutex& branch_writer_mutex() {
        return branch_writer_mutex_;
    }

    std::mutex& second_mutex() {
        return second_mutex_;
    }

    std::mutex& object_sum_mutex() {
        return object_sum_mutex_;
    }
    std::mutex& tree_branch_mutex() {
        return tree_branch_mutex_;
    }

private:

    std::mutex branch_writer_mutex_;

    exroot::TreeBranch* tree_branch_;
    std::mutex tree_branch_mutex_;

    exroot::TreeWriter tree_writer_;
    std::mutex tree_writer_mutex_;

    long object_sum_ = 0;
    std::mutex object_sum_mutex_;

    Second& second_;
    std::mutex second_mutex_;

    Tagger& tagger_;
    std::mutex tagger_mutex_;

    Reader<Tagger> reader_;
    std::mutex reader_mutex_;

};

template<typename Tagger>
class Third
{
public:
    Third(BranchWriter<Tagger>& branch_writer, int core, int max) :
        branch_writer_(branch_writer),
        tagger_(branch_writer.tagger()),
        reader_(branch_writer.reader()) {
        Info0;
        event_number_ = core;
        max_= max;
    }

    void Initialize() {
      Info0;
        std::lock_guard<std::mutex> second_guard(branch_writer().second_mutex());
        tree_reader_ = second().file().TreeReader();
        std::lock_guard<std::mutex> clones_arrays_guard(clones_arrays_mutex_);
        clones_arrays_ = ClonesArrays(second().file().source());
        std::lock_guard<std::mutex> tree_reader_guard(tree_reader_mutex_);
        clones_arrays_.UseBranches(tree_reader().exroot());
        std::lock_guard<std::mutex> info_branch_guard(info_branch_mutex);
        info_branch_ = FillInfoBranch(second().file());
    }

    InfoBranch FillInfoBranch(boca::File const& file)  {
      Info0;
        InfoBranch info_branch;
        info_branch.Crosssection = file.crosssection() / fb;
        info_branch.CrosssectionError = file.crosssection_error() / fb;
        info_branch.Mass = file.mass() / GeV;
        info_branch.Name = file.nice_name();
        return info_branch;
    }

    Range range(long max) {
        return Range(FirstEntry(max), GetEntries());
    }

    long FirstEntry(long max)  {
        Info0;
        long entry = 0;
        std::lock_guard<std::mutex> second_guard(branch_writer().second_mutex());
        if (second().first().stage() == Stage::reader) entry = std::min(GetEntries(), max) / 2;  // TODO fix corner cases
        return entry;
    }

    long GetEntries() {
        Info0;
        std::lock_guard<std::mutex> tree_reader_guard(tree_reader_mutex_);
        return tree_reader().GetEntries();
    }

    bool SaveEntry(int object_number) {
        Info0;
        std::lock_guard<std::mutex> event_number_guard(event_number_mutex);
        std::lock_guard<std::mutex> info_branch_guard(info_branch_mutex);
        info_branch().EventNumber = event_number();
        std::lock_guard<std::mutex> tree_branch_guard(branch_writer().tree_branch_mutex());
        static_cast<InfoBranch&>(*branch_writer().tree_branch().NewEntry()) = info_branch();
        std::lock_guard<std::mutex> branch_writer_guard(branch_writer().branch_writer_mutex());
        branch_writer().tree_writer().Fill();
        branch_writer().tree_writer().Clear();
        return object_number;
    }

    void ReadEntry() {
        Info0;
        std::lock_guard<std::mutex> event_number_guard(event_number_mutex);
        std::lock_guard<std::mutex> tree_reader_guard(tree_reader_mutex_);
        Error(event_number());
        event_number() += max_;
        tree_reader().ReadEntry(event_number());
    }

    ClonesArrays const& clones_arrays()  {
        Info0;
        return clones_arrays_;
    }

    TreeReader& tree_reader() {
        Info0;
        return tree_reader_;
    }


    InfoBranch& info_branch() {
        Info0;
        return info_branch_;
    }

    long& event_number() {
        Info0;
        return event_number_;
    }

    Tagger& tagger() {
        Info0;
        return tagger_;
    }

    Second& second()  {
        Info0;
        return branch_writer().second();
    }

    BranchWriter<Tagger>& branch_writer() {
        Info0;
        return branch_writer_;
    }

    Reader<Tagger>& reader() {
        Info0;
        return reader_;
    }

private:

//     int core_;

    int max_;

    BranchWriter<Tagger>& branch_writer_;

    Tagger tagger_;

    ClonesArrays clones_arrays_;
    std::mutex clones_arrays_mutex_;

    TreeReader tree_reader_;
    std::mutex tree_reader_mutex_;

    InfoBranch info_branch_;
    std::mutex info_branch_mutex;

    long event_number_ = 0;
    std::mutex event_number_mutex;

    Reader<Tagger> reader_;
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
        Info0;
        for (auto const & tag : std::vector<Tag> {Tag::signal, Tag::background}) FirstLoop({stage, tag});
    }

protected:

    template<typename Class>
    bool TaggerIs() const {
        Info0;
        return typeid(tagger_).hash_code() == typeid(Class).hash_code();
    }

private:

    void FirstLoop(First first) {
        Info0;
        TFile export_file(tagger().ExportFileName(first.stage(), first.tag()).c_str(), "Recreate");
        ClearFiles();
        SetFiles(first.tag(), first.stage());
        for (auto & file : this->Files(first.tag())) SecondLoop( {first, file, export_file});
    }

    /**
     * @brief Analysis performed on each file
     *
     */
    void SecondLoop(Second second) {
        Info0;
        BranchWriter<Tagger> branch_writer(second, tagger_);
        std::vector<std::thread> threads;
        int max = 2;
        for (auto core : Range(2)) threads.emplace_back(std::thread([&, core] {ThirdLoop({branch_writer, core, max});}));
        for (auto & thread : threads) if (thread.joinable()) thread.join();
        branch_writer.Write();
    }

    void ThirdLoop(Third<Tagger> third) {
        Info0;
        third.Initialize();
        while (third.branch_writer().object_sum() < 100 && third.event_number() < third.GetEntries()) third.branch_writer().Increment(FourthLoop(third));
    }

    /**
     * @brief Checks for PreCuts and saves the results of each analysis.
     *
     */
    int FourthLoop(Third<Tagger>& third) const {
      Info0;
        third.ReadEntry();
        Event event(third.clones_arrays(), third.second().file().source());
        if (!PassPreCut(event, third.second().first().tag())) return 0;
        return third.SaveEntry(Switch(event, third));
    }

    /**
     * @brief Starts the analysis on each Event
     *
     * @return int number of safed objects
     */
    int Switch(Event const& event, Third<Tagger>& third) const {
        Info0;
        std::lock_guard<std::mutex> tree_branch_guard(third.branch_writer().tree_branch_mutex());
        std::lock_guard<std::mutex> branch_writer_guard(third.branch_writer().branch_writer_mutex());
        switch (third.second().first().stage()) {
        case Stage::trainer :
            std::lock_guard<std::mutex> tagger_guard(third.branch_writer().tagger_mutex());
            return third.tagger().Train(event, pre_cuts(), third.second().first().tag());
        case Stage::reader :
            std::lock_guard<std::mutex> reader_guard(third.branch_writer().reader_mutex());
            return third.reader().Bdt(event, pre_cuts());
        default : return 0;
        }
    }

    /**
     * @brief getter for Tagger
     *
     * @return boca::Tagger&
     */
    Tagger& tagger() final {
        Info0;
        return tagger_;
    }

    /**
     * @brief getter for Tagger
     *
     * @return const boca::Tagger&
     */
    Tagger const& tagger() const final {
        Info0;
        return tagger_;
    }

    /**
     * @brief Tagger template
     *
     */
    Tagger tagger_;

};

}









