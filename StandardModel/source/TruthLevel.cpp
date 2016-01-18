/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "TruthLevel.hh"

#include "Event.hh"
#include "Vector.hh"
#include "PreCuts.hh"
#include "Exception.hh"
// #define DEBUG
#include "Debug.hh"

namespace boca
{

namespace standardmodel
{


int TruthLevel::Train(Event const& event, PreCuts const& pre_cuts, Tag) const
{
    Info0;
    return SaveEntries(Jets(event, pre_cuts, [&](Particle & jet) {
//         if (Problematic(jet, pre_cuts, tag)) throw boca::Problematic();
        return jet;
    }));
}



std::vector<TruthVariables> TruthLevel::Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const&) const
{
    Info0;
    return Jets(event, pre_cuts, [&](Particle & jet) {
//         if (Problematic(jet, pre_cuts)) throw boca::Problematic();
        return jet;
    });
}

std::vector<TruthVariables> TruthLevel::Jets(Event const& event, PreCuts const& pre_cuts, std::function<Particle(Particle&)>)const
{
    Info0;
    std::vector<Particle> particle = event.Partons().GenParticles();
    std::vector<Particle> tops = CopyIfParticle(particle, Id::top);
    Check(tops.size() == 2, tops.size());
    std::vector<TruthVariables> truths;
    for (auto const & top : tops) {
        if (top.Pt() < pre_cuts.PtLowerCut().Get(Id::top) || top.Pt() > pre_cuts.PtUpperCut().Get(Id::top)) continue;
        TruthVariables truth;
        truth.SetTop(top);
        std::vector<Particle> bottoms = CopyIfMother(CopyIfParticle(particle, Id::bottom), top);
        Check(bottoms.size() == 1, bottoms.size());
        truth.SetBottom(bottoms.front());
        std::vector<Particle> Ws = CopyIfMother(CopyIfParticle(particle, Id::W), top);
        Check(Ws.size() == 1, Ws.size());
        truth.SetW(Ws.front());
        std::vector<Particle> quarks = CopyIfGrandMother(CopyIfQuark(particle), top);
        Check(quarks.size() == 2, quarks.size());
        truth.SetQuark1(quarks.at(0));
        truth.SetQuark2(quarks.at(1));
        truths.emplace_back(truth);
    }
    return truths;
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

