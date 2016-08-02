/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "boca/standardmodel/tagger/ZHadronic.hh"
#include "boca/MomentumRange.hh"
#include "boca/Event.hh"
#include "boca/multiplets/Particles.hh"
#include "boca/generic/Exception.hh"
#include "boca/generic/DEBUG.hh"

namespace boca
{

namespace standardmodel
{

namespace tagger {

ZHadronic::ZHadronic()
{
    INFO0;
    z_mass_window = 50_GeV;
}

int ZHadronic::Train(Event const& event, boca::PreCuts const& pre_cuts, Tag tag)
{
    INFO0;
    return SaveEntries(Doublets(event, [&](Doublet & doublet) {
        return SetTag(doublet, pre_cuts, tag);
    }), Particles(event), tag, Id::Z);
}

std::vector<Doublet> ZHadronic::Doublets(Event const& event, std::function<boost::optional<Doublet>(Doublet&)> function)
{
    INFO0;
    auto jets = event.Jets();
    MomentumRange jet_range(Id::Z, Id::Z);
    std::vector<Jet> soft;
    for (auto & jet : jet_range.SofterThanMax(jets)) soft.emplace_back(bottom_reader_.Multiplet(jet));

    auto doublets = UnorderedPairs(soft, [&](Jet const & jet_1, Jet const & jet_2) {
        Doublet doublet(jet_1, jet_2);
        if (!jet_range.BelowUpperBound(doublet)) throw boca::Problematic();
        if (auto optional = function(doublet)) return *optional;
        else throw boca::Problematic();
    });

    for (auto const & jet : jet_range.HarderThanMin(jets)) {
        Doublet doublet;
        doublet.Enforce(bottom_reader_.SubMultiplet(jet, 2));
        if (auto optional = function(doublet)) doublets.emplace_back(*optional);
    }
    return doublets;
}

boost::optional<Doublet> ZHadronic::SetTag(Doublet doublet, PreCuts const& pre_cuts, Tag tag) const
{
    INFO0;
    if (Problematic(doublet, pre_cuts, tag)) return boost::none;
    doublet.SetTag(tag);
    return doublet;
}

std::vector<Particle> ZHadronic::Particles(Event const& event) const
{
    INFO0;
    return CopyIfParticle(event.GenParticles(), Id::Z);
}

bool ZHadronic::Problematic(boca::Doublet const& doublet, boca::PreCuts const& pre_cuts, Tag tag) const
{
    INFO0;
    if (Problematic(doublet, pre_cuts))return true;
    switch (tag) {
    case Tag::signal :
        if (pre_cuts.NotParticleRho(doublet)) return true;
        if (boost::units::abs(doublet.Mass() - MassOf(Id::Z)) > z_mass_window) return true;
        break;
    case Tag::background :
        break;
    }
    return false;
}

bool ZHadronic::Problematic(boca::Doublet const& doublet, boca::PreCuts const& pre_cuts) const
{
    INFO0;
    if (pre_cuts.ApplyCuts(Id::Z, doublet)) return true;
    return false;
}

std::vector<Doublet> ZHadronic::Multiplets(Event const& event, boca::PreCuts const& pre_cuts, TMVA::Reader const& reader)
{
    INFO0;
    return Doublets(event, [&](Doublet & doublet) {
        return Multiplet(doublet, pre_cuts, reader);
    });
}

boost::optional<Doublet> ZHadronic::Multiplet(Doublet& doublet, PreCuts const& pre_cuts, TMVA::Reader const& reader)
{
    INFO0;
    if (Problematic(doublet, pre_cuts)) return boost::none;
    doublet.SetBdt(Bdt(doublet, reader));
    return doublet;
}

std::string ZHadronic::Name() const
{
    return "ZHadronic";
}

latex::String ZHadronic::LatexName() const
{
    return {"Z", true};
}

}

}

}