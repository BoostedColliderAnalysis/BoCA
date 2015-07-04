#pragma once

#include "TopHadronicTagger.hh"
#include "Quartet.hh"

namespace analysis
{

/**
 * @brief JetPair BDT tagger
 *
 */
class TripletJetPairTagger : public BranchTagger<TripletJetPairBranch>
{

public:

    TripletJetPairTagger();

    int Train(const Event &event, PreCuts &pre_cuts, const Tag tag);

    std::vector< Quartet31 > Multiplets(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader);

private:

    BottomTagger bottom_tagger_;

    TopHadronicTagger top_hadronic_tagger;

    Reader bottom_reader_;

    Reader top_hadronic_reader_;

};

}
