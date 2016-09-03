#pragma once

#include "standardmodel/tagger/Bottom.hh"
#include "boca/multivariant/Reader.hh"
#include "boca/tagger/Tagger.hh"
#include "heavyhiggs/CutVariables.hh"

#include "heavyhiggs/branch/Cut.hh"

namespace heavyhiggs
{

namespace tagger
{

/**
 *
 * @brief event BDT for semi leptonic heavy higgs
 *
 */
class Cut : public Tagger<CutVariables, branch::Cut>
{

public:

    int Train(const boca::Event& event, const boca::PreCuts&, boca::Tag) override;

    std::vector<CutVariables> Multiplets(boca::Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

    TMVA::Types::EMVA Mva() const override;

private:

    boost::optional<CutVariables> CutMethod(const boca::Event& event);

    Reader<standardmodel::tagger::Bottom> bottom_reader_;

};

}

}
