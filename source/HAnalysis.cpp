# include "HAnalysis.hh"

HAnalysis::HAnalysis()
{

    Print(1, "Constructor");

//     DebugLevel=4;

}

void HAnalysis::AnalysisLoop()
{

    Print(1, "Analysis Loop");

    for (const auto & StudyName : GetStudyNames()) {

        Print(1, "Analysing Mva Sample", StudyName);

        HClonesArray * const ClonesArrays = GetClonesArrays(StudyName);

        HEvent * const Event = GetEvent(StudyName);

        TFile * const ExportFile = GetExportFile(StudyName);

        for (const auto &File : GetFiles(StudyName)) {

            SubLoop(ExportFile, File, ClonesArrays, Event, StudyName);

        }
        
        ExportFile->Close();

        delete ExportFile;

        delete Event;

        delete ClonesArrays;

    }
    Print(1, "All Samples analysed");



}


void HAnalysis::SubLoop(TFile * const ExportFile, const HFile * const File, HClonesArray * const ClonesArrays, HEvent * const Event, const string StudyName)
{

    bool AnalysisNotEmpty = 0;

    ExRootTreeWriter * const TreeWriter = GetTreeWriter(ExportFile, File->Title());

    ExRootTreeBranch *const InfoBranch = TreeWriter->NewBranch("Info", HInfoBranch::Class());

    const ExRootTreeReader *const TreeReader = GetTreeReader(File, ClonesArrays);

    ExRootProgressBar *const ProgressBar = new ExRootProgressBar(GetEventSum(TreeReader));

    for (const int EventNumber : HRange(GetEventSum(TreeReader))) {

//         AnalysisNotEmpty = AnalysisNotEmpty | 
//         MiniLoop(TreeReader, TreeWriter, InfoBranch,ProgressBar, Event, File, ClonesArrays, StudyName, EventNumber);
        
        
        Event->NewEvent(ClonesArrays);
        
        const_cast<ExRootTreeReader*>(TreeReader)->ReadEntry(EventNumber);
        
        const bool Successfull = Analysis(Event, StudyName);
        
        if (Successfull) {
            
            AnalysisNotEmpty = 1;
            
            HInfoBranch *Info = static_cast<HInfoBranch *>(InfoBranch->NewEntry());
            Info->Crosssection = File->Crosssection;
            Info->Error = File->Error;
            Info->EventNumber = GetEventSum(TreeReader);
            
            TreeWriter->Fill();
            
        }
        
        TreeWriter->Clear();
        

    }
    ProgressBar->Finish();
    
    delete ProgressBar;

    Print(1, "All Events analysed", GetEventSum(TreeReader));

    if (AnalysisNotEmpty) TreeWriter->Write();
    
    CloseFile();

    ClonesArrays->ResetBranches();

    delete TreeReader;

    delete InfoBranch;

//     delete TreeWriter;

    if (DebugLevel > 0) cout << endl;


}




HClonesArray *HAnalysis::GetClonesArrays(const string StudyName) const
{

    Print(1, "Get Clones Arrays");
    
    vector<HFile*> Files = GetFiles(StudyName); 

    HClonesArray *ClonesArrays;

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
    
    DeleteFiles(Files);

    return ClonesArrays;

}




HEvent *HAnalysis::GetEvent(const string StudyName) const
{

    Print(1, "Get Event");

    vector<HFile*> Files = GetFiles(StudyName); 
    
    HEvent *Event;

    if (Files.front()->GetTreeName() == "Delphes") {

        Event = new HEventDelphes();

    } else if (Files.front()->GetTreeName() == "LHEF") {

        Event = new HEventParton();

    } else if (Files.front()->GetTreeName() == "LHCO") {

        Event = new HEventPgs();

    } else {

        Print(0, "unknown Tree String", Files.front()->GetTreeName());

    }
    
    DeleteFiles(Files);

    return Event;

}



TFile *HAnalysis::GetExportFile(const string StudyName) const
{

    const string ExportName = GetProjectName() + "/" + StudyName + ".root";
    TFile *ExportFile = new TFile(ExportName.c_str(), "Recreate");
    Print(1, "ExportFile", ExportName);

    return ExportFile;

}


ExRootTreeWriter *HAnalysis::GetTreeWriter(TFile *const ExportFile, const string ExportTreeName)
{

    Print(1, "ExportTreeName", ExportTreeName.c_str());

    ExRootTreeWriter * const TreeWriter = new ExRootTreeWriter(ExportFile, ExportTreeName.c_str());

    NewBranches(TreeWriter);

    return TreeWriter;

}


ExRootTreeReader *HAnalysis::GetTreeReader(const HFile * const File, HClonesArray *const ClonesArrays)
{

    // Import file
    const string ImportPath = File->GetFilePath();
    TFile *ImportFile = new TFile(ImportPath.c_str());
//     TFile ImportFile = TFile(ImportPath.c_str());
    Print(1, "File", ImportPath);

    // Import tree
    const string ImportTreeName = File->GetTreeName();
    TTree *ImportTree = (TTree *)ImportFile->Get(ImportTreeName.c_str());
//     TTree ImportTree = (TTree)ImportFile->Get(ImportTreeName.c_str());
    Print(1, "Tree", ImportTreeName);

    // TreeReader
    ExRootTreeReader *TreeReader = new ExRootTreeReader(ImportTree);

    ClonesArrays->UseBranches(TreeReader);


//     delete ImportFile; // FIXME Possible?

//     delete ImportTree; // FIXME Possible?

    return TreeReader;

}


HAnalysis::~HAnalysis()
{

    Print(1, "Destructor");

}

void HAnalysis::DeleteFiles(const std::vector< HFile * > Files) const
{

    for (const auto & File : Files) {

        delete File;

    }

}
