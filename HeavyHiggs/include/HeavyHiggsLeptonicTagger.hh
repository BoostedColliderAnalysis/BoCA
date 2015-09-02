#pragma once

#include "TopLeptonicTagger.hh"
#include "Sextet.hh"
#include "Branch.hh"

namespace boca {

namespace heavyhiggs {

/**
 * @brief Leptonic heavy higgs BDT tagger
 *
 */
class HeavyHiggsLeptonicTagger : public BranchTagger<HeavyHiggsLeptonicBranch> {

public:

    HeavyHiggsLeptonicTagger();

    int Train(Event const& event, PreCuts const& pre_cuts,
              Tag tag) const final;

    std::vector<Sextet> Multiplets(Event const& event, TMVA::Reader const& reader) const;

    std::string Name() const final { return "HeavyHiggsLeptonic"; }

private:

    Reader<TopLeptonicTagger> top_leptonic_reader_;

};

}

}
