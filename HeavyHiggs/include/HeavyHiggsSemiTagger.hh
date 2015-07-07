#pragma once

#include "TopSemiTagger.hh"
#include "Sextet.hh"
#include "TopHadronicTagger.hh"
#include "Branch.hh"

namespace analysis
{

namespace heavyhiggs {

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class HeavyHiggsSemiTagger : public BranchTagger<HeavyHiggsSemiBranch>
{

public:

    HeavyHiggsSemiTagger();

    int Train(const Event &event, PreCuts &pre_cuts, const Tag tag) const;

    std::vector<Sextet> Multiplets(const Event& event, PreCuts &pre_cuts, const TMVA::Reader &reader) const;

    int GetBdt(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) const {
      return SaveEntries(Multiplets(event, pre_cuts, reader));
    }

    std::string name() const {
      return "HeavyHiggsSemi";
    }

private:

    ReaderTagger<TopHadronicTagger> top_hadronic_reader_;

    ReaderTagger<TopSemiTagger> top_semi_reader_;
};

}

}
