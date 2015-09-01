#pragma once

#include "TauTagger.hh"
#include "Doublet.hh"
#include "Reader.hh"
#include "Branch.hh"

namespace boca {

namespace heavyhiggs {

/**
 * @brief Semi leptonic top BDT tagger
 *
 */
class HeavyHiggsTauTagger : public BranchTagger<HeavyHiggsTauBranch> {

public:

    HeavyHiggsTauTagger();

    int Train(Event const& event, PreCuts const& pre_cuts,
              Tag tag) const final;

    std::vector<Doublet>  Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const;

private:

    Reader<TauTagger> tau_reader_;

};

}

}
