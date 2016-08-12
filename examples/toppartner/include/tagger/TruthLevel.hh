/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/Tagger.hh"

#include "include/multiplets/TruthVariables.hh"
#include "include/branch/Truth.hh"

namespace toppartner
{

namespace tagger
{

class TruthLevel : public Tagger<TruthVariables, branch::Truth>
{

public:

    int Train(boca::Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    std::vector<TruthVariables> Multiplets(const boca::Event& event, const boca::PreCuts& pre_cuts, const TMVA::Reader&) override;

    std::string Name() const override;

    latex::String LatexName() const override;

private:

    std::vector<TruthVariables> Jets(boca::Event const& event, PreCuts const& pre_cuts, std::function<Particle(Particle&)>const&)const;

};

}

}
