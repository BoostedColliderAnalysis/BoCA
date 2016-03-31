/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include <functional>
#include "multiplets/Quintet.hh"
#include "TopPartnerHadronicNeutralTagger.hh"
#include "TopLeptonicTagger.hh"
#include "HiggsTagger.hh"

namespace boca
{

namespace naturalness
{

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class VetoTopPartnerLeptonicTagger : public TaggerTemplate<Quintet, VetoTopPartnerBranch>
{

public:

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) const override;

    std::vector<Quintet> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const override;

    std::string Name() const override;

    std::string LatexName() const override;

private:

    std::vector<Particle> Particles(Event const& event) const;

    std::vector<Quintet> Quintets(Event const& event, std::function<Quintet(Quintet&)> const& function) const;

    Reader<TopPartnerHadronicNeutralTagger> partner_reader_;

    Reader<standardmodel::TopLeptonicTagger> top_reader_;

    Reader<standardmodel::HiggsTagger> higgs_reader_;

};

}

}
