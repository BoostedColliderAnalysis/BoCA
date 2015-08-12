#pragma once

#include "Quartet.hh"
#include "HiggsTagger.hh"
#include "BranchesTopPartner.hh"

namespace analysis {

namespace toppartner {

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class HiggsPairTagger : public BranchTagger<HiggsPairBranch> {

public:

    HiggsPairTagger();

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) const final;

    std::vector<Quartet22> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const;

    int GetBdt(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const final {
                 return SaveEntries(Multiplets(event, pre_cuts, reader), 1);
    }

    std::string Name() const final { return "HiggsPair"; }

private:

    Reader<HiggsTagger> higgs_reader_;
};

}

}
