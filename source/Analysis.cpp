#include "Analysis.hh"

#include <sys/stat.h>

#include "TTree.h"

#include "exroot/ExRootAnalysis.hh"

#include "Branches.hh"
#include "Event.hh"
#include "Debug.hh"

namespace analysis
{

// HAnalysis::HAnalysis(const std::string &ConfigName) : config_(ConfigName)
Analysis::Analysis(Tagger &tagger) : tagger_(tagger)
{
    Note();
}

void Analysis::AnalysisLoop(const Stage stage)
{
    Note();
    mkdir(ProjectName().c_str(), 0700);
    if (stage == Stage::reader) reader_.SetTagger(tagger_);
    tagger_.clear_tree_names();
    for (const auto & tag : std::vector<Tag> {Tag::signal, Tag::background}) {
        Note("Analysing Mva Sample", Name(tag));
        TFile export_file(ExportName(stage, tag).c_str(), "Recreate");
        files_.clear();
        SetFiles(tag);
        for (auto & file : Files(tag)) {
            Note(file.tree_name());
            ClonesArrays clones_arrays = file.clones_arrays();
            Event event = file.event();
            bool analysis_empty = true;
            exroot::TreeWriter tree_writer = TreeWriter(export_file, file.Title(), stage);
            exroot::TreeBranch &tree_branch = *tree_writer.NewBranch(tagger_.weight_branch_name().c_str(), InfoBranch::Class());
            exroot::TreeReader tree_reader = file.TreeReader();
            clones_arrays.UseBranches(tree_reader);
//             exroot::ProgressBar progress_bar(std::min((int)tree_reader.GetEntries(), EventNumberMax()));
            int object_sum = 0;
            int pre_cut_sum = 0;
            InfoBranch info_branch = FillInfoBranch(tree_reader, file);
            int initial_number = 0;
            if (stage == Stage::reader) initial_number = std::min((int)tree_reader.GetEntries(), EventNumberMax()); // TODO fix corner cases
            for (int event_number = initial_number; event_number < tree_reader.GetEntries(); ++event_number) {
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
                        static_cast<InfoBranch &>(*tree_branch.NewEntry()) = info_branch;
//                         dynamic_cast<InfoBranch &>(*tree_branch.NewEntry()) = info_branch;
                        tree_writer.Fill();
                    }
                }
                tree_writer.Clear();
                if (object_sum >= EventNumberMax()) break;
//                 progress_bar.Update(event_number);
            }
            Error("All events analysed", info_branch.EventNumber);
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

std::string Analysis::ExportName(const Stage stage, const Tag tag) const
{
    Note(tagger_.name(stage, tag));
    return ProjectName() + "/" + tagger_.name(stage, tag) + FileSuffix();
}

exroot::TreeWriter Analysis::TreeWriter(TFile &export_file, const std::string &export_tree_name, Stage stage)
{
    Note(export_tree_name.c_str());
    exroot::TreeWriter tree_writer(&export_file, export_tree_name.c_str());
    tagger_.SetTreeBranch(tree_writer, stage);
    return tree_writer;
}

int Analysis::RunAnalysis(Event &event, const Stage stage, const Tag tag)
{
    Info();
    switch (stage) {
    case Stage::trainer :
        return tagger_.Train(event, pre_cuts_, tag);
    case Stage::reader :
        return reader_.GetBdt(event, pre_cuts_);
    default :
        return 0;
    }
}

bool Analysis::Missing(const std::string &name) const
{
    Error(name);
    struct stat buffer;
    return (stat(name.c_str(), &buffer) != 0);
}
std::vector< File > Analysis::Files(const Tag tag)
{
    Error(Name(tag));
    return files_;
}
void Analysis::SetFiles(const Tag tag)
{
    Error("should be subclassed", Name(tag));
}
int Analysis::PassPreCut(Event &)
{
    Error("no pre cut applied");
    return 1;
}

}
