#pragma once

#include "boca/Tagger.hh"
#include "boca/standardmodel/tagger/Bottom.hh"
#include "boca/multivariant/Reader.hh"

#include "include/CutVariables.hh"
#include "include/branch/CutNeutral.hh"

namespace heavyhiggs
{

namespace tagger
{

/**
 *
 * @brief event BDT for semi leptonic heavy higgs
 *
 */
class CutNeutral : public Tagger<CutVariables, branch::CutNeutral>
{

public:

    int Train(boca::Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    std::vector<CutVariables> Multiplets(boca::Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

    TMVA::Types::EMVA Mva() const override;

private:

    boost::optional<CutVariables> CutMethod(const boca::Event& event);

    Reader<standardmodel::tagger::Bottom> bottom_reader_;

};

}

}
