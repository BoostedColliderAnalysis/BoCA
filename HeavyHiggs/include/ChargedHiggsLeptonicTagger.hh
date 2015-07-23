#pragma once

#include "TopLeptonicTagger.hh"
#include "Triplet.hh"
#include "Branch.hh"

namespace analysis {

namespace heavyhiggs {

/**
 * @brief Leptonic heavy higgs BDT tagger
 *
 */
class ChargedHiggsLeptonicTagger : public analysis::BranchTagger<ChargedHiggsLeptonicBranch> {

public:

    ChargedHiggsLeptonicTagger();

    int Train(const Event& event, const PreCuts& pre_cuts, const analysis::Tag tag);

    std::vector<analysis::Triplet> Multiplets(const Event& event, const PreCuts& pre_cuts, const TMVA::Reader& reader) const;

    std::string Name() const final
    {
        return "ChargedHiggsLeptonic";
    }

private:

    analysis::Reader<analysis::BottomTagger> bottom_reader_;

    analysis::Reader<analysis::TopLeptonicTagger> top_leptonic_reader_;

};

}

}
