#pragma once

#include "Reader.hh"
#include "Doublet.hh"
#include "BranchTagger.hh"

namespace analysis {

/**
 * @brief Semi leptonic top BDT tagger
 *
 */
class WSemiTagger : public BranchTagger<WSemiBranch>
{

public:

    WSemiTagger();

    int Train(const Event &event, PreCuts &, const Tag tag);

    std::vector<Doublet> Multiplets(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader);

    int GetBdt(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) {
      return SaveEntries(Multiplets(event,pre_cuts, reader));
    }

    int WSemiId(const Event &event) {
        return WSemiId(WSemiDaughters(event));
    }

private:

    Jets WSemiDaughters(const Event &event);

    int WSemiId(const Jets &jets);

    Tag GetTag(const Doublet &doublet) const;

    std::vector< Doublet > ReconstructNeutrino(const Doublet &doublet)const;

    std::vector<Doublet> GetNeutrino(const Doublet &doublet, const Jets &Neutrinos, const Tag Tag)const;

    float w_mass_window_;

};

}

