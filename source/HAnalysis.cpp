# include "HAnalysis.hh"

# include <sys/stat.h>

# include "TTree.h"

# include "ExRootAnalysis/ExRootTreeWriter.h"
# include "ExRootAnalysis/ExRootTreeBranch.h"
# include "ExRootAnalysis/ExRootProgressBar.h"

# include "Branch.hh"
# include "Event.hh"

// hanalysis::HAnalysis::HAnalysis(const std::string &ConfigName) : config_(ConfigName)
hanalysis::HAnalysis::HAnalysis(hanalysis::Tagger &tagger) : tagger_(tagger)
{
    Print(kNotification, "Constructor");
    event_sum_ = 0;
}

void hanalysis::HAnalysis::AnalysisLoop(const Tagger::Stage stage)
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
            hanalysis::Event &event = file.event();
            bool analysis_not_empty = false;
            ExRootTreeWriter tree_writer = TreeWriter(export_file, file.Title(), stage);
            ExRootTreeBranch &tree_branch = *tree_writer.NewBranch("Info", InfoBranch::Class());
            ExRootTreeReader tree_reader = file.TreeReader();
            clones_arrays.UseBranches(tree_reader);
//             ExRootProgressBar progress_bar(eventSum(tree_reader));
//             Print(kInformation, "Sum", eventSum(tree_reader));
            int object_sum = 0;
            int pre_cut_sum = 0;
            InfoBranch info_branch = FillInfoBranch(tree_reader, file);
            for (const int event_number : Range(eventSum(tree_reader))) {
//                 Print(kError, "event Number", event_number);
                tree_reader.ReadEntry(event_number);
                event.Newevent(clones_arrays);
                event.SetMass(file.mass());
                int pre_cut_number = PassPreCut(event);
                if (pre_cut_number > 0) {
                    pre_cut_sum += pre_cut_number;
                    int object_number = Analysis(event, stage, tag);
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

InfoBranch hanalysis::HAnalysis::FillInfoBranch(const ExRootTreeReader &tree_reader, const File &file)
{
    InfoBranch info_branch;
    info_branch.Crosssection = file.crosssection();
    info_branch.CrosssectionError = file.crosssection_error();
    info_branch.Mass = file.mass();
    info_branch.EventNumber = eventSum(tree_reader);
//     Print(kError, "event Number", info_branch.eventNumber);
    return info_branch;
}

std::string hanalysis::HAnalysis::ExportName(const Tagger::Stage stage, const Tag tag) const
{
    Print(kNotification, "Get Export File", tagger_.tagger_name(), tag);
    std::string name = tagger_.name(stage, tag);
//     std::string name = StudyName(tagger);
//     if (tag == kBackground) name = "Not" + name ;
    return ProjectName() + "/" + name + ".root";
}

ExRootTreeWriter hanalysis::HAnalysis::TreeWriter(TFile &export_file, const std::string &export_tree_name, hanalysis::Tagger::Stage stage)
{
    Print(kNotification, "Get Tree Writer", export_tree_name.c_str());
    ExRootTreeWriter tree_writer(&export_file, export_tree_name.c_str());
    tagger_.SetTreeBranch(tree_writer, stage);
//     NewBranches(tree_writer, tagger);
    return tree_writer;
}

