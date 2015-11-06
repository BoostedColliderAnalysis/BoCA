/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "Branches.hh"
#include "TaggerTemplate.hh"

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

    Jets CleanJets(boca::Jets& jets, boca::Jets const& Particles, Tag tag) const;

};

}

}
