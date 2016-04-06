#include "EventTTagger.hh"
#include "generic/DEBUG.hh"

namespace boca
{

namespace higgscpv
{

int EventTTagger::Train(boca::Event const& event, boca::PreCuts const&, Tag tag)
{
    INFO0;
   std::vector<Jet> jets = bottom_reader_.Jets(event);
    std::vector<MultipletSignature<Octet332>> octets = signature_reader_.Multiplets(event);
    INFO(octets.size());
    std::vector<MultipletEvent<Octet332>> multipletevents;
    for (auto const& octet : octets) {
        MultipletEvent<Octet332> multipletevent(octet.Multiplet(), event, jets);
        multipletevent.SetTag(tag);
        multipletevents.emplace_back(multipletevent);
    }
    return SaveEntries(multipletevents, 1);
}

std::vector<MultipletEvent<Octet332>> EventTTagger::Multiplets(Event const& event, PreCuts const&, TMVA::Reader const& reader)
{
    INFO0;
   std::vector<Jet> jets = bottom_reader_.Jets(event);
    std::vector<MultipletSignature<Octet332>> octets = signature_reader_.Multiplets(event);
    std::vector<MultipletEvent<Octet332>> multiplet_events;
    for (auto const& octet : octets) {
        MultipletEvent<Octet332> multiplet_event(octet.Multiplet(), event, jets);
        multiplet_event.SetBdt(Bdt(multiplet_event, reader));
        multiplet_events.emplace_back(multiplet_event);
    }
    return ReduceResult(multiplet_events,1);
}
std::string EventTTagger::Name() const
{
    return "EventTChannel";
}

}

}
