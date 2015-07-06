#pragma once

#include "SignatureTagger.hh"
#include "MultipletEvent.hh"

namespace analysis {

namespace toppartner
{

/**
 *
 * @brief Prepares multivariant analysis
 *
 */
class EventTagger : public BranchTagger<EventBranch>
{

public:

    /**
    * @brief Constructor
    *
    */
    EventTagger();

    int Train(const Event &event,PreCuts &pre_cuts, const Tag tag) const;

    std::vector<MultipletEvent<Quattuordecuplet>> Multiplets(const Event &event,PreCuts &pre_cuts, const TMVA::Reader &reader) const;

    int GetBdt(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) const {
      return SaveEntries(Multiplets(event, pre_cuts, reader));
    }

    auto Multiplets(const Event &event, const TMVA::Reader &reader) {
      PreCuts pre_cuts;
      return Multiplets(event, pre_cuts, reader);
    }

private:

    ReaderTagger<SignatureTagger> signature_reader_;

    ReaderTagger<BottomTagger> bottom_reader_;

};

}

}
