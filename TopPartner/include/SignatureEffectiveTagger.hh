#pragma once

#include "TopPartnerPairTagger.hh"
#include "HiggsPairTagger.hh"
#include "Quattuordecuplet.hh"

namespace boca
{

namespace naturalness
{

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class SignatureEffectiveTagger : public BranchTagger<SignatureBranch>
{

public:

    SignatureEffectiveTagger();

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) const final;

    std::vector<Quattuordecuplet> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const;

    int SaveBdt(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const final {
        return SaveEntries(Multiplets(event, pre_cuts, reader), 1);
    }

    std::string Name() const final {
        return "Signature";
    }

private:

    Reader<TopPartnerPairTagger> top_partner_pair_reader_;

    Reader<HiggsPairTagger> higgs_pair_reader_;
};

}

}
