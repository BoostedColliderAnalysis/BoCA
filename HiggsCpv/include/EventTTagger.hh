#pragma once

#include "SignatureTTagger.hh"
#include "MultipletEvent.hh"

namespace boca {

namespace higgscpv {

/**
 *
 * @brief Prepares multivariant analysis
 *
 */
class EventTTagger : public BranchTagger<EventBranch> {

public:

    EventTTagger();

    int Train(Event const& event, boca::PreCuts const&,
              Tag tag) const override;

    std::vector<MultipletEvent<Octet332>> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const;

    int GetBdt(Event const& event, PreCuts const& pre_cuts,
               TMVA::Reader const& reader) const final {
                 return SaveEntries(Multiplets(event, pre_cuts, reader), 1);
    }

    auto Multiplets(Event const& event, TMVA::Reader const& reader)
    {
        PreCuts pre_cuts;
        return Multiplets(event, pre_cuts, reader);
    }

    std::string Name() const final { return "EventTChannel"; }

private:

    Reader<SignatureTTagger> signature_reader_;

    Reader<BottomTagger> bottom_reader_;

};

}

}
