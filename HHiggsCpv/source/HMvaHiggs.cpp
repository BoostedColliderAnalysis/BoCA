# include "HMvaHiggs.hh"

hhiggscpv::HMvaHiggs::HMvaHiggs()
{

    Print(HNotification , "Constructor");

    SetTaggerName("HiggsCpv");

//     TaggerName = "HiggsTagger";

//     SignalNames = {"Higgs"};

//     BackgroundNames = {"NotHiggs"};

//     TestName = "Test";

//     TestTreeNames = {"pp-bbtt-bblvlv-background", "pp-x0tt-bblvlv-even", "pp-x0tt-bblvlv-mix", "pp-x0tt-bblvlv-odd"};
//     TestTreeNames = {"pp-bbtt-bblvlv-background", "pp-x0tt-bblvlv-even"};

//     SignalTreeNames = {"pp-x0tt-bblvlv-even", "pp-x0tt-bblvlv-mix", "pp-x0tt-bblvlv-odd"};
//     SignalTreeNames = {"pp-x0tt-bblvlv-even"};

//     BackgroundTreeNames = TestTreeNames;

//     SetBranchName("Higgs");

//     SpectatorBranchName = "Lepton";

//     WeightBranchName = "Info";

//     SignalEfficiency = 0.5;

//     Luminosity = 3000; // fb

//     DoLatex = 1;

    Higgs = new HHiggsBranch();

    DefineVariables();

}

hhiggscpv::HMvaHiggs::~HMvaHiggs()
{

    Print(HNotification , "Destructor");

    delete Higgs;

}

float hhiggscpv::HMvaHiggs::GetBdt(TObject *Branch, const TMVA::Reader &Reader){

  Print(HInformation, "Get Bdt",BdtMethodName());

    *Higgs = *static_cast<HHiggsBranch*>(Branch);
    const float BdtEvaluation = const_cast<TMVA::Reader *>(&Reader)->EvaluateMVA(BdtMethodName());
    Print(HInformation,"BTagger Bdt",BdtEvaluation);

    return ((BdtEvaluation+1)/2);

}

void hhiggscpv::HMvaHiggs::DefineVariables()
{

    Print(HNotification , "Define Variables");

    AddObservable(Higgs->Mass, "Mass");
    AddObservable(Higgs->PtSum, "PtSum");
    AddObservable(Higgs->PtDiff, "PtDiff");
    AddObservable(Higgs->DeltaPhi, "DeltaPhi");
    AddObservable(Higgs->DeltaRap, "DeltaRap");
    AddObservable(Higgs->DeltaR, "DeltaR");
    AddObservable(Higgs->Pull1, "Pull1");
    AddObservable(Higgs->Pull2,"Pull2");
    AddObservable(Higgs->Pull, "Pull");
    AddObservable(Higgs->BottomBdt, "BottomTag");

    AddSpectator(Higgs->HiggsTag, "HiggsTag");

    Print(HNotification, "Variables defined");

}

