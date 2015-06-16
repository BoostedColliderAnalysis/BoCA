# pragma once

# include "Quartet22.hh"
# include "HiggsTagger.hh"
# include "BranchesTopPartner.hh"

namespace analysis
{

namespace toppartner
{

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class HiggsPairTagger : public BranchTagger<HiggsPairBranch>
{

public:

    HiggsPairTagger();

    int Train(Event &event, PreCuts &pre_cuts, const Object::Tag tag);

    std::vector<Quartet22> Multiplets(Event &event, const TMVA::Reader &reader);

protected:

    virtual inline std::string ClassName() const {
        return "HiggsPairTagger";
    }

private:

    HiggsTagger higgs_tagger_;

    Reader higgs_reader_;
};

}

}
