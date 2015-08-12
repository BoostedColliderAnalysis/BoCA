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

    int Train(Event const& event, PreCuts const& pre_cuts,
              Tag tag) const final;

    std::vector<analysis::Triplet> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const;

    std::string Name() const final { return "ChargedHiggsLeptonic"; }

private:

    analysis::Reader<analysis::BottomTagger> bottom_reader_;

    analysis::Reader<analysis::TopLeptonicTagger> top_leptonic_reader_;

};

}

}
