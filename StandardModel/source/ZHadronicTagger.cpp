/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "ZHadronicTagger.hh"
#include "MomentumRange.hh"
#include "Event.hh"
#include "Particles.hh"
#include "Exception.hh"
#include "DEBUG.hh"

namespace boca
{

namespace standardmodel
{

ZHadronicTagger::ZHadronicTagger()
{
    INFO0;
    z_mass_window = 50_GeV;
}

int ZHadronicTagger::Train(Event const& event, boca::PreCuts const& pre_cuts, Tag tag) const
{
    INFO0;
    return SaveEntries(Doublets(event, [&](Doublet & doublet) {
        return SetTag(doublet, pre_cuts, tag);
    }), Particles(event), tag, Id::Z);
}

std::vector<Doublet> ZHadronicTagger::Doublets(Event const& event, std::function<boost::optional<Doublet>(Doublet&)> function) const
{
    INFO0;
    auto jets = event.Hadrons().Jets();
    MomentumRange jet_range(Id::Z, Id::Z);
    std::vector<Jet> soft;
    for(auto & jet : jet_range.SofterThanMax(jets)) soft.emplace_back(bottom_reader_.Multiplet(jet));

    auto doublets = UnorderedPairs(soft, [&](Jet const & jet_1, Jet const & jet_2) {
      Doublet doublet(jet_1, jet_2);
      if (!jet_range.BelowUpperBound(doublet)) throw boca::Problematic();
        if (boost::optional<Doublet> optional_doublet = function(doublet)) return *optional_doublet;
        else throw boca::Problematic();
    });

    for (auto const & jet : jet_range.HarderThanMin(jets)) {
        Doublet doublet;
        doublet.Enforce(bottom_reader_.SubMultiplet(jet, 2));
        if (boost::optional<Doublet> optional = function(doublet)) doublets.emplace_back(*optional);
    }
    return doublets;
}

boost::optional<Doublet> ZHadronicTagger::SetTag(Doublet doublet, PreCuts const& pre_cuts, Tag tag) const
{
    INFO0;
    if (Problematic(doublet, pre_cuts, tag)) return boost::none;
    doublet.SetTag(tag);
    return doublet;
}

std::vector<Particle> ZHadronicTagger::Particles(Event const& event) const
{
    INFO0;
    return CopyIfParticle(event.Partons().GenParticles(), Id::Z);
}

bool ZHadronicTagger::Problematic(boca::Doublet const& doublet, boca::PreCuts const& pre_cuts, Tag tag) const
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

bool ZHadronicTagger::Problematic(boca::Doublet const& doublet, boca::PreCuts const& pre_cuts) const
{
    INFO0;
    if (pre_cuts.ApplyCuts(Id::Z, doublet)) return true;
    return false;
}

std::vector<Doublet> ZHadronicTagger::Multiplets(Event const& event, boca::PreCuts const& pre_cuts, TMVA::Reader const& reader) const
{
    INFO0;
    return Doublets(event, [&](Doublet & doublet) {
        return Multiplet(doublet, pre_cuts, reader);
    });
}

boost::optional<Doublet> ZHadronicTagger::Multiplet(Doublet& doublet, PreCuts const& pre_cuts, TMVA::Reader const& reader) const
{
    INFO0;
    if (Problematic(doublet, pre_cuts)) return boost::none;
    doublet.SetBdt(Bdt(doublet, reader));
    return doublet;
}

std::string ZHadronicTagger::Name() const
{
    INFO0;
    return "ZHadronic";
}

std::string ZHadronicTagger::LatexName() const
{
    INFO0;
    return "Z";
}

}

}
