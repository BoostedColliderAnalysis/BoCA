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

    int Train(const Event &event, const Tag tag);

    std::vector<MultipletEvent<Octet44>> Multiplets(const Event &event, const TMVA::Reader &reader);

private:

    BottomTagger bottom_tagger_;

    SignatureChargedTagger signature_semi_tagger_;

    Reader bottom_reader_;

    Reader signature_semi_reader_;

};

}

}
