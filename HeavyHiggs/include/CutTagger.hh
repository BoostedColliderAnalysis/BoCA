#pragma once

#include "TaggerTemplate.hh"
#include "BranchesHeavyHiggs.hh"
#include "BottomTagger.hh"
#include "Reader.hh"
#include "CutVariables.hh"

namespace boca
{

namespace heavyhiggs
{

/**
 *
 * @brief event BDT for semi leptonic heavy higgs
 *
 */
class CutTagger : public TaggerTemplate<CutVariables, HeavyHiggsCutBranch>
{

public:

    int Train(const boca::Event& event, const boca::PreCuts&, boca::Tag) override;

    std::vector<CutVariables> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

    TMVA::Types::EMVA Mva() const override;

private:

    boost::optional<CutVariables> CutMethod(const boca::Event& event);

    Reader<standardmodel::BottomTagger> bottom_reader_;

};

}

}
