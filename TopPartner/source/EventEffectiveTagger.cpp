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
    return SaveEntries(Events(event, [&](MultipletEvent<Quattuordecuplet554>& multiplet_event) {
        multiplet_event.SetTag(tag);
        return multiplet_event;
    }), 1);
}

std::vector<MultipletEvent<Quattuordecuplet554>> EventEffectiveTagger::Multiplets(Event const& event, PreCuts const&, TMVA::Reader const& reader) const
{
    INFO0;
    return ReduceResult(Events(event, [&](MultipletEvent<Quattuordecuplet554>& multiplet_event) {
        multiplet_event.SetBdt(Bdt(multiplet_event, reader));
        return multiplet_event;
    }), 1);
}

std::vector<MultipletEvent<Quattuordecuplet554>> EventEffectiveTagger::Events(Event const& event, std::function< MultipletEvent<Quattuordecuplet554>(MultipletEvent<Quattuordecuplet554>&)> const& function) const
{
    auto jets = bottom_reader_.Jets(event);
    auto octets = signature_reader_.Multiplets(event);
    std::vector<MultipletEvent<Quattuordecuplet554>> events;
    for (auto const & octet : octets) {
        MultipletEvent<Quattuordecuplet554> multiplet_event(octet, event, jets);
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
