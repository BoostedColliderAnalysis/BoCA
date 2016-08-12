/**
 * Copyright (C) 2015-2016 Jan Hajer
 */

#include "TCut.h"

#include "TMVA/Reader.h"

#include "boca/fastjet/ClusterSequence.hh"
#include "boca/io/TreeWriter.hh"
#include "boca/multivariant/Reader.hh"
#include "boca/analysis/AnalysisBase.hh"
#include "boca/Filter.hh"
#include "boca/Settings.hh"
#include "boca/TaggerBase.hh"
// #define INFORMATION
#include "boca/generic/DEBUG_MACROS.hh"

namespace boca
{

// std::mutex TaggerBase::mutex_;

// std::string TaggerBase::analysis_name_;

// small memory leak, but better than static variable Initialization hell
std::string& AnalysisName_()
{
    static auto* analysis_name = new std::string;
    return *analysis_name;
}

void TaggerBase::Initialize(std::string const& analysis_name)
{
    INFO(analysis_name);
    if (!analysis_name.empty()) AnalysisName_() = analysis_name;
    ClearTreeNames();
    DefineVariables();
    INFO("done");
}

TMVA::Types::EMVA TaggerBase::Mva() const
{
    return TMVA::Types::EMVA::kBDT;
}

std::string TaggerBase::MvaName() const
{
    return std::string(TMVA::Types::Instance().GetMethodName(Mva()));
}

double TaggerBase::Bdt(TMVA::Reader const& reader) const
{
    INFO(Name());
//     std::lock_guard<std::mutex> guard(ReaderBase::mutex_);
    return const_cast<TMVA::Reader&>(reader).EvaluateMVA(MethodName());  // const cast is necessary because TMVA is not using const getters
}

bool TaggerBase::Cut(TMVA::Reader const& reader, double eff) const
{
    INFO(Name());
//     std::lock_guard<std::mutex> guard(ReaderBase::mutex_);
    return const_cast<TMVA::Reader&>(reader).EvaluateMVA(MethodName(), eff);  // const cast is necessary because TMVA is not using const getters
}

std::vector<Jet> TaggerBase::SubJets(Jet const& jet, int sub_jet_number) const
{
    INFO0;
    ClusterSequence cluster_sequence(jet.Constituents(), Settings::SubJetDefinition());
    return cluster_sequence.ExclusiveJetsUpTo(sub_jet_number);
}

void TaggerBase::AddTreeName(std::string const& tree_name, Tag tag)
{
    INFO0;
    switch (tag) {
    case Tag::signal : signal_tree_names_.emplace_back(tree_name);
        break;
    case Tag::background : background_tree_names_.emplace_back(tree_name);
        break;
    }
}

std::string TaggerBase::BranchName(Stage stage) const
{
    INFO0;
    return Name(stage);
}

// std::string TaggerBase::BranchName(Stage stage, Tag tag) const
// {
//     INFO0;
//     return Name(stage, tag);
// }

std::string TaggerBase::BranchName(Phase const& phase) const
{
    INFO0;
    return Name(phase.Stage());
}

std::string TaggerBase::TrainerName() const
{
    INFO0;
    return "Mva" + Name();
}

std::string TaggerBase::FactoryFileName() const
{
    INFO0;
    return PathName(TrainerName());
}

std::string TaggerBase::ExportFileName(Phase const& phase) const
{
    INFO0;
    return ExportFileName(phase.Stage(), phase.Tag());
}

std::string TaggerBase::ExportFileName(Stage stage, Tag tag) const
{
    INFO0;
    return PathName(Name(stage, tag));
}

std::string TaggerBase::ExportName() const
{
    INFO0;
    return AnalysisName() + "-" + Name();
}
std::string TaggerBase::ExportFileName() const
{
    INFO0;
    return PathName(ExportName());
}
std::string TaggerBase::ExportFolderName() const
{
    INFO0;
    return AnalysisName() + "/" + ExportName();
}
std::string TaggerBase::FolderName() const
{
    INFO0;
    return AnalysisName() + "/" + Name();
}
std::string TaggerBase::ReaderName() const
{
    INFO0;
    return ReaderName(Name());
}
std::string TaggerBase::ReaderName(std::string const& name) const
{
    INFO(name);
    return name + "Reader";
}
std::string TaggerBase::Name(Stage stage) const
{
    INFO0;
    switch (stage) {
    case Stage::trainer : return Name();
    case Stage::reader : return ReaderName();
        DEFAULT(boca::Name(stage), "");
    }
}
std::string TaggerBase::Name(Phase const& phase) const
{
    INFO0;
    auto name = TaggerBase::Name(phase.Stage());
    switch (phase.Tag()) {
    case Tag::signal : return name;
    case Tag::background : return BackgroundName(name);
        DEFAULT(boca::Name(phase.Tag()), "");
    }
}
std::string TaggerBase::Name(Stage stage, Tag tag) const
{
    INFO0;
    return TaggerBase::Name(Phase(stage, tag));
}

std::string TaggerBase::FileName(Stage stage, Tag tag) const
{
    INFO0;
    switch (tag) {
    case Tag::signal : return SignalFileName(stage);
    case Tag::background : return BackgroundFileName(stage);
        DEFAULT(boca::Name(tag), "");
    }
}

std::string TaggerBase::FileName(Phase const& phase) const
{
    INFO0;
    switch (phase.Tag()) {
    case Tag::signal : return SignalFileName(phase.Stage());
    case Tag::background : return BackgroundFileName(phase.Stage());
        DEFAULT(boca::Name(phase.Tag()), "");
    }
}

std::string TaggerBase::SignalFileName(Stage stage) const
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
std::string TaggerBase::BackgroundFileName(Stage stage) const
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
std::string TaggerBase::AnalysisName() const
{
//     analysis_name_ = boost::filesystem::current_path().filename().string();
//     ERROR(analysis_name_, _analysis_name_);
    return !AnalysisName_().empty() ? AnalysisName_() : _analysis_name_;
}
std::vector<Observable> const& TaggerBase::Variables() const
{
    INFO0;
    return variables_;
}
std::vector<Observable> const& TaggerBase::Spectators() const
{
    INFO0;
    return spectators_;
}

void TaggerBase::ClearTreeNames()
{
    INFO0;
    signal_tree_names_.clear();
    background_tree_names_.clear();
}

std::vector<std::string> TaggerBase::TreeNames(Tag tag) const
{
    INFO0;
    switch (tag) {
    case Tag::signal : return signal_tree_names_;
    case Tag::background : return background_tree_names_;
        DEFAULT(boca::Name(tag), {});
    }
}

std::vector<std::string> TaggerBase::TreeNames(Phase const& phase) const
{
    INFO0;
    return TreeNames(phase.Tag());
}

TCut TaggerBase::Cut() const
{
    INFO0;
    return TCut();
}

std::string TaggerBase::MethodName() const
{
    INFO0;
    switch (Mva()) {
    case TMVA::Types::EMVA::kBDT : return "Bdt";
    case TMVA::Types::EMVA::kCuts : return "Cuts";
        DEFAULT(Mva(), "");
    }
}

std::string TaggerBase::WeightName() const
{
    INFO0;
    return Name() + "_" + MethodName() + "." + WeightFileExtension();
}

std::string TaggerBase::WeightFileName() const
{
    INFO0;
    return PathName(WeightName(), ".xml");
}

std::string TaggerBase::WeightFileExtension() const
{
    INFO0;
    return "weights";
    return "";
}

std::string TaggerBase::WeightBranchName() const
{
    INFO0;
    return "Info";
}
std::string TaggerBase::BackgroundName() const
{
    INFO0;
    return BackgroundName(Name());
}
std::string TaggerBase::SignalName() const
{
    INFO0;
    return SignalName(Name());
}
std::string TaggerBase::SignalName(std::string const& name) const
{
    INFO0;
    return name;
    return name + "SG";
}
std::string TaggerBase::BackgroundName(std::string const& name) const
{
    INFO0;
    return "Not" + name;
    return name + "BG";
}
void TaggerBase::NewBranch(TreeWriter& tree_writer, Stage stage)
{
    INFO(Name(stage));
    tree_branch_ = &tree_writer.NewBranch(Name(stage), Class());
}

void TaggerBase::AddVariable(Observable& observable)
{
    INFO0;
    observable.SetBranchName(BranchName(Stage::trainer));
    variables_.emplace_back(observable);
}
void TaggerBase::AddSpectator(Observable& observable)
{
    INFO0;
    observable.SetBranchName(BranchName(Stage::trainer));
    spectators_.emplace_back(observable);
}
void TaggerBase::ClearObservables()
{
    INFO0;
    variables_.clear();
    spectators_.clear();
}

TreeBranch& TaggerBase::TreeBranch() const
{
    INFO0;
    return *tree_branch_;
}

latex::String TaggerBase::LatexName() const
{
    INFO0;
    return Name();
}

std::string TaggerBase::Root() const
{
    INFO0;
    return ".root";
}

std::string TaggerBase::PathName(std::string const& file_name, std::string const& suffix) const
{
    INFO(file_name, suffix);
    return AnalysisName() + "/" + file_name + suffix;
}
Filter TaggerBase::Filter() const
{
    return {};
}
boca::Range< double > TaggerBase::MvaRange() const
{
    switch (Mva()) {
    case TMVA::Types::kCuts : return { -1 , 1};
    case TMVA::Types::kBDT : return {0 , 1};
        DEFAULT(MvaName(), boca::Range< double >(0, 0));
    }
}

}

