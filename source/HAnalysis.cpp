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

            HEvent *Event = File->GetEvent();

            bool AnalysisNotEmpty = 0;

            ExRootTreeWriter *const TreeWriter = GetTreeWriter(ExportFile, File->GetTitle());

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

            delete TreeWriter;

            delete Event;

            delete ClonesArrays;

            if (DebugLevel > 0) Print(0," ");

        }

        ExportFile->Close();

        delete ExportFile;

    }

}

void hanalysis::HAnalysis::FillInfoBranch(const ExRootTreeReader *const TreeReader, ExRootTreeBranch *const InfoBranch, const HFile *const File)
{

    HInfoBranch *Info = static_cast<HInfoBranch *>(InfoBranch->NewEntry());
    Info->Crosssection = File->GetCrosssection();
    Info->Error = File->GetError();
    Info->EventNumber = GetEventSum(TreeReader);

}

TFile *hanalysis::HAnalysis::GetExportFile(const string &StudyName) const
{

    const string ExportName = GetProjectName() + "/" + StudyName + ".root";

    Print(1, "ExportFile", ExportName);

    return (new TFile(ExportName.c_str(), "Recreate"));

}


ExRootTreeWriter *hanalysis::HAnalysis::GetTreeWriter(TFile *const ExportFile, const string &ExportTreeName)
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
