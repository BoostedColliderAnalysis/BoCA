# include "HMvaTop.hh"

hhiggscpv::HMvaTop::HMvaTop()
{

    Print(kNotification , "Constructor");

//     AnalysisName = "HiggsCpv";

    set_tagger_name("TopTagger");

//     SignalNames = {"Top"};

//     BackgroundNames = {"NotTop"};

//     TestName = "Test";

//     TestTreeNames = {"pp-bbtt-bblvlv-background", "pp-x0tt-bblvlv-even", "pp-x0tt-bblvlv-mix", "pp-x0tt-bblvlv-odd"};
//     TestTreeNames = {"pp-bbtt-bblvlv-background", "pp-x0tt-bblvlv-even"};

//     SignalTreeNames = {"pp-x0tt-bblvlv-even", "pp-x0tt-bblvlv-mix", "pp-x0tt-bblvlv-odd"};
//     SignalTreeNames = {"pp-x0tt-bblvlv-even"};

//     BackgroundTreeNames = TestTreeNames;

//     SetBranchName("Top");

//     SpectatorBranchName = "Lepton";

//     WeightBranchName = "Info";

//     SignalEfficiency = 0.5;

//     Luminosity = 3000; // fb

//     DoLatex = 1;

    Top = new HTopLeptonicBranch();

    DefineVariables();

}

hhiggscpv::HMvaTop::~HMvaTop()
{

    Print(kNotification , "Destructor");

    delete Top;

}

float hhiggscpv::HMvaTop::GetBdt(TObject *Branch, const TMVA::Reader &Reader){

  Print(kInformation, "Get Bdt",bdt_method_name());

    *Top = *static_cast<HTopLeptonicBranch*>(Branch);
    const float BdtEvaluation = const_cast<TMVA::Reader *>(&Reader)->EvaluateMVA(bdt_method_name());
    Print(kInformation,"BTagger Bdt",BdtEvaluation);

    return ((BdtEvaluation+1)/2);

}

void hhiggscpv::HMvaTop::DefineVariables()
{

    Print(kNotification , "Define Variables");

    AddVariable(Top->Mass, "Mass");
    AddVariable(Top->Pt, "Pt");
    AddVariable(Top->LeptonPt, "Pt");
    AddVariable(Top->DeltaPhi, "DeltaPhi");
    AddVariable(Top->DeltaRap, "DeltaRap");
    AddVariable(Top->DeltaR, "DeltaR");
    AddVariable(Top->Bdt, "BottomTag");

    AddSpectator(Top->Tag, "TopTag");

    Print(kNotification, "Variables defined");

}

