# include "HMvaTop.hh"

hhiggscpv::HMvaTop::HMvaTop()
{

    Print(HNotification , "Constructor");

    AnalysisName = "HiggsCpv";

    TaggerName = "TopTagger";

    SignalNames = {"Top"};

    BackgroundNames = {"NotTop"};

    TestName = "Test";

//     TestTreeNames = {"pp-bbtt-bblvlv-background", "pp-x0tt-bblvlv-even", "pp-x0tt-bblvlv-mix", "pp-x0tt-bblvlv-odd"};
    TestTreeNames = {"pp-bbtt-bblvlv-background", "pp-x0tt-bblvlv-even"};

//     SignalTreeNames = {"pp-x0tt-bblvlv-even", "pp-x0tt-bblvlv-mix", "pp-x0tt-bblvlv-odd"};
    SignalTreeNames = {"pp-x0tt-bblvlv-even"};

    BackgroundTreeNames = TestTreeNames;

    CandidateBranchName = "Top";

    SpectatorBranchName = "Lepton";

    WeightBranchName = "Info";

    SignalEfficiency = 0.5;

    Luminosity = 3000; // fb

    DoLatex = 1;

    Top = new HLeptonicTopBranch();

    DefineVariables();

}

hhiggscpv::HMvaTop::~HMvaTop()
{

    Print(HNotification , "Destructor");

    delete Top;

}

float hhiggscpv::HMvaTop::GetBdt(TObject *Branch, TMVA::Reader *Reader){

    Print(HInformation, "Get Bdt",BdtMethodName);

    *Top = *static_cast<HLeptonicTopBranch*>(Branch);
    const float BdtEvaluation = Reader->EvaluateMVA(BdtMethodName);
    Print(HInformation,"BTagger Bdt",BdtEvaluation);

    return ((BdtEvaluation+1)/2);

}

void hhiggscpv::HMvaTop::DefineVariables()
{

    Print(HNotification , "Define Variables");

    Observables.push_back(NewObservable(&Top->Mass, "Mass"));
    Observables.push_back(NewObservable(&Top->JetPt, "Pt"));
    Observables.push_back(NewObservable(&Top->LeptonPt, "Pt"));
    Observables.push_back(NewObservable(&Top->DeltaPhi, "DeltaPhi"));
    Observables.push_back(NewObservable(&Top->DeltaRap, "DeltaRap"));
    Observables.push_back(NewObservable(&Top->DeltaR, "DeltaR"));
    Observables.push_back(NewObservable(&Top->BottomBdt, "BottomTag"));

    Spectators.push_back(NewObservable(&Top->TopTag, "TopTag"));

    Print(HNotification, "Variables defined");

}

