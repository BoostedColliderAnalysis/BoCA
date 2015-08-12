#include "EventPairTagger.hh"
#define DEBUG
#include "Debug.hh"

namespace analysis {

namespace toppartner {

EventPairTagger::EventPairTagger()
{
    Info();
    DefineVariables();
}

int EventPairTagger::Train(Event const& event, PreCuts const&, Tag tag) const
{
    Info();
    Jets jets = bottom_reader_.Multiplets(event);
    std::vector<Decuplet55> decuplets = signature_reader_.Multiplets(event);
    std::vector<MultipletEvent<Decuplet55>> multipletevents;
    for (auto const& decuplet : decuplets) {
        MultipletEvent<Decuplet55> multipletevent(decuplet, event, jets);
        multipletevent.SetTag(tag);
        multipletevents.emplace_back(multipletevent);
    }
    return SaveEntries(ReduceResult(multipletevents, 1));
}

std::vector<MultipletEvent<Decuplet55>> EventPairTagger::Multiplets(analysis::Event const& event, analysis::PreCuts const&, TMVA::Reader const& reader) const
{
    Info();
    Jets jets = bottom_reader_.Multiplets(event);
    std::vector<Decuplet55> decuplets = signature_reader_.Multiplets(event);
    std::vector<MultipletEvent<Decuplet55>> multiplet_events;
    for (auto const& decuplet : decuplets) {
        MultipletEvent<Decuplet55> multiplet_event(decuplet, event, jets);
        multiplet_event.SetBdt(Bdt(multiplet_event, reader));
        multiplet_events.emplace_back(multiplet_event);
    }
    return ReduceResult(multiplet_events,1);
}

}

}
