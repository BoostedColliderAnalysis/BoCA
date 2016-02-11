#pragma once

#include "TauTagger.hh"
#include "multiplets/Doublet.hh"
#include "Reader.hh"
#include "Branch.hh"

namespace boca
{

namespace heavyhiggs
{

/**
 * @brief Semi leptonic top BDT tagger
 *
 */
class HeavyHiggsTauTagger : public TaggerTemplate<Doublet, HeavyHiggsTauBranch>
{

public:

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) const override;

    std::vector<Doublet>  Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const override;

private:

    Reader<standardmodel::TauTagger> tau_reader_;

};

}

}
