# pragma once

# include "SignatureTagger.hh"
# include "MultipletEvent.hh"

namespace toppartner
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

    int Train(analysis::Event &event,analysis::PreCuts &pre_cuts, const analysis::Object::Tag tag);

    std::vector<analysis::MultipletEvent<Quattuordecuplet>> Multiplets(analysis::Event &event,analysis::PreCuts &pre_cuts, const TMVA::Reader &reader);

    int GetBdt(analysis::Event &event, analysis::PreCuts &pre_cuts, const TMVA::Reader &reader) {
      return SaveEntries(Multiplets(event, pre_cuts, reader));
    }

    auto Multiplets(analysis::Event &event, const TMVA::Reader &reader) {
      analysis::PreCuts pre_cuts;
      return Multiplets(event, pre_cuts, reader);
    }

protected:

    virtual inline std::string NameSpaceName() const {
      return "toppartner";
    }

    virtual inline std::string ClassName() const {
      return "EventTagger";
    }

private:

    void DefineVariables();

    SignatureTagger signature_tagger_;

    analysis::Reader signature_reader_;

    analysis::BottomTagger bottom_tagger_;

    analysis::Reader bottom_reader_;

};

}
