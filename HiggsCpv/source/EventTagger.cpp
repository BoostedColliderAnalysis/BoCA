#include "../include/EventTTagger.hh"
#include "Debug.hh"

namespace analysis
{

namespace higgscpv
{

EventTTagger::EventTTagger()
{
  Info();
    DefineVariables();
}

int EventTTagger::Train(analysis::Event const& event, analysis::PreCuts const&, Tag tag) const
{
    Info();
    Jets jets = bottom_reader_.Multiplets(event);
    std::vector<MultipletSignature<Octet332>> octets = signature_reader_.Multiplets(event);
    Info(octets.size());
    std::vector<MultipletEvent<Octet332>> multipletevents;
    for (auto const& octet : octets) {
        MultipletEvent<Octet332> multipletevent(octet.Multiplet(), event, jets);
        multipletevent.SetTag(tag);
        multipletevents.emplace_back(multipletevent);
    }
    return SaveEntries(ReduceResult(multipletevents, 1));
}

std::vector<MultipletEvent<Octet332>> EventTTagger::Multiplets(Event const& event, PreCuts const&, TMVA::Reader const& reader) const
{
    Info();
    Jets jets = bottom_reader_.Multiplets(event);
    std::vector<MultipletSignature<Octet332>> octets = signature_reader_.Multiplets(event);
    std::vector<MultipletEvent<Octet332>> multiplet_events;
    for (auto const& octet : octets) {
        MultipletEvent<Octet332> multiplet_event(octet.Multiplet(), event, jets);
        multiplet_event.SetBdt(Bdt(multiplet_event, reader));
        multiplet_events.emplace_back(multiplet_event);
    }
    return ReduceResult(multiplet_events);
}

}

}
