#pragma once

#include "boca/multiplets/EventMultiplet.hh"

#include "include/tagger/SignatureNeutral.hh"
#include "include/branch/EventNeutralFourTop.hh"

namespace heavyhiggs
{

namespace tagger
{

/**
 *
 * @brief event BDT for semi leptonic heavy higgs
 *
 */
class EventNeutralFourTop : public Tagger<EventMultiplet<Octet62>, branch::EventNeutralFourTop>
{

public:

    int Train(boca::Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    std::vector<EventMultiplet<Octet62>> Multiplets(boca::Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

private:

    Reader<SignatureNeutral> signature_neutral_reader_;

    Reader<standardmodel::tagger::Bottom> bottom_reader_;

};

}

}
