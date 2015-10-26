#include "EventNeutralFourTopTagger.hh"
#include "Event.hh"
#include "Debug.hh"

namespace boca {

namespace heavyhiggs {

int EventNeutralFourTopTagger::Train(boca::Event const& event, PreCuts const& , Tag tag) const
{
    Info();
    Jets jets = bottom_reader_.Jets(event);
    Jets leptons = event.Leptons().leptons();
    std::vector<Octet62> octets = signature_neutral_reader_.Multiplets(event);
    std::vector<MultipletEvent<Octet62>> events;
    for (auto const& octet : octets) {
        MultipletEvent<Octet62> octetevent(octet, event, jets);
        octetevent.SetTag(tag);
        events.emplace_back(octetevent);
    }
    std::sort(events.begin(),events.end());
    return SaveEntries(events, 1);
}

std::vector<MultipletEvent<Octet62>> EventNeutralFourTopTagger::Multiplets(Event const& event, PreCuts const& , TMVA::Reader const& reader) const
{
    Info();
    std::vector<Octet62> octets = signature_neutral_reader_.Multiplets(event);
    Jets jets = bottom_reader_.Jets(event);
    Jets Leptons = event.Leptons().leptons();
    std::vector<MultipletEvent<Octet62>> multiplet_events;
    for (auto const& octet : octets) {
        MultipletEvent<Octet62> multiplet_event(octet, event, jets);
        multiplet_event.SetBdt(Bdt(multiplet_event, reader));
        multiplet_events.emplace_back(multiplet_event);
    }
    std::sort(multiplet_events.begin(), multiplet_events.end());
    if (multiplet_events.size() > 1)
        multiplet_events.erase(multiplet_events.begin() + 1, multiplet_events.end());
    Info(multiplet_events.size(), jets.size());
    return multiplet_events;
}
std::string EventNeutralFourTopTagger::Name() const
{
    return "EventNeutralFourTop";
}

}

}
