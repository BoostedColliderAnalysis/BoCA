/**
 * Copyright (C) 2015 Jan Hajer
 */

#include "TClonesArray.h"
#include "TFile.h"

#include "TMVA/Config.h"
#include "TMVA/MethodBDT.h"
#include "TMVA/Ranking.h"

#include "exroot/ExRootAnalysis.hh"
#include "Trainer.hh"
#include "Types.hh"
#include "Tagger.hh"
#include "Options.hh"
// #define DEBUG
#include "Debug.hh"

namespace boca
{

Trainer::Trainer(boca::Tagger& tagger) :
    tagger_(tagger) ,
    factory_(tagger.Name(), &OutputFile(), FactoryOptions())
{
    Info0;
    AddObservables();
    PrepareTrainingAndTestTree(AddAllTrees());
//     TMVA::MethodBase& method =
    BookMethod();
//     const TMVA::Ranking& rank = *method.CreateRanking();
//     rank.SetContext("test");
    Factory().TrainAllMethods();
//     rank.Print();
    Factory().TestAllMethods();
    Factory().EvaluateAllMethods();
}

std::string Trainer::FactoryOptions()
{
    Info0;
    Options options("Color", false);
//     options.Add("V");
//     options.Add("Silent", false);
    options.Add("DrawProgressBar", false);
    return options;
}

TFile& Trainer::OutputFile() const
{
    Info0;
    return *TFile::Open(Tagger().FactoryFileName().c_str(), "Recreate");
}

void Trainer::AddObservables()
{
    Info0;
    TMVA::gConfig().GetIONames().fWeightFileDir = Tagger().AnalysisName();
    TMVA::gConfig().GetIONames().fWeightFileExtension = Tagger().WeightFileExtension();
    for (auto const & observable : Tagger().Variables()) Factory().AddVariable(observable.Expression(), observable.Name(), observable.Unit(), observable.Type());
    for (auto const & spectator : Tagger().Spectators()) Factory().AddSpectator(spectator.Expression(), spectator.Name(), spectator.Unit(), spectator.Type());
}

long Trainer::AddAllTrees()
{
    Info0;
    return std::min(AddTrees(Tag::background), AddTrees(Tag::signal)) / 2;
}

long Trainer::AddTrees(Tag tag)
{
    Info0;
    long number = 0;
    for (auto const & tree_name : Tagger().TreeNames(tag)) number += AddTree(tree_name, tag);
    return number;
}

long Trainer::AddTree(std::string const& tree_name, Tag tag)
{
    INFO(tree_name, Name(tag));
    TTree& tree = Tree(tree_name, tag);
//     TTree& tree2 = Tree(tree_name, tag);
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

exroot::TreeReader Trainer::TreeReader(std::string const& tree_name, Tag tag)
{
    Info0;
    return exroot::TreeReader(&Tree(tree_name, tag));
}

long Trainer::Entries(exroot::TreeReader& tree_reader)
{
    Info0;
    long entries = 0;
    TClonesArray* clones_array = tree_reader.UseBranch(Tagger().BranchName(Stage::trainer).c_str());
    Check(clones_array, "no " + Tagger().BranchName(Stage::trainer) + " Branch");
    for (auto const & entry : Range(tree_reader.GetEntries())) {
        tree_reader.ReadEntry(entry);
        entries += clones_array->GetEntries();
    }
    return entries;
}

float Trainer::Weight(exroot::TreeReader& tree_reader)
{
    INFO(Tagger().WeightBranchName());
    TClonesArray* clones_array = tree_reader.UseBranch(Tagger().WeightBranchName().c_str());
    Check(clones_array, "no " + Tagger().WeightBranchName() + " Branch");
    tree_reader.ReadEntry(0);
    return static_cast<InfoBranch&>(*clones_array->First()).Crosssection() / fb / tree_reader.GetEntries();
}

TTree& Trainer::Tree(std::string const& tree_name, Tag tag)
{
    INFO(Tagger().FileName(Stage::trainer, tag));
    if (!Exists(Tagger().FileName(Stage::trainer, tag))) Error("File not found", Tagger().FileName(Stage::trainer, tag));
    TFile& file = *TFile::Open(Tagger().FileName(Stage::trainer, tag).c_str());
    if (file.GetListOfKeys()) {
        auto list = file.GetListOfKeys()->MakeIterator();
        TTree* tree;
        while ((tree = static_cast<TTree*>(list->Next()))) Error(tree->GetName());
    }
    if (!file.GetListOfKeys()->Contains(tree_name.c_str())) Error("no tree", tree_name);
    return static_cast<TTree&>(*file.Get(tree_name.c_str()));
}

void Trainer::PrepareTrainingAndTestTree(long event_number)
{
    Info0;
    Options options;
//     options.Add("SplitMode", "Block");
    options.Add("nTrain_Background", event_number);
    options.Add("nTest_Background", event_number);
    options.Add("nTrain_Signal", event_number);
    options.Add("nTest_Signal", event_number);
    Factory().PrepareTrainingAndTestTree(Tagger().Cut(), Tagger().Cut(), options);
}

TMVA::MethodBase& Trainer::BookMethod()
{
    Info0;
    return *Factory().BookMethod(Tagger().Mva(), Tagger().MethodName(), MethodOptions());
}
std::string Trainer::MethodOptions() const
{
    Info0;
    Options options;
    switch (Tagger().Mva()) {
    case TMVA::Types::EMVA::kBDT :
        options.Add("NTrees", 1000);
        options.Add("MinNodeSize", 2.5, "%");
        options.Add("MaxDepth", 3);
        options.Add("BoostType", "AdaBoost");
        options.Add("AdaBoostBeta", 0.5);
        options.Add("UseBaggedBoost");
        options.Add("BaggedSampleFraction", 0.5);
        options.Add("SeparationType", "GiniIndex");
        options.Add("nCuts", 20);
        break;
    case TMVA::Types::EMVA::kLikelihood :
        options.Add("VarTransform", "D");
        options.Add("MinNodeSize", 1.5, "%");
        options.Add("BoostType", "Grad");
        options.Add("Shrinkage", 0.10);
        options.Add("UseBaggedGrad");
        options.Add("UseRandomisedTrees");
        options.Add("GradBaggingFraction", 0.5);
        options.Add("MaxDepth", 4);
        options.Add("CreateMVAPdfs");
        options.Add("DoBoostMonitor");
        break;
    case TMVA::Types::EMVA::kCuts :
        options.Add("FitMethod", "GA");
        options.Add("EffSel");
        options.Add("VarProp", "FSmart");
        Default(Tagger().Mva(), "");
    }
    return options;
}

Tagger const& Trainer::Tagger() const
{
    return tagger_;
}

Tagger& Trainer::Tagger()
{
    return tagger_;
}

TMVA::Factory& Trainer::Factory()
{
    return factory_;
}

TMVA::Factory const& Trainer::Factory() const
{
    return factory_;
}

}
