/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include <typeinfo>
#include <mutex>
#include <thread>

#include "exroot/ExRootAnalysis.hh"
#include "File.hh"
#include "Reader.hh"
#include "AnalysisBase.hh"

// #define INFORMATION
#include "Debug.hh"
// #define Info0
// #define Error(...)
// #define INFO(...)

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
    Second(First& first, File& file, TFile& export_file)
        : first_(first)
        , file_(file)
        , export_file_(export_file) {
        Info0;
    }
    First first() const {
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
    First first_;
    File& file_;
    TFile& export_file_;
};

template<typename Tagger>
class BranchWriter
{

public:
    BranchWriter(Second& second, Tagger& tagger)
        : second_(second)
        , tagger_(tagger)
        , reader_(second.first().stage())
        , tree_writer_(&(second.export_file()), second.file().Title().c_str()) {
        Info0;
        Initialize();
    }

    void Initialize() {
        Info0;
        switch (second().first().stage()) {
        case Stage::trainer : tagger_.NewBranch(tree_writer(), second().first().stage());
            break;
        case Stage::reader : reader_.NewBranch(tree_writer(), second().first().stage());
            break;
        }
        tree_branch_ = tree_writer_.NewBranch(tagger_.WeightBranchName().c_str(), InfoBranch::Class());
        for (auto const & path : second().file().Paths()) chain_.AddFile(path.c_str(), TChain::kBigNumber, second().file().tree_name().c_str());
    }

    void Write() {
        Info0;
        std::lock_guard<std::mutex> object_sum_guard(object_sum_mutex_);
        if (object_sum_) tree_writer().Write();
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

    long object_sum() {
        Info0;
        std::lock_guard<std::mutex> object_sum_guard(object_sum_mutex_);
        return object_sum_;
    }

    long event_sum() {
        Info0;
        std::lock_guard<std::mutex> event_sum_guard(event_sum_mutex_);
        return event_sum_;
    }

    void Increment() {
        std::lock_guard<std::mutex> object_sum_guard(object_sum_mutex_);
        ++object_sum_;
    }

    void Increment(int number) {
        std::lock_guard<std::mutex> object_sum_guard(object_sum_mutex_);
        object_sum_ += number;
        std::lock_guard<std::mutex> event_sum_guard(event_sum_mutex_);
        ++event_sum_;
    }

    bool KeepGoing(long max) {
        std::lock_guard<std::mutex> object_sum_guard(object_sum_mutex_);
        return object_sum_ < max;
    }

    Reader<Tagger> reader() const {
        return reader_;
    }

    Tagger tagger() const {
        return tagger_;
    }

    TChain& chain() {
        return chain_;
    }

private:

    TChain chain_;

    Second& second_;

    Tagger& tagger_;

    Reader<Tagger> reader_;

    exroot::TreeWriter tree_writer_;

    exroot::TreeBranch* tree_branch_;

    long object_sum_ = 0;
    std::mutex object_sum_mutex_;

    long event_sum_ = 0;
    std::mutex event_sum_mutex_;

};

template<typename Tagger>
class Third
{
public:
    Third(BranchWriter<Tagger>& branch_writer, int core_number, int core_sum, int object_sum_max)
        : branch_writer_(branch_writer)
        , reader_(branch_writer.reader())
        , tagger_(branch_writer.tagger())
//         , tree_reader_(branch_writer.chain())
        , tree_reader_(second().file().Paths(), second().file().tree_name())
        {
        Info0;
        event_number_ = FirstEntry(object_sum_max, core_number);
        max_ = core_sum;
        info_branch_ = FillInfoBranch(second().file());
    }

//     void Initialize() {
//         Info0;
//         tree_reader().Initialize();
//     }

