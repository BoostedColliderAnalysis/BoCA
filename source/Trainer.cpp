#include "Trainer.hh"

#include "TClonesArray.h"
#include "TFile.h"

#include "TMVA/Config.h"
#include "TMVA/MethodBDT.h"
#include "TMVA/Ranking.h"

#include "Types.hh"
#include "Tagger.hh"
#include "Debug.hh"

namespace analysis
{

  Trainer::Trainer(analysis::Tagger& tagger, TMVA::Types::EMVA mva) : tagger_(tagger) , factory_(tagger.Name(), OutputFile(), FactoryOptions())
{
    Error();
    AddVariables();
    PrepareTrainingAndTestTree(GetTrees());
//     TMVA::MethodBDT& method =
    BookMethod(mva);
//     const TMVA::Ranking& rank = *method.CreateRanking();
//     rank.SetContext("test");
    Factory().TrainAllMethods();
//     rank.Print();
    Factory().TestAllMethods();
    Factory().EvaluateAllMethods();
}

std::string Trainer::FactoryOptions()
{
    return "!Color:!DrawProgressBar";
}

TFile* Trainer::OutputFile() const
{
    return TFile::Open(Tagger().FactoryFileName().c_str(), "Recreate");
}

void Trainer::AddVariables()
{
    Note();
    TMVA::gConfig().GetIONames().fWeightFileDir = Tagger().AnalysisName();
    TMVA::gConfig().GetIONames().fWeightFileExtension = Tagger().WeightFileExtension();
    for (const auto & observable : Tagger().Variables()) Factory().AddVariable(observable.expression(), observable.title(), observable.unit(), observable.type());
    for (const auto & spectator : Tagger().Spectators()) Factory().AddSpectator(spectator.expression(), spectator.title(), spectator.unit(), spectator.type());
}

long Trainer::GetTrees()
{
    Note();
    return std::min(GetTree(Tag::signal), GetTree(Tag::background)) / 2;
}

long Trainer::GetTree(Tag tag)
{
    long number = 0;
    for (const auto & tree_name : Tagger().TreeNames(tag)) number += AddTree(tree_name, tag);
    return number;
}

long Trainer::AddTree(const std::string& tree_name, Tag tag)
{
    Debug(tree_name, Name(tag));
    TTree& tree = Tree(tree_name, tag);
    exroot::TreeReader tree_reader = TreeReader(tree_name, tag);
    float weight = Weight(tree_reader);
    Note(weight);
    switch (tag) {
    case Tag::signal :
        Factory().AddSignalTree(&tree, weight);
        break;
    case Tag::background :
        Factory().AddBackgroundTree(&tree, weight);
        break;
    }
    return Entries(tree_reader);
}

exroot::TreeReader Trainer::TreeReader(const std::string& tree_name, Tag tag)
{
   return exroot::TreeReader(&Tree(tree_name, tag));
}

long Trainer::Entries(exroot::TreeReader& tree_reader)
{
    long entries = 0;
    TClonesArray& clones_array = *tree_reader.UseBranch(Tagger().BranchName(Stage::trainer).c_str());
    for (const auto & entry : Range(tree_reader.GetEntries())) {
        tree_reader.ReadEntry(entry);
        entries += clones_array.GetEntries();
    }
    return entries;
}

float Trainer::Weight(exroot::TreeReader& tree_reader)
{
    TClonesArray& clones_array = *tree_reader.UseBranch(Tagger().WeightBranchName().c_str());
    tree_reader.ReadEntry(0);
    return static_cast<InfoBranch&>(*clones_array.First()).Crosssection / tree_reader.GetEntries();
}

TTree& Trainer::Tree(const std::string& tree_name, Tag tag)
{
    Note(Tagger().FileName(Stage::trainer, tag));
    if (!Exists(Tagger().FileName(Stage::trainer, tag).c_str())) Error("File not found", Tagger().FileName(Stage::trainer, tag));
    TFile& file = *TFile::Open(Tagger().FileName(Stage::trainer, tag).c_str());
    if (!file.GetListOfKeys()->Contains(tree_name.c_str())) Error("no tree");
    return static_cast<TTree&>(*file.Get(tree_name.c_str()));
}

void Trainer::PrepareTrainingAndTestTree(long event_number)
{
    Error();
    std::string number_options = "nTrain_Background=" + std::to_string(event_number) + ":nTest_Background=" + std::to_string(event_number) + ":nTrain_Signal=" + std::to_string(event_number) + ":nTest_Signal=" + std::to_string(event_number);
//     std::string TrainingAndTestOptions = "nTrain_Signal=0:nTrain_Background=0:SplitMode=Random:NormMode=Numevents:!V";
    std::string training_and_test_options = number_options + "SplitMode=Block";
    Factory().PrepareTrainingAndTestTree(Tagger().Cut(), Tagger().Cut(), training_and_test_options);
}

TMVA::MethodBDT& Trainer::BookMethod(TMVA::Types::EMVA mva)
{
    Note();
    return static_cast<TMVA::MethodBDT&>(*Factory().BookMethod(mva, Tagger().MethodName(mva), MethodOptions(mva)));
}

std::string Trainer::MethodOptions(TMVA::Types::EMVA mva)
{
    switch (mva) {
    case TMVA::Types::EMVA::kBDT :
        // return "NTrees=1000:MinNodeSize=2.5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20";
        return "NTrees=1000:MinNodeSize=2.5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20";
        //:VarTransform=D
        // return "!H:!V:NTrees=1000:MinNodeSize=1.5%:BoostType=Grad:Shrinkage=0.10:UseBaggedGrad:UseRandomisedTrees:GradBaggingFraction=0.5:nCuts=20:MaxDepth=4";
        //:CreateMVAPdfs:DoBoostMonitor";
    default :
        return "";
    }
}

}
