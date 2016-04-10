/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include <functional>
#include "Decuplet.hh"
#include "VetoTopPartnerLeptonicTagger.hh"

namespace boca
{

namespace naturalness
{

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class SignatureSingleHadronicTagger : public TaggerTemplate<Decuplet532, SignatureSingleHadronicBranch>
{

public:

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    std::vector<Decuplet532> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

    std::string LatexName() const override;

private:

    std::vector<Decuplet532> Decuplets(Event const& event, std::function<Decuplet532(Decuplet532&)> const& function);

    Reader<TopPartnerHadronicNeutralTagger> partner_reader_;

    Reader<standardmodel::TopLeptonicTagger> top_reader_;

    Reader<standardmodel::HiggsTagger> higgs_reader_;

    Reader<VetoTopPartnerLeptonicTagger> veto_reader_;

};

}

}
