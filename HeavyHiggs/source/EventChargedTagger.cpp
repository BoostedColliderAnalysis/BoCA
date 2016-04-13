#include "EventChargedTagger.hh"
#include "Event.hh"
#include "generic/DEBUG.hh"

namespace boca
{

namespace heavyhiggs
{

int EventChargedTagger::Train(boca::Event const& event, boca::PreCuts const&, Tag tag)
{
    INFO0;
    return SaveEntries(Events(event, [&](MultipletEvent<Octet44>& multiplet_event) {
        multiplet_event.SetTag(tag);
        return multiplet_event;
    }), tag);
}


std::vector<MultipletEvent<Octet44>> EventChargedTagger::Multiplets(Event const& event, PreCuts const&, TMVA::Reader const& reader)
{
    INFO0;
    return ReduceResult(Events(event, [&](MultipletEvent<Octet44>& multiplet_event) {
        multiplet_event.SetBdt(Bdt(multiplet_event, reader));
        return multiplet_event;
    }), 1);
}

std::vector<MultipletEvent<Octet44>> EventChargedTagger::Events(Event const& event, std::function<MultipletEvent<Octet44>(MultipletEvent<Octet44> &)> const& function)
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

std::string EventChargedTagger::Name() const
{
    return "EventCharged";
}

}

}
