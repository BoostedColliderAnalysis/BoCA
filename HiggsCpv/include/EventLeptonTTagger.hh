#pragma once

#include "SignatureLeptonTTagger.hh"
#include "MultipletEvent.hh"

namespace boca {

namespace higgscpv {

/**
 *
 * @brief Prepares multivariant analysis
 *
 */
class EventLeptonTTagger : public TaggerTemplate<MultipletEvent<Octet332>,EventBranch> {

public:

    int Train(Event const& event, boca::PreCuts const&, Tag tag) const final;

    std::vector<MultipletEvent<Octet332>> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const final;

    std::string Name() const final;

private:

    Reader<SignatureLeptonTTagger> signature_reader_;

    Reader<standardmodel::BottomTagger> bottom_reader_;

};

}

}