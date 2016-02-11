#pragma once

#include "MultipletEvent.hh"
#include "SignatureNeutralTagger.hh"

namespace boca
{

namespace heavyhiggs
{

/**
 *
 * @brief event BDT for semi leptonic heavy higgs
 *
 */
class EventNeutralTagger : public TaggerTemplate<MultipletEvent<Octet62>, EventNeutralBranch>
{

public:

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) const override;

    std::vector<MultipletEvent<Octet62>> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const override;

    std::string Name() const override;

private:

    std::vector<MultipletEvent<Octet62>> Events(Event const& event, std::function<MultipletEvent<Octet62>(MultipletEvent<Octet62> &)> const& function) const;

    Reader<SignatureNeutralTagger> signature_neutral_reader_;

    Reader<standardmodel::BottomTagger> bottom_reader_;

};

}

}
