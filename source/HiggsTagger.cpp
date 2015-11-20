#include "fastjet/tools/MassDropTagger.hh"
#include "fastjet/tools/Filter.hh"

#include "HiggsTagger.hh"
#include "Event.hh"
#include "Types.hh"
#include "JetInfo.hh"
#include "InfoRecombiner.hh"
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
    Info(analysis::TagName(tag));
//     Jets jets =  bottom_reader_.Multiplets(event);
    Jets jets =  event.Hadrons().Jets();
    std::vector<Doublet> doublets = unordered_pairs(jets, [&](const fastjet::PseudoJet & jet_1, const fastjet::PseudoJet & jet_2) {
        Doublet doublet(jet_1, jet_2);
        doublet = MassDrop(doublet);
        if (Problematic(doublet, pre_cuts, tag)) throw "problematic";
        doublet.SetTag(tag);
        return doublet;
    });
    for (const auto & jet : jets) {
        unsigned sub_jet_number = 2;
//         Jets pieces = bottom_reader_.SubMultiplet(jet, sub_jet_number);
        Jets pieces = Tagger::SubJets(jet, sub_jet_number);
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
    doublets = SetClosestLepton(event, doublets);
    Jets higgses = CopyIfParticles(event.Partons().GenParticles(), Id::higgs, Id::CP_violating_higgs);
//     std::vector<Doublet> matches = BestMatches(doublets, higgses, tag);
//     if (tag == Tag::signal && matches.size() > higgses.size()) return 0;
    return SaveEntries(doublets, higgses, tag);
}

bool HiggsTagger::Problematic(const Doublet& doublet, const PreCuts& pre_cuts, Tag tag) const
{
    if (Problematic(doublet, pre_cuts)) return true;
    switch (tag) {
    case Tag::signal :
        if (std::abs(doublet.Jet().m() - Mass(Id::higgs)) > higgs_mass_window) return true;
        if ((doublet.Rho() > 2 || doublet.Rho() < 0.5) && doublet.Rho() > 0) return true;
        if (doublet.Singlet1().Bdt() < 0 || doublet.Singlet2().Bdt() < 0) return true;
        break;
    case Tag::background :
        break;
    }
    return false;
}

bool HiggsTagger::Problematic(const Doublet& doublet, const PreCuts& pre_cuts) const
{
    if (pre_cuts.PtLowerCut(Id::higgs) > 0 && pre_cuts.PtLowerCut(Id::higgs) > doublet.Jet().pt()) return true;
    if (pre_cuts.PtUpperCut(Id::higgs) > 0 && pre_cuts.PtUpperCut(Id::higgs) < doublet.Jet().pt()) return true;
    if (pre_cuts.MassUpperCut(Id::higgs) > 0 && pre_cuts.MassUpperCut(Id::higgs) < doublet.Jet().m()) return true;
    if (pre_cuts.MassLowerCut(Id::higgs) > 0 && pre_cuts.MassLowerCut(Id::higgs) < doublet.Jet().m()) return true;
    return false;
}

std::vector<Doublet> HiggsTagger::Multiplets(const Event& event, const PreCuts& pre_cuts, const TMVA::Reader& reader) const
{
    Info();
    Jets leptons = event.Leptons().leptons();
    if(leptons.empty()) return {};
//     Jets jets =  bottom_reader_.Multiplets(event);
    Jets jets =  event.Hadrons().Jets();
    std::vector<Doublet> doublets = unordered_pairs(jets, [&](const fastjet::PseudoJet & jet_1, const fastjet::PseudoJet & jet_2) {
        Doublet doublet(jet_1, jet_2);
        doublet = MassDrop(doublet);
        if (Problematic(doublet, pre_cuts)) throw "problematic";
        SetClosestLepton(doublet, leptons);
        doublet.SetBdt(Bdt(doublet, reader));
        return doublet;
    });
    for (const auto & jet : jets) {
        size_t sub_jet_number = 2;
//         Jets pieces = bottom_reader_.SubMultiplet(jet, sub_jet_number);
        Jets pieces = Tagger::SubJets(jet, sub_jet_number);
        if (pieces.size() < sub_jet_number) continue;
        Doublet doublet(pieces.at(0), pieces.at(1));
        try {
            doublet = MassDrop(doublet);
            SetClosestLepton(doublet, leptons);
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
            SetClosestLepton(doublet, leptons);
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
    fastjet::JetDefinition jet_definition(fastjet::cambridge_algorithm, doublet.DeltaR() + 2 * DetectorGeometry::JetConeSize(), &info_recombiner);
    fastjet::ClusterSequence& cluster_sequence = *new fastjet::ClusterSequence(doublet.Jet().constituents(), jet_definition);
    unsigned jet_number = 1;
    Jets exclusive_jets = cluster_sequence.exclusive_jets(int(jet_number));
    Check(exclusive_jets.size() == jet_number);
    cluster_sequence.delete_self_when_unused();

    fastjet::MassDropTagger mass_drop_tagger(0.667, 0.09);
    fastjet::PseudoJet mass_drop_jet = mass_drop_tagger(exclusive_jets.front());
    if (mass_drop_jet == 0) throw "no substructure";

    double radius = mass_drop_jet.pieces().at(0).delta_R(mass_drop_jet.pieces().at(1));
    radius = std::min(radius / 2,0.3);
    unsigned sub_jet_number = 3;
    fastjet::Filter filter(fastjet::JetDefinition(fastjet::cambridge_algorithm, radius, &info_recombiner), fastjet::SelectorNHardest(sub_jet_number));
    fastjet::PseudoJet filtered_jet = filter(mass_drop_jet);
    if (!filtered_jet.has_pieces()) throw "no pieces";
    Jets pieces = fastjet::sorted_by_pt(filtered_jet.pieces());
    if (pieces.size() < 2) throw "no enough pieces";
    fastjet::PseudoJet jet_1 = pieces.at(0);
    fastjet::PseudoJet jet_2 = pieces.at(1);

    Doublet filtered_doublet(bottom_reader_.Multiplet(jet_1), bottom_reader_.Multiplet(jet_2));
    return filtered_doublet;
}

}
