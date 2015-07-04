#pragma once

#include "BottomTagger.hh"
#include "Doublet.hh"
#include "Reader.hh"

namespace analysis
{

/**
 * @brief JetPair BDT tagger
 *
 */
class JetPairTagger : public BranchTagger<JetPairBranch>
{

public:

    JetPairTagger();

    int Train(const Event &event, PreCuts &pre_cuts, const Tag tag);

    std::vector<Doublet> Multiplets(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader);

private:

    void DefineVariables();

    BottomTagger bottom_tagger_;

    Reader bottom_reader_;

};

}
