#pragma once

#include "Quartet.hh"
#include "TopSemiTagger.hh"
#include "Branch.hh"

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

    int Train(Event &event, PreCuts &pre_cuts, const Tag tag);

    std::vector<Quartet31> Multiplets(Event& event, PreCuts &pre_cuts, const TMVA::Reader& reader);

protected:

    virtual  std::string ClassName() const {
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
