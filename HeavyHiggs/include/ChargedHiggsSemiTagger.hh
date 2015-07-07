#pragma once

#include "TopSemiTagger.hh"
#include "Quartet.hh"
#include "Branch.hh"

namespace analysis
{

namespace heavyhiggs{

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class ChargedHiggsSemiTagger : public BranchTagger<ChargedHiggsSemiBranch>
{

public:

    ChargedHiggsSemiTagger();

    int Train(const Event &event, PreCuts &pre_cuts, const Tag tag) const;

    std::vector<Quartet31> Multiplets(const Event& event, PreCuts &pre_cuts, const TMVA::Reader& reader) const;

    int GetBdt(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) const {
      return SaveEntries(Multiplets(event, pre_cuts, reader));
    }

    std::string name() const {
      return "ChargedHiggsSemi";
    }

private:

    ReaderTagger<BottomTagger> bottom_reader_;

    ReaderTagger<TopSemiTagger> top_semi_reader_;
};

}

}
