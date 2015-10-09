#pragma once

#include "Branch.hh"
#include "TopLeptonicTagger.hh"
#include "TopHadronicTagger.hh"
#include "Sextet.hh"

namespace boca {

namespace heavyhiggs {

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class HeavyHiggsSemiTagger : public BranchTagger<HeavyHiggsSemiBranch> {

public:

    HeavyHiggsSemiTagger();

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) const final;

    std::vector<Sextet> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const;

    int SaveBdt(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const final {
      return SaveEntries(Multiplets(event, pre_cuts, reader), 1);
    }

    std::string Name() const final { return "HeavyHiggsSemi"; }

    Jets TopParticles(Event const& event, Decay decay) const;

    Jets HiggsParticle(Event const& event, Tag tag) const;

    std::vector<Triplet> FinalTriplet(Event const& event, Tag tag, Decay decay) const;

private:

    Reader<TopHadronicTagger> top_hadronic_reader_;

    Reader<TopLeptonicTagger> top_leptonic_reader_;
};

}

}
