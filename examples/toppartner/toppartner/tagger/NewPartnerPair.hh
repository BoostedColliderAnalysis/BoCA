#pragma once

#include "toppartner/tagger/NewPartnerHadronic.hh"
#include "toppartner/tagger/NewPartnerLeptonic.hh"
#include "toppartner/multiplets/Decuplet.hh"

namespace toppartner
{

namespace tagger
{

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class NewPartnerPair : public Tagger<Decuplet55, boca::branch::Multi>
{

public:

    int Train(boca::Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    std::vector<Decuplet55> Multiplets(boca::Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

    latex::String LatexName() const override;

private:

    Reader<NewPartnerHadronic> top_partner_hadronic_reader_;

    Reader<NewPartnerLeptonic> top_partner_leptonic_reader_;
};

}

}
