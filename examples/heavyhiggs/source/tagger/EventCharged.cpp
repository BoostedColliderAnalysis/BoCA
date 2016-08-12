#include "boca/Event.hh"

#include "include/tagger/EventCharged.hh"

#include "boca/generic/DEBUG_MACROS.hh"

namespace heavyhiggs
{

namespace tagger
{

int EventCharged::Train(boca::Event const& event, boca::PreCuts const&, Tag tag)
{
    INFO0;
    return SaveEntries(Events(event, [&](MultipletEvent<Octet44>& multiplet_event) {
        multiplet_event.SetTag(tag);
        return multiplet_event;
    }), tag);
}


std::vector<MultipletEvent<Octet44>> EventCharged::Multiplets(boca::Event const& event, PreCuts const&, TMVA::Reader const& reader)
{
    INFO0;
    return ReduceResult(Events(event, [&](MultipletEvent<Octet44>& multiplet_event) {
        multiplet_event.SetBdt(Bdt(multiplet_event, reader));
        return multiplet_event;
    }), 1);
}

std::vector<MultipletEvent<Octet44>> EventCharged::Events(boca::Event const& event, std::function<MultipletEvent<Octet44>(MultipletEvent<Octet44> &)> const& function)
{
    INFO0;
    auto jets = bottom_reader_.Jets(event);
    auto octets = signature_semi_reader_.Multiplets(event);
    std::vector<MultipletEvent<Octet44>> multiplet_events;
    for (auto & octet : octets) {
        MultipletEvent<Octet44> multiplet_event(octet, event, jets);
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
