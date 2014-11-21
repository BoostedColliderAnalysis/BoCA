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

    Print(HNotification , "Define Variables");

    Observables.push_back(NewObservable(&BTagger->Mass, "BTagger.VertexMass", "VertexMass", "GeV"));
//    Observables.push_back(NewObservable(&Candidate->JetMass, "BTagger.JetMass", "JetMass", "GeV"));
    Observables.push_back(NewObservable(&BTagger->Multipliticity, "BTagger.VertexNumber", "VertexNumber"));
    Observables.push_back(NewObservable(&BTagger->Displacement, "BTagger.Vertex", "Vertex"));

    Print(HNotification, "Variables defined");

}

float hhiggscpv::HMvaBTagger::GetBdt(TObject *Branch, TMVA::Reader *Reader)
{

    Print(HInformation, "Get Bdt", BdtMethodName);

    BTagger = static_cast<HBTaggerBranch *>(Branch);
    Print(HInformation, "Mass", BTagger->Mass);

    const float BdtEvaluation = Reader->EvaluateMVA(BdtMethodName);

    Print(HInformation, "BTagger Bdt", BdtEvaluation);

    return ((BdtEvaluation + 1.) / 2.);

}
