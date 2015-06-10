# pragma once

# include "Quartet31.hh"
# include "TopSemiTagger.hh"
# include "Branch.hh"

namespace heavyhiggs{

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class ChargedHiggsSemiTagger : public analysis::BranchTagger<ChargedHiggsSemiBranch>
{

public:

    ChargedHiggsSemiTagger();

    int Train(analysis::Event &event, const Tag tag);

    std::vector<analysis::Quartet31> Multiplets(analysis::Event& event, const TMVA::Reader& reader);

protected:

    virtual inline std::string ClassName() const {
        return "ChargedHiggsSemiTagger";
    }

private:

    void DefineVariables();

    analysis::BottomTagger bottom_tagger_;

    analysis::TopSemiTagger top_semi_tagger_;

    analysis::Reader bottom_reader_;

    analysis::Reader top_semi_reader_;
};

}
