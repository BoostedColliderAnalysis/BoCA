# pragma once

# include "MultipletEvent.hh"
# include "SignatureChargedTagger.hh"

namespace heavyhiggs
{

/**
 *
 * @brief event BDT for semi leptonic heavy higgs
 *
 */
class EventChargedTagger : public analysis::Tagger
{

public:

    /**
    * @brief Constructor
    *
    */
    EventChargedTagger();

    int Train(analysis::Event &event, const Tag tag);

    std::vector<analysis::MultipletEvent<Octet44>> Multiplets(analysis::Event &event, const TMVA::Reader &reader);

protected:

    virtual inline std::string NameSpaceName() const {
        return "heavyhiggs";
    }

    virtual inline std::string ClassName() const {
        return "EventChargedTagger";
    }

private:

    TClass &Class() const {
        return *EventChargedBranch::Class();
    }

    void DefineVariables();

    analysis::BottomTagger bottom_tagger_;

    SignatureChargedTagger signature_semi_tagger_;

    analysis::Reader bottom_reader_;

    analysis::Reader signature_semi_reader_;

    EventChargedBranch branch_;

};

}
