#pragma once

#include "Nonet.hh"
#include "TopPartnerHadronicTagger.hh"
#include "TopPartnerLeptonicTagger.hh"
#include "BranchesTopPartner.hh"

namespace analysis
{

namespace toppartner
{

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class TopPartnerLeptonicPairTagger : public BranchTagger<MultiBranch>
{

public:

    TopPartnerLeptonicPairTagger();

    int Train(const Event &event, PreCuts &pre_cuts, const Tag tag);

    std::vector<Nonet> Multiplets(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader);

    int GetBdt(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) {
      return SaveEntries(Multiplets(event,pre_cuts, reader));
    }

private:

    TopPartnerHadronicTagger top_partner_hadronic_tagger_;

    TopPartnerLeptonicTagger top_partner_semi_tagger_;

    Reader top_partner_hadronic_reader_;

    Reader top_partner_semi_reader_;
};

}

}
