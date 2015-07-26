#include "Factory.hh"
#include "TSystem.h"
#include "TMVA/Config.h"
#include "TClonesArray.h"
#include "exroot/ExRootAnalysis.hh"
#include "TFile.h"
#include "Branches.hh"
#include "Predicate.hh"
#include "TMVA/MethodBDT.h"
#include "Debug.hh"

namespace analysis {

Factory::Factory(Tagger& tagger) : tagger_(tagger) , factory_(tagger.Name(), output_file(), factory_options())
{
    Error();
    AddVariables();
    PrepareTrainingAndTestTree(GetTrees());
//     TMVA::MethodBDT & method =
    BookMethods();
//     std::vector<double> importances = method.GetVariableImportance();
//     for(const auto & importance : importances) Error(importance);
    factory().TrainAllMethods();
    factory().TestAllMethods();
    factory().EvaluateAllMethods();
}

std::string Factory::factory_options()
{
    return "!Color:!Silent";
}

TFile* Factory::output_file() const
{
    return TFile::Open(tagger().FactoryFileName().c_str(), "Recreate");
}

void Factory::AddVariables()
{
    Note("Add Variables");
    TMVA::gConfig().GetIONames().fWeightFileDir = tagger().AnalysisName();
    TMVA::gConfig().GetIONames().fWeightFileExtension = tagger().WeightFileExtension();
    for (const auto& observable : tagger().Variables())
        factory().AddVariable(observable.expression(), observable.title(), observable.unit(), observable.type());
    for (const auto& spectator : tagger().Spectators())
        factory().AddSpectator(spectator.expression(), spectator.title(), spectator.unit(), spectator.type());
}

long Factory::GetTrees()
{
    Note();
    Note(tagger().SignalFileName(Stage::trainer));
    if (gSystem->AccessPathName(tagger().SignalFileName(Stage::trainer).c_str()))
      Error("File not found", tagger().SignalFileName(Stage::trainer));
    TFile& signal_file = *TFile::Open(tagger().SignalFileName(Stage::trainer).c_str());
    Note(signal_file.GetName(), tagger().SignalTreeNames().size());
    long signal_number = 0;
    for (const auto& tree_number : Range(tagger().SignalTreeNames().size())) {
      Note("signal Tree Name", tagger().SignalTreeNames().at(tree_number));
        signal_number += AddTree(signal_file, tagger().SignalTreeNames().at(tree_number), Tag::signal);
    }
    Note(tagger().BackgroundFileName(Stage::trainer));
    if (gSystem->AccessPathName(tagger().BackgroundFileName(Stage::trainer).c_str()))
      Error("File not found", tagger().BackgroundFileName(Stage::trainer));
    TFile& background_file = *TFile::Open(tagger().BackgroundFileName(Stage::trainer).c_str());
    Note(background_file.GetName(), tagger().BackgroundFileName(Stage::trainer));
    long background_number = 0;
    for (const auto& background_tree_name : tagger().BackgroundTreeNames()) {
        Note(background_tree_name);
        background_number += AddTree(background_file, background_tree_name, Tag::background);
    }
    Error(signal_number, background_number);
    return std::min(signal_number, background_number) / 2;
}

long Factory::AddTree(TFile& file, const std::string& tree_name, Tag tag)
{
    Error(tree_name);
    if (!file.GetListOfKeys()->Contains(tree_name.c_str()))
        return 0;
    TTree& tree = static_cast<TTree&>(*file.Get(tree_name.c_str()));
    Error("Branch Name", tagger().BranchName(Stage::trainer).c_str());
    tree.GetBranch(tagger().BranchName(Stage::trainer).c_str());
    exroot::TreeReader& tree_reader = *new exroot::TreeReader(&tree); // FIXME nasty hack with memeory leak; necessary because the tree reader destructor closes the file which makes it invisible for tmva; reimplment in a cleaner way!!
    TClonesArray& clones_array = *tree_reader.UseBranch(tagger().WeightBranchName().c_str());
    tree_reader.ReadEntry(0);
    float crosssection = static_cast<InfoBranch&>(*clones_array.First()).Crosssection / tree_reader.GetEntries();  // this takes care of the multiplicity
    Note("Weight", crosssection);
    switch (tag) {
    case Tag::signal :
        factory().AddSignalTree(&tree, crosssection);
        break;
    case Tag::background :
        factory().AddBackgroundTree(&tree, crosssection);
        break;
    }
    long entries = 0;
    TClonesArray& event_clones_array = *tree_reader.UseBranch(tagger().BranchName(Stage::trainer).c_str());
    for (const auto& entry : Range(tree_reader.GetEntries())) {
        tree_reader.ReadEntry(entry);
        entries += event_clones_array.GetEntries();
    }
    return entries;
}

void Factory::PrepareTrainingAndTestTree(long event_number)
{
    Error("PrepareTrainingAndTestTree");
    std::string number_options = "nTrain_Background=" + std::to_string(event_number) + ":nTest_Background=" + std::to_string(event_number) + ":nTrain_Signal=" + std::to_string(event_number) + ":nTest_Signal=" + std::to_string(event_number);
//     std::string TrainingAndTestOptions = "nTrain_Signal=0:nTrain_Background=0:SplitMode=Random:NormMode=Numevents:!V";
    std::string training_and_test_options = number_options + "SplitMode=Block";
    factory().PrepareTrainingAndTestTree(tagger().Cut(), tagger().Cut(), training_and_test_options);
}

TMVA::MethodBDT& Factory::BookMethods()
{
    Note();
//     std::string bdt_options = "NTrees=1000:MinNodeSize=2.5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20";
    std::string bdt_options = "NTrees=1000:MinNodeSize=2.5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20";
    //:VarTransform=D
//     std::string bdt_options = "!H:!V:NTrees=1000:MinNodeSize=1.5%:BoostType=Grad:Shrinkage=0.10:UseBaggedGrad:UseRandomisedTrees:GradBaggingFraction=0.5:nCuts=20:MaxDepth=4";
    //:CreateMVAPdfs:DoBoostMonitor";
    return dynamic_cast<TMVA::MethodBDT&>(*factory().BookMethod(TMVA::Types::kBDT, tagger().BdtMethodName(), bdt_options));
}

}
