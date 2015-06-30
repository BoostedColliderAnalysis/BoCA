#include "EventNeutralTagger.hh"
#include "Debug.hh"

namespace analysis
{

namespace heavyhiggs {

EventNeutralTagger::EventNeutralTagger()
{
    //   DebugLevel = Severity::debug;
    Note("Constructor");
    set_tagger_name("EventNeutral");
    bottom_reader_.SetTagger(bottom_tagger_);
    signature_neutral_reader_.SetTagger(signature_neutral_tagger_);
    DefineVariables();
}

int EventNeutralTagger::Train(Event &event, const Tag tag)
{
    Info("event Tags");

    Jets jets = bottom_reader_.Multiplets<BottomTagger>(event);
    Jets leptons = event.Leptons().leptons();

    std::vector<Octet62> octets = signature_neutral_reader_.Multiplets<SignatureNeutralTagger>(event);

    std::vector<MultipletEvent<Octet62>> events;
    for (const auto & octet : octets) {
      MultipletEvent<Octet62> octetevent(octet,event,jets);
        octetevent.SetTag(tag);
        events.emplace_back(octetevent);
    }
    return SaveEntries(events);
}

std::vector<MultipletEvent<Octet62>> EventNeutralTagger::Multiplets(Event &event, const TMVA::Reader &reader)
{
    Info("event Tags");
    std::vector<Octet62> octets = signature_neutral_reader_.Multiplets<SignatureNeutralTagger>(event);


    Jets jets = bottom_reader_.Multiplets<BottomTagger>(event);
    Jets Leptons = event.Leptons().leptons();

    std::vector<MultipletEvent<Octet62>> multiplet_events;
    for (const auto & octet : octets) {
        MultipletEvent<Octet62> multiplet_event(octet, event,jets);
        multiplet_event.SetBdt(Bdt(multiplet_event,reader));
        multiplet_events.emplace_back(multiplet_event);
    }

    std::sort(multiplet_events.begin(), multiplet_events.end());
    if (multiplet_events.size() > 1) multiplet_events.erase(multiplet_events.begin() + 1, multiplet_events.end());
    Info("event Number", multiplet_events.size(), jets.size());
    return multiplet_events;
}

}

}
