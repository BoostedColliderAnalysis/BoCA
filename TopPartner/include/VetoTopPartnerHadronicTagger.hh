/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include <functional>
#include "multiplets/Quintet.hh"
#include "TopPartnerLeptonicTagger.hh"
#include "TopHadronicTagger.hh"
#include "HiggsTagger.hh"

namespace boca
{

namespace naturalness
{

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class VetoTopPartnerHadronicTagger : public TaggerTemplate<Quintet, TopPartnerBranch>
{

public:

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) const final;

    std::vector<Quintet> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const final;

    std::string Name() const final;

    std::string NiceName() const final;

private:

    std::vector<Particle> Particles(Event const& event) const;

    std::vector<Quintet> Quintets(Event const& event, std::function<Quintet(Quintet&)> const& function) const;

    Reader<TopPartnerLeptonicTagger> partner_reader_;

    Reader<standardmodel::TopHadronicTagger> top_reader_;

    Reader<standardmodel::HiggsTagger> higgs_reader_;

};

}

}
