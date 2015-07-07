#include "EventChargedTagger.hh"
#include "Debug.hh"

namespace analysis
{

namespace heavyhiggs {

EventChargedTagger::EventChargedTagger()
{
    Info();
    DefineVariables();
}

int EventChargedTagger::Train(const analysis::Event &event, analysis::PreCuts &pre_cuts, const analysis::Tag tag) const
{
    Info("event Tags");

    Jets jets = bottom_reader_.Multiplets(event);
    Jets Leptons = event.Leptons().leptons();
    std::vector<Octet44> octets = signature_semi_reader_.Multiplets(event);

    std::vector<MultipletEvent<Octet44>> events;
    for (const auto & octet : octets) {
      MultipletEvent<Octet44> octetevent(octet,event,jets);
        octetevent.SetTag(tag);
        events.emplace_back(octetevent);
    }
    return SaveEntries(ReduceResult(events,1));
}


std::vector<MultipletEvent<Octet44>> EventChargedTagger::Multiplets(const Event &event, const TMVA::Reader &reader) const
{
  Info("event Tags");
  Jets jets = bottom_reader_.Multiplets(event);
    std::vector<Octet44> octets = signature_semi_reader_.Multiplets(event);
    std::vector<MultipletEvent<Octet44>> multiplet_events;
    for (auto & octet : octets) {
        MultipletEvent<Octet44> multiplet_event(octet, event,jets);
        multiplet_event.SetBdt(Bdt(multiplet_event,reader));
        multiplet_events.emplace_back(multiplet_event);
    }
    return ReduceResult(multiplet_events,1);
}

}

}
