/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/BranchesTopPartner.hh"
#include "boca/TaggerTemplate.hh"
#include "boca/../boca/TruthVariables.hh"

namespace boca
{

namespace naturalness
{

class TruthLevel : public TaggerTemplate<TruthVariables, TruthBranch>
{

public:

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    std::vector<TruthVariables> Multiplets(const boca::Event& event, const boca::PreCuts& pre_cuts, const TMVA::Reader&) override;

    std::string Name() const override;

    Latex LatexName() const override;

private:

  std::vector<TruthVariables> Jets(Event const& event, PreCuts const& pre_cuts, std::function<Particle(Particle&)>const&)const;

};

}

}
