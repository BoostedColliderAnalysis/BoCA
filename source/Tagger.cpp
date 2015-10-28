/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "Tagger.hh"

#include "TMVA/Reader.h"

#include "fastjet/ClusterSequence.hh"

#include "exroot/ExRootAnalysis.hh"
#include "JetInfo.hh"
#include "DetectorGeometry.hh"
// #define INFORMATION
#include "Debug.hh"

namespace boca
{

std::string Tagger::analysis_name_;

void Tagger::Initialize()
{
    Info();
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
    Info();
    return const_cast<TMVA::Reader&>(reader).EvaluateMVA(MethodName(TMVA::Types::EMVA::kBDT));  // TODO get rid of the const cast
}

Jets Tagger::SubJets(fastjet::PseudoJet const& jet, int sub_jet_number) const
{
    Info();
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
    Info();
    switch (tag) {
    case Tag::signal : signal_tree_names_.emplace_back(tree_name);
        break;
    case Tag::background : background_tree_names_.emplace_back(tree_name);
        break;
    }
}

std::string Tagger::BranchName(Stage stage) const
{
    Info();
    return Name(stage);
}

std::string Tagger::BranchName(Stage stage, Tag tag) const
{
    Info();
    return Name(stage, tag);
}

std::string Tagger::TrainerName() const
{
    Info();
    return "Mva" + Name();
}

std::string Tagger::FactoryFileName() const
{
    Info();
    return PathName(TrainerName());
}

std::string Tagger::ExportFileName(Stage stage, Tag tag) const
{
    Info();
    return PathName(Name(stage, tag));
}

std::string Tagger::ExportName() const
{
    Info();
    return AnalysisName() + "-" + Name();
}
std::string Tagger::ExportFileName() const
{
    Info();
    return PathName(ExportName());
}
std::string Tagger::ExportFolderName() const
{
    Info();
    return AnalysisName() + "/" + ExportName();
}
std::string Tagger::FolderName() const
{
    Info();
    return AnalysisName() + "/" + Name();
}
std::string Tagger::ReaderName() const
{
    Info();
    return ReaderName(Name());
}
std::string Tagger::ReaderName(std::string const& name) const
{
    Info(name);
    return name + "Reader";
}
std::string Tagger::Name(Stage stage) const
{
    Info();
    switch (stage) {
    case Stage::trainer : return Name();
    case Stage::reader : return ReaderName();
    }
}
std::string Tagger::Name(Stage stage, Tag tag) const
{
    Info();
    std::string name = Tagger::Name(stage);
    switch (tag) {
    case Tag::signal : return name;
    case Tag::background : return BackgroundName(name);
    }
}

std::string Tagger::FileName(Stage stage, Tag tag) const
{
    Info();
    switch (tag) {
    case Tag::signal : return SignalFileName(stage);
    case Tag::background : return BackgroundFileName(stage);
    }
}

std::string Tagger::SignalFileName(Stage stage) const
{
    Info();
    std::string name = SignalName();
    switch (stage) {
    case Stage::trainer :
        break;
    case Stage::reader : name = ReaderName(name);
        break;
    }
    return PathName(name);
}
std::string Tagger::BackgroundFileName(Stage stage) const
{
    Info();
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
    Debug();
    return analysis_name_;
}
std::vector<Observable> Tagger::Variables() const
{
    Info();
    return variables_;
}
std::vector<Observable> Tagger::Spectators() const
{
    Info();
    return spectators_;
}

void Tagger::ClearTreeNames()
{
    Info();
    signal_tree_names_.clear();
    background_tree_names_.clear();
}

Strings Tagger::TreeNames(Tag tag) const
{
    Info();
    switch (tag) {
    case Tag::signal : return signal_tree_names_;
    case Tag::background : return background_tree_names_;
    }
}

TCut Tagger::Cut() const
{
    Info();
    return TCut();
}

void Tagger::SetAnalysisName(std::string const& analysis_name)
{
    Info(analysis_name);
    analysis_name_ = analysis_name;
}

std::string Tagger::MethodName(TMVA::Types::EMVA mva) const
{
    Info();
    switch (mva) {
    case TMVA::Types::EMVA::kBDT : return "Bdt";
    default : return "";
    }
}

std::string Tagger::WeightName(TMVA::Types::EMVA mva) const
{
    Info();
    return Name() + "_" + MethodName(mva) + "." + WeightFileExtension();
}

std::string Tagger::WeightFileName(TMVA::Types::EMVA mva) const
{
    Info();
    return PathName(WeightName(mva), ".xml");
}

std::string Tagger::WeightFileExtension() const
{
    Info();
    return "weights";
    return "";
}

std::string Tagger::WeightBranchName() const
{
    Info();
    return "Info";
}
std::string Tagger::BackgroundName() const
{
    Info();
    return BackgroundName(Name());
}
std::string Tagger::SignalName() const
{
    Info();
    return SignalName(Name());
}
std::string Tagger::SignalName(std::string const& name) const
{
    Info();
    return name;
    return name + "SG";
}
std::string Tagger::BackgroundName(std::string const& name) const
{
    Info();
    return "Not" + name;
    return name + "BG";
}
void Tagger::SetTreeBranch(exroot::TreeWriter& tree_writer, Stage stage)
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
    Info();
    variables_.clear();
    spectators_.clear();
}

exroot::TreeBranch& Tagger::TreeBranch() const
{
    Info();
    return *tree_branch_;
}

std::string Name(Stage stage)
{
    Info(Name(stage));
    switch (stage) {
    case Stage::trainer : return "Trainer";
    case Stage::reader : return "Reader";
    }
}
std::string Tagger::NiceName() const
{
    Info();
    return Name();
}

std::string Tagger::Root() const
{
    Info();
    return ".root";
}

std::string Tagger::PathName(std::string const& file_name, std::string const& suffix) const
{
    Debug(file_name);
    return AnalysisName() + "/" + file_name + suffix;
}

}

