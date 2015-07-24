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

    int Train(const Event& event, const PreCuts& pre_cuts, Tag tag) const final;

    std::vector<Quartet22> Multiplets(const Event& event, const PreCuts& pre_cuts, const TMVA::Reader& reader) const;

    int GetBdt(const Event& event, const PreCuts& pre_cuts, const TMVA::Reader& reader) const  final
    {
        return SaveEntries(Multiplets(event, pre_cuts, reader));
    }

    std::string Name() const final
    {
        return "HiggsPair";
    }

private:

    Reader<HiggsTagger> higgs_reader_;
};

}

}
