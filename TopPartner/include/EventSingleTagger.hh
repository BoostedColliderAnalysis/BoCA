#pragma once

#include "TopPartnerLeptonicPairTagger.hh"
#include "MultipletEvent.hh"

namespace analysis
{

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

    int Train(const Event &event, PreCuts &pre_cuts, const Tag tag);

    std::vector<MultipletEvent<Nonet>> Multiplets(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader);

    int GetBdt(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) {
        return SaveEntries(Multiplets(event, pre_cuts, reader));
    }

    auto Multiplets(const Event &event, const TMVA::Reader &reader) {
        PreCuts pre_cuts;
        return Multiplets(event, pre_cuts, reader);
    }

private:

    TopPartnerLeptonicPairTagger signature_tagger_;

    Reader signature_reader_;

    BottomTagger bottom_tagger_;

    Reader bottom_reader_;

};

}

}
