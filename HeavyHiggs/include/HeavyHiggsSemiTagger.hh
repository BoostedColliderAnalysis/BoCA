#pragma once

#include "Branch.hh"
#include "TopLeptonicTagger.hh"
#include "TopHadronicTagger.hh"
#include "Sextet.hh"

namespace analysis {

namespace heavyhiggs {
  
enum class TopProcess
{
  hadronic, leptonic
};

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class HeavyHiggsSemiTagger : public BranchTagger<HeavyHiggsSemiBranch> {

public:

    HeavyHiggsSemiTagger();

    int Train(const Event &event, const PreCuts &pre_cuts,
              Tag tag) const final;

    std::vector<Sextet> Multiplets(const Event& event, const PreCuts& pre_cuts, const TMVA::Reader& reader) const;

    int GetBdt(const Event &event, const PreCuts &pre_cuts, const TMVA::Reader &reader) const final {
                 return SaveEntries(Multiplets(event, pre_cuts, reader), 1);
    }

    std::string Name() const final { return "HeavyHiggsSemi"; }


    static Jets HiggsParticle(const Event& event, Tag tag);

    std::vector<Triplet> FinalTriplet(const Event& event, Tag tag, TopProcess top_process) const;

private:

    Reader<TopHadronicTagger> top_hadronic_reader_;

    Reader<TopLeptonicTagger> top_leptonic_reader_;
};

}

}
