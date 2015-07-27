#pragma once

#include "BranchTagger.hh"
#include "Branches.hh"

namespace analysis {

/**
 * @brief Bottom BDT tagger
 *
 */
class TauTagger : public BranchTagger<TauBranch> {

public:

    TauTagger();

    int Train(const Event& event, const PreCuts& pre_cuts, Tag tag) const final;

    Jets Multiplets(const Event& event, const PreCuts& pre_cuts, const TMVA::Reader& reader) const;

    int GetBdt(const Event& event, const PreCuts& pre_cuts, const TMVA::Reader& reader) const  final
    {
        return SaveEntries(Multiplets(event, pre_cuts, reader));
    }

    std::string Name() const final
    {
        return "Tau";
    }

private:

    Jets CleanJets(analysis::Jets& jets, const analysis::Jets& Particles, Tag tag) const;

};

}
