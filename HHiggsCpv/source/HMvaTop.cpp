# include "HMvaTop.hh"

hhiggscpv::HMvaTop::HMvaTop()
{

    Print(HNotification , "Constructor");

//     AnalysisName = "HiggsCpv";

    SetTaggerName("TopTagger");

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

    Print(HNotification , "Destructor");

    delete Top;

}

float hhiggscpv::HMvaTop::GetBdt(TObject *Branch, const TMVA::Reader &Reader){

  Print(HInformation, "Get Bdt",bdt_method_name());

    *Top = *static_cast<HTopLeptonicBranch*>(Branch);
    const float BdtEvaluation = const_cast<TMVA::Reader *>(&Reader)->EvaluateMVA(bdt_method_name());
    Print(HInformation,"BTagger Bdt",BdtEvaluation);

    return ((BdtEvaluation+1)/2);

}

void hhiggscpv::HMvaTop::DefineVariables()
{

    Print(HNotification , "Define Variables");

    AddObservable(Top->Mass, "Mass");
    AddObservable(Top->Pt, "Pt");
    AddObservable(Top->LeptonPt, "Pt");
    AddObservable(Top->DeltaPhi, "DeltaPhi");
    AddObservable(Top->DeltaRap, "DeltaRap");
    AddObservable(Top->DeltaR, "DeltaR");
    AddObservable(Top->Bdt, "BottomTag");

    AddSpectator(Top->Tag, "TopTag");

    Print(HNotification, "Variables defined");

}

