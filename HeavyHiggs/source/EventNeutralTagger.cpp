#include "EventNeutralTagger.hh"
#include "Debug.hh"

namespace analysis {

namespace heavyhiggs {

EventNeutralTagger::EventNeutralTagger()
{
    Note();
    DefineVariables();
}

int EventNeutralTagger::Train(const analysis::Event& event, const PreCuts& pre_cuts, const analysis::Tag tag) const
{
    Info("event Tags");
    Jets jets = bottom_reader_.Multiplets(event);
    Jets leptons = event.Leptons().leptons();
    std::vector<Octet62> octets = signature_neutral_reader_.Multiplets(event);
    std::vector<MultipletEvent<Octet62>> events;
    for (const auto& octet : octets) {
        MultipletEvent<Octet62> octetevent(octet, event, jets);
        octetevent.SetTag(tag);
        events.emplace_back(octetevent);
    }
    return SaveEntries(events);
}

std::vector<MultipletEvent<Octet62>> EventNeutralTagger::Multiplets(const Event& event, const TMVA::Reader& reader) const
{
    Info("event Tags");
    std::vector<Octet62> octets = signature_neutral_reader_.Multiplets(event);
    Jets jets = bottom_reader_.Multiplets(event);
    Jets Leptons = event.Leptons().leptons();
    std::vector<MultipletEvent<Octet62>> multiplet_events;
    for (const auto& octet : octets) {
        MultipletEvent<Octet62> multiplet_event(octet, event, jets);
        multiplet_event.SetBdt(Bdt(multiplet_event, reader));
        multiplet_events.emplace_back(multiplet_event);
    }
    std::sort(multiplet_events.begin(), multiplet_events.end());
    if (multiplet_events.size() > 1)
        multiplet_events.erase(multiplet_events.begin() + 1, multiplet_events.end());
    Info("event Number", multiplet_events.size(), jets.size());
    return multiplet_events;
}

}

}
