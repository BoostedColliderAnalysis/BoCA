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

    int Train(const Event& event, PreCuts& pre_cuts, const Tag tag) const final;

    std::vector<MultipletEvent<Octet62>> Multiplets(const Event& event, const TMVA::Reader& reader) const;

    int GetBdt(const Event& event, PreCuts& pre_cuts, const TMVA::Reader& reader) const  final
    {
//       return SaveEntries(Multiplets(event, pre_cuts, reader));
    }

    std::string Name() const final
    {
        return "EventNeutral";
    }

private:

    Reader<SignatureNeutralTagger> signature_neutral_reader_;

    Reader<BottomTagger> bottom_reader_;

};

}

}
