#pragma once

#include "boca/standardmodel/TopLeptonicTagger.hh"
#include "boca/multiplets/Triplet.hh"
#include "boca/BranchesHeavyHiggs.hh"

namespace boca
{

namespace heavyhiggs
{

/**
 * @brief Leptonic heavy higgs BDT tagger
 *
 */
class ChargedHiggsLeptonicTagger : public Tagger<Triplet, ChargedHiggsLeptonicBranch>
{

public:

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    std::vector<Triplet> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override {
        return "ChargedHiggsLeptonic";
    }

private:

    Reader<standardmodel::BottomTagger> bottom_reader_;

    Reader<standardmodel::TopLeptonicTagger> top_leptonic_reader_;

};

}

}
