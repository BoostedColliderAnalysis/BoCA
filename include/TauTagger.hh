#pragma once

#include "BranchTagger.hh"
#include "Branches.hh"

namespace analysis
{

/**
 * @brief Bottom BDT tagger
 *
 */
class TauTagger : public BranchTagger<TauBranch>
{

public:

    TauTagger();

    int Train(const Event &event, PreCuts &pre_cuts, const analysis::Tag tag);

    Jets Multiplets(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader);

private:

    void DefineVariables();

    Jets CleanJets(Jets &jets, const Jets &Particles, const analysis::Tag Tag);

};

}
