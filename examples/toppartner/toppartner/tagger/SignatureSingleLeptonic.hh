/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include <functional>

#include "toppartner/multiplets/Decuplet.hh"
#include "toppartner/tagger/VetoTopPartnerHadronic.hh"
#include "toppartner/branch/SignatureSingle.hh"

namespace toppartner
{

namespace tagger
{

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class SignatureSingleLeptonic : public Tagger<Decuplet532, branch::SignatureSingle>
{

public:

    int Train(boca::Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    std::vector<Decuplet532> Multiplets(boca::Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

    latex::String LatexName() const override;

private:

    std::vector<Decuplet532> Decuplets(boca::Event const& event, std::function<Decuplet532(Decuplet532&)> const& function);

    Reader<TopPartnerLeptonicNeutral> partner_reader_;

    Reader<standardmodel::tagger::TopHadronic> top_reader_;

    Reader<standardmodel::tagger::Higgs> higgs_reader_;

    Reader<VetoTopPartnerHadronic> veto_reader_;
};

}

}
