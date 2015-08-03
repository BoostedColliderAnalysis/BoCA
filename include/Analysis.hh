/**
 * Copyright (C) 2015 Jan Hajer <jan@hajer.com>
 */
#pragma once

#include "AnalysisBase.hh"
#include "Reader.hh"
#include "Branches.hh"
#include "Trees.hh"

namespace analysis {

/**
 * @brief Analysis provides main analysis loops and logic.
 * @details This class has to be subclassed for each analysis.
 * The subclasses have to be instantiated with a Tagger as template argument.
 * Subclasses should be templated classes.
 * @author Jan Hajer
 * @copyright Copyright (C) 2015 Jan Hajer <jan@hajer.com>
 * @date 2015
 * @license GPL 3+
 *
 */
template<typename Tagger>
class Analysis : public AnalysisBase {

public:

  /**
   * @brief Main analysis loop which has to be called by main.cpp
   *
   */
  void AnalysisLoop(Stage stage) final {
        Initialize();
        Reader<Tagger> reader(stage);
        for (const auto& tag : std::vector<Tag> {Tag::signal, Tag::background})
        {
            Files files(tagger().ExportFileName(stage, tag), stage, tag);
            ClearFiles();
            SetFiles(tag);
            for (auto& file : this->files(tag)) {
                files.set_file(file);
                AnalyseFile(files, reader);
            }
            files.export_file().Close();
        }
    }

protected:

  /**
   * @brief getter for Tagger
   *
   * @return const analysis::Tagger&
   */
  const Tagger &tagger() const final { return tagger_; }

    /**
     * @brief setter for AnalysisName of Tagger
     * @details must be set in each analysis in order for Tagger to know about the folder structure
     *
     */
    void set_tagger_analysis_name(const std::string& name){
      tagger().SetAnalysisName(name);
    }

    /**
     * @brief getter for Tagger
     *
     * @return analysis::Tagger&
     */
    Tagger &tagger() final { return tagger_; }

private:

  /**
   * @brief Analysis performed on each file
   *
   */
  void AnalyseFile(Files& files, Reader<Tagger>& reader)
    {
        Trees trees(files);
        SetTreeBranch(files.stage(), trees.tree_writer(), reader);
        trees.UseBranches(files.file(), tagger().WeightBranchName());
        if (files.stage() == Stage::reader) {
            trees.entry = std::min(long(trees.tree_reader().GetEntries()), EventNumberMax()) / 2;    // TODO fix corner cases
        }
        for (; trees.entry < trees.tree_reader().GetEntries(); ++trees.entry) {
            ++trees.event_number_;
            DoAnalysis(files, trees, reader);
            if (trees.object_sum() >= EventNumberMax()) break;
        }
        trees.WriteTree();
    }

    /**
     * @brief Set exroot::TreeBranch of exroot::TreeWriter to the pointer in the right Tagger
     *
     */
    void SetTreeBranch(Stage stage, exroot::TreeWriter& tree_writer, Reader<Tagger>& reader)
    {
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
    void DoAnalysis(const Files& files, Trees& trees, const Reader<Tagger>& reader) const
    {
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
    int RunAnalysis(const Event& event, const Reader<Tagger>& reader, Stage stage, Tag tag) const
    {
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