    InfoBranch FillInfoBranch(boca::File const& file)  {
        Info0;
        InfoBranch info_branch;
        info_branch.Crosssection = file.crosssection() / fb;
        info_branch.CrosssectionError = file.crosssection_error() / fb;
        info_branch.Mass = file.mass() / GeV;
        info_branch.Name = file.nice_name();
        return info_branch;
    }

//     Range range(long max) {
//         return Range(FirstEntry(max), GetEntries());
//     }
//
    long FirstEntry(long object_sum_max, int core_number)  {
        Info0;
        long entry = core_number;
        if (second().first().stage() == Stage::reader) entry = std::min(GetEntries(), object_sum_max + core_number);  // TODO fix corner cases
        return entry;
    }

    long GetEntries() {
        return tree_reader().GetEntries();
    }

    void PreCutPassed(){}

    void SaveEntry() {
        info_branch().EventNumber = branch_writer().event_sum();
        std::lock_guard<std::mutex> tagger_guard(tagger_.mutex_);
        static_cast<InfoBranch&>(*branch_writer().tree_branch().NewEntry()) = info_branch();
        branch_writer().tree_writer().Fill();
        branch_writer().tree_writer().Clear();
    }

    bool ReadEntry() {
        INFO(event_number());
        return tree_reader().ReadEntry(event_number());
    }

    void Increment() {
        event_number() += max_;
    }

    bool KeepGoing() {
        return event_number() < GetEntries();
    }

    TreeReader& tree_reader() {
        return tree_reader_;
    }

    InfoBranch& info_branch() {
        return info_branch_;
    }

    long& event_number() {
        return event_number_;
    }

    Tagger& tagger() {
        return tagger_;
    }

    Second& second()  {
        return branch_writer().second();
    }

    BranchWriter<Tagger>& branch_writer() {
        return branch_writer_;
    }

    Reader<Tagger>& reader() {
        return reader_;
    }

private:

    BranchWriter<Tagger>& branch_writer_;

    Reader<Tagger> reader_;

    Tagger tagger_;

    TreeReader tree_reader_;

    InfoBranch info_branch_;

    long event_number_;

    int max_;
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
        bool do_threading = false;
        if (do_threading) {
            std::mutex branch_writer_mutex;
            std::vector<std::thread> threads;
//         int cores = std::thread::hardware_concurrency(); // breaks in the tree reader, find  a cheap way to store the position of the data
            int cores = 1;
            for (auto core : Range(cores)) {
                threads.emplace_back(std::thread([&, core, cores] {
                    branch_writer_mutex.lock();
                    Third<Tagger> third(branch_writer, core, cores, EventNumberMax());
                    branch_writer_mutex.unlock();
                    ThirdLoop(third);
                }));
            }
            for (auto & thread : threads) thread.join();
        } else {
            int cores = 1;
            int core = 0;
            Third<Tagger> third(branch_writer, core, cores, EventNumberMax());
            ThirdLoop(third);
        }
        branch_writer.Write();
    }

    void ThirdLoop(Third<Tagger>& third) {
        Info0;
        while (third.branch_writer().KeepGoing(EventNumberMax()) && third.KeepGoing()) {
          int number = FourthLoop(third);
          third.Increment();
          third.branch_writer().Increment(number);
        }
    }

    int FourthLoop(Third<Tagger>& third) const {
        Info0;
        if (!third.ReadEntry()) return 0;
        Event event(third.tree_reader(), third.second().file().source());
        if (!PassPreCut(event, third.second().first().tag())) return 0;
        int number = Switch(event, third);
        third.SaveEntry();
        return number;
    }

    int Switch(Event const& event, Third<Tagger>& third) const {
        Info0;
        switch (third.second().first().stage()) {
        case Stage::trainer : return third.tagger().Train(event, pre_cuts(), third.second().first().tag());
        case Stage::reader : return third.reader().Bdt(event, pre_cuts());
        default : return 0;
        }
    }

    Tagger& tagger() final {
        return tagger_;
    }

    Tagger const& tagger() const final {
        return tagger_;
    }

    Tagger tagger_;

};

}
