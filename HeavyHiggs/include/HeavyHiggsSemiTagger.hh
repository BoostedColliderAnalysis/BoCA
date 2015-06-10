# pragma once

# include "Sextet.hh"
# include "TopSemiTagger.hh"
# include "TopHadronicTagger.hh"
# include "Branch.hh"

namespace heavyhiggs {

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class HeavyHiggsSemiTagger : public analysis::BranchTagger<HeavyHiggsSemiBranch>
{

public:

    HeavyHiggsSemiTagger();

    int Train(analysis::Event &event, analysis::PreCuts &pre_cuts, const Tag tag);

    std::vector<analysis::Sextet> Multiplets(analysis::Event& event, const TMVA::Reader& reader);

protected:

    virtual inline std::string ClassName() const {
        return "HeavyHiggsSemiTagger";
    }

private:

    void DefineVariables();

    analysis::TopHadronicTagger top_hadronic_tagger;

    analysis::TopSemiTagger top_semi_tagger;

    analysis::Reader top_hadronic_reader_;

    analysis::Reader top_semi_reader_;
};

}
