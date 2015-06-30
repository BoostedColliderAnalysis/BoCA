#pragma once

#include "Quartet.hh"
#include "TopHadronicTagger.hh"

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

    int Train(Event &event, PreCuts &pre_cuts, const Tag tag);

    std::vector< Quartet31 > Multiplets(Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader);

protected:

    virtual  std::string ClassName() const {
        return "TripletJetPairTagger";
    }

private:

    BottomTagger bottom_tagger_;

    TopHadronicTagger top_hadronic_tagger;

    Reader bottom_reader_;

    Reader top_hadronic_reader_;

};

}
