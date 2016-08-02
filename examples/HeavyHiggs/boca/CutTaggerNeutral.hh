#pragma once

#include "boca/Tagger.hh"
#include "boca/BranchesHeavyHiggs.hh"
#include "boca/standardmodel/tagger/Bottom.hh"
#include "boca/multivariant/Reader.hh"
#include "boca/CutVariables.hh"

namespace boca
{

namespace heavyhiggs
{

/**
 *
 * @brief event BDT for semi leptonic heavy higgs
 *
 */
class CutTaggerNeutral : public Tagger<CutVariables, HeavyHiggsCutNeutralBranch>
{

public:

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    std::vector<CutVariables> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

    TMVA::Types::EMVA Mva() const override;

private:

    boost::optional<CutVariables> CutMethod(const boca::Event& event);

    Reader<standardmodel::tagger::Bottom> bottom_reader_;

};

}

}
