/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/TaggerTemplate.hh"
#include "boca/standardmodel/Branches.hh"
#include "boca/standardmodel/TruthVariables.hh"

namespace boca
{

namespace standardmodel
{

class TruthLevel : public TaggerTemplate<TruthVariables, TruthBranch>
{

public:

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    using TaggerTemplate::Multiplets;

    std::vector<TruthVariables> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

    latex::String LatexName() const override;

private:

    std::vector<TruthVariables> Jets(const boca::Event& event, const boca::PreCuts& pre_cuts, std::function< Particle(Particle&) > const&)const;

};

}

}