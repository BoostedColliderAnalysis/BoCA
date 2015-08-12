#include "EventEffectiveTagger.hh"
#include "Debug.hh"

namespace analysis {

namespace toppartner {

EventEffectiveTagger::EventEffectiveTagger()
{
  Info();
    DefineVariables();
}

int EventEffectiveTagger::Train(Event const& event, PreCuts const&, Tag tag) const
{
    Info("Train");
    Jets jets = bottom_reader_.Multiplets(event);
    std::vector<Quattuordecuplet> octets = signature_reader_.Multiplets(event);
    Info("Octets", octets.size());
    std::vector<MultipletEvent<Quattuordecuplet>> multipletevents;
    for (auto const& octet : octets) {
        MultipletEvent<Quattuordecuplet> multipletevent(octet, event, jets);
        multipletevent.SetTag(tag);
        multipletevents.emplace_back(multipletevent);
    }
    return SaveEntries(ReduceResult(multipletevents, 1));
}

std::vector<MultipletEvent<Quattuordecuplet>> EventEffectiveTagger::Multiplets(Event const& event, PreCuts const&, TMVA::Reader const& reader) const
{
    Info("Multiplets");
    Jets jets = bottom_reader_.Multiplets(event);
    std::vector<Quattuordecuplet> octets = signature_reader_.Multiplets(event);
    std::vector<MultipletEvent<Quattuordecuplet>> multiplet_events;
    for (auto const& octet : octets) {
        MultipletEvent<Quattuordecuplet> multiplet_event(octet, event, jets);
        multiplet_event.SetBdt(Bdt(multiplet_event, reader));
        multiplet_events.emplace_back(multiplet_event);
    }
    return ReduceResult(multiplet_events);
}

}

}
