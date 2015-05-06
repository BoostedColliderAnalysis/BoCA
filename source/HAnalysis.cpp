# include "HAnalysis.hh"

// hanalysis::HAnalysis::HAnalysis(const std::string &ConfigName) : config_(ConfigName)
hanalysis::HAnalysis::HAnalysis(hanalysis::Tagger &tagger) : tagger_(tagger)
{
    Print(HNotification, "Constructor");
    event_sum_ = 0;
}

void hanalysis::HAnalysis::AnalysisLoop(const Tagger::Stage stage)
{
    Print(HNotification, "Analysis Loop");
    tagger_.SetAnalysisName(ProjectName());
    mkdir(ProjectName().c_str(), 0700);
    if (stage == Tagger::kReader) reader_.SetMva(tagger_);
    for (const auto & tag : std::vector<Tag> {kSignal, kBackground}) {
        Print(HNotification, "Analysing Mva Sample", tag);
        TFile export_file(ExportName(stage, tag).c_str(), "Recreate");
        files_.clear();
        SetFiles(tag);
        for (auto & file : Files(tag)) {
            Print(HNotification, "Analysing File", file.TreeName());
            event_sum_ = 0;
            ClonesArrays &clones_arrays = file.GetClonesArrays();
            hanalysis::HEvent &event = file.Event();
            bool analysis_not_empty = false;
            ExRootTreeWriter tree_writer = TreeWriter(export_file, file.GetTitle(), stage);
            ExRootTreeBranch &tree_branch = *tree_writer.NewBranch("Info", HInfoBranch::Class());
            ExRootTreeReader tree_reader = file.TreeReader();
            clones_arrays.GetBranches(tree_reader);
//             ExRootProgressBar progress_bar(EventSum(tree_reader));
//             Print(HInformation, "Sum", EventSum(tree_reader));
            ObjectNumber = 0;
            HInfoBranch info_branch = FillInfoBranch(tree_reader, file);
            for (const int event_number : Range(EventSum(tree_reader))) {
//                 Print(HError, "Event Number", event_number);
                tree_reader.ReadEntry(event_number);
                event.NewEvent(clones_arrays);
                event.SetMass(file.Mass());
                int Objects = Analysis(event, stage, tag);
                if (Objects > 0) {
                  ObjectNumber += Objects;
                    info_branch.PreCutNumber = event_number;
                    analysis_not_empty = true;
                    static_cast<HInfoBranch &>(*tree_branch.NewEntry()) = info_branch;
                    tree_writer.Fill();
                }
                tree_writer.Clear();
                if (ObjectNumber >= EventNumberMax()) break;
//                 progress_bar.Update(event_number);
            }
            Print(HError, "All Events analysed", info_branch.EventNumber);
//             progress_bar.Finish();
            if (analysis_not_empty) tree_writer.Write();
//             Print(HError, "Number of Events", event_sum_, EventSum(tree_reader));
        }
        export_file.Close();
    }
}

HInfoBranch hanalysis::HAnalysis::FillInfoBranch(const ExRootTreeReader &tree_reader, const HFile &file)
{
    HInfoBranch info_branch;
    info_branch.Crosssection = file.Crosssection();
    info_branch.CrosssectionError = file.CrosssectionError();
    info_branch.Mass = file.Mass();
    info_branch.EventNumber = EventSum(tree_reader);
//     Print(HError, "Event Number", info_branch.EventNumber);
    return info_branch;
}

std::string hanalysis::HAnalysis::ExportName(const Tagger::Stage stage, const Tag tag) const
{
    Print(HNotification, "Get Export File", tagger_.tagger_name(), tag);
    std::string name = tagger_.name(stage, tag);
//     std::string name = StudyName(tagger);
//     if (tag == kBackground) name = "Not" + name ;
    return ProjectName() + "/" + name + ".root";
}

ExRootTreeWriter hanalysis::HAnalysis::TreeWriter(TFile &export_file, const std::string &export_tree_name, hanalysis::Tagger::Stage stage)
{
    Print(HNotification, "Get Tree Writer", export_tree_name.c_str());
    ExRootTreeWriter tree_writer(&export_file, export_tree_name.c_str());
    tagger_.SetTreeBranch(tree_writer, stage);
//     NewBranches(tree_writer, tagger);
    return tree_writer;
}

