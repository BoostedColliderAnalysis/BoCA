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

    int Train(Event &event, const Tag tag);

    std::vector<MultipletEvent<Octet44>> Multiplets(Event &event, const TMVA::Reader &reader);

protected:

    virtual  std::string NameSpaceName() const {
        return "heavyhiggs";
    }

    virtual  std::string ClassName() const {
        return "EventChargedTagger";
    }

private:

    BottomTagger bottom_tagger_;

    SignatureChargedTagger signature_semi_tagger_;

    Reader bottom_reader_;

    Reader signature_semi_reader_;

};

}

}
