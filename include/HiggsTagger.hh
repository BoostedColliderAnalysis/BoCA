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
class HiggsTagger : public BranchTagger<HiggsBranch>
{

public:

    HiggsTagger();

    int Train(const Event &event, PreCuts &pre_cuts, const Tag tag);

    std::vector< Doublet > Multiplets(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader);

    int GetBdt(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) {
        return SaveEntries(Multiplets(event, pre_cuts, reader), 1);
    }

protected:

private:

    bool Problematic(const Doublet &doublet, PreCuts &pre_cuts, const Tag tag);

    bool Problematic(const Doublet &doublet, PreCuts &pre_cuts);

    BottomTagger bottom_tagger_;

    Reader bottom_reader_;

    float higgs_mass_window = 40;

};

}
