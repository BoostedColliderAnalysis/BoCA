/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "fastjet/tools/MassDropTagger.hh"
#include "fastjet/tools/Filter.hh"

#include "boca/multiplets/Doublet.hh"
#include "boca/Event.hh"
#include "boca/multiplets/Particles.hh"
#include "boca/fastjet/ClusterSequence.hh"
#include "boca/generic/Types.hh"
#include "boca/standardmodel/tagger/Higgs.hh"
#include "boca/MomentumRange.hh"
#include "boca/generic/Exception.hh"
#include "boca/generic/DEBUG_MACROS.hh"

namespace boca
{

namespace standardmodel
{

namespace tagger
{

Higgs::Higgs()
{
    INFO0;
    higgs_mass_window = 70_GeV;
}

int Higgs::Train(Event const& event, PreCuts const& pre_cuts, Tag tag)
{
    INFO0;
    auto leptons = event.Leptons();
    return SaveEntries(Doublets(event, [&](Doublet & doublet) {
        return SetTag(doublet, leptons, pre_cuts, tag);
    }), Particles(event), tag, Id::higgs);
}

std::vector<Doublet> Higgs::Doublets(Event const& event, std::function<boost::optional<Doublet>(Doublet&)> const& function) const
{
    INFO0;
    auto jets = event.Jets();
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

std::vector<Particle> Higgs::Particles(Event const& event) const
{
    INFO0;
    return CopyIfParticles(event.GenParticles(), {Id::higgs, Id::CP_violating_higgs});
}

boost::optional<Doublet> Higgs::SetTag(Doublet& doublet, std::vector<Lepton>& leptons, PreCuts const& pre_cuts, Tag tag)
{
    INFO0;
    doublet = PrepareDoublet(doublet, leptons);
    if (Problematic(doublet, pre_cuts, tag)) return boost::none;
    doublet.SetTag(tag);
    return doublet;
}

Doublet Higgs::PrepareDoublet(Doublet const& doublet, std::vector<Lepton>& leptons)
{
    INFO0;
    //     if (auto optional = MassDrop(doublet)) prepared = *optional;
    Jet jet_1 = doublet.Singlet1();
    Jet jet_2 = doublet.Singlet2();
    Doublet prepared(bottom_reader_.Multiplet(jet_1), bottom_reader_.Multiplet(jet_2));
    prepared.SetClosestLepton(leptons);
    return prepared;
}

bool Higgs::Problematic(Doublet const& doublet, PreCuts const& pre_cuts, Tag tag) const
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

bool Higgs::Problematic(Doublet const& doublet, PreCuts const& pre_cuts) const
{
    INFO0;
    if (pre_cuts.ApplyCuts(Id::higgs, doublet)) return true;
    return false;
}

std::vector<Doublet> Higgs::Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader)
{
    INFO0;
    auto leptons = event.Leptons();
    return Doublets(event, [&](Doublet & doublet) {
        return Multiplet(doublet, leptons, pre_cuts, reader);
    });
}

boost::optional<Doublet> Higgs::Multiplet(Doublet& doublet, std::vector<Lepton>& leptons, PreCuts const& pre_cuts, TMVA::Reader const& reader)
{
    INFO0;
    doublet = PrepareDoublet(doublet, leptons);
    if (Problematic(doublet, pre_cuts)) return boost::none;
    doublet.SetBdt(Bdt(doublet, reader));
    return doublet;
}

boost::optional<Doublet> Higgs::MassDrop(Doublet const& doublet)
{
    INFO0;
    ClusterSequence cluster_sequence(doublet.Constituents(), Settings::JetDefinition(doublet.DeltaR() + 2. * Settings::JetConeSize()));
    auto exclusive_jets = cluster_sequence.ExclusiveJets(1);
    if (exclusive_jets.empty()) return boost::none;
    fastjet::MassDropTagger mass_drop_tagger(0.667, 0.09);
    auto mass_drop_jet = mass_drop_tagger(exclusive_jets.front());
    if (mass_drop_jet == 0) return boost::none;

    auto radius = Jet(mass_drop_jet.pieces().at(0)).DeltaRTo(mass_drop_jet.pieces().at(1));
    radius = std::min(radius / 2., 300_mrad);
    fastjet::Filter filter(Settings::JetDefinition(radius), fastjet::SelectorNHardest(3));
    auto filtered_jet = filter.result(mass_drop_jet);
    if (!filtered_jet.has_pieces()) return boost::none;
    auto pieces = SortedByPt(JetVector(filtered_jet.pieces()));
    if (pieces.size() < 2) return boost::none;
    return Doublet(bottom_reader_.Multiplet(pieces.at(0)), bottom_reader_.Multiplet(pieces.at(1)));
}

std::string Higgs::Name() const
{
    return "Higgs";
}

latex::String Higgs::LatexName() const
{
    return {"h", true};
}

}

}

}


