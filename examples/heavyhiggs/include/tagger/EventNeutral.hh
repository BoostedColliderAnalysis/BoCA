#pragma once

#include "boca/MultipletEvent.hh"

#include "include/tagger/SignatureNeutral.hh"
#include "include/branch/EventNeutral.hh"

namespace heavyhiggs
{

namespace tagger
{

/**
 *
 * @brief event BDT for semi leptonic heavy higgs
 *
 */
class EventNeutral : public Tagger<MultipletEvent<Octet62>, branch::EventNeutral>
{

public:

    int Train(boca::Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    std::vector<MultipletEvent<Octet62>> Multiplets(boca::Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

private:

    std::vector<MultipletEvent<Octet62>> Events(boca::Event const& event, std::function<MultipletEvent<Octet62>(MultipletEvent<Octet62> &)> const& function) const;

    Reader<SignatureNeutral> signature_neutral_reader_;

    Reader<standardmodel::tagger::Bottom> bottom_reader_;

};

}

}
