# include "HMvaHeavyHiggs.hh"

hheavyhiggs::HMva::HMva()
{

    Print(HNotification , "Constructor");

    AnalysisName = "HeavyHiggs";

    SignalNames = {"Signal"};

    BackgroundNames = {"Background"};

    TestName = "Test";

    SignalTreeNames = {"Signal_5f"};

    BackgroundTreeNames = {"5k_Pt20"};

    TestTreeNames = {"Signal_5f","5k_Pt20"};

    CandidateBranchName = "HeavyHiggs";

    WeightBranchName = "Info";

    SignalEfficiency = 0.5;

    Luminosity = 3000; // fb

    DoLatex = 0;

    HeavyHiggs = new HHeavyHiggsBranch();

    DefineVariables();

}

hheavyhiggs::HMva::~HMva()
{

    Print(HNotification , "Constructor");

    delete HeavyHiggs;

}

void hheavyhiggs::HMva::DefineVariables()
{

    Print(HNotification , "Define Variables");

    Observables.push_back(NewObservable(&HeavyHiggs->TopDeltaRap, "DeltaRap"));
    Observables.push_back(NewObservable(&HeavyHiggs->TopDeltaPhi, "DeltaPhi"));

    Print(HNotification,"Variables defined");

}


void hheavyhiggs::HMva::ApplyBdt(const ExRootTreeReader *const TreeReader, const std::string TreeName, const TFile *const ExportFile, TMVA::Reader * Reader)
{
}


HReaderStruct hheavyhiggs::HMva::CutLoop(const ExRootTreeReader *const TreeReader, HReaderStruct &ReaderStruct)
{

}

