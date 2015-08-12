#pragma once

#include <functional>
#include "Decuplet.hh"
#include "TopPartnerTopPairTagger.hh"
#include "HiggsTagger.hh"

namespace analysis
{

namespace toppartner
{

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class SignatureSingleTagger : public BranchTagger<SignatureBranch>
{

public:

    SignatureSingleTagger();

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) const final;

    int GetBdt(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const final {
        return SaveEntries(Multiplets(event, pre_cuts, reader), 1);
    }

    std::vector<Decuplet82> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const;

    std::string Name() const final {
        return "SignatureSingle";
    }

    std::string NiceName() const final {
        return "Tth";
    }

private:

    std::vector<Decuplet82> Decuplets(Event const& event, const std::function<Decuplet82(Decuplet82&)>& function) const;

    Reader<TopPartnerTopPairTagger> pair_reader_;

    Reader<HiggsTagger> higgs_reader_;
};

}

}
