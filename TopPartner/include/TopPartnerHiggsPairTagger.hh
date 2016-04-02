#pragma once

#include "Septet.hh"
#include "TopPartnerLeptonicNeutralTagger.hh"
#include "HiggsTagger.hh"

namespace boca {

namespace naturalness {

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class TopPartnerHiggsPairTagger : public TaggerTemplate<Septet,MultiBranch> {

public:

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) const override;

    std::vector<Septet> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const override;

    std::string Name() const override;

private:

    Reader<TopPartnerLeptonicNeutralTagger> top_partner_hadronic_reader_;

    Reader<standardmodel::HiggsTagger> higgs_reader_;
};

}

}
