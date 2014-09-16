# include "HAnalysisBase.hh"

HAnalysisBase::HAnalysisBase()
{

    Print(0, "Constructor");

    MvaNameVector = {"Test"};

    EventNumberMax = 100000;

    Event = new HEvent();

}

void HAnalysisBase::AnalysisLoop()
{

    Print(0, "Analysis Loop");

    cout << endl;

    int MvaSum = MvaNameVector.size();

    for (int MvaNumber = 0; MvaNumber < MvaSum; ++MvaNumber) {

        MvaName = MvaNameVector[MvaNumber];
        Print(0, "Analysing Mva Sample", MvaName);

        NewMva();

        int AnalysisSum = AnalysisVector.size();
        for (AnalysisNumber = 0; AnalysisNumber < AnalysisSum; ++AnalysisNumber) {

            Print(0, "Analysing File", AnalysisNumber + 1);
            NewAnalysisBase();

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
            CleanAnalysisBase();
            if (Debug > 0) cout << endl;

        }
        Print(0, "All Files analysed", AnalysisSum);

        CleanMva();

    }

    Print(0, "All Mva Samples analysed", MvaSum);

}

void HAnalysisBase::NewMva()
{

    Print(0, "New Mva", MvaName);

    FillAnalysisVector();

    // Export file
    TString ExportName = ProjectName + "/" + MvaName + TString(".root");
    ExportFile = new TFile(ExportName, "Recreate");

}


void HAnalysisBase::NewAnalysisBase()
{
    Print(0, "New Analysis");

    AnalysisNotEmpty = 0;

    // Export tree
    TString ExportTreeString = AnalysisVector[AnalysisNumber]->Title;
    TreeWriter = new ExRootTreeWriter(ExportFile, ExportTreeString);

    NewAnalysis();

    Event->NewAnalysis();

    InfoBranch = TreeWriter->NewBranch("Info", HInfoBranch::Class());

    // Import file
    TString ImportPathString = AnalysisVector[AnalysisNumber]->FilePath();
    ImportFile = new TFile(ImportPathString);
    Print(0, "File", ImportPathString);

    // Import tree
    TString ImportTreeString = AnalysisVector[AnalysisNumber]->GetTreeString();
    ImportTree = (TTree *)ImportFile->Get(ImportTreeString);
    Print(0, "Tree", ImportTreeString);

    // TreeReader
    TreeReader = new ExRootTreeReader(ImportTree);
    EventSum = min((int)TreeReader->GetEntries(), EventNumberMax);

    EntrySumVector.push_back(EventSum);

    ClonesArrays->ReadTrees(TreeReader);

}


void HAnalysisBase::NewEvent()
{
    Print(1, "New Event");

    Event->NewEvent(ClonesArrays);

    TreeReader->ReadEntry(EventNumber);

    bool Successfull = Analysis();

    if (Successfull) {

        AnalysisNotEmpty = 1;
        HInfoBranch *Info = static_cast<HInfoBranch *>(InfoBranch->NewEntry());
        Info->Crosssection = AnalysisVector[AnalysisNumber]->Crosssection;
        Info->Error = AnalysisVector[AnalysisNumber]->Error;
        Info->EventNumber = EventSum;

        TreeWriter->Fill();

    }

    TreeWriter->Clear();

}


void HAnalysisBase::CleanAnalysisBase()
{
    Print(0, "Clean Analysis");

    if (AnalysisNotEmpty) TreeWriter->Write();

    Event->CleanAnalysis();

    ClonesArrays->ResetTrees();

    delete TreeReader;
    delete ImportTree;
    delete ImportFile;
    delete TreeWriter;


}


void HAnalysisBase::CleanMva()
{
    Print(0, "Clean Mva");

}


HAnalysisBase::~HAnalysisBase()
{

    Print(0, "Destructor");

    ExportFile->Close();

    delete ExportFile;
    delete ClonesArrays;
    delete Event;

    int PathSum = AnalysisVector.size();
    for (int PathNumber = 0; PathNumber < PathSum; ++PathNumber) {

        delete AnalysisVector[PathNumber];
        AnalysisVector.clear();

    }


}
