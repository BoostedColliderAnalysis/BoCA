/**
 * Copyright (C) 2015-2016 Jan Hajer
 */

#include "boost/range/algorithm/max_element.hpp"
#include "boost/range/numeric.hpp"

#include "TMVA/Config.h"
#include "TMVA/MethodBDT.h"

#include "boca/generic/Options.hh"
#include "boca/generic/Types.hh"
#include "boca/generic/Vector.hh"
#include "boca/io/Io.hh"
#include "boca/io/TreeReader.hh"
#include "boca/multivariant/Trainer.hh"
#include "boca/branch/Info.hh"
#include "boca/TaggerBase.hh"
// #define DEBUGGING
#include "boca/generic/DEBUG_MACROS.hh"

namespace boca
{

Trainer::Trainer(TaggerBase& tagger) :
    tagger_(tagger),
    output_(Tagger().FactoryFileName().c_str(), "Recreate"),
    factory_(tagger.Name(), &output_, FactoryOptions())
//     ,data_loader_(DataLoaderOptions())
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

std::string Trainer::DataLoaderOptions()
{
  INFO0;
  return {};
}

void Trainer::AddObservables()
{
    INFO0;
    TMVA::gConfig().GetIONames().fWeightFileDir = Tagger().AnalysisName();
    TMVA::gConfig().GetIONames().fWeightFileExtension = Tagger().WeightFileExtension();
    for (auto const & variable : Tagger().Variables()) DataLoader().AddVariable(variable.Expression(), variable.Name(), variable.Unit(), variable.Type());
    for (auto const & spectator : Tagger().Spectators()) DataLoader().AddSpectator(spectator.Expression(), spectator.Name(), spectator.Unit(), spectator.Type());
}

long Trainer::AddAllTrees()
{
    INFO0;
    return std::min(AddTrees(Tag::background), AddTrees(Tag::signal)) / 2;
}

long Trainer::AddTrees(Tag tag)
{
    INFO0;
    input_.emplace(std::piecewise_construct, std::forward_as_tuple(tag), std::forward_as_tuple(Tagger().FileName(Stage::trainer, tag).c_str()));
    return boost::accumulate(Tagger().TreeNames(tag), 0, [&](long sum, std::string const & tree_name) {
        return sum + AddTree(tree_name, tag);
    });
}

long Trainer::AddTree(std::string const& tree_name, Tag tag)
{
    INFO(tree_name, Name(tag));
    switch (tag) {
      case Tag::signal : DataLoader().AddSignalTree(static_cast<TTree*>(input_.at(tag).Get(tree_name.c_str())), Weight(tree_name, tag));
        break;
      case Tag::background : DataLoader().AddBackgroundTree(static_cast<TTree*>(input_.at(tag).Get(tree_name.c_str())), Weight(tree_name, tag));
        break;
    }
    return Entries(tree_name, tag);
}

double Trainer::Weight(std::string const& tree_name, Tag tag)
{
    INFO(Tagger().WeightBranchName());
    TreeReader tree_reader( {Tagger().FileName(Stage::trainer, tag)} , tree_name, Source::tagger);
    auto& array = tree_reader.Array<branch::Info>(Tagger().WeightBranchName());
    tree_reader.ReadEntry(0);
    return array.At(0).Crosssection() / fb / tree_reader.GetEntries();
}

long Trainer::Entries(std::string const& tree_name, Tag tag)
{
    INFO0;
    TreeReader tree_reader( {Tagger().FileName(Stage::trainer, tag)} , tree_name, Source::tagger);
    auto& array = tree_reader.Array(Tagger().BranchName(Stage::trainer), Tagger().Class());
    long entries = 0;
    while (tree_reader.Next()) entries += array.GetSize();
    return entries;
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
    DataLoader().PrepareTrainingAndTestTree(Tagger().Cut(), Tagger().Cut(), options);
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
    auto pos = Position(importance, *boost::range::max_element(importance));
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

TaggerBase const& Trainer::Tagger() const
{
    return tagger_;
}

TaggerBase& Trainer::Tagger()
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
