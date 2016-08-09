#pragma once

#include "boca/multiplets/EventMultiplet.hh"

#include "include/tagger/SignatureCharged.hh"
#include "include/branch/EventCharged.hh"

namespace heavyhiggs
{

namespace tagger
{

/**
 *
 * @brief event BDT for semi leptonic heavy higgs
 *
 */
class EventCharged : public Tagger<EventMultiplet<Octet44>, boca::branch::Event>
{

public:

    int Train(boca::Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    std::vector<EventMultiplet<Octet44>> Multiplets(boca::Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

private:

    std::vector<EventMultiplet<Octet44>> Events(boca::Event const& event, std::function<EventMultiplet<Octet44>(EventMultiplet<Octet44> &)> const& function);

    Reader<standardmodel::tagger::Bottom> bottom_reader_;

    Reader<SignatureCharged> signature_semi_reader_;

};

}

}
