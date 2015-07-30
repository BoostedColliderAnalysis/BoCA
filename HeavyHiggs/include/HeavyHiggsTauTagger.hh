#pragma once

#include "TauTagger.hh"
#include "Doublet.hh"
#include "Reader.hh"
#include "Branch.hh"

namespace analysis {

namespace heavyhiggs {

/**
 * @brief Semi leptonic top BDT tagger
 *
 */
class HeavyHiggsTauTagger : public BranchTagger<HeavyHiggsTauBranch> {

public:

    HeavyHiggsTauTagger();

    int Train(const Event &event, const PreCuts &pre_cuts,
              Tag tag) const final;

    std::vector<Doublet>  Multiplets(const Event& event, const PreCuts& pre_cuts, const TMVA::Reader& reader) const;

private:

    Reader<TauTagger> tau_reader_;

};

}

}
