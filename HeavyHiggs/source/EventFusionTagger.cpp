#include "EventFusionTagger.hh"
#include "Debug.hh"

namespace analysis
{

namespace heavyhiggs {

EventFusionTagger::EventFusionTagger()
{
    Note();
    set_tagger_name("EventFusion");
    DefineVariables();
}

int EventFusionTagger::Train(const Event &event,PreCuts &pre_cuts, const Tag tag) const
{
    Info("event Tags");

    Jets jets = bottom_reader_.Multiplets(event);
    Jets leptons = event.Leptons().leptons();
    std::vector<Sextet> sextets = heavy_higgs_semi_reader_.Multiplets(event);

    Jets HiggsParticles = event.Partons().GenParticles();
    Jets Even = RemoveIfWrongAbsFamily(HiggsParticles, Id::heavy_higgs, Id::gluon);
    Jets Odd = RemoveIfWrongAbsFamily(HiggsParticles, Id::CP_odd_higgs, Id::gluon);
    HiggsParticles = Even;
    HiggsParticles.insert(HiggsParticles.end(), Odd.begin(), Odd.end());
    fastjet::PseudoJet HiggsBoson;
    if (tag == Tag::signal) {
        if (HiggsParticles.size() == 1) HiggsBoson = HiggsParticles.front();
        else Error("Where is the Higgs?", HiggsParticles.size());
        std::sort(sextets.begin(), sextets.end(), MinDeltaRTo(HiggsParticles.front()));
        if (sextets.size() > 1) sextets.erase(sextets.begin() + 1, sextets.end());
    }

//     std::vector<EventFusionBranch> eventSemiBranches;
    if (sextets.empty()) return 0;

    if (tag == Tag::signal && sextets.size() > 1) {
        Error("more than one event", sextets.size());
        std::sort(sextets.begin(), sextets.end());
        sextets.erase(sextets.begin() + 1, sextets.end());
    }

    MultipletEvent<Sextet> sextet_event(sextets.front(),event,jets);
    sextet_event.SetTag(tag);
    std::vector<MultipletEvent<Sextet>> sextet_events;
    sextet_events.emplace_back(sextet_event);
    return SaveEntries(sextet_events);
}

std::vector<MultipletEvent<Sextet>> EventFusionTagger::Multiplets(const Event &event, TMVA::Reader &reader)
{
  Info("event Tags");
  std::vector<Sextet> sextets = heavy_higgs_semi_reader_.Multiplets(event);

  Jets jets = bottom_reader_.Multiplets(event);
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
