#pragma once

#include "SignatureTTagger.hh"
#include "MultipletEvent.hh"

namespace analysis {

namespace higgscpv {

/**
 *
 * @brief Prepares multivariant analysis
 *
 */
class EventTTagger : public BranchTagger<EventBranch> {

public:

    EventTTagger();

    int Train(const Event &event, const analysis::PreCuts &,
              Tag tag) const override;

    std::vector<MultipletEvent<Octet332>> Multiplets(const Event& event, const PreCuts& pre_cuts, const TMVA::Reader& reader) const;

    int GetBdt(const Event &event, const PreCuts &pre_cuts,
               const TMVA::Reader &reader) const final {
        return SaveEntries(Multiplets(event, pre_cuts, reader));
    }

    auto Multiplets(const Event& event, const TMVA::Reader& reader)
    {
        PreCuts pre_cuts;
        return Multiplets(event, pre_cuts, reader);
    }

    std::string Name() const final { return "EventTChannel"; }

private:

    Reader<SignatureTTagger> signature_reader_;

    Reader<BottomTagger> bottom_reader_;

};

}

}
