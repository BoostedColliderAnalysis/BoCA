/**
 * Copyright (C) 2015 Jan Hajer
 */

#include "TMVA/Reader.h"

#include "fastjet/ClusterSequence.hh"

#include "exroot/ExRootAnalysis.hh"
#include "Tagger.hh"
#include "JetInfo.hh"
#include "DetectorGeometry.hh"
#include "ReaderBase.hh"
// #define INFORMATION
#include "Debug.hh"

namespace boca
{

std::mutex Tagger::mutex_;

std::string Tagger::analysis_name_;

void Tagger::Initialize()
{
    Info0;
    ClearTreeNames();
    DefineVariables();
    Info("done");
}

Observable Tagger::NewObservable(float& value, std::string const& title) const
{
    Info(title);
    std::string expression = BranchName(Stage::trainer) + "." + title;
    return Observable(value, expression, title, "");
}

float Tagger::Bdt(TMVA::Reader const& reader) const
{
    Info0;
    std::lock_guard<std::mutex> guard(ReaderBase::mutex_);
    return const_cast<TMVA::Reader&>(reader).EvaluateMVA(MethodName(TMVA::Types::EMVA::kBDT));  // TODO get rid of the const cast
}

Jets Tagger::SubJets(fastjet::PseudoJet const& jet, int sub_jet_number) const
{
    Info0;
    if (!jet.has_pieces()) return {};
    if (!jet.has_user_info<JetInfo>()) return {};
    fastjet::ClusterSequence& cluster_sequence = *new fastjet::ClusterSequence(jet.constituents(), DetectorGeometry::SubJetDefinition());
    Jets pieces = cluster_sequence.exclusive_jets_up_to(sub_jet_number);
    if (pieces.empty()) {
        delete &cluster_sequence;
        return pieces;
    }
    cluster_sequence.delete_self_when_unused();
    return pieces;
}

void Tagger::AddTreeName(std::string const& tree_name, Tag tag)
{
    Info0;
    switch (tag) {
    case Tag::signal : signal_tree_names_.emplace_back(tree_name);
        break;
    case Tag::background : background_tree_names_.emplace_back(tree_name);
        break;
    }
}

std::string Tagger::BranchName(Stage stage) const
{
    Info0;
    return Name(stage);
}

std::string Tagger::BranchName(Stage stage, Tag tag) const
{
    Info0;
    return Name(stage, tag);
}

std::string Tagger::TrainerName() const
{
    Info0;
    return "Mva" + Name();
}

std::string Tagger::FactoryFileName() const
{
    Info0;
    return PathName(TrainerName());
}

std::string Tagger::ExportFileName(Stage stage, Tag tag) const
{
    Info0;
    return PathName(Name(stage, tag));
}

std::string Tagger::ExportName() const
{
    Info0;
    return AnalysisName() + "-" + Name();
}
std::string Tagger::ExportFileName() const
{
    Info0;
    return PathName(ExportName());
}
std::string Tagger::ExportFolderName() const
{
    Info0;
    return AnalysisName() + "/" + ExportName();
}
std::string Tagger::FolderName() const
{
    Info0;
    return AnalysisName() + "/" + Name();
}
std::string Tagger::ReaderName() const
{
    Info0;
    return ReaderName(Name());
}
std::string Tagger::ReaderName(std::string const& name) const
{
    Info(name);
    return name + "Reader";
}
std::string Tagger::Name(Stage stage) const
{
    Info0;
    switch (stage) {
    case Stage::trainer : return Name();
    case Stage::reader : return ReaderName();
    Default("Stage","");
    }
}
std::string Tagger::Name(Stage stage, Tag tag) const
{
    Info0;
    std::string name = Tagger::Name(stage);
    switch (tag) {
    case Tag::signal : return name;
    case Tag::background : return BackgroundName(name);
    Default("Tag","");
    }
}

std::string Tagger::FileName(Stage stage, Tag tag) const
{
    Info0;
    switch (tag) {
    case Tag::signal : return SignalFileName(stage);
    case Tag::background : return BackgroundFileName(stage);
    Default("Tag","");
    }
}

std::string Tagger::SignalFileName(Stage stage) const
{
    Info0;
    std::string name = SignalName();
    switch (stage) {
    case Stage::trainer : break;
    case Stage::reader : name = ReaderName(name);
    break;
    Default("Stage","");
    }
    return PathName(name);
}
std::string Tagger::BackgroundFileName(Stage stage) const
{
    Info0;
    std::string name = BackgroundName();
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
    Debug0;
    return analysis_name_;
}
std::vector<Observable> const& Tagger::Variables() const
{
    Info0;
    return variables_;
}
std::vector<Observable> const& Tagger::Spectators() const
{
    Info0;
    return spectators_;
}

void Tagger::ClearTreeNames()
{
    Info0;
    signal_tree_names_.clear();
    background_tree_names_.clear();
}

Strings Tagger::TreeNames(Tag tag) const
{
    Info0;
    switch (tag) {
    case Tag::signal : return signal_tree_names_;
    case Tag::background : return background_tree_names_;
    Default("Tag",{});
    }
}

TCut Tagger::Cut() const
{
    Info0;
    return TCut();
}

void Tagger::SetAnalysisName(std::string const& analysis_name)
{
    Info(analysis_name);
    analysis_name_ = analysis_name;
}

std::string Tagger::MethodName(TMVA::Types::EMVA mva) const
{
    Info0;
    switch (mva) {
    case TMVA::Types::EMVA::kBDT : return "Bdt";
    default : return "";
    }
}

std::string Tagger::WeightName(TMVA::Types::EMVA mva) const
{
    Info0;
    return Name() + "_" + MethodName(mva) + "." + WeightFileExtension();
}

std::string Tagger::WeightFileName(TMVA::Types::EMVA mva) const
{
    Info0;
    return PathName(WeightName(mva), ".xml");
}

std::string Tagger::WeightFileExtension() const
{
    Info0;
    return "weights";
    return "";
}

std::string Tagger::WeightBranchName() const
{
    Info0;
    return "Info";
}
std::string Tagger::BackgroundName() const
{
    Info0;
    return BackgroundName(Name());
}
std::string Tagger::SignalName() const
{
    Info0;
    return SignalName(Name());
}
std::string Tagger::SignalName(std::string const& name) const
{
    Info0;
    return name;
    return name + "SG";
}
std::string Tagger::BackgroundName(std::string const& name) const
{
    Info0;
    return "Not" + name;
    return name + "BG";
}
void Tagger::NewBranch(exroot::TreeWriter& tree_writer, Stage stage)
{
    Info(Name(stage));
    tree_branch_ = tree_writer.NewBranch(Name(stage).c_str(), &Class());
}

void Tagger::AddVariable(float& value, std::string const& title)
{
    Info(value, title);
    variables_.emplace_back(NewObservable(value, title));
}
void Tagger::AddSpectator(float& value, std::string const& title)
{
    Info(value, title);
    spectators_.emplace_back(NewObservable(value, title));
}
void Tagger::ClearObservables()
{
    Info0;
    variables_.clear();
    spectators_.clear();
}

exroot::TreeBranch& Tagger::TreeBranch() const
{
    Info0;
    return *tree_branch_;
}

std::string Name(Stage stage)
{
    Info(Name(stage));
    switch (stage) {
    case Stage::trainer : return "Trainer";
    case Stage::reader : return "Reader";
    Default("Stage","");
    }
}
std::string Tagger::NiceName() const
{
    Info0;
    return Name();
}

std::string Tagger::Root() const
{
    Info0;
    return ".root";
}

std::string Tagger::PathName(std::string const& file_name, std::string const& suffix) const
{
    Debug(file_name);
    return AnalysisName() + "/" + file_name + suffix;
}

}

