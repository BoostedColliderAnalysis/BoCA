#include "EventSingleTagger.hh"
#include "Debug.hh"

namespace analysis {

namespace toppartner {

EventSingleTagger::EventSingleTagger()
{
  Info();
    DefineVariables();
}

int EventSingleTagger::Train(const Event& event, const PreCuts&, Tag tag) const
{
    Info();
    Jets jets = bottom_reader_.Multiplets(event);
    std::vector<Decuplet82> decuplets = signature_reader_.Multiplets(event);
    std::vector<MultipletEvent<Decuplet82>> multipletevents;
    for (const auto& decuplet : decuplets) {
        MultipletEvent<Decuplet82> multipletevent(decuplet, event, jets);
        multipletevent.SetTag(tag);
        multipletevents.emplace_back(multipletevent);
    }
    return SaveEntries(ReduceResult(multipletevents, 1));
}

std::vector<MultipletEvent<Decuplet82>> EventSingleTagger::Multiplets(const analysis::Event& event, const analysis::PreCuts&, const TMVA::Reader& reader) const
{
    Info();
    Jets jets = bottom_reader_.Multiplets(event);
    std::vector<Decuplet82> decuplets = signature_reader_.Multiplets(event);
    std::vector<MultipletEvent<Decuplet82>> multiplet_events;
    for (const auto& decuplet : decuplets) {
        MultipletEvent<Decuplet82> multiplet_event(decuplet, event, jets);
        multiplet_event.SetBdt(Bdt(multiplet_event, reader));
        multiplet_events.emplace_back(multiplet_event);
    }
    return ReduceResult(multiplet_events,1);
}

}

}
