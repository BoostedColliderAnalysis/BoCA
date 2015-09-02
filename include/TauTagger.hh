/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "Branches.hh"
#include "BranchTagger.hh"

namespace boca {

/**
 * @brief Bottom BDT tagger
 *
 */
class TauTagger : public BranchTagger<TauBranch> {

public:

    TauTagger();

    int Train(Event const& event, PreCuts const& pre_cuts,
              Tag tag) const final;

    Jets Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const;

    int GetBdt(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const final {
        return SaveEntries(Multiplets(event, pre_cuts, reader));
    }

    std::string Name() const final { return "Tau"; }

private:

    Jets CleanJets(boca::Jets& jets, boca::Jets const& Particles, Tag tag) const;

};

}
