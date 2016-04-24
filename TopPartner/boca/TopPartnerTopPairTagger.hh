#pragma once

#include "boca/multiplets/Octet.hh"
#include "boca/TopPartnerLeptonicNeutralTagger.hh"
#include "boca/standardmodel/TopHadronicTagger.hh"

namespace boca {

namespace naturalness {

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class TopPartnerTopPairTagger : public TaggerTemplate<Octet53,MultiBranch> {

public:

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    std::vector<Octet53> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

private:

    Reader<TopPartnerLeptonicNeutralTagger> top_partner_reader_;

    Reader<standardmodel::TopHadronicTagger> top_reader_;
};

}

}
