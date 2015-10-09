/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include <typeinfo>

#include "AnalysisBase.hh"
#include "Reader.hh"
#include "Trees.hh"
#include "File.hh"
// #define DEBUG
#include "Debug.hh"

namespace boca
{

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

    Analysis() {
        Info();
    }

    /**
     * @brief Main analysis loop which has to be called by main.cpp
     *
     */
    void AnalysisLoop(Stage stage) final {
        Info();
        tagger().Initialize();
        Initialize();
        Reader<Tagger> reader(stage);
        for (auto const & tag : std::vector<Tag> {Tag::signal, Tag::background}) {
            Files files(tagger().ExportFileName(stage, tag), stage, tag);
            ClearFiles();
            SetFiles(tag);
            for (auto & file : this->files(tag)) {
                Info("in file loop");
                files.set_file(file);
                AnalyseFile(files, reader);
                Info("file analysed");
            }
            Info("file loop finished");
        }
        Info("tag loop finished");
    }

protected:

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
     * @brief setter for AnalysisName of Tagger
     * @details must be set in each analysis in order for Tagger to know about the folder structure
     *
     */
    void set_tagger_analysis_name(std::string const& name) {
        Info();
        tagger().SetAnalysisName(name);
    }

    template<typename Class>
    bool TaggerIs() const {
        Info();
        return typeid(tagger_).hash_code() == typeid(Class).hash_code();
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

private:

    /**
     * @brief Analysis performed on each file
     *
     */
    void AnalyseFile(Files& files, Reader<Tagger>& reader) {
        Info();
        Trees trees(files);
        SetTreeBranch(files.stage(), trees.tree_writer(), reader);
        trees.UseBranches(files.file(), tagger().WeightBranchName());
        if (files.stage() == Stage::reader) {
            trees.entry = std::min(long(trees.tree_reader().GetEntries()), EventNumberMax()) / 2;    // TODO fix corner cases
        }
//         exroot::ProgressBar progress_bar(std::min(long(trees.tree_reader().GetEntries()), EventNumberMax()));
        for (; trees.entry < trees.tree_reader().GetEntries(); ++trees.entry) {
            ++trees.event_number_;
            DoAnalysis(files, trees, reader);
//             progress_bar.Update(trees.object_sum());
            if (trees.object_sum() >= EventNumberMax()) break;
        }
//         progress_bar.Finish();
        trees.WriteTree();
        Info("tree written");
    }

    /**
     * @brief Set exroot::TreeBranch of exroot::TreeWriter to the pointer in the right Tagger
     *
     */
    void SetTreeBranch(Stage stage, exroot::TreeWriter& tree_writer, Reader<Tagger>& reader) {
        Info();
        switch (stage) {
        case Stage::trainer :
            tagger().SetTreeBranch(tree_writer, stage);
            break;
        case Stage::reader :
            reader.SetTreeBranch(tree_writer, stage);
            break;
        }
    }

    /**
     * @brief Checks for PreCuts and saves the results of each analysis.
     *
     */
    void DoAnalysis(Files const& files, Trees& trees, Reader<Tagger> const& reader) const {
        Info();
        trees.NewEvent(files.file().mass());
        int pre_cut = PassPreCut(trees.event(), files.tag());
        if (pre_cut > 0) {
            ++trees.pre_cut_number_;
            trees.SaveAnalysis(RunAnalysis(trees.event(), reader, files.stage(), files.tag()));
        }
        trees.tree_writer().Clear();
    }

    /**
     * @brief Starts the analysis on each Event
     *
     * @return int number of safed objects
     */
    int RunAnalysis(Event const& event, Reader<Tagger> const& reader, Stage stage, Tag tag) const {
        Info();
        switch (stage) {
        case Stage::trainer :
            return tagger_.Train(event, pre_cuts(), tag);
        case Stage::reader :
            return reader.Bdt(event, pre_cuts());
        default :
            return 0;
        }
    }

    /**
     * @brief Tagger template
     *
     */
    Tagger tagger_;

};

}
