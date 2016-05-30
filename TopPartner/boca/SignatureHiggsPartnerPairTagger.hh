/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include <functional>
#include "boca/standardmodel/tagger/Higgs.hh"
#include "boca/Duodecuplet.hh"
#include "boca/TopPartnerHadronicNeutralTagger.hh"
#include "boca/TopPartnerLeptonicNeutralTagger.hh"

namespace boca
{

namespace toppartner
{

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class SignatureHiggsPartnerPairTagger : public Tagger<Duodecuplet552, SignatureSingleHadronicBranch>
{

public:

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    std::vector<Duodecuplet552> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

    latex::String LatexName() const override;

private:

  std::vector<Duodecuplet552> Duodecuplets(Event const& event, std::function<Duodecuplet552(Duodecuplet552&)> const& function);

  Reader<TopPartnerHadronicNeutralTagger> top_partner_hadronic_reader_;

  Reader<TopPartnerLeptonicNeutralTagger> top_partner_leptonic_reader_;

  Reader<standardmodel::tagger::Higgs> higgs_reader_;

};

}

}
