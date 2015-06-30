#pragma once

#include "BottomTagger.hh"
#include "Doublet.hh"
#include "Reader.hh"

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

    int Train(analysis::Event &event, PreCuts &pre_cuts, const analysis::Tag tag);

    std::vector< Doublet> Multiplets(analysis::Event &event, analysis::PreCuts &pre_cuts, const TMVA::Reader &reader);

    int GetBdt(Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) {
        do_fake_leptons = true;
        return SaveEntries(Multiplets(event, pre_cuts, reader), 1);
//         return SaveEntries(Multiplets(event, pre_cuts, reader), Particles(event).size());
    }

    bool Problematic(const Doublet &doublet, PreCuts &pre_cuts, const Tag tag) const;

    bool Problematic(const Doublet &doublet, PreCuts &pre_cuts) const;

    fastjet::PseudoJet FakeLepton(const fastjet::PseudoJet &jet) const;

    Jets Particles(Event &event) const;

    auto Multiplets(Event &event, const TMVA::Reader &reader) {
        PreCuts pre_cuts;
        return Multiplets(event, pre_cuts, reader);
    }

protected:

    virtual  std::string ClassName() const {
        return "TopLeptonicTagger";
    }

private:

    BottomTagger bottom_tagger_;

    Reader bottom_reader_;

    float top_mass_window;

    bool do_fake_leptons = false;

};

}
