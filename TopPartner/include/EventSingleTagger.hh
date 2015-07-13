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

    EventSingleTagger();

    int Train(const Event &event, PreCuts &pre_cuts, const Tag tag) const final;

    std::vector<MultipletEvent<Nonet>> Multiplets(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) const;

    int GetBdt(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) const  final {
        return SaveEntries(Multiplets(event, pre_cuts, reader));
    }

    auto Multiplets(const Event &event, const TMVA::Reader &reader) {
        PreCuts pre_cuts;
        return Multiplets(event, pre_cuts, reader);
    }

    std::string name() const final {
      return "EventSingle";
    }

private:

    Reader<TopPartnerLeptonicPairTagger> signature_reader_;

    Reader<BottomTagger> bottom_reader_;

};

}

}
