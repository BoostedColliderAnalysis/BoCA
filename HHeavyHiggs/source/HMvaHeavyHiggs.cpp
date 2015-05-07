# include "HMvaHeavyHiggs.hh"

hheavyhiggs::HMva::HMva()
{

    Print(HNotification , "Constructor");

    set_tagger_name("HeavyHiggs");

//     SignalNames = {"Signal"};

//     BackgroundNames = {"Background"};

//     TestName = "Test";

//     SignalTreeNames = {"Signal_5f"};

//     BackgroundTreeNames = {"5k_Pt20"};

//     TestTreeNames = {"Signal_5f","5k_Pt20"};

//     SetBranchName("HeavyHiggs");

//     WeightBranchName = "Info";

//     SignalEfficiency = 0.5;

//     Luminosity = 3000; // fb

//     DoLatex = 0;

    HeavyHiggs = new HHeavyHiggsLeptonicBranch();

    DefineVariables();

}

hheavyhiggs::HMva::~HMva()
{

    Print(HNotification , "Constructor");

    delete HeavyHiggs;

}

void hheavyhiggs::HMva::DefineVariables()
{

    Print(HNotification , "Define Variables");

    AddVariable(HeavyHiggs->DeltaRap, "DeltaRap");
    AddVariable(HeavyHiggs->DeltaPhi, "DeltaPhi");

    Print(HNotification,"Variables defined");

}


// void hheavyhiggs::HMva::ApplyBdt(const ExRootTreeReader *const TreeReader, const std::string TreeName, const TFile *const ExportFile, const TMVA::Reader &Reader)
// {
// }


// ReaderStruct hheavyhiggs::HMva::CutLoop(const ExRootTreeReader *const TreeReader, ReaderStruct &ReaderStruct)
// {
//
// }

