#include "EventSingleLeptonicTagger.hh"
#include "Debug.hh"

namespace boca {

namespace naturalness {

int EventSingleLeptonicTagger::Train(Event const& event, PreCuts const&, Tag tag) const
{
    INFO0;
   std::vector<Jet> jets = bottom_reader_.Jets(event);
    std::vector<Decuplet532> decuplets = signature_reader_.Multiplets(event);
    std::vector<MultipletEvent<Decuplet532>> multipletevents;
    for (auto const& decuplet : decuplets) {
        MultipletEvent<Decuplet532> multipletevent(decuplet, event, jets);
        multipletevent.SetTag(tag);
        multipletevents.emplace_back(multipletevent);
    }
    return SaveEntries(ReduceResult(multipletevents, 1));
}

std::vector<MultipletEvent<Decuplet532>> EventSingleLeptonicTagger::Multiplets(boca::Event const& event, boca::PreCuts const&, TMVA::Reader const& reader) const
{
    INFO0;
   std::vector<Jet> jets = bottom_reader_.Jets(event);
    std::vector<Decuplet532> decuplets = signature_reader_.Multiplets(event);
    std::vector<MultipletEvent<Decuplet532>> multiplet_events;
    for (auto const& decuplet : decuplets) {
        MultipletEvent<Decuplet532> multiplet_event(decuplet, event, jets);
        multiplet_event.SetBdt(Bdt(multiplet_event, reader));
        multiplet_events.emplace_back(multiplet_event);
    }
    return ReduceResult(multiplet_events,1);
}
std::string EventSingleLeptonicTagger::Name() const
{
    return "EventSingle";
}

}

}
