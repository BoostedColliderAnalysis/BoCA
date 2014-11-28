# include "HMvaEvent.hh"

hheavyhiggs::HMvaEvent::HMvaEvent()
{

    Print(HNotification , "Constructor");

    AnalysisName = "HHeavyHiggs";

    TaggerName = "EventTagger";

    SignalNames = {"Signal"};

    BackgroundNames = {"Background"};

    TestName = "Test";

//     SignalTreeNames = {"pp-x0tt-bblvlv-even", "pp-x0tt-bblvlv-mix", "pp-x0tt-bblvlv-odd"};
    SignalTreeNames = {"pp-x0tt-bblvlv-even"};

    BackgroundTreeNames = {"pp-bbtt-bblvlv-background"};

//     TestTreeNames = {"pp-bbtt-bblvlv-background", "pp-x0tt-bblvlv-even", "pp-x0tt-bblvlv-mix", "pp-x0tt-bblvlv-odd"};
    TestTreeNames = {"pp-bbtt-bblvlv-background", "pp-x0tt-bblvlv-even"};

    CandidateBranchName = "Event";

    SpectatorBranchName = "Lepton";

    WeightBranchName = "Info";

    SignalEfficiency = 0.5;

    Luminosity = 3000; // fb

    DoLatex = 1;

    EventBranch = new hheavyhiggs::HEventBranch();

    DefineVariables();

}

hheavyhiggs::HMvaEvent::~HMvaEvent()
{

    Print(HNotification , "Constructor");

    delete EventBranch;

}

void hheavyhiggs::HMvaEvent::DefineVariables()
{

    Print(HNotification , "Define Variables");

    Observables.push_back(NewObservable(&EventBranch->ScalarHt, "ScalarHt"));
    Observables.push_back(NewObservable(&EventBranch->JetNumber, "JetNumber"));
    Observables.push_back(NewObservable(&EventBranch->BottomNumber, "BottomNumber"));
    Observables.push_back(NewObservable(&EventBranch->LeptonNumber, "LeptonNumber"));
    Observables.push_back(NewObservable(&EventBranch->HeavyParticleTag, "HeavyParticleTag"));
    Observables.push_back(NewObservable(&EventBranch->DeltaEta, "DeltaEta"));
    Observables.push_back(NewObservable(&EventBranch->DeltaPhi, "DeltaPhi"));
    Observables.push_back(NewObservable(&EventBranch->DeltaR, "DeltaR"));

    Spectators.push_back(NewObservable(&EventBranch->Signal, "Signal"));

    Print(HNotification, "Variables defined");

}