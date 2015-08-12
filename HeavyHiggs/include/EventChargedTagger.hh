#pragma once

#include "MultipletEvent.hh"
#include "SignatureChargedTagger.hh"

namespace analysis {

namespace heavyhiggs {

/**
 *
 * @brief event BDT for semi leptonic heavy higgs
 *
 */
class EventChargedTagger : public BranchTagger<EventChargedBranch> {

public:

    EventChargedTagger();

    int Train(Event const& event, PreCuts const& pre_cuts,
              Tag tag) const final;

    std::vector<MultipletEvent<Octet44>> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const;

    int GetBdt(Event const& event, PreCuts const& pre_cuts,
               TMVA::Reader const& reader) const final {
                 return SaveEntries(Multiplets(event, pre_cuts, reader), 1);
    }

    std::string Name() const final { return "EventCharged"; }

private:

    Reader<BottomTagger> bottom_reader_;

    Reader<SignatureChargedTagger> signature_semi_reader_;

};

}

}
