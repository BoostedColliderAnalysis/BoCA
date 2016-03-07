#include "EventEffectiveTagger.hh"
#include "plotting/Font.hh"
#include "Debug.hh"

namespace boca
{

namespace naturalness
{

int EventEffectiveTagger::Train(Event const& event, PreCuts const&, Tag tag) const
{
    INFO0;
    return SaveEntries(Events(event, [&](EventMultiplet<Quattuordecuplet554>& multiplet_event) {
        multiplet_event.SetTag(tag);
        return multiplet_event;
    }), tag);
}

std::vector<EventMultiplet<Quattuordecuplet554>> EventEffectiveTagger::Multiplets(Event const& event, PreCuts const&, TMVA::Reader const& reader) const
{
    INFO0;
    return ReduceResult(Events(event, [&](EventMultiplet<Quattuordecuplet554>& multiplet_event) {
        multiplet_event.SetBdt(Bdt(multiplet_event, reader));
        return multiplet_event;
    }), 1);
}

std::vector<EventMultiplet<Quattuordecuplet554>> EventEffectiveTagger::Events(Event const& event, std::function< EventMultiplet<Quattuordecuplet554>(EventMultiplet<Quattuordecuplet554>&)> const& function) const
{
    auto octets = signature_reader_.Multiplets(event);
    auto global_observables = global_reader_.Multiplets(event).front();
    std::vector<EventMultiplet<Quattuordecuplet554>> events;
    for (auto const & octet : octets) {
        EventMultiplet<Quattuordecuplet554> multiplet_event(octet, global_observables);
        events.emplace_back(function(multiplet_event));
    }
    return events;
}

std::string EventEffectiveTagger::Name() const
{
    return "Event";
}

std::string EventEffectiveTagger::LatexName() const
{
    return Formula("T_{h} T_{l} h h");
}

}

}
