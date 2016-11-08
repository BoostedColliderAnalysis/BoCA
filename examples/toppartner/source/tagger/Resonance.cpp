/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "boca/fastjet/Particles.hh"
#include "boca/generic/Exception.hh"
#include "boca/event/Event.hh"
#include "boca/generic/DEBUG_MACROS.hh"
#include "toppartner/tagger/Resonance.hh"

namespace toppartner
{

namespace tagger
{

int Resonance::Train(boca::Event const& event, PreCuts const&, Tag tag)
{
    INFO0;
    return SaveEntries(Doublets(event, [&](Doublet & doublet) {
        doublet.SetTag(tag);
        return doublet;
    }), Particles(event), tag);
}

std::vector<Doublet> Resonance::Doublets(boca::Event const& event, std::function<Doublet(Doublet&)> const& function) const
{
    return UnorderedPairs(event.Photons(), [&](boca::Photon const & photon_1, boca::Photon const & photon_2) {
        Doublet doublet(photon_1, photon_2);
        if (doublet.Overlap()) throw Overlap();
        return function(doublet);
    });
}

std::vector<Doublet> Resonance::Multiplets(boca::Event const& event, boca::PreCuts const&, TMVA::Reader const& reader)
{
    return Doublets(event, [&](Doublet & doublet) {
        doublet.SetBdt(Bdt(doublet, reader));
        return doublet;
    });
}

std::vector<Particle> Resonance::Particles(boca::Event const& event) const
{
    return CopyIfParticle(event.GenParticles(), Id::heavy_higgs);
}
std::string Resonance::Name() const
{
    return "Resonance";
}
latex::String Resonance::LatexName() const
{
    return {"S", true};
}

}

}
