# include "HAnalysis.hh"
# include "HEventDelphes.hh"
# include "HEventParton.hh"
# include "HEventPgs.hh"

Analysis::HAnalysis()
{

    Print(1, "Constructor");

    EventNumberMax = 100000;

    DebugLevel = 5;

}

vector<string> Analysis::GetStudyNameVector()
{

    vector<string> StudyNameVector = {ProjectName};

    return StudyNameVector;

}

void Analysis::AnalysisLoop()
{

    Print(1, "Analysis Loop");

    Print(1,"");

    vector<string> StudyNames = GetStudyNames();

    GetFiles();

    if (Files.front()->GetTreeName() == "Delphes") {

      if (Files.front()->Snowmass) {

        ClonesArrays = new HClonesArraySnowmass();

      } else {

        ClonesArrays = new HClonesArray();

      }

      Event = new HEvent();

    } else if (Files.front()->GetTreeName() == "LHEF") {

      ClonesArrays = new HClonesArray();

      Event = new HEvent();

    } else if (Files.front()->GetTreeName() == "LHCO") {

      ClonesArrays = new HClonesArray();

      Event = new HEvent();

    } else {

      Print(0, "unknown Tree String", Files.front()->GetTreeName());

    }

    int StudySum = StudyNameVector.size();

    for (unsigned StudyNumber = 0; StudyNumber < StudySum; ++StudyNumber) {

        StudyName = StudyNameVector[StudyNumber];
        Print(1, "Analysing Mva Sample", StudyName);

        GetClonesArrays();

    }

    int FileSum = Files.size();
    for (FileNumber = 0; FileNumber < FileSum; ++FileNumber) {

        Print(1, "Analysing File", FileNumber + 1);
        NewFileBase();

        ExRootProgressBar ProgressBar(EventSum);

        for (EventNumber = 0; EventNumber < EventSum; ++EventNumber) {

            Print(2, "Analysing Event", EventNumber + 1);
            NewEvent();
            ProgressBar.Update(EventNumber);
            if (DebugLevel > 1) cout << endl;

        }
        ProgressBar.Finish();
        //             cout << endl;

        Print(1, "All Events analysed", EventSum);
        CloseFileBase();
        if (DebugLevel > 0) cout << endl;

    }
    Print(1, "All Files analysed", FileSum);

//         DeleteStudy();

//     }

//     Print(1, "All Mva Samples analysed", StudySum);

}

void Analysis::NewStudy()
{

    Print(1, "New Mva", StudyName);


    // Export file
    TString ExportName = ProjectName + "/" + StudyName + TString(".root");
    TFile *ExportFile = new TFile(ExportName, "Recreate");
    ExportFiles.push_back(ExportFile);

}


void Analysis::NewFileBase()
{
    Print(1, "New Analysis");

    AnalysisNotEmpty = 0;

    // Export tree
    TString ExportTreeName = Files[FileNumber]->Title();

    vector<string> StudyNameVector = GetStudyNameVector();
    int StudySum = StudyNameVector.size();

    TreeWriter = new ExRootTreeWriter(ExportFiles.front(), ExportTreeName);
    InfoBranch = TreeWriter->NewBranch("Info", HInfoBranch::Class());


    NewBranches();

//     Event->NewFile();



    // Import file
    TString ImportPath = Files[FileNumber]->GetFilePath();
    ImportFile = new TFile(ImportPath);
    Print(1, "File", ImportPath);

    // Import tree
    TString ImportTreeName = Files[FileNumber]->GetTreeName();
    ImportTree = (TTree *)ImportFile->Get(ImportTreeName);
    Print(1, "Tree", ImportTreeName);

    // TreeReader
    TreeReader = new ExRootTreeReader(ImportTree);
    EventSum = min((int)TreeReader->GetEntries(), EventNumberMax);

    ClonesArrays->UseBranches(TreeReader);
    Print(3,"we have new branches");

}


void Analysis::NewEvent()
{
    Print(2, "New Event");

    Event->NewEvent(ClonesArrays);

    TreeReader->ReadEntry(EventNumber);

    int Successfull = Analysis();

//     if (Successfull) {

    Print(0,"File",ExportFiles[Successfull]->GetName());

        TreeWriter->SetTreeFile(ExportFiles[Successfull]);

        AnalysisNotEmpty = 1;
        HInfoBranch *Info = static_cast<HInfoBranch *>(InfoBranch->NewEntry());
        Info->Crosssection = Files[FileNumber]->Crosssection;
        Info->Error = Files[FileNumber]->Error;
        Info->EventNumber = EventSum;

        TreeWriter->Fill();

//     }

    TreeWriter->Clear();

}


void Analysis::CloseFileBase()
{
    Print(1, "Clean Analysis");


    for (unsigned StudyNumber = 0; StudyNumber < ExportFiles.size(); ++StudyNumber) {

      TreeWriter->SetTreeFile(ExportFiles[StudyNumber]);
    TreeWriter->Write();

    }

    delete TreeWriter;

    Event->CloseFile();
    CloseFile();

    ClonesArrays->ResetBranches();

//     delete TreeReader; // FIXME should get deleted here
    delete ImportTree;
    delete ImportFile;


}


void Analysis::DeleteStudy()
{
    Print(1, "Clean Mva");

}


Analysis::~HAnalysis()
{

    Print(1, "Destructor");

    for (unsigned StudyNumber = 0; StudyNumber < ExportFiles.size(); ++StudyNumber) {

      ExportFiles[StudyNumber]->Close();

    }


    EmptyFileVector();

    delete ExportFile;
    delete ClonesArrays;
    delete Event;



}

void Analysis::EmptyFileVector()
{

    int PathSum = Files.size();
    for (int PathNumber = 0; PathNumber < PathSum; ++PathNumber) {

        delete Files[PathNumber];

    }
    Files.clear();

}
