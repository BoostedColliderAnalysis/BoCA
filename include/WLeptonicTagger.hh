#pragma once

#include "Doublet.hh"
#include "BranchTagger.hh"
#include "Branches.hh"

namespace analysis {

/**
 * @brief Semi leptonic top BDT tagger
 *
 */
class WLeptonicTagger : public BranchTagger<WSemiBranch> {

public:

    WLeptonicTagger();

    int Train(const Event &event, const PreCuts &, Tag tag) const override;

    std::vector<Doublet> Multiplets(const Event& event, const PreCuts& pre_cuts, const TMVA::Reader& reader) const;

    int GetBdt(const Event &event, const PreCuts &pre_cuts,
               const TMVA::Reader &reader) const final {
                 return SaveEntries(Multiplets(event, pre_cuts, reader), 1);
    }

    int WLeptonicId(const Event& event) const
    {
        return WLeptonicId(WLeptonicDaughters(event));
    }

    std::string Name() const final { return "WLeptonic"; }

private:

    Jets WLeptonicDaughters(const Event& event) const;

    int WLeptonicId(const Jets& jets) const;

    Tag GetTag(const Doublet& doublet) const;

    std::vector<Doublet> ReconstructNeutrino(const Doublet& doublet) const;

    std::vector<Doublet> GetNeutrino(const Doublet& doublet, const Jets& Neutrinos, const Tag Tag) const;

    float w_mass_window_ = 20;

};

}

