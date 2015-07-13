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

    int Train(const Event &event, PreCuts &pre_cuts, const Tag tag) const final;

    std::vector<Quartet22> Multiplets(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) const;

    int GetBdt(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) const  final {
        return SaveEntries(Multiplets(event, pre_cuts, reader));
    }

    std::string name() const final {
      return "HiggsPair";
    }

private:

    Reader<HiggsTagger> higgs_reader_;
};

}

}
