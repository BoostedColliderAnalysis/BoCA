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

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) const override;

    std::vector<MultipletEvent<Quattuordecuplet554>> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const override;

    std::string Name() const override;

    std::string LatexName() const override;


private:

    std::vector<MultipletEvent<Quattuordecuplet554>> Events(Event const& event, std::function< MultipletEvent<Quattuordecuplet554>(MultipletEvent<Quattuordecuplet554>&)> const& function) const;

    Reader<SignatureEffectiveTagger> signature_reader_;

    Reader<standardmodel::BottomTagger> bottom_reader_;

};

}

}
