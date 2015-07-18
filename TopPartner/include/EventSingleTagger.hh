#pragma once

#include "TopPartnerPairTagger.hh"
#include "MultipletEvent.hh"

namespace analysis {

namespace toppartner {

/**
 *
 * @brief Prepares multivariant analysis
 *
 */
class EventSingleTagger : public BranchTagger<EventBranch> {

public:

    EventSingleTagger();

    int Train(const Event& event, PreCuts& pre_cuts, const Tag tag) const final;

    std::vector<MultipletEvent<Decuplet55>> Multiplets(const Event& event, PreCuts& pre_cuts, const TMVA::Reader& reader) const;

    int GetBdt(const Event& event, PreCuts& pre_cuts, const TMVA::Reader& reader) const  final
    {
        return SaveEntries(Multiplets(event, pre_cuts, reader));
    }

    auto Multiplets(const Event& event, const TMVA::Reader& reader)
    {
        PreCuts pre_cuts;
        return Multiplets(event, pre_cuts, reader);
    }

    std::string Name() const final
    {
        return "EventSingle";
    }

private:

    Reader<TopPartnerPairTagger> signature_reader_;

    Reader<BottomTagger> bottom_reader_;

};

}

}
