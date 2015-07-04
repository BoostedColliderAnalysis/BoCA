#pragma once

#include "Quartet.hh"
#include "HiggsTagger.hh"
#include "BranchesTopPartner.hh"

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

    int Train(const Event &event, PreCuts &pre_cuts, const Tag tag);

    std::vector<Quartet22> Multiplets(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader);

    int GetBdt(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) {
        return SaveEntries(Multiplets(event, pre_cuts, reader));
    }

private:

    HiggsTagger higgs_tagger_;

    Reader higgs_reader_;
};

}

}
