# pragma once

# include "Sextet.hh"
# include "TopHadronicTagger.hh"
# include "TopSemiTagger.hh"
# include "BranchesHiggsCpv.hh"

namespace higgscpv {

/**
 * @brief JetPair BDT tagger
 *
 */
class TripletPairTagger : public analysis::Tagger
{

public:

    TripletPairTagger();

    int Train(analysis::Event& event, const Tag tag);

    std::vector<analysis::Sextet> Multiplets(analysis::Event& event, const TMVA::Reader& reader);

protected:

    virtual inline std::string ClassName() const {
        return "TripletPairTagger";
    }

private:

    void DefineVariables();

    TripletPairBranch branch_;

    analysis::TopSemiTagger top_semi_tagger_;

    analysis::TopHadronicTagger top_hadronic_tagger;

    analysis::Reader top_semi_reader_;

    analysis::Reader top_hadronic_reader_;

};

}
