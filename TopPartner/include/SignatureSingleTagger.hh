#pragma once

#include "Decuplet.hh"
#include "TopPartnerHiggsPairTagger.hh"
#include "TopHadronicTagger.hh"

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

    int Train(const Event &event, PreCuts &pre_cuts, const Tag tag) const final;

    std::vector<Decuplet73> Multiplets(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) const;

    std::string name() const final {
      return "SignatureSingle";
    }

private:

    Reader<TopPartnerHiggsPairTagger> top_partner_higgs_pair_reader_;

    Reader<TopHadronicTagger> top_hadronic_reader_;
};

}

}
