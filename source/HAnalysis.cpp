# include "HAnalysis.hh"

HAnalysis::HAnalysis()
{

    Print(1, "Constructor");

    EventNumberMax = 100000;

}

vector<string> HAnalysis::GetStudyNames()
{

    vector<string> StudyNameVector = {ProjectName};

    return StudyNameVector;

}

void HAnalysis::AnalysisLoop()
{

    Print(1, "Analysis Loop");

    Print(1,"");

    vector<string> StudyNameVector = GetStudyNames();

    int StudySum = StudyNameVector.size();

    for (const auto &StudyNameA : StudyNameVector) {

        StudyName = StudyNameA;
        Print(1, "Analysing Mva Sample", StudyName);

        NewStudy();

        for (const auto &File : FileVector) {

            Print(1, "Analysing File", FileNumber + 1);
            NewFileBase(File);
            
            ExRootProgressBar ProgressBar(EventSum);

            for (EventNumber = 0; EventNumber < EventSum; ++ EventNumber) {

                Print(2, "Analysing Event", EventNumber + 1);
                NewEvent();
                //ProgressBar.Update(EventNumber); // FIXME breaks
                if (DebugLevel > 1) cout << endl;

            }
            ProgressBar.Finish();
            //             cout << endl;

            Print(1, "All Events analysed", EventSum);
            CloseFileBase();
            if (DebugLevel > 0) cout << endl;

        }
//         Print(1, "All Files analysed", FileSum);

        DeleteStudy();

    }

    Print(1, "All Mva Samples analysed", StudySum);

}

void HAnalysis::NewStudy()
{

//     Print(1, "New Mva", StudyName);

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

        Print(0, "unknown Tree String", FileVector.front()->GetTreeName());

    }

    // Export file
    const string ExportName = ProjectName + "/" + StudyName + ".root";
    ExportFile = new TFile(ExportName.c_str(), "Recreate");
    Print(1, "ExportFile", ExportName);

}


void HAnalysis::NewFileBase(const HFile * File)
{
    Print(1, "New File Base");

    AnalysisNotEmpty = 0;

    // Export tree
    const string ExportTreeName = File->Title();
    Print(1, "ExportTreeName", ExportTreeName.c_str());
    TreeWriter = new ExRootTreeWriter(ExportFile, ExportTreeName.c_str());

    NewFile();

    Event->NewFile();

    InfoBranch = TreeWriter->NewBranch("Info", HInfoBranch::Class());

    // Import file
    string ImportPath = File->GetFilePath();
    ImportFile = new TFile(ImportPath.c_str());
    Print(1, "File", ImportPath);

    // Import tree
    string ImportTreeName = File->GetTreeName();
    ImportTree = (TTree *)ImportFile->Get(ImportTreeName.c_str());
    Print(1, "Tree", ImportTreeName);

    // TreeReader
    TreeReader = new ExRootTreeReader(ImportTree);
    EventSum = min((int)TreeReader->GetEntries(), EventNumberMax);

    ClonesArrays->UseBranches(TreeReader);

}


void HAnalysis::NewEvent()
{
    Print(2, "New Event");

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
    Print(1, "Clean Analysis");

    if (AnalysisNotEmpty) TreeWriter->Write();

    Event->CloseFile();
    CloseFile();

    ClonesArrays->ResetBranches();


//     delete TreeReader; // FIXME should get deleted here
//     Print(1, "All deleted");
    delete ImportTree;
    delete ImportFile;
    delete TreeWriter;


}


void HAnalysis::DeleteStudy()
{
    Print(1, "Clean Mva");

}


HAnalysis::~HAnalysis()
{

    Print(1, "Destructor");

    ExportFile->Close();

    EmptyFileVector();

    delete ExportFile;
    delete ClonesArrays;
    delete Event;



}

void HAnalysis::EmptyFileVector()
{

  for (const auto &File : FileVector) {

        delete File;

    }

    FileVector.clear();

}
