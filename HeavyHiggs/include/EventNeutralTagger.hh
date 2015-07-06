#pragma once

#include "MultipletEvent.hh"
#include "SignatureNeutralTagger.hh"

namespace analysis
{

namespace heavyhiggs
{

/**
 *
 * @brief event BDT for semi leptonic heavy higgs
 *
 */
class EventNeutralTagger : public BranchTagger<EventNeutralBranch>
{

public:

    EventNeutralTagger();

    int Train(const Event &event, PreCuts &pre_cuts, const Tag tag) const;

    std::vector< MultipletEvent< Octet62 > > Multiplets(const Event &event, const TMVA::Reader &reader) const;

    int GetBdt(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) const {
//       return SaveEntries(Multiplets(event, pre_cuts, reader));
    }

    std::string name() const {
      return "EventNeutral";
    }

private:

    ReaderTagger<SignatureNeutralTagger> signature_neutral_reader_;

    ReaderTagger<BottomTagger> bottom_reader_;

};

}

}
