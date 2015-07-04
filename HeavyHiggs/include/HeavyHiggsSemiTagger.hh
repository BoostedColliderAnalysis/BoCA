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

    int Train(const Event &event, PreCuts &pre_cuts, const Tag tag);

    std::vector<Sextet> Multiplets(const Event& event, PreCuts &pre_cuts, const TMVA::Reader& reader);

private:

    TopHadronicTagger top_hadronic_tagger;

    TopSemiTagger top_semi_tagger;

    Reader top_hadronic_reader_;

    Reader top_semi_reader_;
};

}

}
