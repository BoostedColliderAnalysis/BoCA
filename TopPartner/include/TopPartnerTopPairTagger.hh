#pragma once

#include "Octet.hh"
#include "TopPartnerLeptonicTagger.hh"
#include "TopHadronicTagger.hh"
#include "BranchesTopPartner.hh"

namespace analysis {

namespace toppartner {

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class TopPartnerTopPairTagger : public BranchTagger<MultiBranch> {

public:

    TopPartnerTopPairTagger();

    int Train(const Event &event, const PreCuts &pre_cuts,
              Tag tag) const final;

    std::vector<Octet53> Multiplets(const Event& event, const PreCuts& pre_cuts, const TMVA::Reader& reader) const;

    int GetBdt(const Event &event, const PreCuts &pre_cuts,
               const TMVA::Reader &reader) const final {
                 return SaveEntries(Multiplets(event, pre_cuts, reader), 1);
    }

    auto Multiplets(const Event& event, const TMVA::Reader& reader)
    {
        PreCuts pre_cuts;
        return Multiplets(event, pre_cuts, reader);
    }

    std::string Name() const final { return "TopPartnerTopPair"; }

private:

    Reader<TopPartnerLeptonicTagger> top_partner_reader_;

    Reader<TopHadronicTagger> top_reader_;
};

}

}
