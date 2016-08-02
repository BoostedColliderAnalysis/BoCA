/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "boca/EventEffectiveTagger.hh"
// #define DEBUGGING
#include "boca/generic/DEBUG.hh"

namespace boca
{

namespace toppartner
{

int EventEffectiveTagger::Train(Event const& event, PreCuts const&, Tag tag)
{
    INFO0;
    return SaveEntries(Events(event, [&](EventMultiplet<Quattuordecuplet554>& multiplet_event) {
        multiplet_event.SetTag(tag);
        return multiplet_event;
    }), tag);
}

std::vector<EventMultiplet<Quattuordecuplet554>> EventEffectiveTagger::Multiplets(Event const& event, PreCuts const&, TMVA::Reader const& reader)
{
    INFO0;
    return ReduceResult(Events(event, [&](EventMultiplet<Quattuordecuplet554>& multiplet_event) {
        multiplet_event.SetBdt(Bdt(multiplet_event, reader));
        return multiplet_event;
    }), 1);
}

std::vector<EventMultiplet<Quattuordecuplet554>> EventEffectiveTagger::Events(Event const& event, std::function< EventMultiplet<Quattuordecuplet554>(EventMultiplet<Quattuordecuplet554>&)> const& function)
{
  INFO0;
    auto global_observables = global_reader_.Multiplets(event).front();
    std::vector<EventMultiplet<Quattuordecuplet554>> events;
    for (auto const & octet : signature_reader_.Multiplets(event)) {
        EventMultiplet<Quattuordecuplet554> multiplet_event(octet, global_observables);
        events.emplace_back(function(multiplet_event));
    }
    return events;
}

std::string EventEffectiveTagger::Name() const
{
    return "Event";
}

latex::String EventEffectiveTagger::LatexName() const
{
    return "T_{h} T_{l} h h";
}

}

}