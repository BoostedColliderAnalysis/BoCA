#include "boca/Event.hh"

#include "include/tagger/EventCharged.hh"

#include "boca/generic/DEBUG.hh"

namespace heavyhiggs
{

namespace tagger
{

int EventCharged::Train(boca::Event const& event, boca::PreCuts const&, Tag tag)
{
    INFO0;
    return SaveEntries(Events(event, [&](EventMultiplet<Octet44>& multiplet_event) {
        multiplet_event.SetTag(tag);
        return multiplet_event;
    }), tag);
}


std::vector<EventMultiplet<Octet44>> EventCharged::Multiplets(boca::Event const& event, PreCuts const&, TMVA::Reader const& reader)
{
    INFO0;
    return ReduceResult(Events(event, [&](EventMultiplet<Octet44>& multiplet_event) {
        multiplet_event.SetBdt(Bdt(multiplet_event, reader));
        return multiplet_event;
    }), 1);
}

std::vector<EventMultiplet<Octet44>> EventCharged::Events(boca::Event const& event, std::function<EventMultiplet<Octet44>(EventMultiplet<Octet44> &)> const& function)
{
    INFO0;
    boca::GlobalObservables global_observables(event, bottom_reader_.Jets(event));
//     auto jets = bottom_reader_.Jets(event);
    auto octets = signature_semi_reader_.Multiplets(event);
    std::vector<EventMultiplet<Octet44>> multiplet_events;
    for (auto & octet : octets) {
        EventMultiplet<Octet44> multiplet_event(octet, global_observables);
        multiplet_events.emplace_back(function(multiplet_event));
    }
    return multiplet_events;
}

std::string EventCharged::Name() const
{
    return "EventCharged";
}

}

}
