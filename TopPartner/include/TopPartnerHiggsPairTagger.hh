#pragma once

#include "Septet.hh"
#include "TopPartnerSemiTagger.hh"
// #include "TopPartnerLeptonicTagger.hh"
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
class TopPartnerHiggsPairTagger : public BranchTagger<MultiBranch>
{

public:

    TopPartnerHiggsPairTagger();

    int Train(const Event &event, PreCuts &pre_cuts, const Tag tag);

    std::vector<Septet> Multiplets(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader);

    int GetBdt(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) {
      return SaveEntries(Multiplets(event,pre_cuts, reader));
    }

    auto Multiplets(const Event &event, const TMVA::Reader &reader){
      PreCuts pre_cuts;
      return Multiplets(event, pre_cuts, reader);
    }

private:

    TopPartnerSemiTagger top_partner_hadronic_tagger_;
//     TopPartnerLeptonicTagger top_partner_hadronic_tagger_;

    HiggsTagger higgs_tagger_;

    Reader top_partner_hadronic_reader_;

    Reader higgs_reader_;
};

}

}
