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

    /**
    * @brief Constructor
    *
    */
    EventNeutralTagger();

    int Train(Event &event, const Tag tag);

    std::vector< MultipletEvent< Octet62 > > Multiplets(Event &event, const TMVA::Reader &reader);

private:

    SignatureNeutralTagger signature_neutral_tagger_;

    Reader signature_neutral_reader_;

    BottomTagger bottom_tagger_;

    Reader bottom_reader_;

};

}

}
