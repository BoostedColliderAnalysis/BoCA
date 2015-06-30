#pragma once

#include "Quattuordecuplet.hh"
#include "TopPartnerPairTagger.hh"
#include "HiggsPairTagger.hh"

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

    int Train(Event &event, PreCuts &pre_cuts, const Tag tag);

    std::vector<Quattuordecuplet> Multiplets(Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader);

protected:

    virtual  std::string ClassName() const {
      return "SignatureTagger";
    }

private:

    TopPartnerPairTagger top_partner_pair_tagger_;

    HiggsPairTagger higgs_pair_tagger;

    Reader top_partner_pair_reader_;

    Reader higgs_pair_reader_;
};

}

}
