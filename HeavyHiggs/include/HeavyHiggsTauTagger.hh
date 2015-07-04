#pragma once

#include "TauTagger.hh"
#include "Doublet.hh"
#include "Reader.hh"
#include "Branch.hh"

namespace analysis
{

namespace heavyhiggs
{

/**
 * @brief Semi leptonic top BDT tagger
 *
 */
class HeavyHiggsTauTagger : public BranchTagger<HeavyHiggsTauBranch>
{

public:

    HeavyHiggsTauTagger();

    int Train(const Event &event, const Tag tag);

    std::vector<Doublet>  Multiplets(const Event &event, const TMVA::Reader &reader);

private:
    TauTagger tau_tagger_;

    Reader tau_reader_;

};

}

}
