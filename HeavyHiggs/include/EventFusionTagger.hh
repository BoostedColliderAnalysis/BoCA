#pragma once

#include "HeavyHiggsSemiTagger.hh"
#include "MultipletEvent.hh"

namespace analysis {

namespace heavyhiggs {

/**
 *
 * @brief event BDT for semi leptonic heavy higgs
 *
 */
class EventFusionTagger : public BranchTagger<EventFusionBranch> {

public:

    EventFusionTagger();

    int Train(const Event &event, const PreCuts &pre_cuts,
              Tag tag) const override;

    std::vector<MultipletEvent<Sextet>> Multiplets(const Event& event, const PreCuts& pre_cuts, const TMVA::Reader& reader) const;

    int GetBdt(const Event &event, const PreCuts &pre_cuts,
               const TMVA::Reader &reader) const final override {
      return SaveEntries(Multiplets(event, pre_cuts, reader));
    }

    std::string Name() const final override { return "EventFusion"; }

private:

    Reader<BottomTagger> bottom_reader_;

    Reader<HeavyHiggsSemiTagger> heavy_higgs_semi_reader_;

};

}

}
