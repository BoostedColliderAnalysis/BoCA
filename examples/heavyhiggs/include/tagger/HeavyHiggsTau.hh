#pragma once

#include "boca/standardmodel/tagger/Tau.hh"
#include "boca/multiplets/Doublet.hh"
#include "boca/multivariant/Reader.hh"

#include "include/branch/HeavyHiggsTau.hh"

namespace heavyhiggs
{

namespace tagger
{

/**
 * @brief Semi leptonic top BDT tagger
 *
 */
class HeavyHiggsTau : public Tagger<Doublet, branch::HeavyHiggsTau>
{

public:

    int Train(boca::Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    std::vector<Doublet>  Multiplets(boca::Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

private:

    Reader<standardmodel::tagger::Tau> tau_reader_;

};

}

}
