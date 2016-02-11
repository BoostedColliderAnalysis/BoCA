#pragma once

#include "SignatureTagger.hh"
#include "MultipletEvent.hh"

namespace boca {

namespace higgscpv {

/**
 *
 * @brief Prepares multivariant analysis
 *
 */
class EventTagger : public TaggerTemplate<MultipletEvent<Octet62>,EventBranch> {

public:

    int Train(Event const& event, boca::PreCuts const&, Tag tag) const override;

    std::vector<MultipletEvent<Octet62>> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const override;

    std::string Name() const override;

private:

    Reader<SignatureTagger> signature_reader_;

    Reader<standardmodel::BottomTagger> bottom_reader_;

};

}

}
