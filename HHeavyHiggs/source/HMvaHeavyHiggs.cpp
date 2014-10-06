# include "HMvaHeavyHiggs.hh"

HMvaHeavyHiggs::HMvaHeavyHiggs()
{

    Print(0 , "Constructor");

    AnalysisName = "HeavyHiggs";

    SignalVector = {"Signal"};

    BackgroundVector = {"Background"};

    TestName = "Test";

    SignalTreeVector = {"Signal_5f"};

    BackgroundTreeVector = {"5k_Pt20"};

    TestTreeVector = {"Signal_5f","5k_Pt20"};

    CandidateBranchName = "HeavyHiggs";

    WeightBranchName = "Info";

    SignalEfficiency = 0.5;

    Luminosity = 3000; // fb

    Latex = 0;

    HeavyHiggs = new HHeavyHiggsBranch();

    DefineVariables();

}

HMvaHeavyHiggs::~HMvaHeavyHiggs()
{

    Print(0 , "Constructor");
    
    delete HeavyHiggs;

}

void HMvaHeavyHiggs::DefineVariables()
{

    Print(0 , "Define Variables");

    ObservableVector.push_back(NewObservable(&HeavyHiggs->BottomDeltaEta, "HeavyHiggs.BottomDeltaEta", "BottomeDeltaEta"));
    ObservableVector.push_back(NewObservable(&HeavyHiggs->BottomDeltaPhi, "HeavyHiggs.BottomDeltaPhi", "BottomeDeltaPhi"));

    Print(0,"Variables defined");

}
