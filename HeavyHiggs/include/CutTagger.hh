#pragma once

#include "TaggerTemplate.hh"
#include "Branch.hh"
#include "CutPlet.hh"

namespace boca
{

namespace heavyhiggs
{

/**
 *
 * @brief event BDT for semi leptonic heavy higgs
 *
 */
class CutTagger : public TaggerTemplate<CutPlet, HeavyHiggsCutBranch>
{

public:

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) const final;

    std::vector<CutPlet> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const final;

    std::string Name() const final;

    TMVA::Types::EMVA Mva() const final {
        return TMVA::Types::EMVA::kCuts;
    }

private:

    boost::optional<CutPlet> CutMethod(Event const& event) const;

};

}

}
