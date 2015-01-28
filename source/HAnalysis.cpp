# include "HAnalysis.hh"

hanalysis::HAnalysis::HAnalysis()
{
    Print(HNotification, "Constructor");
}

void hanalysis::HAnalysis::AnalysisLoop(const HTagger Tagger)
{
    Print(HNotification, "Analysis Loop");
    std::vector<HTag> States = {HSignal, HBackground};
    for (const auto & State : States) {
        Print(HNotification, "Analysing Mva Sample", State);
        TFile *const ExportFile = GetExportFile(Tagger, State);
        for (auto * const File : GetFiles(Tagger, State)) {
            HClonesArray *const ClonesArrays = File->GetClonesArrays();
            HEvent *Event = File->GetEvent();
            bool AnalysisNotEmpty = 0;
            ExRootTreeWriter *const TreeWriter = GetTreeWriter(ExportFile, File->GetTitle(), Tagger);
            ExRootTreeBranch *const InfoBranch = TreeWriter->NewBranch("Info", HInfoBranch::Class());
            const ExRootTreeReader *const TreeReader = File->GetTreeReader();
            ClonesArrays->GetBranches(TreeReader);
            ExRootProgressBar ProgressBar(GetEventSum(TreeReader));
            Print(HInformation, "Sum", GetEventSum(TreeReader));
            for (const int EventNumber : HRange(GetEventSum(TreeReader))) {
                Print(HInformation, "Event Number", EventNumber);
                const_cast<ExRootTreeReader *>(TreeReader)->ReadEntry(EventNumber);
                Event->NewEvent(ClonesArrays);
                Event->SetMass(File->GetMass());
                const bool Successfull = Analysis(Event, Tagger, State);
                if (Successfull) {
                    AnalysisNotEmpty = 1;
                    FillInfoBranch(TreeReader, InfoBranch, File);
                    TreeWriter->Fill();
                }
                TreeWriter->Clear();
                //                 ProgressBar.Update(EventNumber);
            }
            Print(HNotification, "All Events analysed", GetEventSum(TreeReader));
            ProgressBar.Finish();
            if (AnalysisNotEmpty) TreeWriter->Write();
            delete TreeWriter;
            delete Event;
            delete ClonesArrays;
            Print(HNotification, " ");
        }
        ExportFile->Close();
        ResetBranch();
        delete ExportFile;
    }
}


void hanalysis::HAnalysis::FillInfoBranch(const ExRootTreeReader *const TreeReader, ExRootTreeBranch *const InfoBranch, const HFile *const File)
{
    HInfoBranch *Info = static_cast<HInfoBranch *>(InfoBranch->NewEntry());
    Info->Crosssection = File->GetCrosssection();
    Info->CrosssectionError = File->GetError();
    Info->Mass = File->GetMass();
    Info->EventNumber = GetEventSum(TreeReader);
}

TFile *hanalysis::HAnalysis::GetExportFile(const HTagger Tagger, const HTag State) const
{
    Print(HNotification, "Get Export File", Tagger, State);
    std::string Name = GetStudyNames(Tagger);
    if (State == HBackground) Name = "Not" + Name ;
    const std::string ExportName = GetProjectName() + "/" + Name + ".root";
    Print(HNotification, "ExportFile", ExportName);
    return (new TFile(ExportName.c_str(), "Recreate"));
}


ExRootTreeWriter *hanalysis::HAnalysis::GetTreeWriter(TFile *const ExportFile, const std::string &ExportTreeName, const HTagger Tagger)
{
    Print(HNotification, "Get Tree Writer", ExportTreeName.c_str());
    ExRootTreeWriter *const TreeWriter = new ExRootTreeWriter(ExportFile, ExportTreeName.c_str());
    NewBranches(TreeWriter, Tagger);
    return TreeWriter;
}

hanalysis::HAnalysis::~HAnalysis()
{
    Print(HNotification, "Destructor");
}

HStrings hanalysis::HAnalysis::JoinHStrings(const HStrings &Strings1, const HStrings &Strings2)
{
    HStrings Combined;
    Combined.reserve(Strings1.size() + Strings2.size());
    Combined.insert(Combined.end(), Strings1.begin(), Strings1.end());
    Combined.insert(Combined.end(), Strings2.begin(), Strings2.end());
    return Combined;
}

std::vector<hanalysis::HFile *>  hanalysis::HAnalysis::JoinFiles(const std::vector< hanalysis::HFile * > &Files1, const std::vector< hanalysis::HFile * > &Files2)
{
    std::vector<hanalysis::HFile *>  Combined;
    Combined.reserve(Files1.size() + Files2.size());
    Combined.insert(Combined.end(), Files1.begin(), Files1.end());
    Combined.insert(Combined.end(), Files2.begin(), Files2.end());
    return Combined;
}
