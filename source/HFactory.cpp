# include "HFactory.hh"
# include "TMVA/Config.h"

hanalysis::HFactory::HFactory(Tagger &tagger) : tagger_(tagger) , factory_(tagger.tagger_name(), output_file(), factory_options())
{
//     DebugLevel = hanalysis::HObject::HDebug;
    Print(HNotification , "Constructor");
    AddVariables();
    PrepareTrainingAndTestTree(GetTrees());
    BookMethods();
    factory().TrainAllMethods();
    factory().TestAllMethods();
    factory().EvaluateAllMethods();
}

std::string hanalysis::HFactory::factory_options()
{
    return "!Color:!Silent";
}

TFile *hanalysis::HFactory::output_file() const
{
    const std::string factory_name = "Mva" + tagger().tagger_name();
    const std::string file_name = tagger().analysis_name() + "/" + factory_name + ".root";
    return TFile::Open(file_name.c_str(), "Recreate");
}

void hanalysis::HFactory::AddVariables()
{
    Print(HNotification , "Add Variables");
    TMVA::gConfig().GetIONames().fWeightFileDir = tagger().analysis_name();
    for (const auto & observable : tagger().observables())
        factory().AddVariable(observable.expression(), observable.title(), observable.unit(), observable.type());
    for (const auto & spectator : tagger().spectators())
        factory().AddSpectator(spectator.expression(), spectator.title(), spectator.unit(), spectator.type());
}

int hanalysis::HFactory::GetTrees()
{
    Print(HNotification , "Get Trees");
    int signal_number = 0;
    for (const auto & signal_name : tagger().GetSignalNames()) {
        std::string signal_file_name = tagger().analysis_name() + "/" + signal_name + ".root";
        if (gSystem->AccessPathName(signal_file_name.c_str())) Print(HError, "File not found", signal_file_name);
        TFile &signal_file = *TFile::Open(signal_file_name.c_str());
        Print(HNotification , "Signal File", signal_file.GetName(), tagger().GetSignalTreeNames().size());

        for (int tree_number : Range(tagger().GetSignalTreeNames().size())) {
            Print(HNotification , "signal Tree Name", tagger().GetSignalTreeNames()[tree_number]);
            signal_number += AddTree(signal_file, tagger().GetSignalTreeNames()[tree_number], 1);
        }
    }

    int background_number = 0;
    for (const auto & background_name : tagger().GetBackgroundNames()) {

        std::string background_file_name = tagger().analysis_name() + "/" + background_name + ".root";
        if (gSystem->AccessPathName(background_file_name.c_str())) Print(HError, "File not found", background_file_name);
        TFile &background_file = *TFile::Open(background_file_name.c_str());
        Print(HNotification , "Background File", background_file.GetName(), tagger().GetBackgroundTreeNames().size());

        for (const auto & background_tree_name : tagger().GetBackgroundTreeNames()) {
            Print(HNotification , "Background Tree Name", background_tree_name);
            background_number += AddTree(background_file, background_tree_name, 0);
        }
    }

    Print(HError, "Event Numbers", signal_number, background_number);
    return (std::min(signal_number, background_number) / 2);
}

int hanalysis::HFactory::AddTree(TFile &file, const std::string &tree_name, const bool signal)
{
    Print(HError , "Add Tree", tree_name);
    if (!file.GetListOfKeys()->Contains(tree_name.c_str()))return 0;

    TTree &tree = static_cast<TTree &>(*file.Get(tree_name.c_str()));

    Print(HError, "Branch Name", tagger().GetBranchName().c_str());
    tree.GetBranch(tagger().GetBranchName().c_str());
    ExRootTreeReader &tree_reader = *new ExRootTreeReader(&tree); // FIXME nasty hack with memeory leak; necessary because the tree reader destructor closes the file which makes it invisible for tmva; reimplment in a cleaner way!!

    TClonesArray &clones_array = *tree_reader.UseBranch(tagger().GetWeightBranchName().c_str());
    tree_reader.ReadEntry(0);
    const float crosssection = static_cast<HInfoBranch &>(*clones_array.First()).Crosssection / tree_reader.GetEntries(); // this takes care of the multiplicity
    Print(HNotification , "Weight", crosssection);

    if (signal) factory().AddSignalTree(&tree, crosssection);
    else factory().AddBackgroundTree(&tree, crosssection);

    int entries = 0;
    TClonesArray &event_clones_array = *tree_reader.UseBranch(tagger().GetBranchName().c_str());
    for (int entry = 0; entry < tree_reader.GetEntries(); ++entry) {
        tree_reader.ReadEntry(entry);
        entries += event_clones_array.GetEntries();
    }
    return entries;
}

void hanalysis::HFactory::PrepareTrainingAndTestTree(const int event_number)
{
    Print(HError , "PrepareTrainingAndTestTree");

    std::string number_options = "nTrain_Background=" + std::to_string(event_number) + ":nTest_Background=" + std::to_string(event_number) + ":nTrain_Signal=" + std::to_string(event_number) + ":nTest_Signal=" + std::to_string(event_number);

//     std::string TrainingAndTestOptions = "nTrain_Signal=0:nTrain_Background=0:SplitMode=Random:NormMode=NumEvents:!V";
    const std::string training_and_test_options = number_options + "";
    factory().PrepareTrainingAndTestTree(tagger().GetCut(), tagger().GetCut(), training_and_test_options);
}

void hanalysis::HFactory::BookMethods()
{

    Print(HNotification , "Book Methods");

//     const std::string CutOptions = "!H:!V:FitMethod=MC:EffSel:SampleSize=200000:VarProp=FSmart";
//     std::string CutOptions = "VarProp=FSmart:VarTransform=PCA";
//     const std::string CutOptions = "";

//     const std::string CutMethodName = Mva.CutMethodName + "_" + Mva.BackgroundName;

    //     factory().BookMethod(TMVA::Types::kCuts, Mva.GetCutMethodName(), CutOptions);

//     const std::string BdtOptions = "!H:!V:NTrees=1000:MinNodeSize=2.5%:BoostType=Grad:Shrinkage=0.10:UseBaggedBoost:BaggedSampleFraction=0.5:nCuts=20:MaxDepth=2";
    const std::string bdt_options =
//     "";
        "NTrees=1000:MinNodeSize=2.5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20";//:CreateMVAPdfs:DoBoostMonitor";
//     const std::string BdtOptions = "";

//     const std::string BdtMethodName = Mva.BdtMethodName + "_" + Mva.BackgroundName;

    factory().BookMethod(TMVA::Types::kBDT, tagger().BdtMethodName(), bdt_options);

}



