#pragma once

#include "SignatureTagger.hh"
#include "MultipletEvent.hh"

namespace analysis {

namespace higgscpv {

/**
 *
 * @brief Prepares multivariant analysis
 *
 */
class EventTagger : public BranchTagger<EventBranch> {

public:

    EventTagger();

    int Train(Event const& event, analysis::PreCuts const&,
              Tag tag) const override;

    std::vector<MultipletEvent<Octet62>> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const;

    int GetBdt(Event const& event, PreCuts const& pre_cuts,
               TMVA::Reader const& reader) const final {
                 return SaveEntries(Multiplets(event, pre_cuts, reader), 1);
    }

    auto Multiplets(Event const& event, TMVA::Reader const& reader)
    {
        PreCuts pre_cuts;
        return Multiplets(event, pre_cuts, reader);
    }

    std::string Name() const final { return "Event"; }

private:

    Reader<SignatureTagger> signature_reader_;

    Reader<BottomTagger> bottom_reader_;

};

}

}
