#include "EventSingleTagger.hh"
#include "Debug.hh"

namespace analysis
{

namespace toppartner
{

EventSingleTagger::EventSingleTagger()
{
    Note();
    DefineVariables();
}

int EventSingleTagger::Train(const Event &event, PreCuts &pre_cuts, const Tag tag) const
{
    Info();
    Jets jets = bottom_reader_.Multiplets(event);
    std::vector<Decuplet55> decuplets = signature_reader_.Multiplets(event);
    std::vector< MultipletEvent< Decuplet55 > > multipletevents;
    for (const auto & decuplet : decuplets) {
      MultipletEvent< Decuplet55 > multipletevent(decuplet, event, jets);
        multipletevent.SetTag(tag);
        multipletevents.emplace_back(multipletevent);
    }
    return SaveEntries(ReduceResult(multipletevents, 1));
}

std::vector< MultipletEvent< Decuplet55 > > EventSingleTagger::Multiplets(const analysis::Event &event, analysis::PreCuts &pre_cuts, const TMVA::Reader &reader) const
{
    Info();
    Jets jets = bottom_reader_.Multiplets(event);
    std::vector<Decuplet55> decuplets = signature_reader_.Multiplets(event);
    std::vector< MultipletEvent< Decuplet55 > > multiplet_events;
    for (const auto & decuplet : decuplets) {
      MultipletEvent< Decuplet55 > multiplet_event(decuplet, event, jets);
        multiplet_event.SetBdt(Bdt(multiplet_event, reader));
        multiplet_events.emplace_back(multiplet_event);
    }
    return ReduceResult(multiplet_events);
}

}

}
