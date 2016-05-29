/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include <functional>
#include "boca/multiplets/Quintet.hh"
#include "boca/TopPartnerHadronicNeutralTagger.hh"
#include "boca/standardmodel/TopLeptonicTagger.hh"
#include "boca/standardmodel/HiggsTagger.hh"

namespace boca
{

namespace toppartner
{

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class VetoTopPartnerLeptonicTagger : public Tagger<Quintet, VetoTopPartnerBranch>
{

public:

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    std::vector<Quintet> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

    latex::String LatexName() const override;

private:

    std::vector<Particle> Particles(Event const& event) const;

    std::vector<Quintet> Quintets(Event const& event, std::function<Quintet(Quintet&)> const& function);

    Reader<TopPartnerHadronicNeutralTagger> partner_reader_;

    Reader<standardmodel::TopLeptonicTagger> top_reader_;

    Reader<standardmodel::HiggsTagger> higgs_reader_;

};

}

}
