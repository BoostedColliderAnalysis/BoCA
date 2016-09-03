/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once
#include "boca/tagger/Tagger.hh"
#include "boca/multiplets/Singlet.hh"

#include "standardmodel/branch/Tau.hh"

namespace boca
{
class Event;
}

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

    int Train(boca::Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    using Tagger::Multiplets;

    std::vector<Singlet> Multiplets(boca::Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

private:

    std::vector<boca::Jet> CleanJets(std::vector<boca::Jet>& jets, std::vector<Particle> const& Particles, Tag tag) const;

};

}

}
