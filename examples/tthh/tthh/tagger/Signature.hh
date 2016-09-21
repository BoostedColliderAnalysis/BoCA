#pragma once

#include "boca/multiplets/Duodecuplet.hh"

#include "standardmodel/tagger/TopHadronic.hh"
#include "standardmodel/tagger/TopLeptonic.hh"

#include "tthh/tagger/HiggsToHiggs.hh"
#include "tthh/branch/Signature.hh"

namespace tthh
{

namespace tagger
{

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class Signature : public Tagger<Duodecuplet633, branch::Signature>
{

public:

    int Train(boca::Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    std::vector<Duodecuplet633> Multiplets(boca::Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

    latex::String LatexName() const override;

private:

    std::vector<Duodecuplet633> Duodecuplets(boca::Event const& event, std::function<Duodecuplet633(Duodecuplet633&)> const& function);

    Reader<standardmodel::tagger::TopHadronic> top_hadronic_reader_;

    Reader<standardmodel::tagger::TopLeptonic> top_leptonic_reader_;

    Reader<HiggsToHiggs> higgs_reader_;

};

}

}
