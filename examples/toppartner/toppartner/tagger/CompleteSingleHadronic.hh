/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include <functional>

#include "boca/multiplets/EventMultiplet.hh"

#include "toppartner/multiplets/Decuplet.hh"
#include "toppartner/tagger/VetoTopPartnerLeptonic.hh"
#include "toppartner/branch/Complete.hh"

namespace toppartner
{

namespace tagger
{

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class CompleteSingleHadronic : public Tagger<EventMultiplet<Decuplet532>, branch::Complete>
{

public:

    int Train(boca::Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    std::vector<EventMultiplet<Decuplet532>> Multiplets(boca::Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

    latex::String LatexName() const override;

private:

    std::vector<EventMultiplet<Decuplet532>> Decuplets(boca::Event const& event, std::function<EventMultiplet<Decuplet532>(boca::EventMultiplet<Decuplet532>&)> const& function);

    Reader<TopPartnerHadronicNeutral> partner_reader_;

    Reader<standardmodel::tagger::TopLeptonic> top_reader_;

    Reader<standardmodel::tagger::Higgs> higgs_reader_;

    Reader<VetoTopPartnerLeptonic> veto_reader_;

    Reader<standardmodel::tagger::Bottom> bottom_reader_;

};

}

}
