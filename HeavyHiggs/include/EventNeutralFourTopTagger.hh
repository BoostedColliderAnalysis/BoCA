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
class EventNeutralFourTopTagger : public BranchTagger<EventNeutralFourTopBranch> {

public:

    EventNeutralFourTopTagger();

    int Train(const Event &event, const PreCuts &pre_cuts,
              Tag tag) const final;

    std::vector<MultipletEvent<Octet62>> Multiplets(const Event& event, const PreCuts& pre_cuts, const TMVA::Reader& reader) const;

    int GetBdt(const Event &event, const PreCuts &pre_cuts,
               const TMVA::Reader &reader) const final {
                 return SaveEntries(Multiplets(event, pre_cuts, reader), 1);
    }

    std::string Name() const final { return "EventNeutralFourTop"; }

private:

    Reader<SignatureNeutralTagger> signature_neutral_reader_;

    Reader<BottomTagger> bottom_reader_;

};

}

}
