# include "HMvaBottom.hh"

hhiggscpv::HMvaBottom::HMvaBottom()
{

    Print(HNotification , "Constructor");

    AnalysisName = "HiggsCpv";

    TaggerName = "Bottom";

    SignalNames = {"Bottom"};

    BackgroundNames = {"NotBottom"};

    TestName = "Test";

    TestTreeNames = {"pp-bbtt-bblvlv-background", "pp-x0tt-bblvlv-even"};

    SignalTreeNames = TestTreeNames;

    BackgroundTreeNames = TestTreeNames;

    EventBranchName = "Bottom";

    BTagger = new HBottomBranch();

    DefineVariables();

}

hhiggscpv::HMvaBottom::~HMvaBottom()
{

    Print(HNotification , "Constructor");

    delete BTagger;

}

void hhiggscpv::HMvaBottom::DefineVariables()
{

    Print(HNotification , "Define Variables",BTagger->Mass);

    Observables.push_back(NewObservable(&BTagger->VertexMass, "VertexMass"));
    Observables.push_back(NewObservable(&BTagger->Pt, "Pt"));
    Observables.push_back(NewObservable(&BTagger->MaxDisplacement, "Displacement"));
    Observables.push_back(NewObservable(&BTagger->Multipliticity, "Multipliticity"));
    Observables.push_back(NewObservable(&BTagger->DeltaR, "DeltaR"));

    Spectators.push_back(NewObservable(&BTagger->Mass, "Mass"));
    Spectators.push_back(NewObservable(&BTagger->Tag, "Tag"));

    Print(HNotification, "Variables defined");

}

float hhiggscpv::HMvaBottom::GetBdt(TObject *Branch, const TMVA::Reader &Reader)
{

    Print(HInformation, "Get Bdt", BdtMethodName);

    *BTagger = *static_cast<HBottomBranch *>(Branch);
    const float BdtEvaluation = const_cast<TMVA::Reader *>(&Reader)->EvaluateMVA(BdtMethodName);
    Print(HInformation, "BTagger Bdt", BdtEvaluation);

    return ((BdtEvaluation + 1.) / 2.);

}
