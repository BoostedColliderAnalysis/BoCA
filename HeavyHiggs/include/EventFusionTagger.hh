#pragma once

#include "HeavyHiggsSemiTagger.hh"
#include "MultipletEvent.hh"

namespace boca
{

namespace heavyhiggs
{

/**
 *
 * @brief event BDT for semi leptonic heavy higgs
 *
 */
class EventFusionTagger : public TaggerTemplate<MultipletEvent<Sextet>, EventFusionBranch>
{

public:

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) const final;

    std::vector<MultipletEvent<Sextet>> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const final;

    std::string Name() const final;

private:

    Reader<standardmodel::BottomTagger> bottom_reader_;

    Reader<HeavyHiggsSemiTagger> heavy_higgs_semi_reader_;

};

}

}
