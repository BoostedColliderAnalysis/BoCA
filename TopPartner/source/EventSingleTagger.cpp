#include "EventSingleTagger.hh"
#include "Debug.hh"

namespace analysis
{

namespace toppartner
{

EventSingleTagger::EventSingleTagger()
{
    Note();
    set_tagger_name("EventSingle");
    signature_reader_.SetTagger(signature_tagger_);
    bottom_reader_.SetTagger(bottom_tagger_);
    DefineVariables();
}

int EventSingleTagger::Train(const Event &event, PreCuts &pre_cuts, const Tag tag)
{
    Info("Train");
    Jets jets = bottom_reader_.Multiplets<BottomTagger>(event);
    std::vector<Nonet> nonets = signature_reader_.Multiplets<TopPartnerLeptonicPairTagger>(event);
    std::vector< MultipletEvent< Nonet > > multipletevents;
    for (const auto nonet : nonets) {
        MultipletEvent< Nonet > multipletevent(nonet, event, jets);
        multipletevent.SetTag(tag);
        multipletevents.emplace_back(multipletevent);
    }
    return SaveEntries(ReduceResult(multipletevents, 1));
}

std::vector< MultipletEvent< Nonet > > EventSingleTagger::Multiplets(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader)
{
    Info("Multiplets");
    Jets jets = bottom_reader_.Multiplets<BottomTagger>(event);
    std::vector<Nonet> nonets = signature_reader_.Multiplets<TopPartnerLeptonicPairTagger>(event);
    std::vector< MultipletEvent< Nonet > > multiplet_events;
    for (const auto nonet : nonets) {
        MultipletEvent< Nonet > multiplet_event(nonet, event, jets);
        multiplet_event.SetBdt(Bdt(multiplet_event, reader));
        multiplet_events.emplace_back(multiplet_event);
    }
    return ReduceResult(multiplet_events);
}

}

}
