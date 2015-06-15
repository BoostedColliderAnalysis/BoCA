# include "EventFusionTagger.hh"

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

void EventFusionTagger::DefineVariables()
{
    Print(kNotification , "Define Variables");
    AddVariable(branch().LeptonNumber, "LeptonNumber");
    AddVariable(branch().JetNumber, "JetNumber");
    AddVariable(branch().BottomNumber, "BottomNumber");
    AddVariable(branch().ScalarHt, "ScalarHt");

    AddVariable(branch().Mass, "Mass");
    AddVariable(branch().Pt, "Pt");
    AddVariable(branch().Rap, "Rap");
    AddVariable(branch().Phi, "Phi");
    AddVariable(branch().Ht, "Ht");

    AddVariable(branch().DeltaPt, "DeltaPt");
    AddVariable(branch().DeltaRap, "DeltaRap");
    AddVariable(branch().DeltaPhi, "DeltaPhi");
    AddVariable(branch().DeltaR, "DeltaR");
    AddVariable(branch().DeltaHt, "DeltaHt");
    AddVariable(branch().DeltaM, "DeltaM");

    AddVariable(branch().HiggsMass, "HiggsMass");
    AddVariable(branch().HiggsBdt, "HiggsBdt");

    AddVariable(branch().RestNumber, "RestNumber");
    AddVariable(branch().RestM, "RestM");
    AddVariable(branch().RestPt, "RestPt");
    AddVariable(branch().RestHt, "RestHt");
    AddVariable(branch().RestPhi, "RestPhi");
    AddVariable(branch().RestRap, "RestRap");
    AddVariable(branch().RestBdt, "RestBdt");
    AddVariable(branch().LeptonHt, "LeptonHt");

    AddVariable(branch().Bdt, "Bdt");
    AddSpectator(branch().Tag, "Tag");
}

int EventFusionTagger::Train(analysis::Event &event, const Tag tag)
{
    Print(kInformation, "event Tags");

    analysis::Jets jets = bottom_reader_.Multiplets<analysis::BottomTagger>(event);
    analysis::Jets leptons = event.Leptons().leptons();
    std::vector<analysis::Sextet> sextets = heavy_higgs_semi_reader_.Multiplets<HeavyHiggsSemiTagger>(event);

    analysis::Jets HiggsParticles = event.Partons().GenParticles();
    analysis::Jets Even = RemoveIfWrongAbsFamily(HiggsParticles, HeavyHiggsId, GluonId);
    analysis::Jets Odd = RemoveIfWrongAbsFamily(HiggsParticles, CPOddHiggsId, GluonId);
    HiggsParticles = Even;
    HiggsParticles.insert(HiggsParticles.end(), Odd.begin(), Odd.end());
    fastjet::PseudoJet HiggsBoson;
    if (tag == kSignal) {
        if (HiggsParticles.size() == 1) HiggsBoson = HiggsParticles.front();
        else Print(kError, "Where is the Higgs?", HiggsParticles.size());
        std::sort(sextets.begin(), sextets.end(), analysis::MinDeltaRTo(HiggsParticles.front()));
        if (sextets.size() > 1) sextets.erase(sextets.begin() + 1, sextets.end());
    }

//     std::vector<EventFusionBranch> eventSemiBranches;
    if (sextets.empty()) return 0;

    if (tag == kSignal && sextets.size() > 1) {
        Print(kError, "more than one event", sextets.size());
        std::sort(sextets.begin(), sextets.end());
        sextets.erase(sextets.begin() + 1, sextets.end());
    }

    analysis::MultipletEvent<analysis::Sextet> sextet_event(sextets.front(),event,jets);
    sextet_event.SetTag(tag);
    std::vector<analysis::MultipletEvent<analysis::Sextet>> sextet_events;
    sextet_events.emplace_back(sextet_event);
    return SaveEntries(sextet_events);
}

std::vector<analysis::MultipletEvent<analysis::Sextet>> EventFusionTagger::Multiplets(analysis::Event &event, TMVA::Reader &reader)
{
  Print(kInformation, "event Tags");
  std::vector<analysis::Sextet> sextets = heavy_higgs_semi_reader_.Multiplets<HeavyHiggsSemiTagger>(event);

  analysis::Jets jets = bottom_reader_.Multiplets<analysis::BottomTagger>(event);
  analysis::Jets Leptons = event.Leptons().leptons();
    std::vector<analysis::MultipletEvent<analysis::Sextet>> sextet_events;
    for (const auto & sextet : sextets) {
      analysis::MultipletEvent<analysis::Sextet> multiplet_event(sextet, event,jets);
      multiplet_event.SetBdt(Bdt(multiplet_event,reader));
        sextet_events.emplace_back(multiplet_event);
    }
    return ReduceResult(sextet_events);
}

}
