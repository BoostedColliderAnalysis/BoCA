# pragma once

# include "Quartet31.hh"
# include "TopHadronicTagger.hh"

namespace analysis {

/**
 * @brief JetPair BDT tagger
 *
 */
class TripletJetPairTagger : public Tagger
{

public:

    TripletJetPairTagger();

    int Train(Event& event, const Tag tag);

    std::vector< Quartet31 > Multiplets(Event &event, const TMVA::Reader &JetPairReader);

protected:

    virtual inline std::string ClassName() const {
        return "TripletJetPairTagger";
    }

private:

    void DefineVariables();

    TripletJetPairBranch branch_;

    BottomTagger bottom_tagger_;

    TopHadronicTagger top_hadronic_tagger;

    Reader bottom_reader_;

    Reader top_hadronic_reader_;

};

}
