#pragma once

#include "SignatureEffectiveTagger.hh"
#include "MultipletEvent.hh"

namespace boca {

namespace naturalness {

/**
 *
 * @brief Prepares multivariant analysis
 *
 */
class EventEffectiveTagger : public TaggerTemplate<MultipletEvent<Quattuordecuplet554>,EventBranch> {

public:

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) const final;

    std::vector<MultipletEvent<Quattuordecuplet554>> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const final;

    std::string Name() const final;

private:

    Reader<SignatureEffectiveTagger> signature_reader_;

    Reader<BottomTagger> bottom_reader_;

};

}

}
