#pragma once

#include "boca/BranchesHeavyHiggs.hh"
#include "boca/standardmodel/TopLeptonicTagger.hh"
#include "boca/standardmodel/TopHadronicTagger.hh"
#include "boca/multiplets/Sextet.hh"

namespace boca
{

namespace heavyhiggs
{

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class HeavyHiggsSemiTagger : public TaggerTemplate<Sextet, HeavyHiggsSemiBranch>
{

public:

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    std::vector<Sextet> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

    std::vector<Particle> TopParticles(Event const& event, Decay decay) const;

    static std::vector<Particle> HiggsParticle(Event const& event, Tag tag);

    std::vector<Triplet> FinalTriplet(Event const& event, Tag tag, Decay decay);

private:

    Reader<standardmodel::TopHadronicTagger> top_hadronic_reader_;

    Reader<standardmodel::TopLeptonicTagger> top_leptonic_reader_;
};

}

}
