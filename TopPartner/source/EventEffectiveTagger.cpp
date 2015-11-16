#include "EventEffectiveTagger.hh"
#include "Debug.hh"

namespace boca {

namespace naturalness {

int EventEffectiveTagger::Train(Event const& event, PreCuts const&, Tag tag) const
{
    Info("Train");
    Jets jets = bottom_reader_.Jets(event);
    std::vector<Quattuordecuplet554> octets = signature_reader_.Multiplets(event);
    Info("Octets", octets.size());
    std::vector<MultipletEvent<Quattuordecuplet554>> multipletevents;
    for (auto const& octet : octets) {
        MultipletEvent<Quattuordecuplet554> multipletevent(octet, event, jets);
        multipletevent.SetTag(tag);
        multipletevents.emplace_back(multipletevent);
    }
    return SaveEntries(ReduceResult(multipletevents, 1));
}

std::vector<MultipletEvent<Quattuordecuplet554>> EventEffectiveTagger::Multiplets(Event const& event, PreCuts const&, TMVA::Reader const& reader) const
{
    Info("Multiplets");
    Jets jets = bottom_reader_.Jets(event);
    std::vector<Quattuordecuplet554> octets = signature_reader_.Multiplets(event);
    std::vector<MultipletEvent<Quattuordecuplet554>> multiplet_events;
    for (auto const& octet : octets) {
        MultipletEvent<Quattuordecuplet554> multiplet_event(octet, event, jets);
        multiplet_event.SetBdt(Bdt(multiplet_event, reader));
        multiplet_events.emplace_back(multiplet_event);
    }
    return ReduceResult(multiplet_events);
}
std::string EventEffectiveTagger::Name() const
{
    return "Event";
}

}

}
