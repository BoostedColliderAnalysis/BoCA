#pragma once

#include "boca/SignatureLeptonTTagger.hh"
#include "boca/MultipletEvent.hh"

namespace boca {

namespace higgscpv {

/**
 *
 * @brief Prepares multivariant analysis
 *
 */
class EventLeptonTTagger : public Tagger<MultipletEvent<Octet332>, Event> {

public:

    int Train(boca::Event const& event, boca::PreCuts const&, Tag tag) override;

    std::vector<MultipletEvent<Octet332>> Multiplets(boca::Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

private:

    Reader<SignatureLeptonTTagger> signature_reader_;

    Reader<standardmodel::tagger::Bottom> bottom_reader_;

};

}

}
