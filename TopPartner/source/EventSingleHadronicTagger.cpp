/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "EventSingleHadronicTagger.hh"
// #define DEBUG
#include "Debug.hh"

namespace boca
{

namespace naturalness
{

int EventSingleHadronicTagger::Train(Event const& event, PreCuts const&, Tag tag) const
{
    Info();
    return SaveEntries(Events(event, [&](MultipletEvent<Decuplet532> & multiplet_event) {
        multiplet_event.SetTag(tag);
        return multiplet_event;
    }), tag);
}

std::vector<MultipletEvent<Decuplet532>> EventSingleHadronicTagger::Multiplets(boca::Event const& event, boca::PreCuts const&, TMVA::Reader const& reader) const
{
    Info();
    return ReduceResult(Events(event, [&](MultipletEvent<Decuplet532> & multiplet_event) {
        multiplet_event.SetBdt(Bdt(multiplet_event, reader));
        return multiplet_event;
    }), 1);
}

std::vector<MultipletEvent<Decuplet532>> EventSingleHadronicTagger::Events(Event const& event, std::function<MultipletEvent<Decuplet532>(MultipletEvent<Decuplet532> &)> const& function) const
{
    Info();
    Jets jets = bottom_reader_.Multiplets(event);
    std::vector<MultipletEvent<Decuplet532>> multiplet_events;
    for (auto const & decuplet : signature_reader_.Multiplets(event)) {
        MultipletEvent<Decuplet532> multiplet_event(decuplet, event, jets);
        multiplet_events.emplace_back(function(multiplet_event));
    }
    return multiplet_events;
}

}

}
