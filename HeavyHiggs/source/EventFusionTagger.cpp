# include "EventFusionTagger.hh"

namespace analysis
{

namespace heavyhiggs {

EventFusionTagger::EventFusionTagger()
{
    //   DebugLevel = kDebug;
    Print(kNotification , "Constructor");
    set_tagger_name("EventFusion");
    bottom_reader_.set_tagger(bottom_tagger_);
    heavy_higgs_semi_reader_.set_tagger(heavy_higgs_semi_tagger_);
    DefineVariables();
}

int EventFusionTagger::Train(Event &event, const Tag tag)
{
    Print(kInformation, "event Tags");

    Jets jets = bottom_reader_.Multiplets<BottomTagger>(event);
    Jets leptons = event.Leptons().leptons();
    std::vector<Sextet> sextets = heavy_higgs_semi_reader_.Multiplets<HeavyHiggsSemiTagger>(event);

    Jets HiggsParticles = event.Partons().GenParticles();
    Jets Even = RemoveIfWrongAbsFamily(HiggsParticles, HeavyHiggsId, GluonId);
    Jets Odd = RemoveIfWrongAbsFamily(HiggsParticles, CPOddHiggsId, GluonId);
    HiggsParticles = Even;
    HiggsParticles.insert(HiggsParticles.end(), Odd.begin(), Odd.end());
    fastjet::PseudoJet HiggsBoson;
    if (tag == kSignal) {
        if (HiggsParticles.size() == 1) HiggsBoson = HiggsParticles.front();
        else Print(kError, "Where is the Higgs?", HiggsParticles.size());
        std::sort(sextets.begin(), sextets.end(), MinDeltaRTo(HiggsParticles.front()));
        if (sextets.size() > 1) sextets.erase(sextets.begin() + 1, sextets.end());
    }

//     std::vector<EventFusionBranch> eventSemiBranches;
    if (sextets.empty()) return 0;

    if (tag == kSignal && sextets.size() > 1) {
        Print(kError, "more than one event", sextets.size());
        std::sort(sextets.begin(), sextets.end());
        sextets.erase(sextets.begin() + 1, sextets.end());
    }

    MultipletEvent<Sextet> sextet_event(sextets.front(),event,jets);
    sextet_event.SetTag(tag);
    std::vector<MultipletEvent<Sextet>> sextet_events;
    sextet_events.emplace_back(sextet_event);
    return SaveEntries(sextet_events);
}

std::vector<MultipletEvent<Sextet>> EventFusionTagger::Multiplets(Event &event, TMVA::Reader &reader)
{
  Print(kInformation, "event Tags");
  std::vector<Sextet> sextets = heavy_higgs_semi_reader_.Multiplets<HeavyHiggsSemiTagger>(event);

  Jets jets = bottom_reader_.Multiplets<BottomTagger>(event);
  Jets Leptons = event.Leptons().leptons();
    std::vector<MultipletEvent<Sextet>> sextet_events;
    for (const auto & sextet : sextets) {
      MultipletEvent<Sextet> multiplet_event(sextet, event,jets);
      multiplet_event.SetBdt(Bdt(multiplet_event,reader));
        sextet_events.emplace_back(multiplet_event);
    }
    return ReduceResult(sextet_events);
}

}

}
