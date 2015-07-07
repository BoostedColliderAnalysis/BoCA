#include "Factory.hh"
#include "TSystem.h"
#include "TMVA/Config.h"
#include "TClonesArray.h"
#include "exroot/ExRootAnalysis.hh"
#include "TFile.h"
#include "Branches.hh"
#include "Predicate.hh"
#include "Debug.hh"

namespace analysis
{

Factory::Factory(Tagger &tagger) : tagger_(tagger) , factory_(tagger.name(), output_file(), factory_options())
{
    Error();
    AddVariables();
    PrepareTrainingAndTestTree(GetTrees());
    BookMethods();
    factory().TrainAllMethods();
    factory().TestAllMethods();
    factory().EvaluateAllMethods();
}

std::string Factory::factory_options()
{
    return "!Color:!Silent";
}

TFile *Factory::output_file() const
{
    const std::string file_name = tagger().analysis_name() + "/" + tagger().factory_name() + ".root";
    return TFile::Open(file_name.c_str(), "Recreate");
}

void Factory::AddVariables()
{
    Note("Add Variables");
    TMVA::gConfig().GetIONames().fWeightFileDir = tagger().analysis_name();
    TMVA::gConfig().GetIONames().fWeightFileExtension = tagger().weight_file_extension();
    for (const auto & observable : tagger().observables())
        factory().AddVariable(observable.expression(), observable.title(), observable.unit(), observable.type());
    for (const auto & spectator : tagger().spectators())
        factory().AddSpectator(spectator.expression(), spectator.title(), spectator.unit(), spectator.type());
}

int Factory::GetTrees()
{
    Note();
//     for (const auto & signal_name : tagger().signal_file_names()) {
//     std::string signal_file_name = tagger().analysis_name() + "/" +  tagger().signal_file_name(Stage::trainer) + ".root";
    std::string signal_file_name = tagger().signal_file_name(Stage::trainer) + ".root";
    Note("Signal", signal_file_name);
    if (gSystem->AccessPathName(signal_file_name.c_str())) Error("File not found", signal_file_name);
    TFile &signal_file = *TFile::Open(signal_file_name.c_str());
    Note("Signal File", signal_file.GetName(), tagger().signal_tree_names().size());
    int signal_number = 0;
    for (int tree_number : Range(tagger().signal_tree_names().size())) {
        Note("signal Tree Name", tagger().signal_tree_names()[tree_number]);
        signal_number += AddTree(signal_file, tagger().signal_tree_names()[tree_number], Tag::signal);
    }
//     }
//     for (const auto & background_name : tagger().background_file_names()) {
//     std::string background_file_name = tagger().analysis_name() + "/" + tagger().background_file_name(Stage::trainer) + ".root";
    std::string background_file_name = tagger().background_file_name(Stage::trainer) + ".root";
    Note("Background", background_file_name);
    if (gSystem->AccessPathName(background_file_name.c_str())) Error("File not found", background_file_name);
    TFile &background_file = *TFile::Open(background_file_name.c_str());
    Note("Background File", background_file.GetName(), tagger().background_tree_names().size());
    int background_number = 0;
    for (const auto & background_tree_name : tagger().background_tree_names()) {
        Note("Background Tree Name", background_tree_name);
        background_number += AddTree(background_file, background_tree_name, Tag::background);
    }
//     }
    Error("event Numbers", signal_number, background_number);
    return std::min(signal_number, background_number) / 2;
}

int Factory::AddTree(TFile &file, const std::string &tree_name, const Tag tag)
{
    Error("Add Tree", tree_name);
    if (!file.GetListOfKeys()->Contains(tree_name.c_str()))return 0;
    TTree &tree = static_cast<TTree &>(*file.Get(tree_name.c_str()));
    Error("Branch Name", tagger().branch_name().c_str());
    tree.GetBranch(tagger().branch_name().c_str());
    exroot::TreeReader &tree_reader = *new exroot::TreeReader(&tree); // FIXME nasty hack with memeory leak; necessary because the tree reader destructor closes the file which makes it invisible for tmva; reimplment in a cleaner way!!
    TClonesArray &clones_array = *tree_reader.UseBranch(tagger().weight_branch_name().c_str());
    tree_reader.ReadEntry(0);
    const float crosssection = static_cast<InfoBranch &>(*clones_array.First()).Crosssection / tree_reader.GetEntries(); // this takes care of the multiplicity
    Note("Weight", crosssection);
    switch (tag) {
    case Tag::signal :
        factory().AddSignalTree(&tree, crosssection);
        break;
    case Tag::background :
        factory().AddBackgroundTree(&tree, crosssection);
        break;
    }
    int entries = 0;
    TClonesArray &event_clones_array = *tree_reader.UseBranch(tagger().branch_name().c_str());
    for (int entry = 0; entry < tree_reader.GetEntries(); ++entry) {
        tree_reader.ReadEntry(entry);
        entries += event_clones_array.GetEntries();
    }
    return entries;
}

void Factory::PrepareTrainingAndTestTree(const int event_number)
{
    Error("PrepareTrainingAndTestTree");
    std::string number_options = "nTrain_Background=" + std::to_string(event_number) + ":nTest_Background=" + std::to_string(event_number) + ":nTrain_Signal=" + std::to_string(event_number) + ":nTest_Signal=" + std::to_string(event_number);
//     std::string TrainingAndTestOptions = "nTrain_Signal=0:nTrain_Background=0:SplitMode=Random:NormMode=Numevents:!V";
    const std::string training_and_test_options = number_options + "SplitMode=Block";
    factory().PrepareTrainingAndTestTree(tagger().cut(), tagger().cut(), training_and_test_options);
}

void Factory::BookMethods()
{
    Note("Book Methods");
//     const std::string bdt_options = "NTrees=1000:MinNodeSize=2.5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20";
    const std::string bdt_options = "NTrees=1000:MinNodeSize=2.5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20:VarTransform=Decorrelate";
//     const std::string bdt_options = "!H:!V:NTrees=1000:MinNodeSize=1.5%:BoostType=Grad:Shrinkage=0.10:UseBaggedGrad:UseRandomisedTrees:GradBaggingFraction=0.5:nCuts=20:MaxDepth=4";
    //:CreateMVAPdfs:DoBoostMonitor";
    factory().BookMethod(TMVA::Types::kBDT, tagger().bdt_method_name(), bdt_options);
}

}
