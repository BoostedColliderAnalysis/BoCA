# include "HMvaBottom.hh"

hhiggscpv::HMvaBottom::HMvaBottom()
{

    Print(HNotification , "Constructor");

    set_tagger_name("Bottom");

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

    AddVariable(BTagger->VertexMass, "VertexMass");
    AddVariable(BTagger->Pt, "Pt");
    AddVariable(BTagger->MaxDisplacement, "Displacement");
    AddVariable(BTagger->Multipliticity, "Multipliticity");
    AddVariable(BTagger->DeltaR, "DeltaR");

    AddSpectator(BTagger->Mass, "Mass");
    AddSpectator(BTagger->Tag, "Tag");

    Print(HNotification, "Variables defined");

}

float hhiggscpv::HMvaBottom::GetBdt(TObject *Branch, const TMVA::Reader &Reader)
{

  Print(HInformation, "Get Bdt", bdt_method_name());

    *BTagger = *static_cast<HBottomBranch *>(Branch);
    const float BdtEvaluation = const_cast<TMVA::Reader *>(&Reader)->EvaluateMVA(bdt_method_name());
    Print(HInformation, "BTagger Bdt", BdtEvaluation);

    return ((BdtEvaluation + 1.) / 2.);

}
