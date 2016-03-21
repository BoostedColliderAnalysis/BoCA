/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "fastjet/tools/MassDropTagger.hh"
#include "fastjet/tools/Filter.hh"

#include "multiplets/Doublet.hh"
#include "Event.hh"
#include "Particles.hh"
#include "ClusterSequence.hh"
#include "Types.hh"
#include "HiggsTagger.hh"
#include "MomentumRange.hh"
#include "Exception.hh"
#include "DEBUG.hh"

namespace boca
{

namespace standardmodel
{

HiggsTagger::HiggsTagger()
{
    INFO0;
    higgs_mass_window = 70_GeV;
}

int HiggsTagger::Train(Event const& event, PreCuts const& pre_cuts, Tag tag) const
{
    INFO0;
    auto leptons = event.Leptons().leptons();
    return SaveEntries(Doublets(event, [&](Doublet & doublet) {
        return SetTag(doublet, leptons, pre_cuts, tag);
    }), Particles(event), tag, Id::higgs);
}

std::vector<Doublet> HiggsTagger::Doublets(Event const& event, std::function<boost::optional<Doublet>(Doublet&)> const& function) const
{
    INFO0;
    auto jets = event.Hadrons().Jets();
    MomentumRange jet_range(Id::higgs, Id::higgs);
    auto doublets = UnorderedPairs(jet_range.SofterThanMax(jets), [&](Jet const & jet_1, Jet const & jet_2) {
        Doublet doublet(jet_1, jet_2);
        if (!jet_range.BelowUpperBound(doublet)) throw boca::Problematic();
        if (auto optional = function(doublet)) return *optional;
        throw boca::Problematic();
    });
    for (auto const & jet : jet_range.HarderThanMin(jets)) {
        Doublet doublet;
        doublet.Enforce(jet);
        if (auto optional = function(doublet)) doublets.emplace_back(*optional);
    }
    return doublets;
}

std::vector<Particle> HiggsTagger::Particles(Event const& event) const
{
    INFO0;
    return CopyIfParticles(event.Partons().GenParticles(), {Id::higgs, Id::CP_violating_higgs});
}

boost::optional<Doublet> HiggsTagger::SetTag(Doublet& doublet, std::vector<Lepton>& leptons, PreCuts const& pre_cuts, Tag tag) const
{
    INFO0;
    doublet = PrepareDoublet(doublet, leptons);
    if (Problematic(doublet, pre_cuts, tag)) return boost::none;
    doublet.SetTag(tag);
    return doublet;
}

Doublet HiggsTagger::PrepareDoublet(Doublet const& doublet, std::vector<Lepton>& leptons) const
{
    INFO0;
    //     if (auto optional = MassDrop(doublet)) prepared = *optional;
    Jet jet_1 = doublet.Singlet1();
    Jet jet_2 = doublet.Singlet2();
    Doublet prepared(bottom_reader_.Multiplet(jet_1), bottom_reader_.Multiplet(jet_2));
    prepared.SetClosestLepton(leptons);
    return prepared;
}

bool HiggsTagger::Problematic(Doublet const& doublet, PreCuts const& pre_cuts, Tag tag) const
{
    INFO0;
    if (Problematic(doublet, pre_cuts)) return true;
    switch (tag) {
    case Tag::signal :
        if (pre_cuts.NotParticleRho(doublet)) return true;
        if (pre_cuts.OutSideMassWindow(doublet, higgs_mass_window, Id::higgs)) return true;
        break;
    case Tag::background :
        break;
    }
    return false;
}

bool HiggsTagger::Problematic(Doublet const& doublet, PreCuts const& pre_cuts) const
{
    INFO0;
    if (pre_cuts.ApplyCuts(Id::higgs, doublet)) return true;
    return false;
}

std::vector<Doublet> HiggsTagger::Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const
{
    INFO0;
    auto leptons = event.Leptons().leptons();
    return Doublets(event, [&](Doublet & doublet) {
        return Multiplet(doublet, leptons, pre_cuts, reader);
    });
}

boost::optional<Doublet> HiggsTagger::Multiplet(Doublet& doublet, std::vector<Lepton>& leptons, PreCuts const& pre_cuts, TMVA::Reader const& reader) const
{
    INFO0;
    doublet = PrepareDoublet(doublet, leptons);
    if (Problematic(doublet, pre_cuts)) return boost::none;
    doublet.SetBdt(Bdt(doublet, reader));
    return doublet;
}

boost::optional<Doublet> HiggsTagger::MassDrop(Doublet const& doublet) const
{
    INFO0;
    ClusterSequence cluster_sequence(doublet.Constituents(), DetectorGeometry::JetDefinition(doublet.DeltaR() + 2. * DetectorGeometry::JetConeSize()));
    auto exclusive_jets = cluster_sequence.ExclusiveJets(1);
    if (exclusive_jets.empty()) return boost::none;
    fastjet::MassDropTagger mass_drop_tagger(0.667, 0.09);
    auto mass_drop_jet = mass_drop_tagger(exclusive_jets.front());
    if (mass_drop_jet == 0) return boost::none;

    auto radius = Jet(mass_drop_jet.pieces().at(0)).DeltaRTo(mass_drop_jet.pieces().at(1));
    radius = std::min(radius / 2., 300_mrad);
    fastjet::Filter filter(DetectorGeometry::JetDefinition(radius), fastjet::SelectorNHardest(3));
    auto filtered_jet = filter.result(mass_drop_jet);
    if (!filtered_jet.has_pieces()) return boost::none;
    auto pieces = SortedByPt(JetVector(filtered_jet.pieces()));
    if (pieces.size() < 2) return boost::none;
    return Doublet(bottom_reader_.Multiplet(pieces.at(0)), bottom_reader_.Multiplet(pieces.at(1)));
}

std::string HiggsTagger::Name() const
{
    return "Higgs";
}

std::string HiggsTagger::LatexName() const
{
    return "h";
}

}

}



