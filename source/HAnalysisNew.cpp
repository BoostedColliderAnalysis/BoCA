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

    Print(0,"");

    vector<string> StudyNameVector = GetStudyNameVector();

    SetFileVector();

    int StudySum = StudyNameVector.size();

    for (int StudyNumber = 0; StudyNumber < StudySum; ++StudyNumber) {

        StudyName = StudyNameVector[StudyNumber];
        Print(0, "Analysing Mva Sample", StudyName);

        NewStudy();

    }

    int FileSum = FileVector.size();
    for (FileNumber = 0; FileNumber < FileSum; ++FileNumber) {

        Print(0, "Analysing File", FileNumber + 1);
        NewFileBase();

        ExRootProgressBar ProgressBar(EventSum);

        for (EventNumber = 0; EventNumber < EventSum; ++EventNumber) {

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

//         DeleteStudy();

//     }

//     Print(0, "All Mva Samples analysed", StudySum);

}

void HAnalysis::NewStudy()
{

    Print(0, "New Mva", StudyName);


    // Export file
    TString ExportName = ProjectName + "/" + StudyName + TString(".root");
    TFile ExportFile = new TFile(ExportName, "Recreate");
    ExportFileVector.push_back(ExportFile);

}


void HAnalysis::NewFileBase()
{
    Print(0, "New Analysis");

    AnalysisNotEmpty = 0;

    // Export tree
    TString ExportTreeName = FileVector[FileNumber]->Title;

    vector<string> StudyNameVector = GetStudyNameVector();
    int StudySum = StudyNameVector.size();
    for (int StudyNumber = 0; StudyNumber < StudySum; ++StudyNumber) {


        ExRootTreeWriter TreeWriter = new ExRootTreeWriter(ExportFile, ExportTreeName);
        ExRootTreeBranch InfoBranch = TreeWriter->NewBranch("Info", HInfoBranch::Class());
        TreeWriterVector.push_back(TreeWriter);

    }


    NewFile();

    Event->NewFile();


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

        TreeWriterVector[Successfull]->Fill();

    }

    TreeWriterVector[Successfull]->Clear();

}


void HAnalysis::CloseFileBase()
{
    Print(0, "Clean Analysis");

    for (int StudyNumber = 0; StudyNumber < GetStudyNameVector().size(); ++StudyNumber) {
        
       TreeWriterVector[StudyNumber]->Write();
       delete TreeWriterVector[StudyNumber];
        
    }
    
    Event->CloseFile();
    CloseFile();

    ClonesArrays->ResetBranches();

    delete TreeReader;
    delete ImportTree;
    delete ImportFile;


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
