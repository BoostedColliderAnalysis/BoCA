#pragma once

#include "boca/branch/ThreeBody.hh"

#include "standardmodel/tagger/Higgs.hh"

#include "toppartner/tagger/TopPartnerLeptonic.hh"
#include "toppartner/tagger/TopPartnerHadronic.hh"
#include "toppartner/multiplets/Duodecuplet.hh"

namespace toppartner
{

namespace tagger
{

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class SignatureSubDom : public Tagger<Duodecuplet552, boca::branch::ThreeBody>
{

public:

    int Train(boca::Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    std::vector<Duodecuplet552> Multiplets(boca::Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

    latex::String LatexName() const override;

private:

    std::vector<Duodecuplet552> Quattuordecuplets(boca::Event const& event, std::function<Duodecuplet552(Duodecuplet552&)> const& function);

    Reader<TopPartnerHadronic> top_partner_hadronic_reader_;
    Reader<TopPartnerLeptonic> top_partner_leptonic_reader_;
    Reader<standardmodel::tagger::Higgs> higgs_reader_;

};

}

}
