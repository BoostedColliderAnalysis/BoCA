#pragma once

#include "TopPartnerHadronicTagger.hh"
#include "TopPartnerLeptonicTagger.hh"
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

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) const final;

    std::vector<Decuplet55> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const;

    int GetBdt(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const final {
        return SaveEntries(Multiplets(event, pre_cuts, reader), 1);
    }

    std::string Name() const final {
        return "TopPartnerPair";
    }

    std::string NiceName() const final {
      return "#tilde t_{h} #tilde t_{l}";
    }

private:

    Reader<TopPartnerHadronicTagger> top_partner_hadronic_reader_;

    Reader<TopPartnerLeptonicTagger> top_partner_leptonic_reader_;
};

}

}
