# pragma once

# include "SignatureSingleTagger.hh"
# include "MultipletEvent.hh"

namespace analysis {

namespace toppartner
{

/**
 *
 * @brief Prepares multivariant analysis
 *
 */
class EventSingleTagger : public BranchTagger<EventBranch>
{

public:

    /**
    * @brief Constructor
    *
    */
    EventSingleTagger();

    int Train(Event &event,PreCuts &pre_cuts, const Tag tag);

    std::vector<MultipletEvent<Decuplet73>> Multiplets(Event &event,PreCuts &pre_cuts, const TMVA::Reader &reader);

    int GetBdt(Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) {
      return SaveEntries(Multiplets(event, pre_cuts, reader));
    }

    auto Multiplets(Event &event, const TMVA::Reader &reader) {
      PreCuts pre_cuts;
      return Multiplets(event, pre_cuts, reader);
    }

protected:

    virtual  std::string NameSpaceName() const {
      return "toppartner";
    }

    virtual  std::string ClassName() const {
      return "EventSingleTagger";
    }

private:

    SignatureSingleTagger signature_tagger_;

    Reader signature_reader_;

    BottomTagger bottom_tagger_;

    Reader bottom_reader_;

};

}

}
