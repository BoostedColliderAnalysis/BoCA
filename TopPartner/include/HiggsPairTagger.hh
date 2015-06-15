# pragma once

# include "Quartet22.hh"
# include "HiggsTagger.hh"
# include "BranchesTopPartner.hh"

namespace toppartner
{

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class HiggsPairTagger : public analysis::BranchTagger<HiggsPairBranch>
{

public:

    HiggsPairTagger();

    int Train(analysis::Event &event, analysis::PreCuts &pre_cuts, const analysis::Object::Tag tag);

    std::vector<analysis::Quartet22> Multiplets(analysis::Event &event, const TMVA::Reader &reader);

protected:

    virtual inline std::string ClassName() const {
        return "HiggsPairTagger";
    }

private:

    void DefineVariables();

    analysis::HiggsTagger higgs_tagger_;

    analysis::Reader higgs_reader_;
};

}
