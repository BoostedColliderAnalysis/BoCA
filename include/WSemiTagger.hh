#pragma once

#include "Doublet.hh"
#include "BranchTagger.hh"
#include "Branches.hh"

namespace analysis {

/**
 * @brief Semi leptonic top BDT tagger
 *
 */
class WSemiTagger : public BranchTagger<WSemiBranch>
{

public:

    WSemiTagger();

    int Train(const Event &event, PreCuts &, const Tag tag) const;

    std::vector<Doublet> Multiplets(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) const;

    int GetBdt(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) const  final {
      return SaveEntries(Multiplets(event,pre_cuts, reader));
    }

    int WSemiId(const Event &event) const {
        return WSemiId(WSemiDaughters(event));
    }

    std::string Name() const final {
      return "WSemi";
    }

private:

    Jets WSemiDaughters(const Event &event) const;

    int WSemiId(const Jets &jets) const;

    Tag GetTag(const Doublet &doublet) const;

    std::vector< Doublet > ReconstructNeutrino(const Doublet &doublet) const;

    std::vector<Doublet> GetNeutrino(const Doublet &doublet, const Jets &Neutrinos, const Tag Tag) const;

    float w_mass_window_ = 20;

};

}

