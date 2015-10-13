/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "fastjet/tools/MassDropTagger.hh"
#include "fastjet/tools/Filter.hh"

#include "Event.hh"
#include "Types.hh"
#include "JetInfo.hh"
#include "InfoRecombiner.hh"
#include "HiggsTagger.hh"
#include "Debug.hh"

namespace boca
{

HiggsTagger::HiggsTagger()
{
    Info();
    higgs_mass_window = 70. * GeV;
}

int HiggsTagger::Train(Event const& event, PreCuts const& pre_cuts, Tag tag) const
{
    Info(boca::Name(tag));
    Jets jets =  event.Hadrons().Jets();
    std::vector<Doublet> doublets = unordered_pairs(jets, [&](fastjet::PseudoJet const & jet_1, fastjet::PseudoJet const & jet_2) {
        return CheckDoublet(Doublet(jet_1, jet_2), pre_cuts, tag);
    });

    for (auto const & jet : jets) {
        try {
            doublets.emplace_back(CheckDoublet(Doublet(jet), pre_cuts, tag));
        } catch (...) {}
        try {
            Jets pieces = Tagger::SubJets(jet, 2);
            doublets.emplace_back(CheckDoublet(Doublet(pieces.at(0), pieces.at(1)), pre_cuts, tag));
        } catch (...) {}
    }
    doublets = SetClosestLepton(event, doublets);
    Jets higgses = Particles(event);
    return SaveEntries(doublets, higgses, tag, Id::higgs);
}

Jets HiggsTagger::Particles(Event const& event) const {
  return CopyIfParticles(event.Partons().GenParticles(), Id::higgs, Id::CP_violating_higgs);
}

Doublet HiggsTagger::CheckDoublet(Doublet doublet, PreCuts const& pre_cuts, Tag tag) const
{
//     doublet = MassDrop(doublet);
    doublet = Doublet(bottom_reader_.Multiplet(doublet.Singlet1().Jet()), bottom_reader_.Multiplet(doublet.Singlet2().Jet()));
    if (Problematic(doublet, pre_cuts, tag)) throw "problematic";
    doublet.SetTag(tag);
    return doublet;
}

bool HiggsTagger::Problematic(Doublet const& doublet, PreCuts const& pre_cuts, Tag tag) const
{
    if (Problematic(doublet, pre_cuts)) return true;
    switch (tag) {
    case Tag::signal :
//         if (std::abs(doublet.Mass() - Mass(Id::higgs)) > higgs_mass_window) return true;
//         if ((doublet.Rho() > 2 || doublet.Rho() < 0.5) && doublet.Rho() > 0) return true;
//         if (doublet.Singlet1().Bdt() < 0 || doublet.Singlet2().Bdt() < 0) return true;
        break;
    case Tag::background :
        break;
    }
    return false;
}

bool HiggsTagger::Problematic(Doublet const& doublet, PreCuts const& pre_cuts) const
{
    if (pre_cuts.PtLowerCut(Id::higgs) > at_rest && doublet.Pt() < pre_cuts.PtLowerCut(Id::higgs)) return true;
    if (pre_cuts.PtUpperCut(Id::higgs) > at_rest && doublet.Pt() > pre_cuts.PtUpperCut(Id::higgs)) return true;
    if (pre_cuts.MassLowerCut(Id::higgs) > massless && doublet.Mass() < pre_cuts.MassLowerCut(Id::higgs)) return true;
    if (pre_cuts.MassUpperCut(Id::higgs) > massless && doublet.Mass() > pre_cuts.MassUpperCut(Id::higgs)) return true;
    if (doublet.Jet().user_info<JetInfo>().VertexNumber() < 1) return true;
    if (doublet.Rho() > 2.5 || doublet.Rho() < 0.5) return true;
    if (doublet.Singlet1().Bdt() < 0 || doublet.Singlet2().Bdt() < 0) return true;
    return false;
}

std::vector<Doublet> HiggsTagger::Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const
{
    Info();
    Jets leptons = event.Leptons().leptons();
    Jets jets =  event.Hadrons().Jets();
    std::vector<Doublet> doublets = unordered_pairs(jets, [&](fastjet::PseudoJet const & jet_1, fastjet::PseudoJet const & jet_2) {
        Doublet doublet(jet_1, jet_2);
        return Multiplet(doublet, leptons, pre_cuts, reader);
    });

    for (auto const & jet : jets) {
        try {
            Doublet doublet(jet);
            doublets.emplace_back(Multiplet(doublet, leptons, pre_cuts, reader));
        } catch (...) {}
        Jets pieces = Tagger::SubJets(jet, 2);
        try {
            Doublet doublet(pieces.at(0), pieces.at(1));
            doublets.emplace_back(Multiplet(doublet, leptons, pre_cuts, reader));
        } catch (...) {}
    }
    return ReduceResult(doublets);
}

Doublet HiggsTagger::Multiplet(Doublet& doublet, Jets const& leptons, PreCuts const& pre_cuts, TMVA::Reader const& reader) const
{
//     doublet = MassDrop(doublet);
    doublet = Doublet(bottom_reader_.Multiplet(doublet.Singlet1().Jet()), bottom_reader_.Multiplet(doublet.Singlet2().Jet()));
    if (Problematic(doublet, pre_cuts)) throw "problematic";
    SetClosestLepton(doublet, leptons);
    doublet.SetBdt(Bdt(doublet, reader));
    return doublet;
}

Doublet HiggsTagger::MassDrop(Doublet const& doublet) const
{
    InfoRecombiner info_recombiner;
    fastjet::JetDefinition jet_definition(fastjet::cambridge_algorithm, doublet.DeltaR() + 2 * DetectorGeometry::JetConeSize(), &info_recombiner);
    fastjet::ClusterSequence& cluster_sequence = *new fastjet::ClusterSequence(doublet.Jet().constituents(), jet_definition);
    unsigned jet_number = 1;
    Jets exclusive_jets = cluster_sequence.exclusive_jets(int(jet_number));
    Check(exclusive_jets.size() == jet_number);
    if (exclusive_jets.empty()) {
      delete &cluster_sequence;
      return {};
    }
    cluster_sequence.delete_self_when_unused();

    fastjet::MassDropTagger mass_drop_tagger(0.667, 0.09);
    fastjet::PseudoJet mass_drop_jet = mass_drop_tagger(exclusive_jets.front());
    if (mass_drop_jet == 0) throw "no substructure";

    double radius = mass_drop_jet.pieces().at(0).delta_R(mass_drop_jet.pieces().at(1));
    radius = std::min(radius / 2, .3);
    fastjet::Filter filter(fastjet::JetDefinition(fastjet::cambridge_algorithm, radius, &info_recombiner), fastjet::SelectorNHardest(3));
    fastjet::PseudoJet filtered_jet = filter.result(mass_drop_jet);
    if (!filtered_jet.has_pieces()) throw "no pieces";
    Jets pieces = fastjet::sorted_by_pt(filtered_jet.pieces());
    if (pieces.size() < 2) throw "not enough pieces";
    return Doublet(bottom_reader_.Multiplet(pieces.at(0)), bottom_reader_.Multiplet(pieces.at(1)));
}

}
