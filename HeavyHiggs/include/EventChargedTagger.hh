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

    int Train(const Event &event, const PreCuts &pre_cuts,
              Tag tag) const final;

    std::vector<MultipletEvent<Octet44>> Multiplets(const Event& event, const PreCuts& pre_cuts, const TMVA::Reader& reader) const;

    int GetBdt(const Event &event, const PreCuts &pre_cuts,
               const TMVA::Reader &reader) const final {
                 return SaveEntries(Multiplets(event, pre_cuts, reader), 1);
    }

    std::string Name() const final { return "EventCharged"; }

private:

    Reader<BottomTagger> bottom_reader_;

    Reader<SignatureChargedTagger> signature_semi_reader_;

};

}

}
