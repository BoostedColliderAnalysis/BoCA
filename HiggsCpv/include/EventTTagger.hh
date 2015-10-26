#pragma once

#include "SignatureTTagger.hh"
#include "MultipletEvent.hh"

namespace boca {

namespace higgscpv {

/**
 *
 * @brief Prepares multivariant analysis
 *
 */
class EventTTagger : public TaggerTemplate<MultipletEvent<Octet332>,EventBranch> {

public:

    int Train(Event const& event, boca::PreCuts const&, Tag tag) const final;

    std::vector<MultipletEvent<Octet332>> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const final;

    std::string Name() const final;

private:

    Reader<SignatureTTagger> signature_reader_;

    Reader<BottomTagger> bottom_reader_;

};

}

}
