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
    int Train(const Event& event, const PreCuts& pre_cuts,
              Tag tag) const override;

    std::vector<Triplet> Multiplets(const Event& event, const analysis::PreCuts& pre_cuts, const TMVA::Reader& reader) const;

    int GetBdt(const Event& event, const PreCuts& pre_cuts,
               const TMVA::Reader& reader) const final {
//         do_fake_leptons = true;
        return SaveEntries(Multiplets(event, pre_cuts, reader), 1);
//         return SaveEntries(Multiplets(event, pre_cuts, reader), Particles(event).size());
    }

    bool Problematic(const Triplet& triplet, const PreCuts& pre_cuts, Tag tag) const;

    bool Problematic(const Triplet& triplet, const PreCuts& pre_cuts) const;

    fastjet::PseudoJet FakeLepton(const fastjet::PseudoJet& jet) const;

    Jets Particles(const analysis::Event& event) const;

    auto Multiplets(const Event& event, const TMVA::Reader& reader) const {
        PreCuts pre_cuts;
        return Multiplets(event, pre_cuts, reader);
    }

    std::string Name() const final {
        return "TopLeptonic";
    }

    std::string NiceName() const final {
      return "t_{l}";
    }

    int TopLeptonicId(const Event& event) const;

private:

    bool use_w_ = false;
//     bool use_w_ = true;

    Reader<BottomTagger> bottom_reader_;

    Reader<WLeptonicTagger> w_leptonic_reader_;

    float top_mass_window;

    Stage InitializeLeptonicReader();

};

}
