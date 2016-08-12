#include "boca/Event.hh"

#include "include/tagger/EventNeutral.hh"

#include "boca/generic/DEBUG_MACROS.hh"

namespace heavyhiggs
{

namespace tagger
{

int EventNeutral::Train(boca::Event const& event, PreCuts const&, Tag tag)
{
    INFO("event Tags");
    auto jets = bottom_reader_.Jets(event);
    auto leptons = event.Leptons();
    auto octets = signature_neutral_reader_.Multiplets(event);
    octets = signature_neutral_reader_.Tagger().CleanOctets(event, octets, tag);
    std::vector<MultipletEvent<Octet62>> events;
    for (auto const & octet : octets) {
        MultipletEvent<Octet62> octetevent(octet, event, jets);
        octetevent.SetTag(tag);
        events.emplace_back(octetevent);
    }
    return SaveEntries(events);
}

std::vector<MultipletEvent<Octet62>> EventNeutral::Multiplets(boca::Event const& event, boca::PreCuts const&, TMVA::Reader const& reader)
{
    INFO("event Tags");
    auto octets = signature_neutral_reader_.Multiplets(event);
    auto jets = bottom_reader_.Jets(event);
    auto leptons = event.Leptons();
    std::vector<MultipletEvent<Octet62>> multiplet_events;
    for (auto const & octet : octets) {
        MultipletEvent<Octet62> multiplet_event(octet, event, jets);
        multiplet_event.SetBdt(Bdt(multiplet_event, reader));
        multiplet_events.emplace_back(multiplet_event);
    }
    std::sort(multiplet_events.begin(), multiplet_events.end());
    if (multiplet_events.size() > 1)
        multiplet_events.erase(multiplet_events.begin() + 1, multiplet_events.end());
    INFO("event Number", multiplet_events.size(), jets.size());
    return multiplet_events;
}

std::string EventNeutral::Name() const
{
    return "EventNeutral";
}

}

}
