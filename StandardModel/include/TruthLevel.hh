/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "BranchesSm.hh"
#include "TaggerTemplate.hh"
#include "TruthVariables.hh"

namespace boca
{

namespace standardmodel
{

class TruthLevel : public TaggerTemplate<TruthVariables, TruthBranch>
{

public:

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) const override;

    std::vector<TruthVariables> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const override;

    std::string Name() const override;

    std::string LatexName() const override;

private:

    std::vector<TruthVariables> Jets(Event const& event, PreCuts const& pre_cuts, std::function<Particle(Particle&)>)const;

};

}

}
