/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "fastjet/tools/MassDropTagger.hh"
#include "fastjet/tools/Filter.hh"

#include "boca/generic/Types.hh"
#include "boca/generic/Exception.hh"
#include "boca/fastjet/ClusterSequence.hh"
#include "boca/fastjet/Particles.hh"
#include "boca/Event.hh"
#include "boca/physics/MomentumRange.hh"

#include "tthh/tagger/HiggsToHiggs.hh"
#define INFORMATION
#include "boca/generic/DEBUG_MACROS.hh"

namespace tthh
{

namespace tagger
{

int HiggsToHiggs::Train(boca::Event const &event, PreCuts const &pre_cuts, Tag tag)
{
    INFO0;
    return SaveEntries(Sextets(event, [&](Sextet42 & sextet) -> boost::optional<Sextet42> {
        if (Problematic(sextet, pre_cuts, tag)) return boost::none;
        sextet.SetTag(tag);
        return sextet;
    }), Particles(event), tag);
}

std::vector<Sextet42> HiggsToHiggs::Sextets(boca::Event const &event, std::function<boost::optional<Sextet42>(Sextet42 &)> const &function)
{
    INFO0;
    auto ww = higgs_to_ww.Multiplets(event);
    INFO(ww.size());
    auto bb = higgs_to_bb_.Multiplets(event);
    INFO(bb.size());
    auto sextets = Pairs(ww, bb, [&](auto const & quartet, auto const & doublet) {
        auto sextet = Sextet42 {quartet, doublet};
        if (auto optional = function(sextet)) return *optional;
        throw boca::Problematic();
    });
    INFO(sextets.size());
    return sextets;
}

std::vector<Particle> HiggsToHiggs::Particles(boca::Event const &event) const
{
    INFO0;
    auto higgs = CopyIfParticles(event.GenParticles(), {Id::higgs, Id::CP_violating_higgs, Id::higgs_coupling});
    INFO(higgs.size());
    if (higgs.size() == 2) return {higgs.at(0) + higgs.at(1)};
    higgs = CopyIfDaughter(higgs, higgs);
    INFO(higgs.size());
    return higgs;
}

bool HiggsToHiggs::Problematic(Sextet42 const &sextet, PreCuts const &pre_cuts, Tag tag) const
{
    INFO0;
    if (Problematic(sextet, pre_cuts)) return true;
    switch (tag) {
    case Tag::signal :
        break;
    case Tag::background :
        break;
    }
    return false;
}

bool HiggsToHiggs::Problematic(Sextet42 const &sextet, PreCuts const &pre_cuts) const
{
    INFO0;
    if (pre_cuts.ApplyCuts(Id::higgs, sextet)) return true;
    if (sextet.Overlap()) return true;
    return false;
}

std::vector<Sextet42> HiggsToHiggs::Multiplets(boca::Event const &event, PreCuts const &pre_cuts, TMVA::Reader const &reader)
{
    INFO0;
    return Sextets(event, [&](Sextet42 & sextet) -> boost::optional<Sextet42> {
        if (Problematic(sextet, pre_cuts)) return boost::none;
        sextet.SetBdt(Bdt(sextet, reader));
        return sextet;
    });
}

std::string HiggsToHiggs::Name() const
{
    return "HiggsToHiggs";
}

latex::String HiggsToHiggs::LatexName() const
{
    return {"h", true};
}

}

}
