#include "boca/EventPairTagger.hh"
// #define DEBUGGING
#include "boca/generic/DEBUG.hh"

namespace boca
{

namespace naturalness
{

int EventPairTagger::Train(Event const& event, PreCuts const&, Tag tag)
{
    INFO0;
    return SaveEntries(Events(event, [&](EventMultiplet<Decuplet55>& multiplet_event) {
        multiplet_event.SetTag(tag);
        return multiplet_event;
    }), tag);
}

std::vector<EventMultiplet<Decuplet55>> EventPairTagger::Multiplets(boca::Event const& event, boca::PreCuts const&, TMVA::Reader const& reader)
{
    INFO0;
    return ReduceResult(Events(event, [&](EventMultiplet<Decuplet55>& multiplet_event) {
        multiplet_event.SetBdt(Bdt(multiplet_event, reader));
        return multiplet_event;
    }), 1);
}

std::vector<EventMultiplet<Decuplet55>> EventPairTagger::Events(Event const& event, std::function<EventMultiplet<Decuplet55>(EventMultiplet<Decuplet55> &)> const& function)
{
    INFO0;
    auto global_observables = global_reader_.Multiplets(event).front();
    std::vector<EventMultiplet<Decuplet55>> events;
    for (auto const & decuplet : signature_reader_.Multiplets(event)) {
        EventMultiplet<Decuplet55> multiplet_event(decuplet, global_observables);
        events.emplace_back(function(multiplet_event));
    }
    return events;
}

std::string EventPairTagger::Name() const
{
    return "EventPair";
}
std::string EventPairTagger::LatexName() const
{
    return "T_{h} T_{l}";
}

}

}
