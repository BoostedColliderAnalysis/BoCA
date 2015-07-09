#pragma once

#include "MultipletEvent.hh"
#include "SignatureChargedTagger.hh"

namespace analysis
{

namespace heavyhiggs
{

/**
 *
 * @brief event BDT for semi leptonic heavy higgs
 *
 */
class EventChargedTagger : public BranchTagger<EventChargedBranch>
{

public:

    EventChargedTagger();

    int Train(const Event &event, PreCuts &pre_cuts, const Tag tag) const final;

    std::vector<MultipletEvent<Octet44>> Multiplets(const Event &event, const TMVA::Reader &reader) const;

    int GetBdt(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) const  final {
//       return SaveEntries(Multiplets(event, pre_cuts, reader));
    }

    std::string name() const final {
      return "EventCharged";
    }

private:

    Reader<BottomTagger> bottom_reader_;

    Reader<SignatureChargedTagger> signature_semi_reader_;

};

}

}
