# pragma once

# include "Quartet31.hh"
# include "TopSemiTagger.hh"
# include "Branch.hh"

namespace analysis
{

namespace heavyhiggs{

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class ChargedHiggsSemiTagger : public BranchTagger<ChargedHiggsSemiBranch>
{

public:

    ChargedHiggsSemiTagger();

    int Train(Event &event, const Tag tag);

    std::vector<Quartet31> Multiplets(Event& event, const TMVA::Reader& reader);

protected:

    virtual inline std::string ClassName() const {
        return "ChargedHiggsSemiTagger";
    }

private:

    BottomTagger bottom_tagger_;

    TopSemiTagger top_semi_tagger_;

    Reader bottom_reader_;

    Reader top_semi_reader_;
};

}

}
