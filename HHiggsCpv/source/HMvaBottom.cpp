# include "HMvaBottom.hh"

hhiggscpv::HMvaBottom::HMvaBottom()
{

    Print(HNotification , "Constructor");

    SetTaggerName("Bottom");

//     SignalNames = {"Bottom"};

//     BackgroundNames = {"NotBottom"};

//     TestName = "Test";

//     TestTreeNames = {"pp-bbtt-bblvlv-background", "pp-x0tt-bblvlv-even"};

//     SignalTreeNames = TestTreeNames;

//     BackgroundTreeNames = TestTreeNames;

//     SetBranchName("Bottom");

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

    AddObservable(BTagger->VertexMass, "VertexMass");
    AddObservable(BTagger->Pt, "Pt");
    AddObservable(BTagger->MaxDisplacement, "Displacement");
    AddObservable(BTagger->Multipliticity, "Multipliticity");
    AddObservable(BTagger->DeltaR, "DeltaR");

    AddSpectator(BTagger->Mass, "Mass");
    AddSpectator(BTagger->Tag, "Tag");

    Print(HNotification, "Variables defined");

}

float hhiggscpv::HMvaBottom::GetBdt(TObject *Branch, const TMVA::Reader &Reader)
{

  Print(HInformation, "Get Bdt", BdtMethodName());

    *BTagger = *static_cast<HBottomBranch *>(Branch);
    const float BdtEvaluation = const_cast<TMVA::Reader *>(&Reader)->EvaluateMVA(BdtMethodName());
    Print(HInformation, "BTagger Bdt", BdtEvaluation);

    return ((BdtEvaluation + 1.) / 2.);

}
