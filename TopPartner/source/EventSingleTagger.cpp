#include "EventSingleTagger.hh"
#include "Debug.hh"

namespace boca {

namespace toppartner {

EventSingleTagger::EventSingleTagger()
{
  Info();
    DefineVariables();
}

int EventSingleTagger::Train(Event const& event, PreCuts const&, Tag tag) const
{
    Info();
    Jets jets = bottom_reader_.Multiplets(event);
    std::vector<Decuplet82> decuplets = signature_reader_.Multiplets(event);
    std::vector<MultipletEvent<Decuplet82>> multipletevents;
    for (auto const& decuplet : decuplets) {
        MultipletEvent<Decuplet82> multipletevent(decuplet, event, jets);
        multipletevent.SetTag(tag);
        multipletevents.emplace_back(multipletevent);
    }
    return SaveEntries(ReduceResult(multipletevents, 1));
}

std::vector<MultipletEvent<Decuplet82>> EventSingleTagger::Multiplets(boca::Event const& event, boca::PreCuts const&, TMVA::Reader const& reader) const
{
    Info();
    Jets jets = bottom_reader_.Multiplets(event);
    std::vector<Decuplet82> decuplets = signature_reader_.Multiplets(event);
    std::vector<MultipletEvent<Decuplet82>> multiplet_events;
    for (auto const& decuplet : decuplets) {
        MultipletEvent<Decuplet82> multiplet_event(decuplet, event, jets);
        multiplet_event.SetBdt(Bdt(multiplet_event, reader));
        multiplet_events.emplace_back(multiplet_event);
    }
    return ReduceResult(multiplet_events,1);
}

}

}
