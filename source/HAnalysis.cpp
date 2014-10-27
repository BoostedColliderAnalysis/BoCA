# include "HAnalysis.hh"

hanalysis::HAnalysis::HAnalysis()
{

    Print(1, "Constructor");

//     DebugLevel=4;

}

void hanalysis::HAnalysis::AnalysisLoop()
{

    Print(1, "Analysis Loop");

    for (const auto & StudyName : GetStudyNames()) {

        Print(1, "Analysing Mva Sample", StudyName);

        TFile *const ExportFile = GetExportFile(StudyName);

        for (auto * const File : GetFiles(StudyName)) {

            HClonesArray *const ClonesArrays = File->GetClonesArrays();

            HEvent *const Event = File->GetEvent();

            bool AnalysisNotEmpty = 0;

            ExRootTreeWriter *const TreeWriter = GetTreeWriter(ExportFile, File->Title());

            ExRootTreeBranch *const InfoBranch = TreeWriter->NewBranch("Info", HInfoBranch::Class());

            const ExRootTreeReader *const TreeReader = File->GetTreeReader();

            ClonesArrays->GetBranches(TreeReader);

            ExRootProgressBar ProgressBar(GetEventSum(TreeReader));

            Print(2, "Sum", GetEventSum(TreeReader));

            for (const int EventNumber : HRange(GetEventSum(TreeReader))) {

                Print(2, "Event Number", EventNumber);

                const_cast<ExRootTreeReader *>(TreeReader)->ReadEntry(EventNumber);

                Event->NewEvent(ClonesArrays);

                const bool Successfull = Analysis(Event, StudyName);

                if (Successfull) {

                    AnalysisNotEmpty = 1;

                    FillInfoBranch(TreeReader, InfoBranch, File);

                    TreeWriter->Fill();

                }

                TreeWriter->Clear();


//                 ProgressBar.Update(EventNumber);
            }

            Print(1, "All Events analysed", GetEventSum(TreeReader));

            ProgressBar.Finish();

            if (AnalysisNotEmpty) TreeWriter->Write();

            ClonesArrays->ResetBranches();

            delete TreeReader;

            delete TreeWriter;

            delete Event;

            delete ClonesArrays;

            if (DebugLevel > 0) cout << endl;

        }

        ExportFile->Close();

        delete ExportFile;

    }

    Print(1, "All Samples analysed");

}

void hanalysis::HAnalysis::FillInfoBranch(const ExRootTreeReader *const TreeReader, ExRootTreeBranch *const InfoBranch, const HFile *const File)
{

    HInfoBranch *Info = static_cast<HInfoBranch *>(InfoBranch->NewEntry());
    Info->Crosssection = File->Crosssection;
    Info->Error = File->Error;
    Info->EventNumber = GetEventSum(TreeReader);

}

// hanalysis::HClonesArray *hanalysis::HAnalysis::GetClonesArrays(const string StudyName) const
// {
//
//     Print(1, "Get Clones Arrays", StudyName);
//
//     vector<HFile *> Files = GetFiles(StudyName);
//
//     HClonesArray *ClonesArrays;
//
//     if (Files.front()->GetTreeName() == "Delphes") {
//
//         if (Files.front()->Snowmass) {
//
//             ClonesArrays = new hdelphes::HClonesArraySnowmass();
//
//         } else {
//
//           ClonesArrays = new hdelphes::HClonesArray();
//
//         }
//
//     } else if (Files.front()->GetTreeName() == "LHEF") {
//
//         ClonesArrays = new hparton::HClonesArray();
//
//     } else if (Files.front()->GetTreeName() == "LHCO") {
//
//         ClonesArrays = new hpgs::HClonesArray();
//
//     } else {
//
//         Print(0, "unknown Tree String", Files.front()->GetTreeName());
//
//     }
//
//     //     DeleteFiles(Files); // FIXME
//
//     return ClonesArrays;
//
// }

// hanalysis::HEvent *hanalysis::HAnalysis::GetEvent(const string StudyName) const
// {
//
//     Print(1, "Get Event");
//
//     vector<HFile *> Files = GetFiles(StudyName);
//
//     HEvent * Event;
//
//     if (Files.front()->GetTreeName() == "Delphes") {
//
//       Event = new hdelphes::HEvent();
//
//     } else if (Files.front()->GetTreeName() == "LHEF") {
//
//         Event = new hparton::HEvent();
//
//     } else if (Files.front()->GetTreeName() == "LHCO") {
//
//         Event = new hpgs::HEvent();
//
//     } else {
//
//         Print(0, "unknown Tree String", Files.front()->GetTreeName());
//
//     }
//
// //     DeleteFiles(Files); // FIXME
//
//     return Event;
//
// }

TFile *hanalysis::HAnalysis::GetExportFile(const string StudyName) const
{

    const string ExportName = GetProjectName() + "/" + StudyName + ".root";

    Print(1, "ExportFile", ExportName);

    return (new TFile(ExportName.c_str(), "Recreate"));

}


ExRootTreeWriter *hanalysis::HAnalysis::GetTreeWriter(TFile *const ExportFile, const string ExportTreeName)
{

    Print(1, "Get Tree Writer", ExportTreeName.c_str());

    ExRootTreeWriter *const TreeWriter = new ExRootTreeWriter(ExportFile, ExportTreeName.c_str());

    NewBranches(TreeWriter);

    return TreeWriter;

}

hanalysis::HAnalysis::~HAnalysis()
{

    Print(1, "Destructor");

}

// void hanalysis::HAnalysis::DeleteFiles(const std::vector< HFile * > Files) const
// {
// 
//     for (const auto * File : Files) {
// 
//         delete File;
// 
//     }
// 
// }
