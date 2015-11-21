#pragma once

#include "Branch.hh"
#include "TopLeptonicTagger.hh"
#include "TopHadronicTagger.hh"
#include "Sextet.hh"

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

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) const final;

    std::vector<Sextet> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const final;

    std::string Name() const final;

    std::vector<Particle> TopParticles(Event const& event, Decay decay) const;

    std::vector<Particle> HiggsParticle(Event const& event, Tag tag) const;

    std::vector<Triplet> FinalTriplet(Event const& event, Tag tag, Decay decay) const;

private:

    Reader<standardmodel::TopHadronicTagger> top_hadronic_reader_;

    Reader<standardmodel::TopLeptonicTagger> top_leptonic_reader_;
};

}

}
