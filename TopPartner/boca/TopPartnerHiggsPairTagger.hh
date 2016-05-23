#pragma once

#include "boca/Septet.hh"
#include "boca/TopPartnerLeptonicNeutralTagger.hh"
#include "boca/standardmodel/HiggsTagger.hh"

namespace boca {

namespace naturalness {

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class TopPartnerHiggsPairTagger : public Tagger<Septet,MultiBranch> {

public:

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    std::vector<Septet> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

private:

    Reader<TopPartnerLeptonicNeutralTagger> top_partner_hadronic_reader_;

    Reader<standardmodel::HiggsTagger> higgs_reader_;
};

}

}
