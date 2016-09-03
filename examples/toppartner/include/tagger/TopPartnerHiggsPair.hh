#pragma once

#include "include/multiplets/Septet.hh"
#include "include/tagger/TopPartnerLeptonicNeutral.hh"

#include "standardmodel/tagger/Higgs.hh"

namespace toppartner
{

namespace tagger
{

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class TopPartnerHiggsPair : public Tagger<Septet, boca::branch::Multi>
{

public:

    int Train(boca::Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    std::vector<Septet> Multiplets(boca::Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

private:

    Reader<TopPartnerLeptonicNeutral> top_partner_hadronic_reader_;

    Reader<standardmodel::tagger::Higgs> higgs_reader_;
};

}

}
