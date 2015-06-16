# include "../include/EventTagger.hh"

namespace analysis
{

namespace higgscpv
{

EventTagger::EventTagger()
{
    Print(kNotification , "Constructor");
//     debug_level_ = kDebug;
    set_tagger_name("Event");
    signature_reader_.set_tagger(signature_tagger_);
    bottom_reader_.set_tagger(bottom_tagger_);
    DefineVariables();
}

int EventTagger::Train(Event &event, PreCuts &pre_cuts, const Tag tag)
{
  Print(kInformation, "Train");
    Jets jets = bottom_reader_.Multiplets<BottomTagger>(event);
    std::vector<Octet62> octets = signature_reader_.Multiplets<SignatureTagger>(event);
    Print(kInformation, "Octets", octets.size());
    std::vector< MultipletEvent< Octet62 > > multipletevents;
    for (const auto octet : octets) {
        MultipletEvent< Octet62 > multipletevent(octet, event, jets);
        multipletevent.SetTag(tag);
        multipletevents.emplace_back(multipletevent);
    }
    return SaveEntries(ReduceResult(multipletevents, 1));
}

std::vector< MultipletEvent< Octet62 > > EventTagger::Multiplets(Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader)
{
  Print(kInformation, "Multiplets");
    Jets jets = bottom_reader_.Multiplets<BottomTagger>(event);
    std::vector<Octet62> octets = signature_reader_.Multiplets<SignatureTagger>(event);
    std::vector< MultipletEvent< Octet62 > > multiplet_events;
    for (const auto octet : octets) {
        MultipletEvent< Octet62 > multiplet_event(octet, event,jets);
        multiplet_event.SetBdt(Bdt(multiplet_event,reader));
        multiplet_events.emplace_back(multiplet_event);
    }
    return ReduceResult(multiplet_events);
}

}

}
