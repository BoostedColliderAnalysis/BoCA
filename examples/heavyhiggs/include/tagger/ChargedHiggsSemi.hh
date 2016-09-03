#pragma once

#include "standardmodel/tagger/TopLeptonic.hh"
#include "boca/multiplets/Quartet.hh"

#include "include/branch/ChargedHiggsSemi.hh"

namespace heavyhiggs
{

namespace tagger
{

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class ChargedHiggsSemi : public Tagger<Quartet31, branch::ChargedHiggsSemi>
{

public:

    int Train(boca::Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    std::vector<Quartet31> Multiplets(boca::Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

private:

    Reader<standardmodel::tagger::Bottom> bottom_reader_;

    Reader<standardmodel::tagger::TopLeptonic> top_leptonic_reader_;
};

}

}
