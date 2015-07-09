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
 * @brief top partner pair tagger
 *
 */
class TopPartnerLeptonicPairTagger : public BranchTagger<MultiBranch>
{

public:

    TopPartnerLeptonicPairTagger();

    int Train(const Event &event, PreCuts &pre_cuts, const Tag tag) const final;

    std::vector<Nonet> Multiplets(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) const;

    int GetBdt(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) const  final {
      return SaveEntries(Multiplets(event,pre_cuts, reader));
    }

    std::string name() const final {
      return "TopPartnerLeptonicPair";
    }

private:

    Reader<TopPartnerHadronicTagger> top_partner_hadronic_reader_;

    Reader<TopPartnerLeptonicTagger> top_partner_semi_reader_;

};

}

}
