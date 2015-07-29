#include "../include/EventTagger.hh"
#include "Debug.hh"

namespace analysis
{

namespace higgscpv
{

EventTagger::EventTagger()
{
    Note();
    DefineVariables();
}

int EventTagger::Train(const analysis::Event& event, const analysis::PreCuts&, Tag tag) const
{
    Info();
    Jets jets = bottom_reader_.Multiplets(event);
    std::vector<MultipletSignature<Octet62>> octets = signature_reader_.Multiplets(event);
    Info(octets.size());
    std::vector<MultipletEvent<Octet62>> multipletevents;
    for (const auto & octet : octets) {
        MultipletEvent<Octet62> multipletevent(octet.Multiplet(), event, jets);
        multipletevent.SetTag(tag);
        multipletevents.emplace_back(multipletevent);
    }
    return SaveEntries(ReduceResult(multipletevents, 1));
}

std::vector<MultipletEvent<Octet62>> EventTagger::Multiplets(const Event& event, const PreCuts&, const TMVA::Reader& reader) const
{
    Info();
    Jets jets = bottom_reader_.Multiplets(event);
    std::vector<MultipletSignature<Octet62>> octets = signature_reader_.Multiplets(event);
    std::vector<MultipletEvent<Octet62>> multiplet_events;
    for (const auto & octet : octets) {
        MultipletEvent<Octet62> multiplet_event(octet.Multiplet(), event, jets);
        multiplet_event.SetBdt(Bdt(multiplet_event, reader));
        multiplet_events.emplace_back(multiplet_event);
    }
    return ReduceResult(multiplet_events);
}

}

}
