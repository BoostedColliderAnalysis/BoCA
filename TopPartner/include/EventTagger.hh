#pragma once

#include "SignatureTagger.hh"
#include "MultipletEvent.hh"

namespace analysis {

namespace toppartner {

/**
 *
 * @brief Prepares multivariant analysis
 *
 */
class EventTagger : public BranchTagger<EventBranch> {

public:

    EventTagger();

    int Train(const Event& event, const PreCuts& pre_cuts, Tag tag) const;

    std::vector<MultipletEvent<Quattuordecuplet>> Multiplets(const Event& event, const PreCuts& pre_cuts, const TMVA::Reader& reader) const;

    int GetBdt(const Event& event, const PreCuts& pre_cuts, const TMVA::Reader& reader) const  final
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
        return "Event";
    }

private:

    Reader<SignatureTagger> signature_reader_;

    Reader<BottomTagger> bottom_reader_;

};

}

}
