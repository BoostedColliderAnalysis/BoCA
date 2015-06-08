# include "Analysis.hh"

# include <sys/stat.h>

# include "TTree.h"

# include "exroot/ExRootAnalysis.hh"

# include "Branches.hh"
# include "Event.hh"

// analysis::HAnalysis::HAnalysis(const std::string &ConfigName) : config_(ConfigName)
analysis::Analysis::Analysis(analysis::Tagger &tagger) : tagger_(tagger)
{
    Print(kNotification, "Constructor");
    event_sum_ = 0;
}

void analysis::Analysis::AnalysisLoop(const Tagger::Stage stage)
{
    Print(kNotification, "Analysis Loop");
    mkdir(ProjectName().c_str(), 0700);
    if (stage == Tagger::kReader) reader_.set_tagger(tagger_);
        tagger_.clear_tree_names();
    for (const auto & tag : std::vector<Tag> {kSignal, kBackground}) {
        Print(kNotification, "Analysing Mva Sample", tag);
        TFile export_file(ExportName(stage, tag).c_str(), "Recreate");
        files_.clear();
        SetFiles(tag);
        for (auto & file : Files(tag)) {
            Print(kNotification, "Analysing File", file.tree_name());
            event_sum_ = 0;
            ClonesArrays clones_arrays = file.clones_arrays();
            analysis::Event event = file.event();
            bool analysis_not_empty = false;
            exroot::TreeWriter tree_writer = TreeWriter(export_file, file.Title(), stage);
            exroot::TreeBranch &tree_branch = *tree_writer.NewBranch("Info", InfoBranch::Class());
            exroot::TreeReader tree_reader = file.TreeReader();
            clones_arrays.UseBranches(tree_reader);
//             exroot:ProgressBar progress_bar(eventSum(tree_reader));
//             Print(kInformation, "Sum", eventSum(tree_reader));
            int object_sum = 0;
            int pre_cut_sum = 0;
            InfoBranch info_branch = FillInfoBranch(tree_reader, file);
            for (const int event_number : Range(eventSum(tree_reader))) {
//                 Print(kError, "event Number", event_number);
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
                        analysis_not_empty = true;
                        static_cast<InfoBranch &>(*tree_branch.NewEntry()) = info_branch;
                        tree_writer.Fill();
                    }
                }
                tree_writer.Clear();
                if (object_sum >= EventNumberMax()) break;
//                 progress_bar.Update(event_number);
            }
            Print(kError, "All events analysed", info_branch.EventNumber);
//             progress_bar.Finish();
            if (analysis_not_empty) tree_writer.Write();
//             Print(kError, "Number of events", event_sum_, eventSum(tree_reader));
        }
        export_file.Close();
    }
}

analysis::InfoBranch analysis::Analysis::FillInfoBranch(const exroot::TreeReader &tree_reader, const File &file)
{
    InfoBranch info_branch;
    info_branch.Crosssection = file.crosssection();
    info_branch.CrosssectionError = file.crosssection_error();
    info_branch.Mass = file.mass();
    info_branch.EventNumber = eventSum(tree_reader);
    return info_branch;
}

std::string analysis::Analysis::ExportName(const Tagger::Stage stage, const Tag tag) const
{
    Print(kNotification, "Export File", tagger_.tagger_name(), tag);
    return ProjectName() + "/" + tagger_.name(stage, tag) + ".root";
}

exroot::TreeWriter analysis::Analysis::TreeWriter(TFile &export_file, const std::string &export_tree_name, analysis::Tagger::Stage stage)
{
    Print(kNotification, "Tree Writer", export_tree_name.c_str());
    exroot::TreeWriter tree_writer(&export_file, export_tree_name.c_str());
    tagger_.SetTreeBranch(tree_writer, stage);
    return tree_writer;
}

int analysis::Analysis::RunAnalysis(analysis::Event &event, const analysis::Tagger::Stage stage, const Tag tag)
{
  Print(kInformation, "Analysis");
  switch (stage) {
    case analysis::Tagger::kTrainer :
      return tagger_.Train(event, pre_cuts_, tag);
    case analysis::Tagger::kReader :
      return reader_.GetBdt(event, pre_cuts_);
    default :
      return 0;
  }
}

