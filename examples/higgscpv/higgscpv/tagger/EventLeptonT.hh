#pragma once

#include "boca/multiplets/EventMultiplet.hh"

#include "higgscpv/tagger/SignatureLeptonT.hh"
#include "higgscpv/branch/Event.hh"

namespace higgscpv {

namespace tagger {

/**
 *
 * @brief Prepares multivariant analysis
 *
 */
class EventLeptonT : public Tagger<EventMultiplet<Octet332>, branch::Event> {

public:

    int Train(boca::Event const& event, boca::PreCuts const&, Tag tag) override;

    std::vector<EventMultiplet<Octet332>> Multiplets(boca::Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

private:

    Reader<SignatureLeptonT> signature_reader_;

    Reader<standardmodel::tagger::Bottom> bottom_reader_;

};

}

}
