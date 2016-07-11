#pragma once

#include "boca/SignatureTagger.hh"
#include "boca/MultipletEvent.hh"

namespace boca {

namespace higgscpv {

/**
 *
 * @brief Prepares multivariant analysis
 *
 */
class GlobalTagger : public Tagger<MultipletEvent<Octet62>,Event> {

public:

    int Train(Event const& event, boca::PreCuts const&, Tag tag) override;

    std::vector<MultipletEvent<Octet62>> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

private:

    Reader<SignatureTagger> signature_reader_;

    Reader<standardmodel::tagger::Bottom> bottom_reader_;

};

}

}
