# include "HMvaHiggs.hh"

hhiggscpv::HMvaHiggs::HMvaHiggs()
{

    Print(HNotification , "Constructor");

    set_tagger_name("HiggsCpv");

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

  Print(HInformation, "Get Bdt",bdt_method_name());

    *Higgs = *static_cast<HHiggsBranch*>(Branch);
    const float BdtEvaluation = const_cast<TMVA::Reader *>(&Reader)->EvaluateMVA(bdt_method_name());
    Print(HInformation,"BTagger Bdt",BdtEvaluation);

    return ((BdtEvaluation+1)/2);

}

void hhiggscpv::HMvaHiggs::DefineVariables()
{

    Print(HNotification , "Define Variables");

    AddVariable(Higgs->Mass, "Mass");
    AddVariable(Higgs->PtSum, "PtSum");
    AddVariable(Higgs->PtDiff, "PtDiff");
    AddVariable(Higgs->DeltaPhi, "DeltaPhi");
    AddVariable(Higgs->DeltaRap, "DeltaRap");
    AddVariable(Higgs->DeltaR, "DeltaR");
    AddVariable(Higgs->Pull1, "Pull1");
    AddVariable(Higgs->Pull2,"Pull2");
    AddVariable(Higgs->Pull, "Pull");
    AddVariable(Higgs->BottomBdt, "BottomTag");

    AddSpectator(Higgs->HiggsTag, "HiggsTag");

    Print(HNotification, "Variables defined");

}

