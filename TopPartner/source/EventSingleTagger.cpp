# include "EventSingleTagger.hh"

namespace analysis {

namespace toppartner
{

EventSingleTagger::EventSingleTagger()
{
    Print(kNotification , "Constructor");
//     debug_level_ = kDebug;
    set_tagger_name("EventSingle");
    signature_reader_.SetTagger(signature_tagger_);
    bottom_reader_.SetTagger(bottom_tagger_);
    DefineVariables();
}

int EventSingleTagger::Train(Event &event, PreCuts &pre_cuts, const Tag tag)
{
  Print(kInformation, "Train");
    Jets jets = bottom_reader_.Multiplets<BottomTagger>(event);
    std::vector<Decuplet73> decuplets = signature_reader_.Multiplets<SignatureSingleTagger>(event);
    Print(kInformation, "Octets", decuplets.size());
    std::vector< MultipletEvent< Decuplet73 > > multipletevents;
    for (const auto decuplet : decuplets) {
        MultipletEvent< Decuplet73 > multipletevent(decuplet, event, jets);
        multipletevent.SetTag(tag);
        multipletevents.emplace_back(multipletevent);
    }
    return SaveEntries(ReduceResult(multipletevents, 1));
}

std::vector< MultipletEvent< Decuplet73 > > EventSingleTagger::Multiplets(Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader)
{
  Print(kInformation, "Multiplets");
    Jets jets = bottom_reader_.Multiplets<BottomTagger>(event);
    std::vector<Decuplet73> decuplets = signature_reader_.Multiplets<SignatureSingleTagger>(event);
    std::vector< MultipletEvent< Decuplet73 > > multiplet_events;
    for (const auto decuplet : decuplets) {
        MultipletEvent< Decuplet73 > multiplet_event(decuplet, event,jets);
        multiplet_event.SetBdt(Bdt(multiplet_event,reader));
        multiplet_events.emplace_back(multiplet_event);
    }
    return ReduceResult(multiplet_events);
}

}

}
