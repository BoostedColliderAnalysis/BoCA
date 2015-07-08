#pragma once

#include "TopPartnerHadronicTagger.hh"
#include "TopPartnerSemiTagger.hh"
#include "BranchesTopPartner.hh"
#include "Decuplet.hh"

namespace analysis
{

namespace toppartner
{

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class TopPartnerPairTagger : public BranchTagger<MultiBranch>
{

public:

    TopPartnerPairTagger();

    int Train(const Event &event, PreCuts &pre_cuts, const Tag tag) const final;

    std::vector<Decuplet55> Multiplets(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) const;

    int GetBdt(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) const  final {
      return SaveEntries(Multiplets(event, pre_cuts, reader));
    }

    std::string name() const final {
      return "TopPartnerPair";
    }

private:

    Reader<TopPartnerHadronicTagger> top_partner_hadronic_reader_;

    Reader<TopPartnerSemiTagger> top_partner_semi_reader_;
};

}

}
