#pragma once

#include "Octet.hh"
#include "TopPartnerLeptonicTagger.hh"
#include "TopHadronicTagger.hh"
#include "BranchesTopPartner.hh"

namespace boca {

namespace naturalness {

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class TopPartnerTopPairTagger : public BranchTagger<MultiBranch> {

public:

    TopPartnerTopPairTagger();

    int Train(Event const& event, PreCuts const& pre_cuts,
              Tag tag) const final;

    std::vector<Octet53> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const;

    int SaveBdt(Event const& event, PreCuts const& pre_cuts,
               TMVA::Reader const& reader) const final {
                 return SaveEntries(Multiplets(event, pre_cuts, reader), 1);
    }

    auto Multiplets(Event const& event, TMVA::Reader const& reader)
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
