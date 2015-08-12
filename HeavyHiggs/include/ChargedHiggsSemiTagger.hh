#pragma once

#include "TopLeptonicTagger.hh"
#include "Quartet.hh"
#include "Branch.hh"

namespace analysis {

namespace heavyhiggs {

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class ChargedHiggsSemiTagger : public BranchTagger<ChargedHiggsSemiBranch> {

public:

    ChargedHiggsSemiTagger();

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) const final;

    std::vector<Quartet31> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const;

    int GetBdt(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const final {
        return SaveEntries(Multiplets(event, pre_cuts, reader),1);
    }

    std::string Name() const final { return "ChargedHiggsSemi"; }

private:

    Reader<BottomTagger> bottom_reader_;

    Reader<TopLeptonicTagger> top_leptonic_reader_;
};

}

}
