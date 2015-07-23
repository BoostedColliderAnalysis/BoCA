#include "Tagger.hh"

#include "TObjArray.h"
#include "TClonesArray.h"

#include "fastjet/ClusterSequence.hh"

#include "JetInfo.hh"
#include "Event.hh"
#include "Analysis.hh"
#include "Debug.hh"

namespace analysis {

std::string Tagger::analysis_name_;

Observable Tagger::NewObservable(float& value, const std::string& title) const
{
    Info(title);
    const std::string expression = branch_name() + "." + title;
    return Observable(value, expression, title, "");
}

float Tagger::Bdt(const TMVA::Reader& reader) const
{
    Info();
    return const_cast<TMVA::Reader&>(reader).EvaluateMVA(bdt_method_name()) + 1;  // TODO get rid of the const cast
}

Jets Tagger::SubJets(const fastjet::PseudoJet& jet, int sub_jet_number) const
{
    Jets pieces;
    if (!jet.has_pieces())
        return pieces;
    if (!jet.has_user_info<JetInfo>())
        return pieces;
    fastjet::ClusterSequence& cluster_sequence = *new fastjet::ClusterSequence(jet.constituents(), DetectorGeometry::SubJetDefinition());
    for (auto& piece : cluster_sequence.exclusive_jets_up_to(sub_jet_number)) {
        std::vector<Constituent> constituents;
        for (const auto& constituent : piece.constituents()) {
            if (!constituent.has_user_info<JetInfo>())
                continue;
            std::vector<Constituent> piece_constituents = constituent.user_info<JetInfo>().constituents();
            constituents = Join(constituents, piece_constituents);
        }
        piece.set_user_info(new JetInfo(constituents));
        pieces.emplace_back(piece);
    }
    cluster_sequence.delete_self_when_unused();
    return pieces;
}

void Tagger::AddSignalTreeName(const std::string signal_tree_name)
{
    signal_tree_names_.emplace_back(signal_tree_name);
}

void Tagger::AddBackgroundTreeName(const std::string background_tree_name)
{
    background_tree_names_.emplace_back(background_tree_name);
}

std::string Tagger::branch_name() const
{
    return Name();
}
std::string Tagger::factory_name() const
{
    return "Mva" + Name();
}
std::string Tagger::export_name() const
{
    return analysis_name() + "-" + Name();
}
std::string Tagger::reader_name() const
{
    return reader(Name());
}
std::string Tagger::reader(const std::string& name) const
{
    return name + "Reader";
}
std::string Tagger::Name(const Stage stage) const
{
    switch (stage) {
    case Stage::trainer :
        return Name();
    case Stage::reader :
        return reader_name();
    }
}
std::string Tagger::Name(const Stage stage,  Tag tag) const
{
    std::string name = Tagger::Name(stage);
    switch (tag) {
    case Tag::signal :
        return name;
    case Tag::background :
        return background(name);
    }
}
std::string Tagger::signal_file_name(const Stage stage) const
{
    const std::string name = analysis_name() + "/" + signal_name();
    switch (stage) {
    case Stage::trainer :
        return name;
    case Stage::reader :
        return reader(name);
    }
}
std::string Tagger::background_file_name(const Stage stage) const
{
    const std::string name = analysis_name() + "/" + background_name();
    switch (stage) {
    case Stage::trainer :
        return name;
    case Stage::reader :
        return reader(name);
    }
}
std::string Tagger::analysis_name() const
{
    Debug();
    return analysis_name_;
}
std::vector<Observable> Tagger::variables() const
{
    return variables_;
}
std::vector<Observable> Tagger::spectators() const
{
    return spectators_;
}
Strings Tagger::signal_tree_names() const
{
    return signal_tree_names_;
}
void Tagger::ClearTreeNames()
{
    signal_tree_names_.clear();
    background_tree_names_.clear();
}
Strings Tagger::background_tree_names() const
{
    return background_tree_names_;
}
TCut Tagger::cut() const
{
    return TCut();
}
void Tagger::set_analysis_name(const std::string& analysis_name)
{
    analysis_name_ = analysis_name;
}

std::string Tagger::bdt_method_name() const
{
    return "Bdt";
}

std::string Tagger::bdt_weight_name() const
{
    return Name() + "_" + bdt_method_name() + "." + weight_file_extension() + ".xml";
}

std::string Tagger::weight_file_extension() const
{
    return "weights";
    return "";
}

std::string Tagger::weight_branch_name() const
{
    return "Info";
}
std::string Tagger::background_name() const
{
    return background(Name());
}
std::string Tagger::signal_name() const
{
    return signal(Name());
}
std::string Tagger::signal(const std::string& name) const
{
    return name;
}
std::string Tagger::background(const std::string& name) const
{
    return "Not" + name;
    return name + "BG";
}
void Tagger::SetTreeBranch(exroot::TreeWriter& tree_writer, const Stage stage)
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
int Tagger::CandidatesMax() const
{
    return 4;
}
exroot::TreeBranch& Tagger::tree_branch() const
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

}

