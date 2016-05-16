/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "boca/standardmodel/BosonTagger.hh"
#include "boca/Event.hh"
#include "boca/multiplets/Particles.hh"
#include "boca/multiplets/Doublet.hh"
#include "boca/MomentumRange.hh"
#include "boca/generic/Exception.hh"
// #define DEBUGGING
#include "boca/generic/DEBUG.hh"

namespace boca
{


namespace standardmodel
{

BosonTagger::BosonTagger()
{
    INFO0;
    boson_mass_window = 80_GeV;
}

int BosonTagger::Train(Event const& event, PreCuts const& pre_cuts, Tag tag)
{
    INFO0;
    return SaveEntries(Doublets(event, [&](Doublet & doublet) {
        return CheckDoublet(doublet, pre_cuts, tag);
    }), Particles(event), tag);
}

boost::optional<Doublet> BosonTagger::CheckDoublet(Doublet doublet, PreCuts const& pre_cuts, Tag tag) const
{
    INFO0;
    if (Problematic(doublet, pre_cuts, tag)) return boost::none;
    doublet.SetTag(tag);
    return doublet;
}

std::vector<Doublet> BosonTagger::Doublets(Event const& event, std::function<boost::optional<Doublet>(Doublet&)> const& function)
{
    INFO0;
    auto jets =  bottom_reader_.Jets(event);
    MomentumRange jet_range(Id::W, Id::higgs);
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

std::vector<Particle> BosonTagger::Particles(Event const& event) const
{
    INFO0;
    return CopyIfParticles(event.GenParticles(), Resolve(MultiId::bosons));
}

bool BosonTagger::Problematic(Doublet const& doublet, PreCuts const& pre_cuts, Tag tag) const
{
    INFO0;
    if (Problematic(doublet, pre_cuts)) return true;
    switch (tag) {
    case Tag::signal :
        if (pre_cuts.NotParticleRho(doublet)) return true;
        if (boost::units::abs(doublet.Mass() - (MassOf(Id::W) + MassOf(Id::higgs)) / 2.) > boson_mass_window) return true;
        break;
    case Tag::background : break;
    }
    return false;
}

bool BosonTagger::Problematic(Doublet const& doublet, PreCuts const& pre_cuts) const
{
    INFO0;
    if (pre_cuts.ApplyCuts(MultiId::bosons, doublet)) return true;
    return false;
}

std::vector<Doublet> BosonTagger::Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader)
{
    INFO0;
    return Doublets(event, [&](Doublet & doublet) {
        return Multiplet(doublet, pre_cuts, reader);
    });
}

boost::optional<Doublet> BosonTagger::Multiplet(Doublet& doublet, PreCuts const& pre_cuts, TMVA::Reader const& reader)
{
    INFO0;
    if (Problematic(doublet, pre_cuts)) return boost::none;
    doublet.SetBdt(Bdt(doublet, reader));
    return doublet;
}

std::string BosonTagger::Name() const
{
    return "Boson";
}

latex::String BosonTagger::LatexName() const
{
    return {"B", true};
}

}

}
