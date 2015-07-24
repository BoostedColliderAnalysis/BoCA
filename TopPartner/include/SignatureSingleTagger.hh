#pragma once

#include "Decuplet.hh"
#include "TopPartnerTopPairTagger.hh"
#include "HiggsTagger.hh"

namespace analysis {

namespace toppartner {

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class SignatureSingleTagger : public BranchTagger<SignatureBranch> {

public:

    SignatureSingleTagger();

    int Train(const Event& event, const PreCuts& pre_cuts, Tag tag) const final;

    int GetBdt(const Event& event, const PreCuts& pre_cuts, const TMVA::Reader& reader) const  final
    {
      return SaveEntries(Multiplets(event, pre_cuts, reader));
    }

    std::vector<Decuplet82> Multiplets(const Event& event, const PreCuts& pre_cuts, const TMVA::Reader& reader) const;

    std::string Name() const final
    {
        return "SignatureSingle";
    }

private:

    Reader<TopPartnerTopPairTagger> pair_reader_;

    Reader<HiggsTagger> higgs_reader_;
};

}

}
