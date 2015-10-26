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
class EventNeutralFourTopTagger : public TaggerTemplate<MultipletEvent<Octet62>, EventNeutralFourTopBranch>
{

public:

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) const final;

    std::vector<MultipletEvent<Octet62>> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const final;

    std::string Name() const final;

private:

    Reader<SignatureNeutralTagger> signature_neutral_reader_;

    Reader<BottomTagger> bottom_reader_;

};

}

}
