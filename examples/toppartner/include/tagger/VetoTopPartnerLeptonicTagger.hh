/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include <functional>

#include "boca/multiplets/Quintet.hh"
#include "boca/standardmodel/tagger/TopLeptonic.hh"
#include "boca/standardmodel/tagger/Higgs.hh"

#include "include/tagger/TopPartnerHadronicNeutralTagger.hh"
#include "include/branch/VetoTopPartner.hh"

namespace toppartner
{

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class VetoTopPartnerLeptonicTagger : public Tagger<Quintet, branch::VetoTopPartnerBranch>
{

public:

    int Train(boca::Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    std::vector<Quintet> Multiplets(boca::Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

    latex::String LatexName() const override;

private:

    std::vector<Particle> Particles(boca::Event const& event) const;

    std::vector<Quintet> Quintets(boca::Event const& event, std::function<Quintet(Quintet&)> const& function);

    Reader<TopPartnerHadronicNeutralTagger> partner_reader_;

    Reader<standardmodel::tagger::TopLeptonic> top_reader_;

    Reader<standardmodel::tagger::Higgs> higgs_reader_;

};

}
