/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "ResonanceTagger.hh"
#include "multiplets/Particles.hh"
#include "generic/Exception.hh"
#include "Event.hh"
#include "generic/DEBUG.hh"

namespace boca
{

namespace naturalness
{

int ResonanceTagger::Train(Event const& event, PreCuts const&, Tag tag) const
{
    INFO0;
    return SaveEntries(Doublets(event, [&](Doublet & doublet) {
        doublet.SetTag(tag);
        return doublet;
    }), Particles(event), tag);
}

std::vector<Doublet> ResonanceTagger::Doublets(Event const& event, std::function<Doublet(Doublet&)> const& function) const
{
    return UnorderedPairs(event.Leptons().Photons(), [&](Lepton const & photon_1, Lepton const & photon_2) {
        Doublet doublet(photon_1, photon_2);
        if (doublet.Overlap()) throw Overlap();
        return function(doublet);
    });
}

std::vector<Doublet> ResonanceTagger::Multiplets(Event const& event, boca::PreCuts const&, TMVA::Reader const& reader) const
{
    return Doublets(event, [&](Doublet & doublet) {
        doublet.SetBdt(Bdt(doublet, reader));
        return doublet;
    });
}

std::vector<Particle> ResonanceTagger::Particles(Event const& event) const
{
    return CopyIfParticle(event.Partons().GenParticles(), Id::heavy_higgs);
}
std::string ResonanceTagger::Name() const
{
    return "Resonance";
}
std::string ResonanceTagger::LatexName() const
{
    return "S";
}

}

}

