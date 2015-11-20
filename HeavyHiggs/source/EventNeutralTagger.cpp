#include "EventNeutralTagger.hh"
#include "Event.hh"
#include "Debug.hh"

namespace analysis {

namespace heavyhiggs {

EventNeutralTagger::EventNeutralTagger()
{
  Info();
    DefineVariables();
}

int EventNeutralTagger::Train(const analysis::Event& event, const PreCuts&, Tag tag) const
{
    Info();
    Jets jets = bottom_reader_.Multiplets(event);
    std::vector<Octet62> octets = signature_neutral_reader_.Multiplets(event);
    octets = signature_neutral_reader_.Tagger().CleanOctets(event, octets, tag);
    std::vector<MultipletEvent<Octet62>> events;
    for (const auto& octet : octets) {
        MultipletEvent<Octet62> octetevent(octet, event, jets);
        octetevent.SetTag(tag);
        events.emplace_back(octetevent);
    }
    return SaveEntries(events, 1);
}

std::vector<MultipletEvent<Octet62>> EventNeutralTagger::Multiplets(const analysis::Event& event, const analysis::PreCuts&, const TMVA::Reader& reader) const
{
    Info();
    std::vector<Octet62> octets = signature_neutral_reader_.Multiplets(event);
    Jets jets = bottom_reader_.Multiplets(event);
    std::vector<MultipletEvent<Octet62>> events;
    for (const auto& octet : octets) {
        MultipletEvent<Octet62> multiplet_event(octet, event, jets);
        multiplet_event.SetBdt(Bdt(multiplet_event, reader));
        events.emplace_back(multiplet_event);
    }
    return ReduceResult(events, 1);
}

}

}
