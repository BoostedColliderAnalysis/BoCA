#pragma once

#include "TopPartnerHadronicTagger.hh"
#include "TopPartnerLeptonicTagger.hh"
#include "BranchesTopPartner.hh"
#include "Decuplet.hh"

namespace analysis {

namespace toppartner {

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class TopPartnerPairTagger : public BranchTagger<MultiBranch> {

public:

    TopPartnerPairTagger();

    int Train(const Event &event, const PreCuts &pre_cuts,
              Tag tag) const final;

    std::vector<Decuplet55> Multiplets(const Event& event, const PreCuts& pre_cuts, const TMVA::Reader& reader) const;

    int GetBdt(const Event &event, const PreCuts &pre_cuts,
               const TMVA::Reader &reader) const final {
                 return SaveEntries(Multiplets(event, pre_cuts, reader), 1);
    }

    std::string Name() const final { return "TopPartnerPair"; }

private:

    Reader<TopPartnerHadronicTagger> top_partner_hadronic_reader_;

    Reader<TopPartnerLeptonicTagger> top_partner_leptonic_reader_;
};

}

}
