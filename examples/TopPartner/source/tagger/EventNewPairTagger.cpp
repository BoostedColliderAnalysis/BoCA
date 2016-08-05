#include "include/tagger/EventNewPairTagger.hh"
// #define DEBUGGING
#include "boca/generic/DEBUG.hh"

namespace toppartner
{

int EventNewPairTagger::Train(boca::Event const& event, PreCuts const&, Tag tag)
{
    INFO0;
    auto jets = bottom_reader_.Jets(event);
    std::vector<MultipletEvent<Decuplet55>> multipletevents;
    for (auto const & decuplet : signature_reader_.Multiplets(event)) {
        MultipletEvent<Decuplet55> multipletevent(decuplet, event, jets);
        multipletevent.SetTag(tag);
        multipletevents.emplace_back(multipletevent);
    }
    return SaveEntries(multipletevents, tag);
}

std::vector<MultipletEvent<Decuplet55>> EventNewPairTagger::Multiplets(boca::Event const& event, boca::PreCuts const&, TMVA::Reader const& reader)
{
    INFO0;
    auto jets = bottom_reader_.Jets(event);
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
latex::String EventNewPairTagger::LatexName() const
{
    return "T_{h} T_{l}";
}

}
