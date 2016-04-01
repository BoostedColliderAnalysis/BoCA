#include "EventPairTagger.hh"
// #define DEBUGGING
#include "generic/DEBUG.hh"

namespace boca
{

namespace naturalness
{

int EventPairTagger::Train(Event const& event, PreCuts const&, Tag tag) const
{
    INFO0;
    std::vector<Jet> jets = bottom_reader_.Jets(event);
    std::vector<MultipletEvent<Decuplet55>> multipletevents;
    for (auto const & decuplet : signature_reader_.Multiplets(event)) {
        MultipletEvent<Decuplet55> multipletevent(decuplet, event, jets);
        multipletevent.SetTag(tag);
        multipletevents.emplace_back(multipletevent);
    }
    return SaveEntries(multipletevents, tag);
}

std::vector<MultipletEvent<Decuplet55>> EventPairTagger::Multiplets(boca::Event const& event, boca::PreCuts const&, TMVA::Reader const& reader) const
{
    INFO0;
    std::vector<Jet> jets = bottom_reader_.Jets(event);
    std::vector<MultipletEvent<Decuplet55>> multiplet_events;
    for (auto const & decuplet : signature_reader_.Multiplets(event)) {
        MultipletEvent<Decuplet55> multiplet_event(decuplet, event, jets);
        multiplet_event.SetBdt(Bdt(multiplet_event, reader));
        multiplet_events.emplace_back(multiplet_event);
    }
    return ReduceResult(multiplet_events, 1);
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
