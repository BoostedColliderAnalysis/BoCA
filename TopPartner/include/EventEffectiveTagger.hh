#pragma once

#include "SignatureEffectiveTagger.hh"
#include "MultipletEvent.hh"

namespace boca {

namespace naturalness {

/**
 *
 * @brief Prepares multivariant analysis
 *
 */
class EventEffectiveTagger : public BranchTagger<EventBranch> {

public:

    EventEffectiveTagger();

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) const override;

    std::vector<MultipletEvent<Quattuordecuplet554>> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const;

    int SaveBdt(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const final {
        return SaveEntries(Multiplets(event, pre_cuts, reader), 1);
    }

    auto Multiplets(Event const& event, TMVA::Reader const& reader)
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
