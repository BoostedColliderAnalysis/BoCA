#pragma once

#include "Branches.hh"
#include "BranchTagger.hh"

namespace analysis {

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

    Jets CleanJets(analysis::Jets& jets, analysis::Jets const& Particles, Tag tag) const;

};

}
