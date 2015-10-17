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
#include "Exception.hh"
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
    Info();
    Jets leptons = event.Leptons().leptons();
    return SaveEntries(Doublets(event, [&](Doublet & doublet) {
        return CheckDoublet(doublet, leptons, pre_cuts, tag);
    }), Particles(event), tag, Id::higgs);
}

std::vector<Doublet> HiggsTagger::Doublets(Event const& event, std::function<Doublet(Doublet&)> const& function) const
{
    Info();
    Jets jets =  event.Hadrons().Jets();
    std::vector<Doublet> doublets = unordered_pairs(jets, [&](fastjet::PseudoJet const & jet_1, fastjet::PseudoJet const & jet_2) {
        Doublet doublet(jet_1, jet_2);
        return function(doublet);
    });
    for (auto const & jet : jets) {
        try {
            Doublet doublet(jet);
            doublets.emplace_back(function(doublet));
        } catch (std::exception const&) {}
        try {
            Jets pieces = Tagger::SubJets(jet, 2);
            Doublet doublet(pieces.at(0), pieces.at(1));
            doublets.emplace_back(function(doublet));
        } catch (std::exception const&) {}
    }
    return doublets;
}

Jets HiggsTagger::Particles(Event const& event) const
{
    Info();
    return CopyIfParticles(event.Partons().GenParticles(), Id::higgs, Id::CP_violating_higgs);
}

Doublet HiggsTagger::CheckDoublet(Doublet& doublet, Jets const& leptons, PreCuts const& pre_cuts, Tag tag) const
{
    Info();
//     doublet = MassDrop(doublet);
    doublet = Doublet(bottom_reader_.Multiplet(doublet.Singlet1().Jet()), bottom_reader_.Multiplet(doublet.Singlet2().Jet()));
    if (Problematic(doublet, pre_cuts, tag)) throw boca::Problematic();
    doublet.SetTag(tag);
    SetClosestLepton(doublet, leptons);
    return doublet;
}

bool HiggsTagger::Problematic(Doublet const& doublet, PreCuts const& pre_cuts, Tag tag) const
{
    Info();
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
    Info();
    if (pre_cuts.ApplyCuts(Id::higgs, doublet)) return true;
    if (pre_cuts.CutOnRho(doublet)) return true;
//     if (doublet.Jet().user_info<JetInfo>().VertexNumber() < 1) return true;
    if (doublet.Singlet1().Bdt() < 0 || doublet.Singlet2().Bdt() < 0) return true;
    return false;
}

std::vector<Doublet> HiggsTagger::Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const
{
    Info();
    Jets leptons = event.Leptons().leptons();
    return ReduceResult(Doublets(event, [&](Doublet & doublet) {
        return Multiplet(doublet, leptons, pre_cuts, reader);
    }));
}

Doublet HiggsTagger::Multiplet(Doublet& doublet, Jets const& leptons, PreCuts const& pre_cuts, TMVA::Reader const& reader) const
{
    Info();
//     doublet = MassDrop(doublet);
    doublet = Doublet(bottom_reader_.Multiplet(doublet.Singlet1().Jet()), bottom_reader_.Multiplet(doublet.Singlet2().Jet()));
    if (Problematic(doublet, pre_cuts)) throw boca::Problematic();
    SetClosestLepton(doublet, leptons);
    doublet.SetBdt(Bdt(doublet, reader));
    return doublet;
}

Doublet HiggsTagger::MassDrop(Doublet const& doublet) const
{
    Info();
    InfoRecombiner info_recombiner;
    fastjet::JetDefinition jet_definition(fastjet::cambridge_algorithm, doublet.DeltaR() + 2 * DetectorGeometry::JetConeSize(), &info_recombiner);
    fastjet::ClusterSequence& cluster_sequence = *new fastjet::ClusterSequence(doublet.Jet().constituents(), jet_definition);
    unsigned jet_number = 1;
    Jets exclusive_jets = cluster_sequence.exclusive_jets(int(jet_number));
    Check(exclusive_jets.size() == jet_number);
    if (exclusive_jets.empty()) {
        delete &cluster_sequence;
        throw Empty();
    }
    cluster_sequence.delete_self_when_unused();

    fastjet::MassDropTagger mass_drop_tagger(0.667, 0.09);
    fastjet::PseudoJet mass_drop_jet = mass_drop_tagger(exclusive_jets.front());
    if (mass_drop_jet == 0) throw Empty();

    double radius = mass_drop_jet.pieces().at(0).delta_R(mass_drop_jet.pieces().at(1));
    radius = std::min(radius / 2, .3);
    fastjet::Filter filter(fastjet::JetDefinition(fastjet::cambridge_algorithm, radius, &info_recombiner), fastjet::SelectorNHardest(3));
    fastjet::PseudoJet filtered_jet = filter.result(mass_drop_jet);
    if (!filtered_jet.has_pieces()) throw Empty();
    Jets pieces = fastjet::sorted_by_pt(filtered_jet.pieces());
    if (pieces.size() < 2) throw Empty();
    return Doublet(bottom_reader_.Multiplet(pieces.at(0)), bottom_reader_.Multiplet(pieces.at(1)));
}

}
