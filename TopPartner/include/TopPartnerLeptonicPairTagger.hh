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

    int Train(const Event &event, PreCuts &pre_cuts, const Tag tag) const;

    std::vector<Nonet> Multiplets(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) const;

    int GetBdt(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) const {
      return SaveEntries(Multiplets(event,pre_cuts, reader));
    }

    std::string name() const {
      return "TopPartnerLeptonicPair";
    }

private:

    ReaderTagger<TopPartnerHadronicTagger> top_partner_hadronic_reader_;

    ReaderTagger<TopPartnerLeptonicTagger> top_partner_semi_reader_;

};

}

}
