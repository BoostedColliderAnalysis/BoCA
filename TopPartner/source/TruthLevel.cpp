/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "../include/TruthLevel.hh"

#include "Event.hh"
#include "PreCuts.hh"
#include "Exception.hh"
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
    std::vector<Particle> particle = event.Partons().GenParticles();
    TruthVariables truths;
    truths.SetLeptons(CopyIfGrandMother(CopyIfParticles(particle, Resolve(MultiId::charged_lepton)), Id::top));
    truths.SetBosons(RemoveIfMother(CopyIfParticles(particle, Resolve(MultiId::bosons)), Resolve(MultiId::bosons)));
    truths.SetTops(CopyIfParticle(particle, Id::top));
    auto detectable = RemoveIfOnlyMother(RemoveIfMother(CopyIfDaughter(particle, CopyIfMother(RemoveIfSoft(CopyIfQuark(particle), 40_GeV), Resolve(MultiId::bosons))), Resolve(MultiId::bosons)), Id::top);
    std::vector<Particle> alone;
    for (auto const & particle_1 : detectable) {
        bool overlap = false;
        for (auto const & particle_2 : detectable) if (particle_1 != particle_2 && particle_1.DeltaRTo(particle_2) < 0.1_rad) overlap = true;
        if (!overlap) alone.emplace_back(particle_1);
    }
    truths.SetDetectable(alone);
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

