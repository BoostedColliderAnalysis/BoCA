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
#include "boca/identification/MomentumRange.hh"

#include "tthh/tagger/HiggsSemiLeptonic.hh"
#define INFORMATION
#include "boca/generic/DEBUG_MACROS.hh"

namespace tthh
{

namespace tagger
{

HiggsSemiLeptonic::HiggsSemiLeptonic()
{
    w_leptonic_reader_.Tagger().DoNeutrinoReconstruction(false);
}

int HiggsSemiLeptonic::Train(boca::Event const &event, PreCuts const &pre_cuts, Tag tag)
{
    INFO0;
    return SaveEntries(Quartets(event, [&](Quartet22 & quartet) -> boost::optional<Quartet22> {
        if (Problematic(quartet, pre_cuts, tag)) return boost::none;
        quartet.SetTag(tag);
        return quartet;
    }), Particles(event), tag);
}

std::vector<Quartet22> HiggsSemiLeptonic::Quartets(boca::Event const &event, std::function<boost::optional<Quartet22>(Quartet22 &)> const &function)
{
    INFO0;
    auto leptonic = w_leptonic_reader_.Multiplets(event);
    INFO(leptonic.size());
    auto hadronic = w_hadronic_reader_.Multiplets(event);
    INFO(hadronic.size());
    auto quartets = Pairs(hadronic, leptonic, [&](Doublet const & doublet_1, Doublet const & doublet_2) {
        auto quartet = Quartet22 {doublet_1, doublet_2};
        if (auto optional = function(quartet)) return *optional;
        throw boca::Problematic();
    });
    INFO(quartets.size());
    return quartets;
}

std::vector<Particle> HiggsSemiLeptonic::Particles(boca::Event const &event) const
{
    INFO0;
    auto higgs = CopyIfParticles(event.GenParticles(), {Id::higgs, Id::CP_violating_higgs,  Id::higgs_coupling});
//     higgs = RemoveIfDaughter(higgs, higgs);
    INFO(higgs.size());
    auto bottom = CopyIfParticle(event.GenParticles(), Id::bottom);
    higgs = RemoveIfDaughter(higgs, bottom);
    INFO(higgs.size());
    return higgs;
}

bool HiggsSemiLeptonic::Problematic(Quartet22 const &quartet, PreCuts const &pre_cuts, Tag tag) const
{
    INFO0;
    if (Problematic(quartet, pre_cuts)) return true;
    switch (tag) {
    case Tag::signal :
        break;
    case Tag::background :
        break;
    }
    return false;
}

bool HiggsSemiLeptonic::Problematic(Quartet22 const &quartet, PreCuts const &pre_cuts) const
{
    INFO0;
    if (pre_cuts.ApplyCuts(Id::higgs, quartet)) return true;
    return false;
}

std::vector<Quartet22> HiggsSemiLeptonic::Multiplets(boca::Event const &event, PreCuts const &pre_cuts, TMVA::Reader const &reader)
{
    INFO0;
    return Quartets(event, [&](Quartet22 & quartet) -> boost::optional<Quartet22> {
        if (Problematic(quartet, pre_cuts)) return boost::none;
        quartet.SetBdt(Bdt(quartet, reader));
        return quartet;
    });
}

std::string HiggsSemiLeptonic::Name() const
{
    return "HiggsSemiLeptonic";
}

latex::String HiggsSemiLeptonic::LatexName() const
{
    return {"h", true};
}

}

}
