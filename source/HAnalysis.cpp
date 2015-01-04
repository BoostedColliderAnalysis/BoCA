# include "HAnalysis.hh"

hanalysis::HAnalysis::HAnalysis()
{

    Print(HNotification, "Constructor");


}

// void hanalysis::HAnalysis::AnalysisLoop()
// {
//
//     Print(HNotification, "Analysis Loop");
//
//     for (const auto & StudyName : GetStudyNames()) {
//
//         Print(HNotification, "Analysing Mva Sample", StudyName);
//
//         TFile *const ExportFile = GetExportFile(StudyName);
//
//         for (auto * const File : GetFiles(StudyName)) {
//
// //             HClonesArray *const ClonesArrays = File->GetClonesArrays();
//
//             HEvent *Event = File->GetEvent();
//
//             bool AnalysisNotEmpty = 0;
//
//             ExRootTreeWriter *const TreeWriter = GetTreeWriter(ExportFile, File->GetTitle());
//
//             ExRootTreeBranch *const InfoBranch = TreeWriter->NewBranch("Info", HInfoBranch::Class());
//
//             const ExRootTreeReader *const TreeReader = File->GetTreeReader();
//
//             ClonesArrays->GetBranches(TreeReader);
//
//             ExRootProgressBar ProgressBar(GetEventSum(TreeReader));
//
//             Print(HInformation, "Sum", GetEventSum(TreeReader));
//
//             for (const int EventNumber : HRange(GetEventSum(TreeReader))) {
//
//                 Print(HInformation, "Event Number", EventNumber);
//
//                 const_cast<ExRootTreeReader *>(TreeReader)->ReadEntry(EventNumber);
//
//                 Event->NewEvent(ClonesArrays);
//
//                 const bool Successfull = Analysis(Event, StudyName);
//
//                 if (Successfull) {
//
//                     AnalysisNotEmpty = 1;
//
//                     FillInfoBranch(TreeReader, InfoBranch, File);
//
//                     TreeWriter->Fill();
//
//                 }
//
//                 TreeWriter->Clear();
//
// //                 ProgressBar.Update(EventNumber);
//             }
//
//             Print(HNotification, "All Events analysed", GetEventSum(TreeReader));
//
//             ProgressBar.Finish();
//
//             if (AnalysisNotEmpty) TreeWriter->Write();
//
//             delete TreeWriter;
//
//             delete Event;
//
//             delete ClonesArrays;
//
//             if (DebugLevel > 0) Print(HError," ");
//
//         }
//
//         ExportFile->Close();
//
//         delete ExportFile;
//
//     }
//
// }
//



void hanalysis::HAnalysis::AnalysisLoop(const HTagger Tagger)
{

  Print(HNotification, "Analysis Loop");

  std::vector<HTag> States = {HSignal,HBackground};

//   for (const auto & StudyName : GetStudyNames(Tagger)) {
  for (const auto & State : States) {

    Print(HNotification, "Analysing Mva Sample", State);
//     TFile *const ExportFile = GetExportFile(State);
    TFile *const ExportFile = GetExportFile(Tagger, State);

//     for (auto * const File : GetFiles(State)) {
    for (auto * const File : GetFiles(Tagger, State)) {

      HClonesArray *const ClonesArrays = File->GetClonesArrays();
      HEvent *Event = File->GetEvent();
      bool AnalysisNotEmpty = 0;
      ExRootTreeWriter *const TreeWriter = GetTreeWriter(ExportFile, File->GetTitle(),Tagger);
      ExRootTreeBranch *const InfoBranch = TreeWriter->NewBranch("Info", HInfoBranch::Class());
      const ExRootTreeReader *const TreeReader = File->GetTreeReader();
      ClonesArrays->GetBranches(TreeReader);
      ExRootProgressBar ProgressBar(GetEventSum(TreeReader));
      Print(HInformation, "Sum", GetEventSum(TreeReader));

      for (const int EventNumber : HRange(GetEventSum(TreeReader))) {

        Print(HInformation, "Event Number", EventNumber);
        const_cast<ExRootTreeReader *>(TreeReader)->ReadEntry(EventNumber);
//         Print(HInformation, "New Event");
        Event->NewEvent(ClonesArrays);
//         Print(HInformation, "Analysis");
        const bool Successfull = Analysis(Event,Tagger, State);

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
      Print(HNotification," ");

    }

    ExportFile->Close();
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

// TFile *hanalysis::HAnalysis::GetExportFile(const std::string &StudyName) const
// {
//     Print(HNotification, "Get Export File", StudyName);
//
//     const std::string ExportName = GetProjectName() + "/" + StudyName + ".root";
//
//     Print(HNotification, "ExportFile", ExportName);
//
//     return (new TFile(ExportName.c_str(), "Recreate"));
//
// }

TFile *hanalysis::HAnalysis::GetExportFile(const HTagger Tagger,const HTag State) const
{

    Print(HNotification, "Get Export File", Tagger, State);

    std::string Name = GetStudyNames(Tagger);

    if(State == HBackground) Name = "Not" + Name ;

    const std::string ExportName = GetProjectName() + "/" + Name + ".root";

    Print(HNotification, "ExportFile", ExportName);

    return (new TFile(ExportName.c_str(), "Recreate"));

}


ExRootTreeWriter *hanalysis::HAnalysis::GetTreeWriter(TFile *const ExportFile, const std::string &ExportTreeName,const HTagger Tagger)
{

    Print(HNotification, "Get Tree Writer", ExportTreeName.c_str());

    ExRootTreeWriter *const TreeWriter = new ExRootTreeWriter(ExportFile, ExportTreeName.c_str());

    NewBranches(TreeWriter,Tagger);

    return TreeWriter;

}

hanalysis::HAnalysis::~HAnalysis()
{

    Print(HNotification, "Destructor");

}
