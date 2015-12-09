#pragma once

#include "TaggerTemplate.hh"
#include "Branch.hh"
#include "CutVariables.hh"
#include  "TCanvas.h"

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

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) const final;

    std::vector<CutVariables> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const final;

    std::string Name() const final;

    TMVA::Types::EMVA Mva() const final {
        return TMVA::Types::EMVA::kCuts;
    }

private:

  boost::optional<CutVariables> CutMethod(Event const& event) const;

};

}

}
