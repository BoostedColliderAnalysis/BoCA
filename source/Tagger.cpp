#include "Tagger.hh"

#include "TObjArray.h"
#include "TClonesArray.h"

#include "fastjet/ClusterSequence.hh"

#include "JetInfo.hh"
#include "Event.hh"
#include "Analysis.hh"
#include "Debug.hh"

namespace analysis
{

std::string Tagger::analysis_name_;

Observable Tagger::NewObservable(float& value, const std::string& title) const
{
    Info(title);
    std::string expression = BranchName(Stage::trainer) + "." + title;
    return Observable(value, expression, title, "");
}

float Tagger::Bdt(const TMVA::Reader& reader) const
{
    Info();
    return const_cast<TMVA::Reader&>(reader).EvaluateMVA(MethodName(TMVA::Types::EMVA::kBDT)) + 1;  // TODO get rid of the const cast
}

Jets Tagger::SubJets(const fastjet::PseudoJet& jet, int sub_jet_number) const
{
    Jets pieces;
    if (!jet.has_pieces()) return pieces;
    if (!jet.has_user_info<JetInfo>()) return pieces;
    fastjet::ClusterSequence& cluster_sequence = *new fastjet::ClusterSequence(jet.constituents(), DetectorGeometry::SubJetDefinition());
    for (auto & piece : cluster_sequence.exclusive_jets_up_to(sub_jet_number)) {
        std::vector<Constituent> constituents;
        for (const auto & constituent : piece.constituents()) {
            if (!constituent.has_user_info<JetInfo>()) continue;
            std::vector<Constituent> piece_constituents = constituent.user_info<JetInfo>().constituents();
            constituents = Join(constituents, piece_constituents);
        }
        piece.set_user_info(new JetInfo(constituents));
        pieces.emplace_back(piece);
    }
    cluster_sequence.delete_self_when_unused();
    return pieces;
}

void Tagger::AddTreeName(const std::string& tree_name, Tag tag)
{
    switch (tag) {
    case Tag::signal : signal_tree_names_.emplace_back(tree_name);
        break;
    case Tag::background : background_tree_names_.emplace_back(tree_name);
        break;
    }
}

std::string Tagger::BranchName(Stage stage) const
{
    return Name(stage);
}

std::string Tagger::BranchName(Stage stage, Tag tag) const
{
    return Name(stage, tag);
}

std::string Tagger::TrainerName() const
{
    return "Mva" + Name();
}

std::string Tagger::FactoryFileName() const
{
    return PathName(TrainerName());
}

std::string Tagger::ExportFileName(Stage stage, Tag tag) const
{
    return PathName(Name(stage, tag));
}

std::string Tagger::ExportName() const
{
    return AnalysisName() + "-" + Name();
}
std::string Tagger::ExportFileName() const
{
    return PathName(ExportName());
}
std::string Tagger::ExportFolderName() const
{
    return AnalysisName() + "/" + ExportName();
}
std::string Tagger::ReaderName() const
{
    return ReaderName(Name());
}
std::string Tagger::ReaderName(const std::string& name) const
{
    return name + "Reader";
}
std::string Tagger::Name(Stage stage) const
{
    switch (stage) {
    case Stage::trainer :
        return Name();
    case Stage::reader :
        return ReaderName();
    }
}
std::string Tagger::Name(Stage stage, Tag tag) const
{
    std::string name = Tagger::Name(stage);
    switch (tag) {
    case Tag::signal :
        return name;
    case Tag::background :
        return BackgroundName(name);
    }
}

std::string Tagger::FileName(Stage stage, Tag tag) const
{
    switch (tag) {
    case Tag::signal :
        return SignalFileName(stage);
    case Tag::background :
        return BackgroundFileName(stage);
    }
}

std::string Tagger::SignalFileName(Stage stage) const
{
    std::string name = SignalName();
    switch (stage) {
    case Stage::trainer :
        break;
    case Stage::reader :
        name = ReaderName(name);
        break;
    }
    return PathName(name);
}
std::string Tagger::BackgroundFileName(Stage stage) const
{
    std::string name = BackgroundName();
    switch (stage) {
    case Stage::trainer :
//          TrainerName(name);
        break;
    case Stage::reader :
        name = ReaderName(name);
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
    return variables_;
}
std::vector<Observable> Tagger::Spectators() const
{
    return spectators_;
}

void Tagger::ClearTreeNames()
{
    signal_tree_names_.clear();
    background_tree_names_.clear();
}

Strings Tagger::TreeNames(Tag tag) const
{
    switch (tag) {
    case Tag::signal :
        return signal_tree_names_;
    case Tag::background :
        return background_tree_names_;
    }
}

TCut Tagger::Cut() const
{
    return TCut();
}
void Tagger::SetAnalysisName(const std::string& analysis_name)
{
    analysis_name_ = analysis_name;
}

std::string Tagger::MethodName(TMVA::Types::EMVA mva) const
{
    switch (mva) {
    case TMVA::Types::EMVA::kBDT :
        return "Bdt";
    default :
        return "";
    }
}

std::string Tagger::WeightName(TMVA::Types::EMVA mva) const
{
    return Name() + "_" + MethodName(mva) + "." + WeightFileExtension();
}

std::string Tagger::WeightFileName(TMVA::Types::EMVA mva) const
{
    return PathName(WeightName(mva), ".xml");
}

std::string Tagger::WeightFileExtension() const
{
    return "weights";
    return "";
}

std::string Tagger::WeightBranchName() const
{
    return "Info";
}
std::string Tagger::BackgroundName() const
{
    return BackgroundName(Name());
}
std::string Tagger::SignalName() const
{
    return SignalName(Name());
}
std::string Tagger::SignalName(const std::string& name) const
{
    return name;
    return name + "SG";
}
std::string Tagger::BackgroundName(const std::string& name) const
{
    return "Not" + name;
    return name + "BG";
}
void Tagger::SetTreeBranch(exroot::TreeWriter& tree_writer, Stage stage)
{
    tree_branch_ = tree_writer.NewBranch(Name(stage).c_str(), &Class());
}

void Tagger::AddVariable(float& value, const std::string& title)
{
    variables_.emplace_back(NewObservable(value, title));
}
void Tagger::AddSpectator(float& value, const std::string& title)
{
    spectators_.emplace_back(NewObservable(value, title));
}
void Tagger::ClearObservables()
{
    variables_.clear();
    spectators_.clear();
}

exroot::TreeBranch& Tagger::TreeBranch() const
{
    return *tree_branch_;
}

std::string Name(const analysis::Stage stage)
{
    switch (stage) {
    case Stage::trainer :
        return "Trainer";
    case Stage::reader :
        return "Reader";
    }
}
std::string Tagger::NiceName() const
{
    return Name();
}

std::string Tagger::Root() const
{
    return ".root";
}

std::string Tagger::PathName(const std::string& file_name, const std::string& suffix) const
{
    Error(file_name);
    return AnalysisName() + "/" + file_name + suffix;
}

}

