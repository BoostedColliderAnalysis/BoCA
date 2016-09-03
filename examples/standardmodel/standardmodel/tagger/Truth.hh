/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/tagger/Tagger.hh"
#include "boca/multiplets/TruthVariables.hh"

#include "standardmodel/branch/Truth.hh"

// namespace boca
// {
// class Event;
// }

namespace standardmodel
{

namespace tagger
{

class Truth : public Tagger<boca::TruthVariables, branch::Truth>
{

public:

    int Train(boca::Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    using Tagger::Multiplets;

    std::vector<TruthVariables> Multiplets(boca::Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

    latex::String LatexName() const override;

private:

    std::vector<TruthVariables> Jets(const boca::Event& event, const boca::PreCuts& pre_cuts, std::function< Particle(Particle&) > const&)const;

};

}

}
