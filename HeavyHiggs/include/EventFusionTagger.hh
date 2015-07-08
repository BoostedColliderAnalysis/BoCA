#pragma once

#include "HeavyHiggsSemiTagger.hh"
#include "MultipletEvent.hh"

namespace analysis
{

namespace heavyhiggs
{

/**
 *
 * @brief event BDT for semi leptonic heavy higgs
 *
 */
class EventFusionTagger : public BranchTagger<EventFusionBranch>
{

public:

    EventFusionTagger();

    int Train(const Event &event,PreCuts &pre_cuts, const Tag tag) const;

    std::vector< MultipletEvent<Sextet> > Multiplets(const Event &event, TMVA::Reader &reader);

    int GetBdt(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) const {
//       return SaveEntries(Multiplets(event, pre_cuts, reader));
    }

    std::string name() const {
      return "EventFusion";
    }

private:

    Reader<BottomTagger> bottom_reader_;

    Reader<HeavyHiggsSemiTagger> heavy_higgs_semi_reader_;

};

}

}
