/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include <functional>

#include "boca/standardmodel/tagger/Higgs.hh"

#include "include/branch/SignatureSingleHadronic.hh"
#include "include/tagger/TopPartnerHadronicNeutralTagger.hh"
#include "include/tagger/TopPartnerLeptonicNeutralTagger.hh"
#include "include/multiplets//Duodecuplet.hh"

namespace toppartner
{

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class SignatureHiggsPartnerPairTagger : public Tagger<Duodecuplet552, branch::SignatureSingleHadronicBranch>
{

public:

    int Train(boca::Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    std::vector<Duodecuplet552> Multiplets(boca::Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

    latex::String LatexName() const override;

private:

  std::vector<Duodecuplet552> Duodecuplets(boca::Event const& event, std::function<Duodecuplet552(Duodecuplet552&)> const& function);

  Reader<TopPartnerHadronicNeutralTagger> top_partner_hadronic_reader_;

  Reader<TopPartnerLeptonicNeutralTagger> top_partner_leptonic_reader_;

  Reader<standardmodel::tagger::Higgs> higgs_reader_;

};

}
