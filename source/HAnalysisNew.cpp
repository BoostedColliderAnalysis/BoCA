# include "HAnalysis.hh"
# include "HEventDelphes.hh"
# include "HEventParton.hh"
# include "HEventPgs.hh"

HAnalysis::HAnalysis()
{

    Print(1, "Constructor");

    EventNumberMax = 100000;

    DebugLevel = 5;

}

vector<string> HAnalysis::GetStudyNameVector()
{

    vector<string> StudyNameVector = {ProjectName};

    return StudyNameVector;

}

void HAnalysis::AnalysisLoop()
{

    Print(1, "Analysis Loop");

    Print(1,"");

    vector<string> StudyNameVector = GetStudyNameVector();

    SetFileVector();

    if (FileVector.front()->GetTreeName() == "Delphes") {

      if (FileVector.front()->Snowmass) {

        ClonesArrays = new HClonesArraySnowmass();

      } else {

        ClonesArrays = new HClonesArrayDelphes();

      }

      Event = new HEventDelphes();

    } else if (FileVector.front()->GetTreeName() == "LHEF") {

      ClonesArrays = new HClonesArrayParton();

      Event = new HEventParton();

    } else if (FileVector.front()->GetTreeName() == "LHCO") {

      ClonesArrays = new HClonesArrayPgs();

      Event = new HEventPgs();

    } else {

      Print(0, "unknown Tree String", FileVector.front()->GetTreeName());

    }

    int StudySum = StudyNameVector.size();

    for (unsigned StudyNumber = 0; StudyNumber < StudySum; ++StudyNumber) {

        StudyName = StudyNameVector[StudyNumber];
        Print(1, "Analysing Mva Sample", StudyName);

        NewStudy();

    }

    int FileSum = FileVector.size();
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

void HAnalysis::NewStudy()
{

    Print(1, "New Mva", StudyName);


    // Export file
    TString ExportName = ProjectName + "/" + StudyName + TString(".root");
    TFile *ExportFile = new TFile(ExportName, "Recreate");
    ExportFileVector.push_back(ExportFile);

}


void HAnalysis::NewFileBase()
{
    Print(1, "New Analysis");

    AnalysisNotEmpty = 0;

    // Export tree
    TString ExportTreeName = FileVector[FileNumber]->Title();

    vector<string> StudyNameVector = GetStudyNameVector();
    int StudySum = StudyNameVector.size();

    TreeWriter = new ExRootTreeWriter(ExportFileVector.front(), ExportTreeName);
    InfoBranch = TreeWriter->NewBranch("Info", HInfoBranch::Class());


    NewFile();

//     Event->NewFile();



    // Import file
    TString ImportPath = FileVector[FileNumber]->GetFilePath();
    ImportFile = new TFile(ImportPath);
    Print(1, "File", ImportPath);

    // Import tree
    TString ImportTreeName = FileVector[FileNumber]->GetTreeName();
    ImportTree = (TTree *)ImportFile->Get(ImportTreeName);
    Print(1, "Tree", ImportTreeName);

    // TreeReader
    TreeReader = new ExRootTreeReader(ImportTree);
    EventSum = min((int)TreeReader->GetEntries(), EventNumberMax);

    ClonesArrays->UseBranches(TreeReader);
    Print(3,"we have new branches");

}


void HAnalysis::NewEvent()
{
    Print(2, "New Event");

    Event->NewEvent(ClonesArrays);

    TreeReader->ReadEntry(EventNumber);

    int Successfull = Analysis();

//     if (Successfull) {

    Print(0,"File",ExportFileVector[Successfull]->GetName());

        TreeWriter->SetTreeFile(ExportFileVector[Successfull]);

        AnalysisNotEmpty = 1;
        HInfoBranch *Info = static_cast<HInfoBranch *>(InfoBranch->NewEntry());
        Info->Crosssection = FileVector[FileNumber]->Crosssection;
        Info->Error = FileVector[FileNumber]->Error;
        Info->EventNumber = EventSum;

        TreeWriter->Fill();

//     }

    TreeWriter->Clear();

}


void HAnalysis::CloseFileBase()
{
    Print(1, "Clean Analysis");


    for (unsigned StudyNumber = 0; StudyNumber < ExportFileVector.size(); ++StudyNumber) {

      TreeWriter->SetTreeFile(ExportFileVector[StudyNumber]);
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


void HAnalysis::DeleteStudy()
{
    Print(1, "Clean Mva");

}


HAnalysis::~HAnalysis()
{

    Print(1, "Destructor");

    for (unsigned StudyNumber = 0; StudyNumber < ExportFileVector.size(); ++StudyNumber) {

      ExportFileVector[StudyNumber]->Close();

    }


    EmptyFileVector();

    delete ExportFile;
    delete ClonesArrays;
    delete Event;



}

void HAnalysis::EmptyFileVector()
{

    int PathSum = FileVector.size();
    for (int PathNumber = 0; PathNumber < PathSum; ++PathNumber) {

        delete FileVector[PathNumber];

    }
    FileVector.clear();

}
