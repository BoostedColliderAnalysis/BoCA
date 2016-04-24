#pragma once

#include "boca/MultipletEvent.hh"
#include "boca/SignatureNeutralTagger.hh"

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

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    std::vector<MultipletEvent<Octet62>> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

private:

    Reader<SignatureNeutralTagger> signature_neutral_reader_;

    Reader<standardmodel::BottomTagger> bottom_reader_;

};

}

}
