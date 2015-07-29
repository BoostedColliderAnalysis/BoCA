#pragma once

#include "Branch.hh"
#include "TopLeptonicTagger.hh"
#include "TopHadronicTagger.hh"
#include "Sextet.hh"

namespace analysis {

namespace heavyhiggs {

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class HeavyHiggsSemiTagger : public BranchTagger<HeavyHiggsSemiBranch> {

public:

    HeavyHiggsSemiTagger();

    int Train(const Event &event, const PreCuts &pre_cuts,
              Tag tag) const final override;

    std::vector<Sextet> Multiplets(const Event& event, const PreCuts& pre_cuts, const TMVA::Reader& reader) const;

    int GetBdt(const Event &event, const PreCuts &pre_cuts,
               const TMVA::Reader &reader) const final override {
        return SaveEntries(Multiplets(event, pre_cuts, reader));
    }

    std::string Name() const final override { return "HeavyHiggsSemi"; }

    Jets TopParticles(const Event& event, int charge) const;

    Jets HiggsParticle(const Event& event, Tag tag) const;

    std::vector<Triplet> FinalTriplet(const Event& event, Tag tag, int charge) const;

private:

    Reader<TopHadronicTagger> top_hadronic_reader_;

    Reader<TopLeptonicTagger> top_leptonic_reader_;
};

}

}
