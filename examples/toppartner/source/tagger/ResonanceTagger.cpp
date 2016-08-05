/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "boca/multiplets/Particles.hh"
#include "boca/generic/Exception.hh"
#include "boca/Event.hh"
#include "boca/generic/DEBUG.hh"
#include "include/tagger/ResonanceTagger.hh"

namespace toppartner
{

int ResonanceTagger::Train(boca::Event const& event, PreCuts const&, Tag tag)
{
    INFO0;
    return SaveEntries(Doublets(event, [&](Doublet & doublet) {
        doublet.SetTag(tag);
        return doublet;
    }), Particles(event), tag);
}

std::vector<Doublet> ResonanceTagger::Doublets(boca::Event const& event, std::function<Doublet(Doublet&)> const& function) const
{
    return UnorderedPairs(event.Photons(), [&](Lepton const & photon_1, Lepton const & photon_2) {
        Doublet doublet(photon_1, photon_2);
        if (doublet.Overlap()) throw Overlap();
        return function(doublet);
    });
}

std::vector<Doublet> ResonanceTagger::Multiplets(boca::Event const& event, boca::PreCuts const&, TMVA::Reader const& reader)
{
    return Doublets(event, [&](Doublet & doublet) {
        doublet.SetBdt(Bdt(doublet, reader));
        return doublet;
    });
}

std::vector<Particle> ResonanceTagger::Particles(boca::Event const& event) const
{
    return CopyIfParticle(event.GenParticles(), Id::heavy_higgs);
}
std::string ResonanceTagger::Name() const
{
    return "Resonance";
}
latex::String ResonanceTagger::LatexName() const
{
    return {"S", true};
}

}
