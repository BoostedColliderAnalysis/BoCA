#pragma once

#include "toppartner/tagger/TopPartnerHadronic.hh"
#include "toppartner/tagger/TopPartnerLeptonic.hh"
#include "toppartner/multiplets/Decuplet.hh"

namespace toppartner
{

namespace tagger
{

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class TopPartnerPair : public Tagger<Decuplet55, boca::branch::Multi>
{

public:

    int Train(boca::Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    std::vector<Decuplet55> Multiplets(boca::Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

    latex::String LatexName() const override;

private:

    std::vector<Decuplet55> Decuplets(boca::Event const& event, std::function<Decuplet55(Decuplet55&)> const& function);

    Reader<TopPartnerHadronic> top_partner_hadronic_reader_;

    Reader<TopPartnerLeptonic> top_partner_leptonic_reader_;
};

}

}
