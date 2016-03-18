#pragma once

#include "MultipletEvent.hh"
#include "SignatureChargedTagger.hh"

namespace boca
{

namespace heavyhiggs
{

/**
 *
 * @brief event BDT for semi leptonic heavy higgs
 *
 */
class EventChargedTagger : public TaggerTemplate<MultipletEvent<Octet44>, EventChargedBranch>
{

public:

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) const override;

    std::vector<MultipletEvent<Octet44>> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const override;

    std::string Name() const override;

private:

    std::vector<MultipletEvent<Octet44>> Events(Event const& event, std::function<MultipletEvent<Octet44>(MultipletEvent<Octet44> &)> const& function) const;

    Reader<standardmodel::BottomTagger> bottom_reader_;

    Reader<SignatureChargedTagger> signature_semi_reader_;

};

}

}
