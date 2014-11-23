# include "HMvaBTagger.hh"

hhiggscpv::HMvaBTagger::HMvaBTagger()
{

    Print(HNotification , "Constructor");

    AnalysisName = "HiggsCpv";

    TaggerName = "BTagger";

    SignalNames = {"Bottom"};

    BackgroundNames = {"LightJet"};

    TestName = "Test";

    TestTreeNames = {"pp-bbtt-bblvlv-background", "pp-x0tt-bblvlv-even"};

    SignalTreeNames = TestTreeNames;

    BackgroundTreeNames = TestTreeNames;

    CandidateBranchName = "BTagger";

    WeightBranchName = "Info";

    SignalEfficiency = 0.5;

    Luminosity = 3000; // fb

    DoLatex = 1;

    BTagger = new HBottomBranch();

    DefineVariables();

}

hhiggscpv::HMvaBTagger::~HMvaBTagger()
{

    Print(HNotification , "Constructor");

    delete BTagger;

}

void hhiggscpv::HMvaBTagger::DefineVariables()
{

    Print(HNotification , "Define Variables",BTagger->Mass);

    Observables.push_back(NewObservable(&BTagger->VertexMass, "VertexMass"));
    Observables.push_back(NewObservable(&BTagger->Pt, "Pt"));
    Observables.push_back(NewObservable(&BTagger->Displacement, "Displacement"));
    Observables.push_back(NewObservable(&BTagger->Multipliticity, "Multipliticity"));
    Observables.push_back(NewObservable(&BTagger->DeltaR, "DeltaR"));

    Spectators.push_back(NewObservable(&BTagger->Mass, "Mass"));
    Spectators.push_back(NewObservable(&BTagger->Bottom, "Bottom"));
    
    Print(HNotification, "Variables defined");

}

float hhiggscpv::HMvaBTagger::GetBdt(TObject *Branch, TMVA::Reader *Reader)
{
    
    Print(HInformation, "Get Bdt", BdtMethodName);

    *BTagger = *static_cast<HBottomBranch *>(Branch);
    const float BdtEvaluation = Reader->EvaluateMVA(BdtMethodName);
    Print(HInformation, "BTagger Bdt", BdtEvaluation);
    
    return ((BdtEvaluation + 1.) / 2.);

}
