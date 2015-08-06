#pragma once

#include "SignatureEffectiveTagger.hh"
#include "MultipletEvent.hh"

namespace analysis {

namespace toppartner {

/**
 *
 * @brief Prepares multivariant analysis
 *
 */
class EventEffectiveTagger : public BranchTagger<EventBranch> {

public:

    EventEffectiveTagger();

    int Train(const Event &event, const PreCuts &pre_cuts,
              Tag tag) const override;

    std::vector<MultipletEvent<Quattuordecuplet>> Multiplets(const Event& event, const PreCuts& pre_cuts, const TMVA::Reader& reader) const;

    int GetBdt(const Event &event, const PreCuts &pre_cuts,
               const TMVA::Reader &reader) const final {
                 return SaveEntries(Multiplets(event, pre_cuts, reader), 1);
    }

    auto Multiplets(const Event& event, const TMVA::Reader& reader)
    {
        PreCuts pre_cuts;
        return Multiplets(event, pre_cuts, reader);
    }

    std::string Name() const final { return "Event"; }

private:

    Reader<SignatureEffectiveTagger> signature_reader_;

    Reader<BottomTagger> bottom_reader_;

};

}

}
