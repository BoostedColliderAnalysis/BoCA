#pragma once

#include "BottomTagger.hh"
#include "Doublet.hh"
#include "ReaderTagger.hh"

namespace analysis {

/**
 * @brief W BDT tagger
 *
 */
// template <typename DoubletBranch>
class DoubletTagger : public BranchTagger<DoubletBranch>
{

public:

    DoubletTagger();

    int Train(const Event &event, const Tag Tag) {
        PreCuts pre_cuts;
        return Train(event, pre_cuts, Tag);
    }

    int Train(const Event &event, PreCuts &pre_cuts, const Tag Tag);

    virtual int GetBdt(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) const {
        return SaveEntries(Multiplets(event, reader));
    }

    virtual int GetBdt(const Event &event, const TMVA::Reader &reader) {
        PreCuts pre_cuts;
        return GetBdt(event, pre_cuts, reader);
    }

    std::vector<Doublet> Multiplets(const Event &event, const TMVA::Reader &reader) const;

    std::vector<Doublet> Multiplets(const Jets &jets, const TMVA::Reader &reader) const;

    std::vector<Doublet> Multiplet(const fastjet::PseudoJet &jet_1, const fastjet::PseudoJet &jet_2, const TMVA::Reader &reader) const;

    std::vector<Doublet> Multiplet(const fastjet::PseudoJet &jet, const TMVA::Reader &reader) const;

private:

  std::vector<analysis::Doublet> Multiplet(analysis::Doublet &doublet, const TMVA::Reader &reader) const;

    std::vector<Doublet> Multiplets(const Jets &jets, const TMVA::Reader &reader, const int sub_jet_number);

    ReaderTagger<BottomTagger> bottom_reader_;

    void DefineVariables();

    DoubletBranch branch_;

    float doublet_mass_window_;
};

}
