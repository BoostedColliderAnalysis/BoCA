/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include <functional>
#include "Decuplet.hh"
#include "TopPartnerLeptonicTagger.hh"
#include "TopPartnerHadronicTagger.hh"
#include "HiggsTagger.hh"

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

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) const final;

    std::vector<Decuplet532> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const final;

    std::string Name() const final;

    std::string NiceName() const final;

private:

    std::vector<Decuplet532> Decuplets(Event const& event, PreCuts const& pre_cuts, std::function<Decuplet532(Decuplet532&)> const& function) const;

    Reader<TopPartnerLeptonicTagger> partner_reader_;

    Reader<TopHadronicTagger> top_reader_;

    Reader<HiggsTagger> higgs_reader_;

    Reader<BosonTagger> boson_reader_;

    Reader<TopPartnerHadronicTagger> veto_reader_;
};

}

}
