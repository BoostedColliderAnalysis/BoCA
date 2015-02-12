# include "HAnalysis.hh"

hanalysis::HAnalysis::HAnalysis()
{
    Print(HNotification, "Constructor");
    EventSumM = 0;
}

void hanalysis::HAnalysis::AnalysisLoop(const HTagger Tagger)
{
    Print(HNotification, "Analysis Loop");
    std::vector<HTag> Tags = {HSignal, HBackground};
    for (const auto & Tag : Tags) {
        Print(HNotification, "Analysing Mva Sample", Tag);
        TFile NewExportFile(ExportName(Tagger, Tag).c_str(), "Recreate");
        for (auto & File : Files(Tagger, Tag)) {
            Print(HNotification, "Analysing File", File.TreeName());
            EventSumM = 0;
            std::shared_ptr<hanalysis::HClonesArray> ClonesArrays = File.ClonesArrays();
            std::shared_ptr<hanalysis::HEvent> Event = File.Event();
            bool AnalysisNotEmpty = 0;
            ExRootTreeWriter ExTreeWriter = TreeWriter(NewExportFile, File.GetTitle(), Tagger);
            ExRootTreeBranch *const InfoBranch = ExTreeWriter.NewBranch("Info", HInfoBranch::Class());
            const std::shared_ptr<ExRootTreeReader> NewTreeReader = File.TreeReader();
            ClonesArrays->GetBranches(NewTreeReader);
            ExRootProgressBar ProgressBar(EventSum(NewTreeReader));
            Print(HInformation, "Sum", EventSum(NewTreeReader));
            for (const int EventNumber : HRange(EventSum(NewTreeReader))) {
                Print(HInformation, "Event Number", EventNumber);
                std::const_pointer_cast<ExRootTreeReader>(NewTreeReader)->ReadEntry(EventNumber);
                Event->NewEvent(ClonesArrays.get());
                Event->SetMass(File.Mass());
                const bool Successfull = Analysis(*Event.get(), Tagger, Tag);
                if (Successfull) {
                    AnalysisNotEmpty = 1;
                    *static_cast<HInfoBranch *>(InfoBranch->NewEntry()) = FillInfoBranch(*NewTreeReader.get(), File);
                    ExTreeWriter.Fill();
                }
                ExTreeWriter.Clear();
                //                 ProgressBar.Update(EventNumber);
            }
            Print(HNotification, "All Events analysed", EventSum(NewTreeReader));
            ProgressBar.Finish();
            if (AnalysisNotEmpty) ExTreeWriter.Write();
            Print(HError, "Number of Events", EventSumM, EventSum(NewTreeReader));
        }
        NewExportFile.Close();
    }
}


HInfoBranch hanalysis::HAnalysis::FillInfoBranch(const ExRootTreeReader &NewTreeReader, const HFile &File)
{
//     HInfoBranch *Info = static_cast<HInfoBranch *>(InfoBranch->NewEntry());
    HInfoBranch Info;
    Info.Crosssection = File.Crosssection();
    Info.CrosssectionError = File.CrosssectionError();
    Info.Mass = File.Mass();
    Info.EventNumber = EventSum(NewTreeReader);
    return Info;
}



std::string hanalysis::HAnalysis::ExportName(const HTagger Tagger, const HTag State) const
{
  Print(HNotification, "Get Export File", Tagger, State);
  std::string Name = StudyName(Tagger);
  if (State == HBackground) Name = "Not" + Name ;
  return ProjectName() + "/" + Name + ".root";
}

ExRootTreeWriter hanalysis::HAnalysis::TreeWriter(const TFile &NewExportFile, const std::string &ExportTreeName, const hanalysis::HAnalysis::HTagger Tagger)
{
  Print(HNotification, "Get Tree Writer", ExportTreeName.c_str());
  ExRootTreeWriter TreeWriterM(const_cast<TFile*>(&NewExportFile), ExportTreeName.c_str());
  NewBranches(TreeWriterM, Tagger);
  return TreeWriterM;
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

std::vector<hanalysis::HFile>  hanalysis::HAnalysis::JoinFiles(const std::vector< hanalysis::HFile> &Files1, const std::vector< hanalysis::HFile> &Files2)
{
    std::vector<hanalysis::HFile>  Combined;
    Combined.reserve(Files1.size() + Files2.size());
    Combined.insert(Combined.end(), Files1.begin(), Files1.end());
    Combined.insert(Combined.end(), Files2.begin(), Files2.end());
    return Combined;
}
