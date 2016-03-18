#include "EventNewPairTagger.hh"
// #define DEBUGGING
#include "DEBUG.hh"

namespace boca
{

namespace naturalness
{

int EventNewPairTagger::Train(Event const& event, PreCuts const&, Tag tag) const
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

std::vector<MultipletEvent<Decuplet55>> EventNewPairTagger::Multiplets(boca::Event const& event, boca::PreCuts const&, TMVA::Reader const& reader) const
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
std::string EventNewPairTagger::Name() const
{
    return "EventPair";
}
std::string EventNewPairTagger::LatexName() const
{
    return "T_{h} T_{l}";
}

}

}
