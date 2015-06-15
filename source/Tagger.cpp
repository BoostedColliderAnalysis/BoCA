# include "Tagger.hh"

# include "TObjArray.h"
# include "TClonesArray.h"

# include "fastjet/ClusterSequence.hh"

# include "JetInfo.hh"
# include "Event.hh"
# include "Analysis.hh"

namespace analysis
{

std::string Tagger::analysis_name_;

Tagger::Tagger()
{
//     DebugLevel = kDebug;
    Print(kInformation, "Constructor");
}

Observable Tagger::NewObservable(float &value, const std::string &title) const
{
    Print(kInformation, "New Observable", title);
    const std::string expression = branch_name() + "." + title;
    return Observable(value, expression, title, "", "");
}

Observable Tagger::NewObservable(float &value, const std::string &title, const std::string &latex) const
{
    Print(kInformation, "New Observable", title);
    const std::string expression = branch_name() + "." + title;
    return Observable(value, expression, title, "", latex);

}

float Tagger::Bdt(const TMVA::Reader &reader)
{
    Print(kInformation, "Bdt");
    return const_cast<TMVA::Reader &>(reader).EvaluateMVA(bdt_method_name()) + 1; // get rid of the const cast
}

Jets Tagger::SubJets(const fastjet::PseudoJet &jet, const int sub_jet_number)
{
    Jets pieces;
    if (!jet.has_pieces()) return pieces;
    if (!jet.has_user_info<JetInfo>()) return pieces;
    fastjet::ClusterSequence *cluster_sequence = new fastjet::ClusterSequence(jet.pieces(), detector_geometry().SubJetDefinition);
    for (auto & piece : cluster_sequence->exclusive_jets_up_to(sub_jet_number)) {
        std::vector<Constituent> constituents;
        for (const auto & constituent : piece.constituents()) {
            if (!constituent.has_user_info<JetInfo>()) continue;
            std::vector<Constituent> piece_constituents = constituent.user_info<JetInfo>().constituents();
            constituents = Join(constituents, piece_constituents);
        }
        piece.set_user_info(new JetInfo(constituents));
        pieces.emplace_back(piece);
    }
    cluster_sequence->delete_self_when_unused();
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
    return tagger_name_;
}
void Tagger::set_tagger_name(const std::string &tagger_name)
{
    tagger_name_ = tagger_name;
    signal_file_names_ = {tagger_name};
    background_file_names_ = {"Not" + tagger_name};
}
std::string Tagger::tagger_name() const
{
    return tagger_name_;
}
std::string Tagger::factory_name() const
{
    return "Mva" + tagger_name();
}
std::string Tagger::signal_file_name(const Tagger::Stage stage) const
{
    const std::string file_name = analysis_name() + "/" + signal_name();
    switch (stage) {
    case kTrainer :
        return file_name;
    case kReader :
        return file_name + "Reader.root";
    }
}
std::string Tagger::background_file_name(const Tagger::Stage stage) const
{
    const std::string file_name = analysis_name() + "/" + background_name();
    switch (stage) {
    case kTrainer :
        return file_name;
    case kReader :
        return file_name + "Reader.root";
    }
}
std::string Tagger::reader_name() const
{
    return tagger_name_ + "Reader";
}
std::string Tagger::name(const Tagger::Stage stage) const
{
    switch (stage) {
    case kTrainer :
        return tagger_name();
    case kReader :
        return reader_name();
    }
}
std::string Tagger::name(const Tagger::Stage stage, const Object::Tag tag) const
{
    std::string name;
    switch (stage) {
    case kTrainer :
        name = tagger_name();
        break;
    case kReader :
        name = reader_name();
        break;
    }
    switch (tag) {
    case kSignal :
        return name;
    case kBackground :
        return "Not" + name;
    }
}
std::string Tagger::analysis_name() const
{
    Print(kError, "Analysis Name", analysis_name_);
    return analysis_name_;
}
std::vector< Observable > Tagger::observables() const
{
    return variables_;
}
std::vector< Observable > Tagger::spectators() const
{
    return spectators_;
}
Strings Tagger::signal_file_names() const
{
    return signal_file_names_;
}
Strings Tagger::signal_tree_names() const
{
    return signal_tree_names_;
}
void Tagger::clear_tree_names()
{
    signal_tree_names_.clear();
    background_tree_names_.clear();
}
Strings Tagger::background_file_names() const
{
    return background_file_names_;
}
Strings Tagger::background_tree_names() const
{
    return background_tree_names_;
}
TCut Tagger::cut() const
{
    return cut_;
}
void Tagger::set_analysis_name(const std::string &analysis_name)
{
    analysis_name_ = analysis_name;
}
std::string Tagger::bdt_method_name() const
{
    return "Bdt";
}
std::string Tagger::weight_branch_name() const
{
    return "Info";
}
std::string Tagger::background_name() const
{
    return "Not" + tagger_name_;
}
std::string Tagger::signal_name() const
{
    return tagger_name_;
}
int Tagger::GetBdt(Event &, PreCuts &, const TMVA::Reader &)
{
    Print(kError, "Get Bdt", "should be subclassed");
    return 0;
}
int Tagger::Train(Event &, PreCuts &, const Object::Tag)
{
    Print(kError, "Train", "Should be subclassed");
    return 0;
}
float Tagger::GetBranches(Event &, Tagger::Stage, const Object::Tag)
{
    Print(kError, "get branches", "Should be subclassed", "should be deleted");
    return 0;
}
float Tagger::ReadBdt(const TClonesArray &, const int)
{
    Print(kError, "Read Bdt", "should be subclassed");
    return 0;
}
DetectorGeometry Tagger::detector_geometry() const
{
    return detector_geometry_;
}
void Tagger::SetTreeBranch(exroot::TreeWriter &tree_writer, const Tagger::Stage stage)
{
    tree_branch_ = tree_writer.NewBranch(name(stage).c_str(), &Class());
}
float Tagger::Bdt(Event &, const TMVA::Reader &) const
{
    Print(kError, "Bdt", "should be subclassed");
    return 0;
}
void Tagger::AddVariable(float &value, const std::string &title)
{
    variables_.emplace_back(NewObservable(value, title));
}
void Tagger::AddVariable(float &value, const std::string &title, const std::string &latex)
{
    variables_.emplace_back(NewObservable(value, title, latex));
}
void Tagger::AddSpectator(float &value, const std::string &title)
{
    spectators_.emplace_back(NewObservable(value, title));
}
void Tagger::ClearVectors()
{
    variables_.clear();
    spectators_.clear();
}
int Tagger::max_combi() const
{
    return 4;
}
exroot::TreeBranch &Tagger::tree_branch()
{
    return *tree_branch_;
}

}
