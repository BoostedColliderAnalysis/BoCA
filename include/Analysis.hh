/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include <typeinfo>

#include "File.hh"
#include "Reader.hh"
#include "AnalysisBase.hh"
// #define DEBUG
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
    Stage stage() const {
        return stage_;
    }
    Tag tag() const {
        return tag_;
    }
    Reader<Tagger>& reader() {
        return reader_;
    }
    Reader<Tagger> const& reader() const {
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
    First<Tagger>& first() {
        return first_;
    }
    File& file() {
        return file_;
    }
    TFile& export_file() {
        return export_file_;
    }
private:
    First<Tagger>& first_;
    File& file_;
    TFile& export_file_;
};

template<typename Tagger>
class Third
{
public:

    Third(
        Second<Tagger>& second,
        exroot::TreeWriter& tree_writer,
        ClonesArrays& clons_arrays,
        exroot::TreeBranch& tree_branch,
        exroot::TreeReader& tree_reader,
        InfoBranch& info_branch,
        long entry,
        long& object_sum,
        long& event_number
    ) :
        second_(second),
        tree_writer_(tree_writer),
        clones_arrays_(clons_arrays),
        tree_reader_(tree_reader),
        tree_branch_(tree_branch) ,
        info_branch_(info_branch),
        object_sum_(object_sum),
        event_number_(event_number) {
        Info();
        entry_ = entry;
    }

    void ReadEntry() {
        ++event_number_;
        Debug(entry_, event_number_);
        tree_reader_.ReadEntry(entry_);
    }

    void SaveEntry(int object_number) {
        object_sum_ += object_number;
        info_branch_.EventNumber = event_number_;
        static_cast<InfoBranch&>(*tree_branch_.NewEntry()) = info_branch_;
        tree_writer_.Fill();
        tree_writer_.Clear();
    }

    bool is_larger(long max) {
        return object_sum_ >= max;
    }
    Second<Tagger>& second() {
        return second_;
    }
    ClonesArrays& clones_arrays() {
        return clones_arrays_;
    }
private:
    long entry_;
    long& event_number_;
    ClonesArrays& clones_arrays_;
    Second<Tagger>& second_;
    exroot::TreeReader& tree_reader_;
    exroot::TreeBranch& tree_branch_;
    exroot::TreeWriter& tree_writer_;
    InfoBranch& info_branch_;
    long& object_sum_;
private:
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
        return typeid(tagger_).hash_code() == typeid(Class).hash_code();
        Info();
    }

private:

    void FirstLoop(First<Tagger> first) {
        TFile export_file(tagger().ExportFileName(first.stage(), first.tag()).c_str(), "Recreate");
        ClearFiles();
        SetFiles(first.tag(), first.stage());
        for (auto & file : this->files(first.tag())) SecondLoop(Second<Tagger>(first, file, export_file));
    }

    /**
     * @brief Analysis performed on each file
     *
     */
    void SecondLoop(Second<Tagger> second) {
        Info();
        exroot::TreeWriter tree_writer(&(second.export_file()), second.file().Title().c_str());
        SetTreeBranch(second.first(), tree_writer);
        ClonesArrays clones_arrays(second.file().source());
        exroot::TreeBranch& weight_branch = *tree_writer.NewBranch(tagger().WeightBranchName().c_str(), InfoBranch::Class());
        exroot::TreeReader tree_reader = second.file().TreeReader();
        clones_arrays.UseBranches(tree_reader);
        InfoBranch info_branch = FillInfoBranch(second.file());
        long object_sum = 0;
        long event_number_ = 0;
        for (auto entry : Range(FirstEntry(tree_reader, second.first().stage()), tree_reader.GetEntries())) if (ThirdLoop(Third<Tagger>(second, tree_writer, clones_arrays, weight_branch, tree_reader, info_branch, entry, object_sum, event_number_))) break;
        if (object_sum) tree_writer.Write();
    }

    long FirstEntry(exroot::TreeReader& tree_reader, Stage stage) {
        long entry = 0;
        if (stage == Stage::reader) entry = std::min(long(tree_reader.GetEntries()), EventNumberMax()) / 2;  // TODO fix corner cases
        return entry;
    }

    /**
     * @brief Set exroot::TreeBranch of exroot::TreeWriter to the pointer in the right Tagger
     *
     */
    void SetTreeBranch(First<Tagger>& first, exroot::TreeWriter& tree_writer) {
        Info();
        switch (first.stage()) {
        case Stage::trainer : tagger().SetTreeBranch(tree_writer, first.stage());
            break;
        case Stage::reader : first.reader().SetTreeBranch(tree_writer, first.stage());
            break;
        }
    }

    /**
     * @brief Checks for PreCuts and saves the results of each analysis.
     *
     */
    bool ThirdLoop(Third<Tagger> third) const {
        Info();
        third.ReadEntry();
        Event event(third.clones_arrays(), third.second().file().source());
        event.SetMass(third.second().file().mass());
        if (!PassPreCut(event, third.second().first().tag())) return false;
        int object_number = Switch(event, third.second().first());
        if (object_number == 0) return false;
        third.SaveEntry(object_number);
        if (third.is_larger(EventNumberMax())) return true;
        else return false;
    }

    /**
     * @brief Starts the analysis on each Event
     *
     * @return int number of safed objects
     */
    int Switch(Event const& event, First<Tagger>& first) const {
        Info();
        switch (first.stage()) {
        case Stage::trainer : return tagger_.Train(event, pre_cuts(), first.tag());
        case Stage::reader : return first.reader().Bdt(event, pre_cuts());
        default : return 0;
        }
    }


    InfoBranch FillInfoBranch(const boca::File& file) {
        Info();
        InfoBranch info_branch;
        info_branch.Crosssection = file.crosssection() / fb;
        info_branch.CrosssectionError = file.crosssection_error() / fb;
        info_branch.Mass = file.mass() / GeV;
        info_branch.Name = file.nice_name();
        return info_branch;
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





