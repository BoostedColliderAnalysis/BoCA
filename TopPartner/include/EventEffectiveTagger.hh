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

    std::string LatexName() const final;


private:

    std::vector<MultipletEvent<Quattuordecuplet554>> Events(Event const& event, std::function< MultipletEvent<Quattuordecuplet554>(MultipletEvent<Quattuordecuplet554>&)> const& function) const;

    Reader<SignatureEffectiveTagger> signature_reader_;

    Reader<standardmodel::BottomTagger> bottom_reader_;

};

}

}
