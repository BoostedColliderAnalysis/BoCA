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

    int Train(const Event &event, PreCuts &pre_cuts, const analysis::Tag tag) const;

    Jets Multiplets(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) const;
    
    int GetBdt(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) const {
      return SaveEntries(Multiplets(event, pre_cuts, reader));
    }

private:

    void DefineVariables();

    Jets CleanJets(analysis::Jets &jets, const analysis::Jets &Particles, const analysis::Tag tag) const;

};

}
