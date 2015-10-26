#pragma once

#include "Septet.hh"
#include "TopPartnerLeptonicTagger.hh"
#include "HiggsTagger.hh"
#include "BranchesTopPartner.hh"

namespace boca {

namespace naturalness {

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class TopPartnerHiggsPairTagger : public TaggerTemplate<Septet,MultiBranch> {

public:

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) const final;

    std::vector<Septet> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const final;

    std::string Name() const final;

private:

    Reader<TopPartnerLeptonicTagger> top_partner_hadronic_reader_;

    Reader<HiggsTagger> higgs_reader_;
};

}

}
