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
class TopPartnerTopPairTagger : public TaggerTemplate<Octet53,MultiBranch> {

public:

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) const final;

    std::vector<Octet53> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const final;

    std::string Name() const final;

private:

    Reader<TopPartnerLeptonicTagger> top_partner_reader_;

    Reader<TopHadronicTagger> top_reader_;
};

}

}
