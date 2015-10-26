/**
 * Copyright (C) 2015 Jan Hajer
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

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) const final;

    std::vector<MultipletEvent<Decuplet532>> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const final;

    std::string Name() const final;

private:

    Reader<SignatureSingleLeptonicTagger> signature_reader_;

    Reader<BottomTagger> bottom_reader_;

};

}

}
