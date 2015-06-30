#pragma once

#include "TopLeptonicTagger.hh"
#include "Sextet.hh"
#include "BranchesHiggsCpv.hh"

namespace analysis
{

namespace higgscpv
{

/**
 * @brief JetPair BDT tagger
 *
 */
class TopLeptonicPairTagger : public BranchTagger<TopLeptonicPairBranch>
{

public:

    TopLeptonicPairTagger();

    int Train(analysis::Event &event, analysis::PreCuts &, const analysis::Tag tag);

    std::vector<Sextet> Multiplets(analysis::Event &event, analysis::PreCuts &, const TMVA::Reader &reader);

    int GetBdt(Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) {
        return SaveEntries(Multiplets(event, pre_cuts, reader));
    }

    auto Multiplets(Event &event, const TMVA::Reader &reader) {
        PreCuts pre_cuts;
        return Multiplets(event, pre_cuts, reader);
    }

private:

    TopLeptonicTagger top_leptonic_tagger_;

    Reader top_leptonic_reader_;

};

}

}
