#pragma once

#include "BottomTagger.hh"
#include "Doublet.hh"
#include "ReaderTagger.hh"

namespace analysis
{

/**
 * @brief Top leptonic BDT tagger
 *
 */
class TopLeptonicTagger : public BranchTagger<TopLeptonicBranch>
{

public:

    TopLeptonicTagger();

    int Train(const Event &event, PreCuts &pre_cuts, const analysis::Tag tag) const;

    std::vector< Doublet> Multiplets(const Event &event, analysis::PreCuts &pre_cuts, const TMVA::Reader &reader) const;

    int GetBdt(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) const {
//         do_fake_leptons = true;
        return SaveEntries(Multiplets(event, pre_cuts, reader), 1);
//         return SaveEntries(Multiplets(event, pre_cuts, reader), Particles(event).size());
    }

    bool Problematic(const Doublet &doublet, PreCuts &pre_cuts, const Tag tag) const;

    bool Problematic(const Doublet &doublet, PreCuts &pre_cuts) const;

    fastjet::PseudoJet FakeLepton(const fastjet::PseudoJet &jet) const;

    Jets Particles(const analysis::Event &event) const;

    auto Multiplets(const Event &event, const TMVA::Reader &reader) const {
        PreCuts pre_cuts;
        return Multiplets(event, pre_cuts, reader);
    }

    std::string name() const {
      return "TopLeptonic";
    }

private:

    ReaderTagger<BottomTagger> bottom_reader_;

    float top_mass_window;

//     bool do_fake_leptons_ = false;

};

}
