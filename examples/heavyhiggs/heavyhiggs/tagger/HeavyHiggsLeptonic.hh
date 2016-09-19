#pragma once

#include "standardmodel/tagger/TopLeptonic.hh"
#include "boca/multiplets/Sextet.hh"

#include "heavyhiggs/branch/HeavyHiggsLeptonic.hh"

namespace heavyhiggs
{

namespace tagger
{

/**
 * @brief Leptonic heavy higgs BDT tagger
 *
 */
class HeavyHiggsLeptonic : public Tagger<Sextet33, branch::HeavyHiggsLeptonic>
{

public:

    int Train(boca::Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    std::vector<Sextet33> Multiplets(boca::Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

private:

    Reader<standardmodel::tagger::TopLeptonic> top_leptonic_reader_;

};

}

}
