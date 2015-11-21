#include "EventChargedTagger.hh"
#include "Event.hh"
#include "Debug.hh"

namespace boca {

namespace heavyhiggs {

int EventChargedTagger::Train(boca::Event const& event, boca::PreCuts const&, Tag tag) const
{
    Info0;
   std::vector<Jet> jets = bottom_reader_.Jets(event);
   std::vector<Jet> Leptons = event.Leptons().leptons();
    std::vector<Octet44> octets = signature_semi_reader_.Multiplets(event);
    std::vector<MultipletEvent<Octet44>> events;
    for (auto const& octet : octets) {
        MultipletEvent<Octet44> octetevent(octet, event, jets);
        octetevent.SetTag(tag);
        events.emplace_back(octetevent);
    }
    return SaveEntries(ReduceResult(events, 1));
}


std::vector<MultipletEvent<Octet44>> EventChargedTagger::Multiplets(Event const& event, PreCuts const&, TMVA::Reader const& reader) const
{
    Info0;
   std::vector<Jet> jets = bottom_reader_.Jets(event);
    std::vector<Octet44> octets = signature_semi_reader_.Multiplets(event);
    std::vector<MultipletEvent<Octet44>> multiplet_events;
    for (auto& octet : octets) {
        MultipletEvent<Octet44> multiplet_event(octet, event, jets);
        multiplet_event.SetBdt(Bdt(multiplet_event, reader));
        multiplet_events.emplace_back(multiplet_event);
    }
    return ReduceResult(multiplet_events, 1);
}
std::string EventChargedTagger::Name() const
{
    return "EventCharged";
}

}

}
