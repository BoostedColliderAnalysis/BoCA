/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "BranchesSm.hh"
#include "TaggerTemplate.hh"
#include "multiplets/Singlet.hh"

namespace boca
{

namespace standardmodel
{

/**
 * @brief Bottom BDT tagger
 *
 */
class TauTagger : public TaggerTemplate<Singlet, TauBranch>
{

public:

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) const final;

    std::vector<Singlet> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const final;

    std::string Name() const final;

private:

  std::vector<Jet> CleanJets(std::vector<Jet>& jets, std::vector<Particle> const& Particles, Tag tag) const;

};

}

}
