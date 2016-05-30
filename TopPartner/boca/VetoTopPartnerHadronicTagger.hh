/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include <functional>
#include "boca/multiplets/Quintet.hh"
#include "boca/TopPartnerLeptonicNeutralTagger.hh"
#include "boca/standardmodel/tagger/TopHadronic.hh"
#include "boca/standardmodel/tagger/Higgs.hh"

namespace boca
{

namespace toppartner
{

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class VetoTopPartnerHadronicTagger : public Tagger<Quintet, TopPartnerBranch>
{

public:

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    std::vector<Quintet> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

    latex::String LatexName() const override;

private:

    std::vector<Particle> Particles(Event const& event) const;

    std::vector<Quintet> Quintets(Event const& event, std::function<Quintet(Quintet&)> const& function);

    Reader<TopPartnerLeptonicNeutralTagger> partner_reader_;

    Reader<standardmodel::tagger::TopHadronic> top_reader_;

    Reader<standardmodel::tagger::Higgs> higgs_reader_;

};

}

}
