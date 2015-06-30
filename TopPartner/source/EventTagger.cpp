#include "../include/EventTagger.hh"

namespace analysis {

namespace toppartner
{

EventTagger::EventTagger()
{
    Print(Severity::notification , "Constructor");
//     debug_level_ = Severity::debug;
    set_tagger_name("Event");
    signature_reader_.SetTagger(signature_tagger_);
    bottom_reader_.SetTagger(bottom_tagger_);
    DefineVariables();
}

int EventTagger::Train(Event &event, PreCuts &pre_cuts, const Tag tag)
{
  Print(Severity::information, "Train");
    Jets jets = bottom_reader_.Multiplets<BottomTagger>(event);
    std::vector<Quattuordecuplet> octets = signature_reader_.Multiplets<SignatureTagger>(event);
    Print(Severity::information, "Octets", octets.size());
    std::vector< MultipletEvent< Quattuordecuplet > > multipletevents;
    for (const auto octet : octets) {
        MultipletEvent< Quattuordecuplet > multipletevent(octet, event, jets);
        multipletevent.SetTag(tag);
        multipletevents.emplace_back(multipletevent);
    }
    return SaveEntries(ReduceResult(multipletevents, 1));
}

std::vector< MultipletEvent< Quattuordecuplet > > EventTagger::Multiplets(Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader)
{
  Print(Severity::information, "Multiplets");
    Jets jets = bottom_reader_.Multiplets<BottomTagger>(event);
    std::vector<Quattuordecuplet> octets = signature_reader_.Multiplets<SignatureTagger>(event);
    std::vector< MultipletEvent< Quattuordecuplet > > multiplet_events;
    for (const auto octet : octets) {
        MultipletEvent< Quattuordecuplet > multiplet_event(octet, event,jets);
        multiplet_event.SetBdt(Bdt(multiplet_event,reader));
        multiplet_events.emplace_back(multiplet_event);
    }
    return ReduceResult(multiplet_events);
}

}

}
