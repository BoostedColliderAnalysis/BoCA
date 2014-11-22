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

    BTagger = new HBTaggerBranch();

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

    Observables.push_back(NewObservable(&BTagger->Mass, "Mass"));
    Observables.push_back(NewObservable(&BTagger->Multipliticity, "Multipliticity"));
    Observables.push_back(NewObservable(&BTagger->Displacement, "Displacement"));

    Print(HNotification, "Variables defined");

}

float hhiggscpv::HMvaBTagger::GetBdt(TObject *Branch, TMVA::Reader *Reader)
{
    
    Print(HInformation, "Get Bdt", BdtMethodName);

    *BTagger = *static_cast<HBTaggerBranch *>(Branch);
    Print(HInformation, "Mass", BTagger->Mass);

    const float BdtEvaluation = Reader->EvaluateMVA(BdtMethodName);

    Print(HInformation, "BTagger Bdt", BdtEvaluation);

    return ((BdtEvaluation + 1.) / 2.);

}
