/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include <functional>
#include "boca/Decuplet.hh"
#include "boca/VetoTopPartnerLeptonicTagger.hh"
#include "boca/EventMultiplet.hh"

namespace boca
{

namespace naturalness
{

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class CompleteSingleHadronicTagger : public TaggerTemplate<EventMultiplet<Decuplet532>, CompleteBranch>
{

public:

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    std::vector<EventMultiplet<Decuplet532>> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

    latex::String LatexName() const override;

private:

    std::vector<EventMultiplet<Decuplet532>> Decuplets(Event const& event, std::function<EventMultiplet<Decuplet532>(EventMultiplet<Decuplet532>&)> const& function);

    Reader<TopPartnerHadronicNeutralTagger> partner_reader_;

    Reader<standardmodel::TopLeptonicTagger> top_reader_;

    Reader<standardmodel::HiggsTagger> higgs_reader_;

    Reader<VetoTopPartnerLeptonicTagger> veto_reader_;

    Reader<standardmodel::BottomTagger> bottom_reader_;

};

}

}
