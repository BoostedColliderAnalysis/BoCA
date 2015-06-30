#include "EventChargedTagger.hh"
#include "Debug.hh"

namespace analysis
{

namespace heavyhiggs {

EventChargedTagger::EventChargedTagger()
{
    Info("Constructor");
    set_tagger_name("ChargedeventSemi");
    bottom_reader_.SetTagger(bottom_tagger_);
    signature_semi_reader_.SetTagger(signature_semi_tagger_);
    DefineVariables();
}

int EventChargedTagger::Train(Event &event, const Tag tag)
{
    Info("event Tags");

    Jets jets = bottom_reader_.Multiplets<BottomTagger>(event);
    Jets Leptons = event.Leptons().leptons();
    std::vector<Octet44> octets = signature_semi_reader_.Multiplets<SignatureChargedTagger>(event);

    std::vector<MultipletEvent<Octet44>> events;
    for (const auto & octet : octets) {
      MultipletEvent<Octet44> octetevent(octet,event,jets);
        octetevent.SetTag(tag);
        events.emplace_back(octetevent);
    }
    return SaveEntries(ReduceResult(events,1));
}


std::vector<MultipletEvent<Octet44>> EventChargedTagger::Multiplets(Event &event, const TMVA::Reader &reader)
{
  Info("event Tags");
  Jets jets = bottom_reader_.Multiplets<BottomTagger>(event);
    std::vector<Octet44> octets = signature_semi_reader_.Multiplets<SignatureChargedTagger>(event);
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
