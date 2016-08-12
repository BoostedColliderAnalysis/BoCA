/**
 * Copyright (C) 2015-2016 Jan Hajer
 */

#include "boca/Event.hh"
#include "boca/PreCuts.hh"
#include "boca/generic/Exception.hh"
#include "boca/physics/Id.hh"
#include "boca/multiplets/Particles.hh"
// #define DEBUGGING
#include "boca/generic/DEBUG.hh"

#include "include/tagger/TruthLevel.hh"

namespace toppartner
{

namespace tagger
{

int TruthLevel::Train(boca::Event const& event, PreCuts const& pre_cuts, Tag)
{
    INFO0;
    return SaveEntries(Jets(event, pre_cuts, [&](Particle & jet) {
        return jet;
    }));
}

std::vector<TruthVariables> TruthLevel::Multiplets(boca::Event const& event, PreCuts const& pre_cuts, TMVA::Reader const&)
{
    INFO0;
    return Jets(event, pre_cuts, [&](Particle & jet) {
        return jet;
    });
}

std::vector<TruthVariables> TruthLevel::Jets(boca::Event const& event, PreCuts const&, std::function<Particle(Particle&)>const&)const
{
    INFO0;
    TruthVariables truths;
    auto particles = event.GenParticles();
    auto bosons = CopyFirst(RemoveIfMother(CopyIfParticles(particles, Resolve(MultiId::bosons)),Id::higgs),6);
    if(bosons.size() > 6) for (auto const & boson : bosons) {
        auto particle = boson.Info().Family().Member(Relative::particle);
        auto mother = boson.Info().Family().Member(Relative::mother);
        auto step_mother = boson.Info().Family().Member(Relative::step_mother);
        INFO(boca::Name(particle.Id()), boca::Name(mother.Id()), boca::Name(step_mother.Id()));
    }
    truths.SetLeptons(CopyIfGrandMother(CopyIfParticles(particles, Resolve(MultiId::charged_lepton)), Id::top));
    truths.SetBosons(bosons);
    truths.SetTops(CopyIfParticle(particles, Id::top));
    auto detectable = CopyIfDaughter(bosons, RemoveIfSoft(CopyIfQuark(particles), 40_GeV));
    std::vector<Particle> alone;
    for (auto const & particle_1 : detectable) {
        auto overlap = false;
        for (auto const & particle_2 : detectable) if (particle_1 != particle_2 && particle_1.DeltaRTo(particle_2) < 0.1_rad) overlap = true;
        if (!overlap) alone.emplace_back(particle_1);
    }
    truths.SetDetectable(alone);
    truths.SetMissingEt(event.MissingEt());
    truths.SetScalarHt(event.ScalarHt());
    truths.SetJets(event.Jets());
    return {truths};
}


std::string TruthLevel::Name() const
{
    return "Truth";
}

latex::String TruthLevel::LatexName() const
{
    return "truth";
}

}

}
