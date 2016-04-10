#include "EventNeutralTagger.hh"
#include "Event.hh"
#include "generic/DEBUG.hh"

namespace boca
{

namespace heavyhiggs
{

int EventNeutralTagger::Train(boca::Event const& event, PreCuts const&, Tag tag)
{
    INFO("event Tags");
    std::vector<Jet> jets = bottom_reader_.Jets(event);
    std::vector<Lepton> leptons = event.Leptons().leptons();
    std::vector<Octet62> octets = signature_neutral_reader_.Multiplets(event);
    octets = signature_neutral_reader_.Tagger().CleanOctets(event, octets, tag);
    std::vector<MultipletEvent<Octet62>> events;
    for (auto const & octet : octets) {
        MultipletEvent<Octet62> octetevent(octet, event, jets);
        octetevent.SetTag(tag);
        events.emplace_back(octetevent);
    }
    return SaveEntries(events);
}

std::vector<MultipletEvent<Octet62>> EventNeutralTagger::Multiplets(boca::Event const& event, boca::PreCuts const&, TMVA::Reader const& reader)
{
    INFO("event Tags");
    std::vector<Octet62> octets = signature_neutral_reader_.Multiplets(event);
    std::vector<Jet> jets = bottom_reader_.Jets(event);
    std::vector<Lepton> leptons = event.Leptons().leptons();
    std::vector<MultipletEvent<Octet62>> multiplet_events;
    for (auto const & octet : octets) {
        MultipletEvent<Octet62> multiplet_event(octet, event, jets);
        multiplet_event.SetBdt(Bdt(multiplet_event, reader));
        multiplet_events.emplace_back(multiplet_event);
    }
    std::sort(multiplet_events.begin(), multiplet_events.end());
    if (multiplet_events.size() > 1)
        multiplet_events.erase(multiplet_events.begin() + 1, multiplet_events.end());
    INFO("event Number", multiplet_events.size(), jets.size());
    return multiplet_events;
}

std::string EventNeutralTagger::Name() const
{
    return "EventNeutral";
}

}

}
