#pragma once

#include "BottomTagger.hh"
#include "Doublet.hh"
#include "Reader.hh"

namespace analysis
{

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class ZHadronicTagger : public BranchTagger<ZHadronicBranch>
{

public:

    ZHadronicTagger();

    int Train(const Event &event, PreCuts &pre_cuts, const Tag tag);

    std::vector< Doublet > Multiplets(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader);

    int GetBdt(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) {
        return SaveEntries(Multiplets(event, pre_cuts, reader), 2);
    }

    auto Multiplets(const Event &event, const TMVA::Reader &reader) {
        PreCuts pre_cuts;
        return Multiplets(event, pre_cuts, reader);
    }

private:

    bool Problematic(const Doublet &doublet, PreCuts &pre_cuts, const Tag tag);

    bool Problematic(const Doublet &doublet, PreCuts &pre_cuts);

    BottomTagger bottom_tagger_;

    Reader bottom_reader_;

    float z_mass_window = 20;

};

}
