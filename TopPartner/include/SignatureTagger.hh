#pragma once

#include "TopPartnerPairTagger.hh"
#include "HiggsPairTagger.hh"
#include "Quattuordecuplet.hh"

namespace analysis
{

namespace toppartner
{

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class SignatureTagger : public BranchTagger<SignatureBranch>
{

public:

    SignatureTagger();

    int Train(const Event &event, PreCuts &pre_cuts, const Tag tag) const final;

    std::vector<Quattuordecuplet> Multiplets(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) const;

    int GetBdt(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) const  final {
      return SaveEntries(Multiplets(event, pre_cuts, reader));
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
