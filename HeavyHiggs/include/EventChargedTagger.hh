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

    /**
    * @brief Constructor
    *
    */
    EventChargedTagger();

    int Train(const Event &event, PreCuts &pre_cuts, const Tag tag) const;

    std::vector<MultipletEvent<Octet44>> Multiplets(const Event &event, const TMVA::Reader &reader) const;

    int GetBdt(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) const {
//       return SaveEntries(Multiplets(event, pre_cuts, reader));
    }

private:

    ReaderTagger<BottomTagger> bottom_reader_;

    ReaderTagger<SignatureChargedTagger> signature_semi_reader_;

};

}

}
