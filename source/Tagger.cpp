/**
 * Copyright (C) 2015-2016 Jan Hajer
 */

// #include <boost/filesystem.hpp>

#include "TMVA/Reader.h"

#include "boca/fastjet/ClusterSequence.hh"

#include "boca/io/TreeWriter.hh"
#include "boca/Tagger.hh"
#include "boca/AnalysisBase.hh"
#include "boca/Filter.hh"
#include "boca/DetectorGeometry.hh"
#include "boca/multivariant/Reader.hh"
// #define INFORMATION
#include "boca/generic/DEBUG.hh"

namespace boca
{

// std::mutex Tagger::mutex_;

// std::string Tagger::analysis_name_;

// small memory leak, but better than static variable Initialization hell
std::string& analysis_name_()
{
    static auto* analysis_name = new std::string;
    return *analysis_name;
}

void Tagger::Initialize(std::string const& analysis_name)
{
    INFO(analysis_name);
    if (!analysis_name.empty()) analysis_name_() = analysis_name;
    ClearTreeNames();
    DefineVariables();
    INFO("done");
}

TMVA::Types::EMVA Tagger::Mva() const
{
    return TMVA::Types::EMVA::kBDT;
}

std::string Tagger::MvaName() const
{
    return std::string(TMVA::Types::Instance().GetMethodName(Mva()));
}

double Tagger::Bdt(TMVA::Reader const& reader) const
{
    INFO(Name());
//     std::lock_guard<std::mutex> guard(ReaderBase::mutex_);
    return const_cast<TMVA::Reader&>(reader).EvaluateMVA(MethodName());  // const cast is necessary because TMVA is not using const getters
}

bool Tagger::Cut(TMVA::Reader const& reader, double eff) const
{
    INFO(Name());
//     std::lock_guard<std::mutex> guard(ReaderBase::mutex_);
    return const_cast<TMVA::Reader&>(reader).EvaluateMVA(MethodName(), eff);  // const cast is necessary because TMVA is not using const getters
}

std::vector<Jet> Tagger::SubJets(Jet const& jet, int sub_jet_number) const
{
    INFO0;
    ClusterSequence cluster_sequence(jet.Constituents(), DetectorGeometry::SubJetDefinition());
    return cluster_sequence.ExclusiveJetsUpTo(sub_jet_number);
}

void Tagger::AddTreeName(std::string const& tree_name, Tag tag)
{
    INFO0;
    switch (tag) {
    case Tag::signal : signal_tree_names_.emplace_back(tree_name);
        break;
    case Tag::background : background_tree_names_.emplace_back(tree_name);
        break;
    }
}

std::string Tagger::BranchName(Stage stage) const
{
    INFO0;
    return Name(stage);
}

// std::string Tagger::BranchName(Stage stage, Tag tag) const
// {
//     INFO0;
//     return Name(stage, tag);
// }

std::string Tagger::BranchName(Phase const& phase) const
{
    INFO0;
    return Name(phase.Stage());
}

std::string Tagger::TrainerName() const
{
    INFO0;
    return "Mva" + Name();
}

std::string Tagger::FactoryFileName() const
{
    INFO0;
    return PathName(TrainerName());
}

std::string Tagger::ExportFileName(Phase const& phase) const
{
    INFO0;
    return ExportFileName(phase.Stage(), phase.Tag());
}

std::string Tagger::ExportFileName(Stage stage, Tag tag) const
{
    INFO0;
    return PathName(Name(stage, tag));
}

std::string Tagger::ExportName() const
{
    INFO0;
    return AnalysisName() + "-" + Name();
}
std::string Tagger::ExportFileName() const
{
    INFO0;
    return PathName(ExportName());
}
std::string Tagger::ExportFolderName() const
{
    INFO0;
    return AnalysisName() + "/" + ExportName();
}
std::string Tagger::FolderName() const
{
    INFO0;
    return AnalysisName() + "/" + Name();
}
std::string Tagger::ReaderName() const
{
    INFO0;
    return ReaderName(Name());
}
std::string Tagger::ReaderName(std::string const& name) const
{
    INFO(name);
    return name + "Reader";
}
std::string Tagger::Name(Stage stage) const
{
    INFO0;
    switch (stage) {
    case Stage::trainer : return Name();
    case Stage::reader : return ReaderName();
        DEFAULT(boca::Name(stage), "");
    }
}
std::string Tagger::Name(Phase const& phase) const
{
    INFO0;
    auto name = Tagger::Name(phase.Stage());
    switch (phase.Tag()) {
    case Tag::signal : return name;
    case Tag::background : return BackgroundName(name);
        DEFAULT(boca::Name(phase.Tag()), "");
    }
}
std::string Tagger::Name(Stage stage, Tag tag) const
{
    INFO0;
    return Tagger::Name(Phase(stage, tag));
}

std::string Tagger::FileName(Stage stage, Tag tag) const
{
    INFO0;
    switch (tag) {
    case Tag::signal : return SignalFileName(stage);
    case Tag::background : return BackgroundFileName(stage);
        DEFAULT(boca::Name(tag), "");
    }
}

std::string Tagger::FileName(Phase const& phase) const
{
    INFO0;
    switch (phase.Tag()) {
    case Tag::signal : return SignalFileName(phase.Stage());
    case Tag::background : return BackgroundFileName(phase.Stage());
        DEFAULT(boca::Name(phase.Tag()), "");
    }
}

std::string Tagger::SignalFileName(Stage stage) const
{
    INFO0;
    auto name = SignalName();
    switch (stage) {
    case Stage::trainer : break;
    case Stage::reader : name = ReaderName(name);
        break;
        DEFAULT(boca::Name(stage), "");
    }
    return PathName(name);
}
std::string Tagger::BackgroundFileName(Stage stage) const
{
    INFO0;
    auto name = BackgroundName();
    switch (stage) {
    case Stage::trainer : // TrainerName(name);
        break;
    case Stage::reader : name = ReaderName(name);
        break;
    }
    return PathName(name);
}
std::string Tagger::AnalysisName() const
{
//     analysis_name_ = boost::filesystem::current_path().filename().string();
//     ERROR(analysis_name_, _analysis_name_);
    return !analysis_name_().empty() ? analysis_name_() : _analysis_name_;
}
std::vector<Observable> const& Tagger::Variables() const
{
    INFO0;
    return variables_;
}
std::vector<Observable> const& Tagger::Spectators() const
{
    INFO0;
    return spectators_;
}

void Tagger::ClearTreeNames()
{
    INFO0;
    signal_tree_names_.clear();
    background_tree_names_.clear();
}

std::vector<std::string> Tagger::TreeNames(Tag tag) const
{
    INFO0;
    switch (tag) {
    case Tag::signal : return signal_tree_names_;
    case Tag::background : return background_tree_names_;
        DEFAULT(boca::Name(tag), {});
    }
}

std::vector<std::string> Tagger::TreeNames(Phase const& phase) const
{
    INFO0;
    return TreeNames(phase.Tag());
}

TCut Tagger::Cut() const
{
    INFO0;
    return TCut();
}

std::string Tagger::MethodName() const
{
    INFO0;
    switch (Mva()) {
    case TMVA::Types::EMVA::kBDT : return "Bdt";
    case TMVA::Types::EMVA::kCuts : return "Cuts";
        DEFAULT(Mva(), "");
    }
}

std::string Tagger::WeightName() const
{
    INFO0;
    return Name() + "_" + MethodName() + "." + WeightFileExtension();
}

std::string Tagger::WeightFileName() const
{
    INFO0;
    return PathName(WeightName(), ".xml");
}

std::string Tagger::WeightFileExtension() const
{
    INFO0;
    return "weights";
    return "";
}

std::string Tagger::WeightBranchName() const
{
    INFO0;
    return "Info";
}
std::string Tagger::BackgroundName() const
{
    INFO0;
    return BackgroundName(Name());
}
std::string Tagger::SignalName() const
{
    INFO0;
    return SignalName(Name());
}
std::string Tagger::SignalName(std::string const& name) const
{
    INFO0;
    return name;
    return name + "SG";
}
std::string Tagger::BackgroundName(std::string const& name) const
{
    INFO0;
    return "Not" + name;
    return name + "BG";
}
void Tagger::NewBranch(TreeWriter& tree_writer, Stage stage)
{
    INFO(Name(stage));
    tree_branch_ = &tree_writer.NewBranch(Name(stage), Class());
}

void Tagger::AddVariable(Observable& observable)
{
    INFO0;
    observable.SetBranchName(BranchName(Stage::trainer));
    variables_.emplace_back(observable);
}
void Tagger::AddSpectator(Observable& observable)
{
    INFO0;
    observable.SetBranchName(BranchName(Stage::trainer));
    spectators_.emplace_back(observable);
}
void Tagger::ClearObservables()
{
    INFO0;
    variables_.clear();
    spectators_.clear();
}

TreeBranch& Tagger::TreeBranch() const
{
    INFO0;
    return *tree_branch_;
}

Latex Tagger::LatexName() const
{
    INFO0;
    return Name();
}

std::string Tagger::Root() const
{
    INFO0;
    return ".root";
}

std::string Tagger::PathName(std::string const& file_name, std::string const& suffix) const
{
    INFO(file_name, suffix);
    return AnalysisName() + "/" + file_name + suffix;
}
Filter Tagger::Filter() const
{
    return {};
}
boca::Range< double > Tagger::MvaRange() const
{
    switch (Mva()) {
    case TMVA::Types::kCuts : return { -1 , 1};
    case TMVA::Types::kBDT : return {0 , 1};
        DEFAULT(MvaName(), boca::Range< double >(0, 0));
    }
}

}

