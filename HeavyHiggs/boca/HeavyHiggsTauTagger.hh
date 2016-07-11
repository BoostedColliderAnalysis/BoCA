#pragma once

#include "boca/standardmodel/tagger/Tau.hh"
#include "boca/multiplets/Doublet.hh"
#include "boca/multivariant/Reader.hh"
#include "boca/BranchesHeavyHiggs.hh"

namespace boca
{

namespace heavyhiggs
{

/**
 * @brief Semi leptonic top BDT tagger
 *
 */
class HeavyHiggsTauTagger : public Tagger<Doublet, HeavyHiggsTau>
{

public:

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    std::vector<Doublet>  Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

private:

    Reader<standardmodel::tagger::Tau> tau_reader_;

};

}

}
