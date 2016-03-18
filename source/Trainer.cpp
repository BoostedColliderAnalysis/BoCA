/**
 * Copyright (C) 2015-2016 Jan Hajer
 */

#include "boost/range/algorithm/max_element.hpp"

#include "TMVA/Config.h"
#include "TMVA/MethodBDT.h"

#include "exroot/ExRootAnalysis.hh"
#include "Trainer.hh"
#include "Tagger.hh"
#include "Options.hh"
// #define DEBUGGING
#include "DEBUG.hh"

namespace boca
{

Trainer::Trainer(boca::Tagger& tagger) :
    tagger_(tagger) ,
    factory_(tagger.Name(), &OutputFile(), FactoryOptions())
{
    INFO0;
    AddObservables();
    PrepareTrainingAndTestTree(AddAllTrees());
    BookMethod();
    Factory().TrainAllMethods();
    Factory().TestAllMethods();
    Factory().EvaluateAllMethods();
}

std::string Trainer::FactoryOptions()
{
    INFO0;
    Options options("Color", false);
//     options.Add("V");
//     options.Add("Silent", false);
    options.Add("DrawProgressBar", false);
    return options;
}

TFile& Trainer::OutputFile() const
{
    INFO0;
    return *TFile::Open(Tagger().FactoryFileName().c_str(), "Recreate");
}

void Trainer::AddObservables()
{
    INFO0;
    TMVA::gConfig().GetIONames().fWeightFileDir = Tagger().AnalysisName();
    TMVA::gConfig().GetIONames().fWeightFileExtension = Tagger().WeightFileExtension();
    for (auto const & variable : Tagger().Variables()) Factory().AddVariable(variable.Expression(), variable.Name(), variable.Unit(), variable.Type());
    for (auto const & spectator : Tagger().Spectators()) Factory().AddSpectator(spectator.Expression(), spectator.Name(), spectator.Unit(), spectator.Type());
}

long Trainer::AddAllTrees()
{
    INFO0;
    return std::min(AddTrees(Tag::background), AddTrees(Tag::signal)) / 2;
}

long Trainer::AddTrees(Tag tag)
{
    INFO0;
    long number = 0;
    for (auto const & tree_name : Tagger().TreeNames(tag)) number += AddTree(tree_name, tag);
    return number;
}

long Trainer::AddTree(std::string const& tree_name, Tag tag)
{
    INFO(tree_name, Name(tag));
    TTree& tree = Tree(tree_name, tag);
    exroot::TreeReader tree_reader = TreeReader(tree_name, tag);
    double weight = Weight(tree_reader);
    NOTE(weight);
    switch (tag) {
    case Tag::signal : Factory().AddSignalTree(&tree, weight);
        break;
    case Tag::background : Factory().AddBackgroundTree(&tree, weight);
        break;
    }
    return Entries(tree_reader);
}

exroot::TreeReader Trainer::TreeReader(std::string const& tree_name, Tag tag)
{
    INFO0;
    return exroot::TreeReader(&Tree(tree_name, tag));
}

long Trainer::Entries(exroot::TreeReader& tree_reader)
{
    INFO0;
    long entries = 0;
    auto* clones_array = tree_reader.UseBranch(Tagger().BranchName(Stage::trainer).c_str());
    CHECK(clones_array, "no " + Tagger().BranchName(Stage::trainer) + " Branch");
    for (auto const & entry : IntegerRange(tree_reader.GetEntries())) {
        tree_reader.ReadEntry(entry);
        entries += clones_array->GetEntries();
    }
    return entries;
}

double Trainer::Weight(exroot::TreeReader& tree_reader)
{
    INFO(Tagger().WeightBranchName());
    auto* clones_array = tree_reader.UseBranch(Tagger().WeightBranchName().c_str());
    CHECK(clones_array, "no " + Tagger().WeightBranchName() + " Branch");
    tree_reader.ReadEntry(0);
    return static_cast<InfoBranch&>(*clones_array->First()).Crosssection() / fb / tree_reader.GetEntries();
}

TTree& Trainer::Tree(std::string const& tree_name, Tag tag)
{
    INFO(Tagger().FileName(Stage::trainer, tag));
    CHECK(Exists(Tagger().FileName(Stage::trainer, tag)), "File not found", Tagger().FileName(Stage::trainer, tag));
    TFile& file = *TFile::Open(Tagger().FileName(Stage::trainer, tag).c_str());
    CHECK(file.GetListOfKeys()->Contains(tree_name.c_str()), "no tree", tree_name);
    auto* tree = static_cast<TTree*>(file.Get(tree_name.c_str()));
    if (!tree) ERROR("no tree");
    if (!tree->GetListOfBranches()) ERROR("no branches");
    return *tree;
}

void Trainer::PrepareTrainingAndTestTree(long event_number)
{
    INFO0;
    Options options;
//     options.Add("SplitMode", "Block");
    options.Add("nTrain_Background", event_number);
    options.Add("nTest_Background", event_number);
    options.Add("nTrain_Signal", event_number);
    options.Add("nTest_Signal", event_number);
    Factory().PrepareTrainingAndTestTree(Tagger().Cut(), Tagger().Cut(), options);
}

std::vector<double> Trainer::BookMethod()
{
    INFO0;
    auto* method = Factory().BookMethod(Tagger().Mva(), Tagger().MethodName(), MethodOptions());
    if (!method) return {};
    TMVA::Event::SetIsTraining(true);
    std::vector<double> importance;
    switch (method->GetMethodType()) {
    case TMVA::Types::EMVA::kBDT : {
        auto& mva = static_cast<TMVA::MethodBDT&>(*method);
        mva.TrainMethod();
        importance = mva.GetVariableImportance();
        mva.Reset();
        break;
    }
    case TMVA::Types::EMVA::kCuts : break;
        DEFAULT(method->GetMethodName());
    }
//     for (auto const & value : importance) ERROR(value);
    auto & max = *boost::range::max_element(importance);
    auto pos = Position(importance, max);
    ERROR(Tagger().Variables().at(pos).Name());
    return importance;
}

std::string Trainer::MethodOptions() const
{
    INFO0;
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
        break;
        DEFAULT(Tagger().MvaName(), "");
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
