# pragma once

# include "SignatureTagger.hh"
# include "BranchesHiggsCpv.hh"
# include "MultipletEvent.hh"

namespace higgscpv {

/**
 *
 * @brief Prepares multivariant analysis
 *
 */
class EventTagger : public analysis::Tagger
{

public:

    /**
    * @brief Constructor
    *
    */
    EventTagger();

    int Train(analysis::Event& event, const analysis::Object::Tag tag);

    std::vector<analysis::MultipletEvent<analysis::Octet62>> Multiplets(analysis::Event& event, const TMVA::Reader &reader);

protected:

    virtual inline std::string NameSpaceName() const {
        return "EventTagger";
    }

    virtual inline std::string ClassName() const {
        return "higgscpv";
    }

private:

    void DefineVariables();

    EventBranch branch_;

    SignatureTagger signature_tagger_;

    analysis::Reader signature_reader_;

};

}
