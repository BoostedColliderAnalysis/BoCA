# include "HMvaPairs.hh"

hhiggscpv::HMvaPair::HMvaPair()
{

    Print(HNotification , "Constructor");

    AnalysisName = "HiggsCpv";

    TaggerName = "PairTagger";

    SignalNames = {"Higgs"};

    BackgroundNames = {"Pair"};

    TestName = "JetPair";

//     TestTreeNames = {"pp-bbtt-bblvlv-background", "pp-x0tt-bblvlv-even", "pp-x0tt-bblvlv-mix", "pp-x0tt-bblvlv-odd"};
    TestTreeNames = {"pp-bbtt-bblvlv-background", "pp-x0tt-bblvlv-even"};

//     SignalTreeNames = {"pp-x0tt-bblvlv-even", "pp-x0tt-bblvlv-mix", "pp-x0tt-bblvlv-odd"};
    SignalTreeNames = {"pp-x0tt-bblvlv-even"};

    BackgroundTreeNames = TestTreeNames;

    CandidateBranchName = "Pair";

    SpectatorBranchName = "Lepton";

    WeightBranchName = "Info";

    SignalEfficiency = 0.5;

    Luminosity = 3000; // fb

    DoLatex = 1;

    Pair = new HPairBranch();

    DefineVariables();

}

hhiggscpv::HMvaPair::~HMvaPair()
{

    Print(HNotification , "Destructor");

    delete Pair;

}

float hhiggscpv::HMvaPair::GetBdt(TObject *Branch, TMVA::Reader *Reader){

    Print(HInformation, "Get Bdt",BdtMethodName);

    *Pair = *static_cast<HPairBranch*>(Branch);

    Print(HInformation, "Mass", Pair->Mass);

    const float BdtEvaluation = Reader->EvaluateMVA(BdtMethodName);

    Print(HInformation,"BTagger Bdt",BdtEvaluation);

    return ((BdtEvaluation+1)/2);

}

void hhiggscpv::HMvaPair::DefineVariables()
{

    Print(HNotification , "Define Variables");

    Observables.push_back(NewObservable(&Pair->Mass, "Mass"));
    Observables.push_back(NewObservable(&Pair->Pt, "Pt"));
    Observables.push_back(NewObservable(&Pair->DeltaPhi, "DeltaPhi"));
    Observables.push_back(NewObservable(&Pair->DeltaEta, "DeltaEta"));
    Observables.push_back(NewObservable(&Pair->DeltaR, "DeltaR"));
//     Observables.push_back(NewObservable(&Pair->Pull1, "Pull1"));
//     Observables.push_back(NewObservable(&Pair->Pull2,"Pull2"));
//     Observables.push_back(NewObservable(&Pair->Pull, "Pull"));
    Observables.push_back(NewObservable(&Pair->BTag, "BTag"));

//     Spectators.push_back(NewObservable(&Pair->HiggsTag, "Pair.HiggsTag", "Higgs Tag"));
//     Spectators.push_back(NewObservable(&Pair->TopTag, "Pair.TopTag", "Top Tag"));

    Print(HNotification, "Variables defined");

}

