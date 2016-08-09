/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/standardmodel/branch/Tau.hh"
#include "boca/tagger/Tagger.hh"
#include "boca/multiplets/Singlet.hh"

namespace boca
{

namespace standardmodel
{

namespace tagger
{

/**
 * @brief BDT tagger for tau leptons
 *
 */
class Tau : public Tagger<Singlet, branch::Tau>
{

public:

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    using Tagger::Multiplets;

    std::vector<Singlet> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

private:

    std::vector<Jet> CleanJets(std::vector<Jet>& jets, std::vector<Particle> const& Particles, Tag tag) const;

};

}

}

}
