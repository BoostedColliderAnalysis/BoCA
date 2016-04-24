/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include <functional>
#include "boca/Decuplet.hh"
#include "boca/VetoTopPartnerHadronicTagger.hh"

namespace boca
{

namespace naturalness
{

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class SignatureSingleLeptonicTagger : public TaggerTemplate<Decuplet532, SignatureSingleBranch>
{

public:

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    std::vector<Decuplet532> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

    std::string LatexName() const override;

private:

    std::vector<Decuplet532> Decuplets(Event const& event, std::function<Decuplet532(Decuplet532&)> const& function);

    Reader<TopPartnerLeptonicNeutralTagger> partner_reader_;

    Reader<standardmodel::TopHadronicTagger> top_reader_;

    Reader<standardmodel::HiggsTagger> higgs_reader_;

    Reader<VetoTopPartnerHadronicTagger> veto_reader_;
};

}

}
