#pragma once

#include "MultipletEvent.hh"
#include "SignatureNeutralTagger.hh"

namespace analysis {

namespace heavyhiggs {

/**
 *
 * @brief event BDT for semi leptonic heavy higgs
 *
 */
class EventNeutralTagger : public BranchTagger<EventNeutralBranch> {

public:

    EventNeutralTagger();

    int Train(Event const& event, PreCuts const& pre_cuts,
              Tag tag) const final;

    std::vector<MultipletEvent<Octet62>> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const;

    int GetBdt(Event const& event, PreCuts const& pre_cuts,
               TMVA::Reader const& reader) const final {
                 return SaveEntries(Multiplets(event, pre_cuts, reader), 1);
    }

    std::string Name() const final { return "EventNeutral"; }

private:

    Reader<SignatureNeutralTagger> signature_neutral_reader_;

    Reader<BottomTagger> bottom_reader_;

};

}

}
