# include "HMvaHiggs.hh"

hhiggscpv::HMvaHiggs::HMvaHiggs()
{

    Print(HNotification , "Constructor");

    AnalysisName = "HiggsCpv";

    TaggerName = "HiggsTagger";

    SignalNames = {"Higgs"};

    BackgroundNames = {"NotHiggs"};

    TestName = "Test";

//     TestTreeNames = {"pp-bbtt-bblvlv-background", "pp-x0tt-bblvlv-even", "pp-x0tt-bblvlv-mix", "pp-x0tt-bblvlv-odd"};
    TestTreeNames = {"pp-bbtt-bblvlv-background", "pp-x0tt-bblvlv-even"};

//     SignalTreeNames = {"pp-x0tt-bblvlv-even", "pp-x0tt-bblvlv-mix", "pp-x0tt-bblvlv-odd"};
    SignalTreeNames = {"pp-x0tt-bblvlv-even"};

    BackgroundTreeNames = TestTreeNames;

    CandidateBranchName = "Higgs";

    SpectatorBranchName = "Lepton";

    WeightBranchName = "Info";

    SignalEfficiency = 0.5;

    Luminosity = 3000; // fb

    DoLatex = 1;

    Higgs = new HHiggsBranch();

    DefineVariables();

}

hhiggscpv::HMvaHiggs::~HMvaHiggs()
{

    Print(HNotification , "Destructor");

    delete Higgs;

}

float hhiggscpv::HMvaHiggs::GetBdt(TObject *Branch, TMVA::Reader *Reader){

    Print(HInformation, "Get Bdt",BdtMethodName);

    *Higgs = *static_cast<HHiggsBranch*>(Branch);
    const float BdtEvaluation = Reader->EvaluateMVA(BdtMethodName);
    Print(HInformation,"BTagger Bdt",BdtEvaluation);

    return ((BdtEvaluation+1)/2);

}

void hhiggscpv::HMvaHiggs::DefineVariables()
{

    Print(HNotification , "Define Variables");

    Observables.push_back(NewObservable(&Higgs->Mass, "Mass"));
    Observables.push_back(NewObservable(&Higgs->PtSum, "PtSum"));
    Observables.push_back(NewObservable(&Higgs->PtDiff, "PtDiff"));
    Observables.push_back(NewObservable(&Higgs->DeltaPhi, "DeltaPhi"));
    Observables.push_back(NewObservable(&Higgs->DeltaRap, "DeltaRap"));
    Observables.push_back(NewObservable(&Higgs->DeltaR, "DeltaR"));
    Observables.push_back(NewObservable(&Higgs->Pull1, "Pull1"));
    Observables.push_back(NewObservable(&Higgs->Pull2,"Pull2"));
    Observables.push_back(NewObservable(&Higgs->Pull, "Pull"));
    Observables.push_back(NewObservable(&Higgs->BottomBdt, "BottomTag"));

    Spectators.push_back(NewObservable(&Higgs->HiggsTag, "HiggsTag"));

    Print(HNotification, "Variables defined");

}

