#pragma once

#include "BottomTagger.hh"
#include "Doublet.hh"
#include "ReaderTagger.hh"

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

    int Train(const Event &event, PreCuts &pre_cuts, const Tag tag) const;

    std::vector< Doublet > Multiplets(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) const;

    int GetBdt(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) const {
        return SaveEntries(Multiplets(event, pre_cuts, reader), 2);
    }

    auto Multiplets(const Event &event, const TMVA::Reader &reader) const {
        PreCuts pre_cuts;
        return Multiplets(event, pre_cuts, reader);
    }

    std::string name() const {
      return "ZHadronic";
    }

private:

    bool Problematic(const Doublet &doublet, PreCuts &pre_cuts, const Tag tag) const;

    bool Problematic(const Doublet &doublet, PreCuts &pre_cuts) const;

    ReaderTagger<BottomTagger> bottom_reader_;

    float z_mass_window = 20;

};

}
