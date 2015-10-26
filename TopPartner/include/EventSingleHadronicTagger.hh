/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "SignatureSingleHadronicTagger.hh"
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
class EventSingleHadronicTagger : public TaggerTemplate<MultipletEvent<Decuplet532>, EventBranch>
{

public:

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) const final;

    std::vector<MultipletEvent<Decuplet532>> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const final;

    std::string Name() const final;

    std::string NiceName() const final;

private:

    std::vector<MultipletEvent<Decuplet532>> Events(Event const& event, std::function<MultipletEvent<Decuplet532>(MultipletEvent<Decuplet532> &)> const& function) const;

    Reader<SignatureSingleHadronicTagger> signature_reader_;

    Reader<BottomTagger> bottom_reader_;

};

}

}
