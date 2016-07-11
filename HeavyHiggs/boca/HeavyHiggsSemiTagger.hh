#pragma once

#include "boca/BranchesHeavyHiggs.hh"
#include "boca/standardmodel/tagger/TopLeptonic.hh"
#include "boca/standardmodel/tagger/TopHadronic.hh"
#include "boca/multiplets/Sextet.hh"

namespace boca
{

namespace heavyhiggs
{

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class HeavyHiggsSemiTagger : public Tagger<Sextet, HeavyHiggsSemiBranch>
{

public:

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    using Tagger::Multiplets;

    std::vector<Sextet> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

    std::vector<Particle> TopParticles(Event const& event, Decay decay) const;

    static std::vector<Particle> HiggsParticle(Event const& event, Tag tag);

    std::vector<Triplet> FinalTriplet(Event const& event, Tag tag, Decay decay);

private:

    Reader<standardmodel::tagger::TopHadronic> top_hadronic_reader_;

    Reader<standardmodel::tagger::TopLeptonic> top_leptonic_reader_;
};

}

}
