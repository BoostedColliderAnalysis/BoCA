#include "boca/event/Event.hh"

#include "heavyhiggs/tagger/EventNeutralFourTop.hh"

#include "boca/generic/DEBUG_MACROS.hh"

namespace heavyhiggs
{

namespace tagger
{

int EventNeutralFourTop::Train(boca::Event const& event, PreCuts const& , Tag tag)
{
    INFO0;
    auto jets = bottom_reader_.Jets(event);
    auto leptons = event.Leptons();
    auto octets = signature_neutral_reader_.Multiplets(event);
    octets = signature_neutral_reader_.Tagger().CleanOctets(event, octets, tag);
    std::vector<EventMultiplet<Octet62>> events;
    for (auto const & octet : octets) {
        EventMultiplet<Octet62> octetevent(octet, event, jets);
        octetevent.SetTag(tag);
        events.emplace_back(octetevent);
    }
    return SaveEntries(events, 1);
}

std::vector<EventMultiplet<Octet62>> EventNeutralFourTop::Multiplets(boca::Event const& event, PreCuts const& , TMVA::Reader const& reader)
{
    INFO0;
    auto octets = signature_neutral_reader_.Multiplets(event);
    auto jets = bottom_reader_.Jets(event);
    auto leptons = event.Leptons();
    std::vector<EventMultiplet<Octet62>> events;
    for (auto const & octet : octets) {
        EventMultiplet<Octet62> multiplet_event(octet, event, jets);
        multiplet_event.SetBdt(Bdt(multiplet_event, reader));
        events.emplace_back(multiplet_event);
    }
    return ReduceResult(events, 1);
}
std::string EventNeutralFourTop::Name() const
{
    return "EventNeutralFourTop";
}

}

}
