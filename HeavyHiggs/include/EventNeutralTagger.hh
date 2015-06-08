# pragma once

# include "MultipletEvent.hh"
# include "SignatureNeutralTagger.hh"

namespace heavyhiggs {

/**
 *
 * @brief event BDT for semi leptonic heavy higgs
 *
 */
class EventNeutralTagger : public analysis::Tagger
{

public:

    /**
    * @brief Constructor
    *
    */
    EventNeutralTagger();

    int Train(analysis::Event &event, const Tag tag);

    std::vector< analysis::MultipletEvent< analysis::Octet62 > > Multiplets(analysis::Event &event, const TMVA::Reader &reader);

protected:

    virtual inline std::string NameSpaceName() const {
        return "heavyhiggs";
    }

    virtual inline std::string ClassName() const {
        return "EventNeutralTagger";
    }

private:

    SignatureNeutralTagger signature_neutral_tagger_;

    analysis::Reader signature_neutral_reader_;

    analysis::BottomTagger bottom_tagger_;

    analysis::Reader bottom_reader_;

    TClass &Class() const {
      return *EventNeutralBranch::Class();
    }

  void DefineVariables();

    EventNeutralBranch branch_;

};

}
