# include "HAnalysis.hh"
# include "HEventDelphes.hh"
# include "HEventParton.hh"
# include "HEventPgs.hh"

HAnalysis::HAnalysis()
{

    Print(0, "Constructor");

    EventNumberMax = 100000;

}

vector<string> HAnalysis::GetStudyNameVector()
{

    vector<string> StudyNameVector = {ProjectName};

    return StudyNameVector;

}

void HAnalysis::AnalysisLoop()
{

    Print(0, "Analysis Loop");

    cout << endl;

    vector<string> StudyNameVector = GetStudyNameVector();

    int StudySum = StudyNameVector.size();

    for (int StudyNumber = 0; StudyNumber < StudySum; ++StudyNumber) {

        StudyName = StudyNameVector[StudyNumber];
        Print(0, "Analysing Mva Sample", StudyName);

        NewStudy();

        int FileSum = FileVector.size();
        for (FileNumber = 0; FileNumber < FileSum; ++FileNumber) {

            Print(0, "Analysing File", FileNumber + 1);
            NewFileBase();

            ExRootProgressBar ProgressBar(EventSum);

            for (EventNumber = 0; EventNumber < EventSum; ++ EventNumber) {

                Print(1, "Analysing Event", EventNumber + 1);
                NewEvent();
                ProgressBar.Update(EventNumber);
                if (Debug > 1) cout << endl;

            }
            ProgressBar.Finish();
            //             cout << endl;

            Print(0, "All Events analysed", EventSum);
            CloseFileBase();
            if (Debug > 0) cout << endl;

        }
        Print(0, "All Files analysed", FileSum);

        DeleteStudy();

    }

    Print(0, "All Mva Samples analysed", StudySum);

}

void HAnalysis::NewStudy()
{

    Print(0, "New Mva", StudyName);

    EmptyFileVector();
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

        Print(-1, "unknown Tree String", FileVector.front()->GetTreeName());

    }

    // Export file
    TString ExportName = ProjectName + "/" + StudyName + TString(".root");
    ExportFile = new TFile(ExportName, "Recreate");
    Print(0, "ExportFile",ExportName);

}


void HAnalysis::NewFileBase()
{
    Print(0, "New File Base");

    AnalysisNotEmpty = 0;

    // Export tree
    TString ExportTreeName = FileVector[FileNumber]->Title;
    Print(0, "ExportTreeName",ExportTreeName);
    TreeWriter = new ExRootTreeWriter(ExportFile, ExportTreeName);

    NewFile();

    Event->NewFile();

    InfoBranch = TreeWriter->NewBranch("Info", HInfoBranch::Class());

    // Import file
    TString ImportPath = FileVector[FileNumber]->GetFilePath();
    ImportFile = new TFile(ImportPath);
    Print(0, "File", ImportPath);

    // Import tree
    TString ImportTreeName = FileVector[FileNumber]->GetTreeName();
    ImportTree = (TTree *)ImportFile->Get(ImportTreeName);
    Print(0, "Tree", ImportTreeName);

    // TreeReader
    TreeReader = new ExRootTreeReader(ImportTree);
    EventSum = min((int)TreeReader->GetEntries(), EventNumberMax);

    ClonesArrays->UseBranches(TreeReader);

}


void HAnalysis::NewEvent()
{
    Print(1, "New Event");

    Event->NewEvent(ClonesArrays);

    TreeReader->ReadEntry(EventNumber);

    bool Successfull = Analysis();

    if (Successfull) {

        AnalysisNotEmpty = 1;
        HInfoBranch *Info = static_cast<HInfoBranch *>(InfoBranch->NewEntry());
        Info->Crosssection = FileVector[FileNumber]->Crosssection;
        Info->Error = FileVector[FileNumber]->Error;
        Info->EventNumber = EventSum;

        TreeWriter->Fill();

    }

    TreeWriter->Clear();

}


void HAnalysis::CloseFileBase()
{
    Print(0, "Clean Analysis");

    if (AnalysisNotEmpty) TreeWriter->Write();

    Event->CloseFile();
    CloseFile();

    ClonesArrays->ResetBranches();
    

//     delete TreeReader; // FIXME should get deleted here
//     Print(0, "All deleted");
    delete ImportTree;
    delete ImportFile;
    delete TreeWriter;


}


void HAnalysis::DeleteStudy()
{
    Print(0, "Clean Mva");

}


HAnalysis::~HAnalysis()
{

    Print(0, "Destructor");

    ExportFile->Close();

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
