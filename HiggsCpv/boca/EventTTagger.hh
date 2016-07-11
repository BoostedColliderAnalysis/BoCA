#pragma once

#include "boca/SignatureTTagger.hh"
#include "boca/MultipletEvent.hh"

namespace boca {

namespace higgscpv {

/**
 *
 * @brief Prepares multivariant analysis
 *
 */
class EventTTagger : public Tagger<MultipletEvent<Octet332>,Event> {

public:

    int Train(Event const& event, boca::PreCuts const&, Tag tag) override;

    std::vector<MultipletEvent<Octet332>> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

private:

    Reader<SignatureTTagger> signature_reader_;

    Reader<standardmodel::tagger::Bottom> bottom_reader_;

};

}

}
