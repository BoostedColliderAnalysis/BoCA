/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "../include/TruthLevel.hh"

#include "Event.hh"
#include "PreCuts.hh"
#include "Exception.hh"
#include "physics/Particles.hh"
// #define DEBUGGING
#include "Debug.hh"

namespace boca
{

namespace naturalness
{

int TruthLevel::Train(Event const& event, PreCuts const& pre_cuts, Tag) const
{
    INFO0;
    return SaveEntries(Jets(event, pre_cuts, [&](Particle & jet) {
        return jet;
    }));
}

std::vector<TruthVariables> TruthLevel::Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const&) const
{
    INFO0;
    return Jets(event, pre_cuts, [&](Particle & jet) {
        return jet;
    });
}

std::vector<TruthVariables> TruthLevel::Jets(Event const& event, PreCuts const& pre_cuts, std::function<Particle(Particle&)>)const
{
    INFO0;
    TruthVariables truths;
    std::vector<Particle> particles = event.Partons().GenParticles();
    std::vector<Particle> bosons = CopyFirst(RemoveIfMother(CopyIfParticles(particles, Resolve(MultiId::bosons)),Id::higgs),6);
    if(bosons.size() > 6) for (auto const & boson : bosons) {
        Member particle = boson.Info().Family().Member(Relative::particle);
        Member mother = boson.Info().Family().Member(Relative::mother);
        Member step_mother = boson.Info().Family().Member(Relative::step_mother);
        INFO(boca::Name(particle.Id()), boca::Name(mother.Id()), boca::Name(step_mother.Id()));
    }
    truths.SetLeptons(CopyIfGrandMother(CopyIfParticles(particles, Resolve(MultiId::charged_lepton)), Id::top));
    truths.SetBosons(bosons);
    truths.SetTops(CopyIfParticle(particles, Id::top));
    auto detectable = CopyIfDaughter(bosons, RemoveIfSoft(CopyIfQuark(particles), 40_GeV));
    std::vector<Particle> alone;
    for (auto const & particle_1 : detectable) {
        bool overlap = false;
        for (auto const & particle_2 : detectable) if (particle_1 != particle_2 && particle_1.DeltaRTo(particle_2) < 0.1_rad) overlap = true;
        if (!overlap) alone.emplace_back(particle_1);
    }
    truths.SetDetectable(alone);
    truths.SetMissingEt(event.Hadrons().MissingEt());
    truths.SetScalarHt(event.Hadrons().ScalarHt());
    truths.SetJets(event.Hadrons().Jets());
    return {truths};
}


std::string TruthLevel::Name() const
{
    return "Truth";
}

std::string TruthLevel::LatexName() const
{
    return "truth";
}

}

}


