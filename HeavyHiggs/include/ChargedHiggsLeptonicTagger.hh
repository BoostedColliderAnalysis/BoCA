#pragma once

#include "TopLeptonicTagger.hh"
#include "multiplets/Triplet.hh"
#include "BranchesHeavyHiggs.hh"

namespace boca
{

namespace heavyhiggs
{

/**
 * @brief Leptonic heavy higgs BDT tagger
 *
 */
class ChargedHiggsLeptonicTagger : public TaggerTemplate<Triplet, ChargedHiggsLeptonicBranch>
{

public:

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) const override;

    std::vector<Triplet> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const override;

    std::string Name() const override {
        return "ChargedHiggsLeptonic";
    }

private:

    Reader<standardmodel::BottomTagger> bottom_reader_;

    Reader<standardmodel::TopLeptonicTagger> top_leptonic_reader_;

};

}

}
