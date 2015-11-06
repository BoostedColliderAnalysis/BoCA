#pragma once

#include "TopLeptonicTagger.hh"
#include "Quartet.hh"
#include "Branch.hh"

namespace boca
{

namespace heavyhiggs
{

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class ChargedHiggsSemiTagger : public TaggerTemplate<Quartet31, ChargedHiggsSemiBranch>
{

public:

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) const final;

    std::vector<Quartet31> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const final;

    std::string Name() const final;

private:

    Reader<standardmodel::BottomTagger> bottom_reader_;

    Reader<standardmodel::TopLeptonicTagger> top_leptonic_reader_;
};

}

}
