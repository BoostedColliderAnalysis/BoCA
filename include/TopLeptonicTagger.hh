#pragma once

#include "BottomTagger.hh"
#include "WLeptonicTagger.hh"
#include "Triplet.hh"
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
// 
    int Train(Event const& event, PreCuts const& pre_cuts,
              Tag tag) const override;

    std::vector<Triplet> Multiplets(Event const& event, analysis::PreCuts const& pre_cuts, TMVA::Reader const& reader) const;

    int GetBdt(Event const& event, PreCuts const& pre_cuts,
               TMVA::Reader const& reader) const final {
//         do_fake_leptons = true;
        return SaveEntries(Multiplets(event, pre_cuts, reader), 1);
//         return SaveEntries(Multiplets(event, pre_cuts, reader), Particles(event).size());
    }

    bool Problematic(Triplet const& triplet, PreCuts const& pre_cuts, Tag tag) const;

    bool Problematic(Triplet const& triplet, PreCuts const& pre_cuts) const;

    fastjet::PseudoJet FakeLepton(fastjet::PseudoJet const& jet) const;

    Jets Particles(analysis::Event const& event, PreCuts const& pre_cuts) const;

    auto Multiplets(Event const& event, TMVA::Reader const& reader) const {
        PreCuts pre_cuts;
        return Multiplets(event, pre_cuts, reader);
    }

    std::string Name() const final {
        return "TopLeptonic";
    }

    std::string NiceName() const final {
      return "t_{l}";
    }

    int TopLeptonicId(Event const& event) const;

private:

    bool use_w_ = false;

    Reader<BottomTagger> bottom_reader_;

    Reader<WLeptonicTagger> w_leptonic_reader_;

    float top_mass_window;

    Stage InitializeLeptonicReader();

};

}
