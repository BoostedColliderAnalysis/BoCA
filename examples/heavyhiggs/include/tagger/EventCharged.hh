#pragma once

#include "boca/MultipletEvent.hh"

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
class EventCharged : public Tagger<MultipletEvent<Octet44>, branch::EventCharged>
{

public:

    int Train(boca::Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    std::vector<MultipletEvent<Octet44>> Multiplets(boca::Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

private:

    std::vector<MultipletEvent<Octet44>> Events(boca::Event const& event, std::function<MultipletEvent<Octet44>(MultipletEvent<Octet44> &)> const& function);

    Reader<standardmodel::tagger::Bottom> bottom_reader_;

    Reader<SignatureCharged> signature_semi_reader_;

};

}

}
