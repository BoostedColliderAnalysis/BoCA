# include "Analysis.hh"

# include <sys/stat.h>

# include "TTree.h"

# include "exroot/ExRootAnalysis.hh"

# include "Branches.hh"
# include "Event.hh"

namespace analysis
{

// HAnalysis::HAnalysis(const std::string &ConfigName) : config_(ConfigName)
Analysis::Analysis(Tagger &tagger) : tagger_(tagger)
{
//   debug_level_ = Severity::debug;
    Print(Severity::notification, "Constructor");
}

void Analysis::AnalysisLoop(const Tagger::Stage stage)
{
    Print(Severity::notification, "Analysis Loop");
    mkdir(ProjectName().c_str(), 0700);
    if (stage == Tagger::kReader) reader_.SetTagger(tagger_);
    tagger_.clear_tree_names();
    for (const auto & tag : std::vector<Tag> {Tag::signal, Tag::background}) {
        Print(Severity::notification, "Analysing Mva Sample", Name(tag));
        TFile export_file(ExportName(stage, tag).c_str(), "Recreate");
        files_.clear();
        SetFiles(tag);
        for (auto & file : Files(tag)) {
            Print(Severity::notification, "Analysing File", file.tree_name());
            ClonesArrays clones_arrays = file.clones_arrays();
            Event event = file.event();
            bool analysis_empty = true;
            exroot::TreeWriter tree_writer = TreeWriter(export_file, file.Title(), stage);
            exroot::TreeBranch &tree_branch = *tree_writer.NewBranch(tagger_.weight_branch_name().c_str(), InfoBranch::Class());
            exroot::TreeReader tree_reader = file.TreeReader();
            clones_arrays.UseBranches(tree_reader);
            //             exroot:ProgressBar progress_bar(std::min((int)tree_reader.GetEntries(), EventNumberMax());
            int object_sum = 0;
            int pre_cut_sum = 0;
            InfoBranch info_branch = FillInfoBranch(tree_reader, file);
            for (const int event_number : Range(tree_reader.GetEntries())) {
                tree_reader.ReadEntry(event_number);
                event.NewEvent(clones_arrays);
                event.SetMass(file.mass());
                int pre_cut_number = PassPreCut(event);
                if (pre_cut_number > 0) {
                    pre_cut_sum += pre_cut_number;
                    int object_number = RunAnalysis(event, stage, tag);
                    if (object_number > 0) {
                        object_sum += object_number;
                        info_branch.PreCutNumber = event_number;
                        analysis_empty = false;
//                         static_cast<InfoBranch &>(*tree_branch.NewEntry()) = info_branch;
                        dynamic_cast<InfoBranch &>(*tree_branch.NewEntry()) = info_branch;
                        tree_writer.Fill();
                    }
                }
                tree_writer.Clear();
                if (object_sum >= EventNumberMax()) break;
//                 progress_bar.Update(event_number);
            }
            Print(Severity::error, "All events analysed", info_branch.EventNumber);
//             progress_bar.Finish();
            if (!analysis_empty) tree_writer.Write();
        }
        export_file.Close();
    }
}

InfoBranch Analysis::FillInfoBranch(const exroot::TreeReader &tree_reader, const File &file)
{
    InfoBranch info_branch;
    info_branch.Crosssection = file.crosssection();
    info_branch.CrosssectionError = file.crosssection_error();
    info_branch.Mass = file.mass();
    info_branch.EventNumber = std::min((int)tree_reader.GetEntries(), EventNumberMax());
    info_branch.Name = file.nice_name();
    return info_branch;
}

std::string Analysis::ExportName(const Tagger::Stage stage, const Tag tag) const
{
    Print(Severity::notification, "Export File", tagger_.name(stage, tag));
    return ProjectName() + "/" + tagger_.name(stage, tag) + FileSuffix();
}

exroot::TreeWriter Analysis::TreeWriter(TFile &export_file, const std::string &export_tree_name, Tagger::Stage stage)
{
    Print(Severity::notification, "Tree Writer", export_tree_name.c_str());
    exroot::TreeWriter tree_writer(&export_file, export_tree_name.c_str());
    tagger_.SetTreeBranch(tree_writer, stage);
    return tree_writer;
}

int Analysis::RunAnalysis(Event &event, const Tagger::Stage stage, const Tag tag)
{
    Print(Severity::information, "Analysis");
    switch (stage) {
    case Tagger::kTrainer :
        return tagger_.Train(event, pre_cuts_, tag);
    case Tagger::kReader :
        return reader_.GetBdt(event, pre_cuts_);
    default :
        return 0;
    }
}

}
