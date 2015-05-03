# include "HAnalysis.hh"

// hanalysis::HAnalysis::HAnalysis(const std::string &ConfigName) : config_(ConfigName)
hanalysis::HAnalysis::HAnalysis()
{
    Print(HNotification, "Constructor");
    event_sum_ = 0;
}

void hanalysis::HAnalysis::AnalysisLoop(const HTagger tagger)
{
    Print(HNotification, "Analysis Loop");
    for (const auto & tag : std::vector<HTag> {HSignal, HBackground}) {
        Print(HNotification, "Analysing Mva Sample", tag);
        TFile export_file(ExportName(tagger, tag).c_str(), "Recreate");
        for (auto & file : Files(tagger, tag)) {
            Print(HNotification, "Analysing File", file.TreeName());
            event_sum_ = 0;
            HClonesArray &clones_arrays = file.ClonesArrays();
            hanalysis::HEvent &event = file.Event();
            bool analysis_not_empty = false;
            ExRootTreeWriter tree_writer = TreeWriter(export_file, file.GetTitle(), tagger);
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
                if (Analysis(event, tagger, tag)) {
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

std::string hanalysis::HAnalysis::ExportName(const HTagger tagger, const HTag tag) const
{
    Print(HNotification, "Get Export File", tagger, tag);
    std::string Name = StudyName(tagger);
    if (tag == HBackground) Name = "Not" + Name ;
    return ProjectName() + "/" + Name + ".root";
}

ExRootTreeWriter hanalysis::HAnalysis::TreeWriter(const TFile &export_file, const std::string &export_tree_name, const hanalysis::HAnalysis::HTagger tagger)
{
    Print(HNotification, "Get Tree Writer", export_tree_name.c_str());
    ExRootTreeWriter tree_writer(&const_cast<TFile &>(export_file), export_tree_name.c_str());
    NewBranches(tree_writer, tagger);
    return tree_writer;
}

