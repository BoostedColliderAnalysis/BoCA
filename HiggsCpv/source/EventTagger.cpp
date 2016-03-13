#include "../include/GlobalTagger.hh"
#include "DEBUG.hh"

namespace boca
{

namespace higgscpv
{

int GlobalTagger::Train(boca::Event const& event, boca::PreCuts const&, Tag tag) const
{
    INFO0;
   std::vector<Jet> jets = bottom_reader_.Jets(event);
    std::vector<MultipletSignature<Octet62>> octets = signature_reader_.Multiplets(event);
    INFO(octets.size());
    std::vector<MultipletEvent<Octet62>> multipletevents;
    for (auto const& octet : octets) {
        MultipletEvent<Octet62> multipletevent(octet.Multiplet(), event, jets);
        multipletevent.SetTag(tag);
        multipletevents.emplace_back(multipletevent);
    }
    return SaveEntries(ReduceResult(multipletevents, 1));
}

std::vector<MultipletEvent<Octet62>> GlobalTagger::Multiplets(Event const& event, PreCuts const&, TMVA::Reader const& reader) const
{
    INFO0;
   std::vector<Jet> jets = bottom_reader_.Jets(event);
    std::vector<MultipletSignature<Octet62>> octets = signature_reader_.Multiplets(event);
    std::vector<MultipletEvent<Octet62>> multiplet_events;
    for (auto const& octet : octets) {
        MultipletEvent<Octet62> multiplet_event(octet.Multiplet(), event, jets);
        multiplet_event.SetBdt(Bdt(multiplet_event, reader));
        multiplet_events.emplace_back(multiplet_event);
    }
    return ReduceResult(multiplet_events);
}
std::string GlobalTagger::Name() const
{
    return "Event";
}

}

}
