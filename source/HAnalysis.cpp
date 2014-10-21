# include "HAnalysis.hh"

HAnalysis::HAnalysis()
{

    Print(1, "Constructor");

    EventNumberMax = 100000;

}

vector<string> HAnalysis::GetStudyNames()
{

    return {ProjectName};

}

void HAnalysis::AnalysisLoop()
{

    Print(1, "Analysis Loop");

    Print(1,"");

    const vector<string> StudyNames = GetStudyNames();

    const vector<HFile*> Files = GetFiles();

    for (const auto &StudyName : StudyNames) {

        Print(1, "Analysing Mva Sample", StudyName);

        HClonesArray* ClonesArrays = GetClonesArrays(Files);

        HEvent* Event = GetEvent(Files);

        TFile* ExportFile = GetExportFile(StudyName);

        for (const auto &File : Files) {

            Print(1, "Analysing File", File);

            bool AnalysisNotEmpty = 0;

            ExRootTreeWriter *TreeWriter = GetTreeWriter(ExportFile,File->Title());

            NewFile(TreeWriter);

            Event->NewFile();

            ExRootTreeBranch *InfoBranch = TreeWriter->NewBranch("Info", HInfoBranch::Class());

            ExRootTreeReader *TreeReader = GetTreeReader(File);

            ClonesArrays->UseBranches(TreeReader);

            ExRootProgressBar *ProgressBar(GetEventSum(TreeReader));

            for (int EventNumber : HRange(GetEventSum(TreeReader))) {

                Print(2, "Analysing Event", EventNumber + 1);
//                 NewEvent(StudyName,File,EventNumber);

                Event->NewEvent(ClonesArrays);

                TreeReader->ReadEntry(EventNumber);

                const bool Successfull = Analysis(Event,StudyName);

                if (Successfull) {

                    AnalysisNotEmpty = 1;
                    HInfoBranch *Info = static_cast<HInfoBranch *>(InfoBranch->NewEntry());
                    Info->Crosssection = File->Crosssection;
                    Info->Error = File->Error;
                    Info->EventNumber = GetEventSum(TreeReader);

                    TreeWriter->Fill();

                }

                TreeWriter->Clear();

                //ProgressBar->Update(EventNumber); // FIXME breaks
                if (DebugLevel > 1) cout << endl;

            }
            ProgressBar->Finish();
            //             cout << endl;

            Print(1, "All Events analysed", GetEventSum(TreeReader));
//             CloseFileBase();

            if (AnalysisNotEmpty) TreeWriter->Write();

            Event->CloseFile();
            CloseFile();

            ClonesArrays->ResetBranches();


            //     delete TreeReader; // FIXME should get deleted here
            //     Print(1, "All deleted");
            delete TreeWriter;


















            if (DebugLevel > 0) cout << endl;

        }
//         Print(1, "All Files analysed", FileSum);


        delete Event;
        delete ClonesArrays;


        ExportFile->Close();

        //     EmptyFileVector();

        delete ExportFile;


    }


    Print(1, "All Mva Samples analysed");

}

HClonesArray* HAnalysis::GetClonesArrays(const vector<HFile*> Files)
{

    Print(1, "Get Clones Arrays");

    HClonesArray* ClonesArrays;

    if (Files.front()->GetTreeName() == "Delphes") {

        if (Files.front()->Snowmass) {

            ClonesArrays = new HClonesArraySnowmass();

        } else {

            ClonesArrays = new HClonesArrayDelphes();

        }

    } else if (Files.front()->GetTreeName() == "LHEF") {

        ClonesArrays = new HClonesArrayParton();

    } else if (Files.front()->GetTreeName() == "LHCO") {

        ClonesArrays = new HClonesArrayPgs();

    } else {

        Print(0, "unknown Tree String", Files.front()->GetTreeName());

    }

    return ClonesArrays;

}




HEvent *HAnalysis::GetEvent(const vector<HFile*> Files)
{

    Print(1, "Get Event");

    HEvent* Event;

    if (Files.front()->GetTreeName() == "Delphes") {

        Event = new HEventDelphes();

    } else if (Files.front()->GetTreeName() == "LHEF") {

        Event = new HEventParton();

    } else if (Files.front()->GetTreeName() == "LHCO") {

        Event = new HEventPgs();

    } else {

        Print(0, "unknown Tree String", Files.front()->GetTreeName());

    }

    return Event;

}



TFile *HAnalysis::GetExportFile(const string StudyName) {

    const string ExportName = ProjectName + "/" + StudyName + ".root";
    TFile *ExportFile = new TFile(ExportName.c_str(), "Recreate");
    Print(1, "ExportFile", ExportName);

    return ExportFile;

}


ExRootTreeWriter *HAnalysis::GetTreeWriter(TFile * ExportFile, const string ExportTreeName) {

    Print(1, "ExportTreeName", ExportTreeName.c_str());
    ExRootTreeWriter *TreeWriter = new ExRootTreeWriter(ExportFile, ExportTreeName.c_str());

    return TreeWriter;

}


ExRootTreeReader *HAnalysis::GetTreeReader(const HFile* const File) {

    // Import file
    const string ImportPath = File->GetFilePath();
    TFile* ImportFile = new TFile(ImportPath.c_str());
    Print(1, "File", ImportPath);

    // Import tree
    const string ImportTreeName = File->GetTreeName();
    TTree* ImportTree = (TTree *)ImportFile->Get(ImportTreeName.c_str());
    Print(1, "Tree", ImportTreeName);

    // TreeReader
    ExRootTreeReader *TreeReader = new ExRootTreeReader(ImportTree);


    delete ImportFile; // FIXME Possible?

    delete ImportTree; // FIXME Possible?

    return TreeReader;

}


HAnalysis::~HAnalysis()
{

    Print(1, "Destructor");

}

// void HAnalysis::EmptyFileVector()
// {
//
//   for (const auto &File : Files) {
//
//         delete File;
//
//     }
//
//     Files.clear();
//
// }
