/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "SignatureSingleHadronicTagger.hh"
#include "GlobalTagger.hh"
#include "EventMultiplet.hh"

namespace boca
{

namespace naturalness
{

/**
 *
 * @brief Prepares multivariant analysis
 *
 */
class EventSingleHadronicTagger : public TaggerTemplate<EventMultiplet<Decuplet532>, NewEventBranch2>
{

public:

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) const override;

    std::vector<EventMultiplet<Decuplet532>> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const override;

    std::string Name() const override;

    std::string LatexName() const override;

private:

    std::vector<EventMultiplet<Decuplet532>> Events(Event const& event, std::function<EventMultiplet<Decuplet532>(EventMultiplet<Decuplet532> &)> const& function) const;

    Reader<SignatureSingleHadronicTagger> signature_reader_;

    Reader<GlobalTagger> global_reader_;

};

}

}
