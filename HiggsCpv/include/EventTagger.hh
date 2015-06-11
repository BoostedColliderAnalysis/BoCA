# pragma once

# include "SignatureTagger.hh"
# include "MultipletEvent.hh"

namespace higgscpv
{

/**
 *
 * @brief Prepares multivariant analysis
 *
 */
class EventTagger : public analysis::BranchTagger<EventBranch>
{

public:

    /**
    * @brief Constructor
    *
    */
    EventTagger();

    int Train(analysis::Event &event, const analysis::Object::Tag tag);

    std::vector<analysis::MultipletEvent<analysis::Octet62>> Multiplets(analysis::Event &event, const TMVA::Reader &reader);

protected:

    virtual inline std::string NameSpaceName() const {
        return "EventTagger";
    }

    virtual inline std::string ClassName() const {
        return "higgscpv";
    }

private:

    void DefineVariables();

    SignatureTagger signature_tagger_;

    analysis::Reader signature_reader_;

};

}
