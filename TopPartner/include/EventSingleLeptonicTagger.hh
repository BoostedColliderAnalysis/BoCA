/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "SignatureSingleLeptonicTagger.hh"
#include "MultipletEvent.hh"

namespace boca
{

namespace naturalness
{

/**
 *
 * @brief Prepares multivariant analysis
 *
 */
class EventSingleLeptonicTagger : public TaggerTemplate<MultipletEvent<Decuplet532>, EventBranch>
{

public:

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) const override;

    std::vector<MultipletEvent<Decuplet532>> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const override;

    std::string Name() const override;

private:

    Reader<SignatureSingleLeptonicTagger> signature_reader_;

    Reader<standardmodel::BottomTagger> bottom_reader_;

};

}

}
