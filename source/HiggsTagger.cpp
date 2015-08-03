#include "HiggsTagger.hh"
#include "Event.hh"
#include "Predicate.hh"
#include "fastjet/tools/MassDropTagger.hh"
#include "fastjet/tools/Filter.hh"
#include "JetInfo.hh"
#include "Debug.hh"

namespace analysis
{

HiggsTagger::HiggsTagger()
{
    Info();
    DefineVariables();
}

int HiggsTagger::Train(const Event& event, const PreCuts& pre_cuts, Tag tag) const
{
    Info(analysis::Name(tag));
    Jets jets =  bottom_reader_.Multiplets(event);
    std::vector<Doublet> doublets = unordered_pairs(jets, [&](const fastjet::PseudoJet & jet_1, const fastjet::PseudoJet & jet_2) {
        Doublet doublet(jet_1, jet_2);
        doublet = MassDrop(doublet);
        if (Problematic(doublet, pre_cuts, tag)) throw "problematic";
        doublet.SetTag(tag);
        return doublet;
    });
    for (const auto & jet : jets) {
        size_t sub_jet_number = 2;
        Jets pieces = bottom_reader_.SubMultiplet(jet, sub_jet_number);
        if (pieces.size() < sub_jet_number) {
            continue;
        }
        Doublet doublet(pieces.at(0), pieces.at(1));
        try {
            doublet = MassDrop(doublet);
        } catch (...) {
            continue;
        }
        if (Problematic(doublet, pre_cuts, tag)) {
            continue;
        }
        doublet.SetTag(tag);
        doublets.emplace_back(doublet);
    }
    for (const auto & jet : jets) {
        Doublet doublet(jet);
        try {
            doublet = MassDrop(doublet);
        } catch (...) {
            continue;
        }
        if (Problematic(doublet, pre_cuts, tag)) {
            continue;
        }
        doublet.SetTag(tag);
        doublets.emplace_back(doublet);
    }
    Jets higgses = CopyIfParticles(event.Partons().GenParticles(), Id::higgs, Id::CP_violating_higgs);
    return SaveEntries(BestMatches(doublets, higgses, tag));
}

bool HiggsTagger::Problematic(const Doublet& doublet, const PreCuts& pre_cuts, Tag tag) const
{
    if (Problematic(doublet, pre_cuts)) {
        return true;
    }
    switch (tag) {
    case Tag::signal :
        if (std::abs(doublet.Jet().m() - Mass(Id::higgs)) > higgs_mass_window) {
            return true;
        }
        if ((doublet.Rho() > 2 || doublet.Rho() < 0.5) && doublet.Rho() > 0) {
            return true;
        }
        break;
    case Tag::background :
        break;
    }
    return false;
}

bool HiggsTagger::Problematic(const Doublet& doublet, const PreCuts& pre_cuts) const
{
    if (pre_cuts.PtLowerCut(Id::higgs) > 0 && pre_cuts.PtLowerCut(Id::higgs) < doublet.Jet().pt()) {
        return true;
    }
    if (pre_cuts.PtUpperCut(Id::higgs) > 0 && pre_cuts.PtUpperCut(Id::higgs) > doublet.Jet().pt()) {
        return true;
    }
    if (pre_cuts.MassUpperCut(Id::higgs) > 0 && pre_cuts.MassUpperCut(Id::higgs) > doublet.Jet().m()) {
        return true;
    }
    return false;
}

std::vector<Doublet>  HiggsTagger::Multiplets(const Event& event, const PreCuts& pre_cuts, const TMVA::Reader& reader) const
{
    Info();
    Jets jets =  bottom_reader_.Multiplets(event);
    std::vector<Doublet> doublets = unordered_pairs(jets, [&](const fastjet::PseudoJet & jet_1, const fastjet::PseudoJet & jet_2) {
        Doublet doublet(jet_1, jet_2);
        doublet = MassDrop(doublet);
        if (Problematic(doublet, pre_cuts)) throw "problematic";
        doublet.SetBdt(Bdt(doublet, reader));
        return doublet;
    });
    for (const auto & jet : jets) {
        size_t sub_jet_number = 2;
        Jets pieces = bottom_reader_.SubMultiplet(jet, sub_jet_number);
        if (pieces.size() < sub_jet_number) continue;
        Doublet doublet(pieces.at(0), pieces.at(1));
        try {
            doublet = MassDrop(doublet);
        } catch (...) {
            continue;
        }
        if (Problematic(doublet, pre_cuts)) {
            continue;
        }
        doublet.SetBdt(Bdt(doublet, reader));
        doublets.emplace_back(doublet);
    }
    for (const auto & jet : jets) {
        Doublet doublet(jet);
        try {
            doublet = MassDrop(doublet);
        } catch (...) {
            continue;
        }
        if (Problematic(doublet, pre_cuts)) {
            continue;
        }
        doublet.SetBdt(Bdt(doublet, reader));
        doublets.emplace_back(doublet);
    }
    return ReduceResult(doublets);
}

Doublet HiggsTagger::MassDrop(const Doublet& doublet) const
{
    InfoRecombiner info_recombiner;
    fastjet::JetDefinition jet_definition(fastjet::cambridge_algorithm, 2 * doublet.DeltaR(), &info_recombiner);
    fastjet::ClusterSequence& cluster_sequence = *new fastjet::ClusterSequence(doublet.Jet().constituents(), jet_definition);
    Jets exclusive_jets = cluster_sequence.exclusive_jets_up_to(1);
    cluster_sequence.delete_self_when_unused();

    fastjet::MassDropTagger mass_drop_tagger(0.667, 0.09);
    fastjet::PseudoJet mass_drop_jet = mass_drop_tagger(exclusive_jets.front());

    if (mass_drop_jet == 0) {
        throw "no substructure";
    }

    float radius = mass_drop_jet.pieces().at(0).delta_R(mass_drop_jet.pieces().at(1)) / 2;
    size_t sub_jet_number = 3;
    fastjet::Filter filter(fastjet::JetDefinition(fastjet::cambridge_algorithm, radius, &info_recombiner), fastjet::SelectorNHardest(sub_jet_number));
    fastjet::PseudoJet filtered_jet = filter(mass_drop_jet);
    if (!filtered_jet.has_pieces()) {
        throw "no pieces";
    }
    if (filtered_jet.pieces().size() < 2) {
        throw "no enough pieces";
    }

    fastjet::PseudoJet jet_1 = filtered_jet.pieces().at(0);
    if (!jet_1.has_constituents()) {
        throw "no constituents";
    }
    std::vector<Constituent> constituents_1;
    for (const auto & constituent : jet_1.constituents()) {
        if (!constituent.has_user_info<JetInfo>()) {
            continue;
        }
        constituents_1 = Join(constituents_1, constituent.user_info<JetInfo>().constituents());
    }
    if (constituents_1.empty()) {
        throw "no constituents";
    }
    jet_1.set_user_info(new JetInfo(constituents_1));

    fastjet::PseudoJet jet_2 = filtered_jet.pieces().at(1);
    if (!jet_2.has_constituents()) {
        throw "no constituents";
    }
    std::vector<Constituent> constituents_2;
    for (const auto & constituent : jet_2.constituents()) {
        if (!constituent.has_user_info<JetInfo>()) {
            continue;
        }
        constituents_2 = Join(constituents_2, constituent.user_info<JetInfo>().constituents());
    }
    if (constituents_2.empty()) {
        throw "no constituents";
    }
    jet_2.set_user_info(new JetInfo(constituents_2));

    Doublet filtered_doublet(bottom_reader_.Multiplet(jet_1), bottom_reader_.Multiplet(jet_2));
    return filtered_doublet;

}

}

