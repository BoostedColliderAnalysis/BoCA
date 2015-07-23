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

    int Train(const Event& event, const PreCuts& pre_cuts,  Tag tag) const final;

    std::vector<Quartet31> Multiplets(const Event& event, const PreCuts& pre_cuts, const TMVA::Reader& reader) const;

    int GetBdt(const Event& event, const PreCuts& pre_cuts, const TMVA::Reader& reader) const  final
    {
        return SaveEntries(Multiplets(event, pre_cuts, reader));
    }

    std::string Name() const final
    {
        return "ChargedHiggsSemi";
    }

private:

    Reader<BottomTagger> bottom_reader_;

    Reader<TopLeptonicTagger> top_leptonic_reader_;
};

}

}
