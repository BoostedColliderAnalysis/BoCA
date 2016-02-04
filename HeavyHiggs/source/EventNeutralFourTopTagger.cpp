#include "EventNeutralFourTopTagger.hh"
#include "Event.hh"
#include "Debug.hh"

namespace boca
{

namespace heavyhiggs
{

int EventNeutralFourTopTagger::Train(boca::Event const& event, PreCuts const& , Tag tag) const
{
    INFO0;
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
    return SaveEntries(events, 1);
}

std::vector<MultipletEvent<Octet62>> EventNeutralFourTopTagger::Multiplets(Event const& event, PreCuts const& , TMVA::Reader const& reader) const
{
    INFO0;
    std::vector<Octet62> octets = signature_neutral_reader_.Multiplets(event);
    std::vector<Jet> jets = bottom_reader_.Jets(event);
    std::vector<Lepton> leptons = event.Leptons().leptons();
    std::vector<MultipletEvent<Octet62>> events;
    for (auto const & octet : octets) {
        MultipletEvent<Octet62> multiplet_event(octet, event, jets);
        multiplet_event.SetBdt(Bdt(multiplet_event, reader));
        events.emplace_back(multiplet_event);
    }
    return ReduceResult(events, 1);
}
std::string EventNeutralFourTopTagger::Name() const
{
    return "EventNeutralFourTop";
}

}

}
