#pragma once

#include "TopHadronicTagger.hh"
#include "TopSemiTagger.hh"
#include "Sextet.hh"
#include "BranchesHiggsCpv.hh"

namespace analysis
{

namespace higgscpv
{

/**
 * @brief JetPair BDT tagger
 *
 */
class TopSemiPairTagger : public BranchTagger<TripletPairBranch>
{

public:

    TopSemiPairTagger();

    int Train(Event &event, const Tag tag);

    std::vector<Sextet> Multiplets(Event &event, const TMVA::Reader &reader);

private:

    TopSemiTagger top_semi_tagger_;

    TopHadronicTagger top_hadronic_tagger;

    Reader top_semi_reader_;

    Reader top_hadronic_reader_;

};

}

}
