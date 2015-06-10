# include "Tagger.hh"

# include "TObjArray.h"
# include "TClonesArray.h"

# include "fastjet/ClusterSequence.hh"

# include "JetInfo.hh"
# include "Event.hh"
# include "Analysis.hh"

analysis::Observable::Observable(float &value, const std::string &expression, const std::string &title, const std::string &unit, const std::string &latex)
{
    value_ = &value;
    expression_ = expression;
    title_ = title;
    unit_ = unit;
    if (value == int(value)) type_ = 'I';
    else type_ = 'F';
}

float *analysis::Observable::value() const
{
    return value_;
}

std::string analysis::Observable::expression() const
{
    return expression_;
}

std::string analysis::Observable::title() const
{
    return title_;
}

std::string analysis::Observable::unit() const
{
    return unit_;
}

char analysis::Observable::type() const
{
    return type_;
}

std::string analysis::Tagger::analysis_name_;

analysis::Tagger::Tagger()
{
//     DebugLevel = kDebug;
    Print(kInformation, "Constructor");
    bdt_method_name_ = "Bdt";
    weight_branch_name_ = "Info";
}


analysis::Observable analysis::Tagger::NewObservable(float &value, const std::string &title) const
{
    Print(kInformation, "New Observable", title);
    const std::string expression = branch_name() + "." + title;
    return Observable(value, expression, title, "", "");
}

analysis::Observable analysis::Tagger::NewObservable(float &value, const std::string &title, const std::string &latex) const
{
    Print(kInformation, "New Observable", title);
    const std::string expression = branch_name() + "." + title;
    return Observable(value, expression, title, "", latex);

}

float analysis::Tagger::Bdt(const TMVA::Reader &reader)
{
    Print(kInformation, "Bdt");
    return const_cast<TMVA::Reader &>(reader).EvaluateMVA(bdt_method_name()) + 1; // get rid of the const cast
}

analysis::Jets analysis::Tagger::SubJets(const fastjet::PseudoJet &jet, const int sub_jet_number)
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
            constituents = JoinVectors(constituents, piece_constituents);
        }
        piece.set_user_info(new JetInfo(constituents));
        pieces.emplace_back(piece);
    }
    cluster_sequence->delete_self_when_unused();
    return pieces;
}
