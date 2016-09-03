#pragma once

#include "standardmodel/tagger/TopLeptonic.hh"
#include "boca/multiplets/Triplet.hh"

#include "heavyhiggs/branch/ChargedHiggsLeptonic.hh"

namespace heavyhiggs
{

namespace tagger
{

/**
 * @brief Leptonic heavy higgs BDT tagger
 *
 */
class ChargedHiggsLeptonic : public Tagger<Triplet, branch::ChargedHiggsLeptonic>
{

public:

    int Train(boca::Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    std::vector<Triplet> Multiplets(boca::Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override {
        return "ChargedHiggsLeptonic";
    }

private:

    Reader<standardmodel::tagger::Bottom> bottom_reader_;

    Reader<standardmodel::tagger::TopLeptonic> top_leptonic_reader_;

};

}

}
