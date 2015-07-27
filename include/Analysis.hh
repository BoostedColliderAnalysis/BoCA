#pragma once

#include <sys/stat.h>
#include "AnalysisBase.hh"
#include "Reader.hh"
#include "Branches.hh"
#include "Trees.hh"
#include "Debug.hh"

namespace analysis {

/**
 * @brief Base for analyses
 *
 */
template<typename Tagger>
class Analysis : public AnalysisBase {

public:

    void AnalysisLoop(Stage stage) final {
        mkdir(ProjectName().c_str(), 0700);
        Reader<Tagger> reader(stage);
        tagger().ClearTreeNames();
        for (const auto& tag : std::vector<Tag> {Tag::signal, Tag::background})
        {
            Files files(tagger().ExportFileName(stage, tag), stage, tag);
            ClearFiles();
            SetFiles(tag);
            for (auto& file : this->files(tag)) {
                files.file(file);
                AnalyseFile(files, reader);
            }
            files.export_file().Close();
        }
    }


protected:

    const Tagger& tagger() const final {
        return tagger_;
    }

    void set_tagger_analysis_name(const std::string& name){
      tagger().SetAnalysisName(name);
    }

    Tagger& tagger() final {
        return tagger_;
    }

private:

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
        if(trees.event_number_ == trees.tree_reader().GetEntries()) Error("All Events used",trees.event_number_);
        trees.WriteTree();
    }

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

    void DoAnalysis(const Files& files, Trees& trees, const Reader<Tagger>& reader)
    {
        trees.NewEvent(files.file().mass());
        int pre_cut = PassPreCut(trees.event(), files.tag());
        if (pre_cut > 0) trees.SaveAnalysis(RunAnalysis(trees.event(), reader, files.stage(), files.tag()));
        trees.tree_writer().Clear();
    }

    int RunAnalysis(const Event& event, const Reader<Tagger>& reader, Stage stage, Tag tag)
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

    Tagger tagger_;

};

}
