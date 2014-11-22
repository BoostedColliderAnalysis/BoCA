# include "HAnalysis.hh"
# include "HEventDelphes.hh"
# include "HEventParton.hh"
# include "HEventPgs.hh"

hanalysis::HAnalysis()
{

    Print(HNotification, "Constructor");

    EventNumberMax = 100000;

    DebugLevel = 5;

}

HStrings hanalysis::GetStudyNameVector()
{

    HStrings StudyNameVector = {ProjectName};

    return StudyNameVector;

}

void hanalysis::AnalysisLoop()
{

    Print(HNotification, "Analysis Loop");

    Print(HNotification,"");

    HStrings StudyNames = GetStudyNames();

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

      Print(HError, "unknown Tree String", Files.front()->GetTreeName());

    }

    int StudySum = StudyNameVector.size();

    for (unsigned StudyNumber = 0; StudyNumber < StudySum; ++StudyNumber) {

        StudyName = StudyNameVector[StudyNumber];
        Print(HNotification, "Analysing Mva Sample", StudyName);

        GetClonesArrays();

    }

    int FileSum = Files.size();
    for (FileNumber = 0; FileNumber < FileSum; ++FileNumber) {

        Print(HNotification, "Analysing File", FileNumber + 1);
        NewFileBase();

        ExRootProgressBar ProgressBar(EventSum);

        for (EventNumber = 0; EventNumber < EventSum; ++EventNumber) {

            Print(HInformation, "Analysing Event", EventNumber + 1);
            NewEvent();
            ProgressBar.Update(EventNumber);
            if (DebugLevel > 1) cout << endl;

        }
        ProgressBar.Finish();
        //             cout << endl;

        Print(HNotification, "All Events analysed", EventSum);
        CloseFileBase();
        if (DebugLevel > 0) cout << endl;

    }
    Print(HNotification, "All Files analysed", FileSum);

//         DeleteStudy();

//     }

//     Print(HNotification, "All Mva Samples analysed", StudySum);

}

void hanalysis::NewStudy()
{

    Print(HNotification, "New Mva", StudyName);


    // Export file
    TString ExportName = ProjectName + "/" + StudyName + TString(".root");
    TFile *ExportFile = new TFile(ExportName, "Recreate");
    ExportFiles.push_back(ExportFile);

}


void hanalysis::NewFileBase()
{
    Print(HNotification, "New Analysis");

    AnalysisNotEmpty = 0;

    // Export tree
    TString ExportTreeName = Files[FileNumber]->Title();

    HStrings StudyNameVector = GetStudyNameVector();
    int StudySum = StudyNameVector.size();

    TreeWriter = new ExRootTreeWriter(ExportFiles.front(), ExportTreeName);
    InfoBranch = TreeWriter->NewBranch("Info", HInfoBranch::Class());


    NewBranches();

//     Event->NewFile();



    // Import file
    TString ImportPath = Files[FileNumber]->GetFilePath();
    ImportFile = new TFile(ImportPath);
    Print(HNotification, "File", ImportPath);

    // Import tree
    TString ImportTreeName = Files[FileNumber]->GetTreeName();
    ImportTree = (TTree *)ImportFile->Get(ImportTreeName);
    Print(HNotification, "Tree", ImportTreeName);

    // TreeReader
    TreeReader = new ExRootTreeReader(ImportTree);
    EventSum = min((int)TreeReader->GetEntries(), EventNumberMax);

    ClonesArrays->UseBranches(TreeReader);
    Print(HDebug,"we have new branches");

}


void hanalysis::NewEvent()
{
    Print(HInformation, "New Event");

    Event->NewEvent(ClonesArrays);

    TreeReader->ReadEntry(EventNumber);

    int Successfull = hanalysis();

//     if (Successfull) {

    Print(HError,"File",ExportFiles[Successfull]->GetName());

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


void hanalysis::CloseFileBase()
{
    Print(HNotification, "Clean Analysis");


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


void hanalysis::DeleteStudy()
{
    Print(HNotification, "Clean Mva");

}


hanalysis::~HAnalysis()
{

    Print(HNotification, "Destructor");

    for (unsigned StudyNumber = 0; StudyNumber < ExportFiles.size(); ++StudyNumber) {

      ExportFiles[StudyNumber]->Close();

    }


    EmptyFileVector();

    delete ExportFile;
    delete ClonesArrays;
    delete Event;



}

void hanalysis::EmptyFileVector()
{

    int PathSum = Files.size();
    for (int PathNumber = 0; PathNumber < PathSum; ++PathNumber) {

        delete Files[PathNumber];

    }
    Files.clear();

}
