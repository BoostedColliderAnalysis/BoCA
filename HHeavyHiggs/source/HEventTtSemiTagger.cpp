# include "HEventTtSemiTagger.hh"

hheavyhiggs::HEventTtSemiTagger::HEventTtSemiTagger()
{
    //   DebugLevel = HDebug;
    Print(HNotification , "Constructor");
    DefineVariables();
}

void hheavyhiggs::HEventTtSemiTagger::SetTagger(
    const hanalysis::HBottomTagger &NewBottomTagger,
    const hanalysis::HWSemiTagger &NewWSemiTagger,
    const hanalysis::HWHadronicTagger &NewWTagger,
    const hanalysis::HTopSemiTagger &NewTopSemiTagger,
    const hanalysis::HTopHadronicTagger &NewTopHadronicTagger,
    const hanalysis::HHeavyHiggsSemiTagger &NewHeavyHiggsSemiTagger)
{
    Print(HNotification , "Constructor");
    BottomTagger = NewBottomTagger;
    WSemiTagger = NewWSemiTagger;
    WTagger = NewWTagger;
    TopSemiTagger = NewTopSemiTagger;
    TopHadronicTagger = NewTopHadronicTagger;
    HeavyHiggsSemiTagger = NewHeavyHiggsSemiTagger;
    DefineVariables();
}

void hheavyhiggs::HEventTtSemiTagger::DefineVariables()
{
    Print(HNotification , "Define Variables");
    SetTaggerName("EventSemi");
    ClearVectors();

    AddObservable(Branch.LeptonNumber, "LeptonNumber");
    AddObservable(Branch.JetNumber, "JetNumber");
    AddObservable(Branch.BottomNumber, "BottomNumber");
    AddObservable(Branch.ScalarHt, "ScalarHt");

    AddObservable(Branch.Mass, "Mass");
    AddObservable(Branch.Pt, "Pt");
    AddObservable(Branch.Rap, "Rap");
    AddObservable(Branch.Phi, "Phi");
    AddObservable(Branch.Ht, "Ht");

    AddObservable(Branch.DeltaPt, "DeltaPt");
    AddObservable(Branch.DeltaRap, "DeltaRap");
    AddObservable(Branch.DeltaPhi, "DeltaPhi");
    AddObservable(Branch.DeltaR, "DeltaR");
    AddObservable(Branch.DeltaHt, "DeltaHt");
    AddObservable(Branch.DeltaM, "DeltaM");

    AddObservable(Branch.HiggsMass, "HiggsMass");
    AddObservable(Branch.HiggsBdt, "HiggsBdt");

    AddObservable(Branch.RestNumber, "RestNumber");
    AddObservable(Branch.RestM, "RestM");
    AddObservable(Branch.RestPt, "RestPt");
    AddObservable(Branch.RestHt, "RestHt");
    AddObservable(Branch.RestPhi, "RestPhi");
    AddObservable(Branch.RestRap, "RestRap");
    AddObservable(Branch.RestBdt, "RestBdt");
    AddObservable(Branch.LeptonHt, "LeptonHt");

    AddObservable(Branch.Bdt, "Bdt");
    AddSpectator(Branch.Tag, "Tag");


    Print(HNotification, "Variables defined");

}

hheavyhiggs::HEventTtSemiBranch hheavyhiggs::HEventTtSemiTagger::GetBranch(const HSextetEvent &Event) const
{
    Print(HInformation, "FillPairTagger", Event.Bdt());

    HEventTtSemiBranch EventSemiBranch;
    EventSemiBranch.LeptonNumber = Event.LeptonNumber();
    EventSemiBranch.JetNumber = Event.JetNumber();
    EventSemiBranch.BottomNumber = Event.BottomNumber();
    EventSemiBranch.ScalarHt = Event.ScalarHt();

    EventSemiBranch.Mass = Event.Jet().m();
    EventSemiBranch.Rap = Event.Jet().rap();
    EventSemiBranch.Phi = Event.Jet().phi();
    EventSemiBranch.Pt = Event.Jet().pt();
    EventSemiBranch.Ht = Event.Ht();

    EventSemiBranch.DeltaPt = Event.DeltaPt();
    EventSemiBranch.DeltaPhi = Event.DeltaPhi();
    EventSemiBranch.DeltaRap = Event.DeltaRap();
    EventSemiBranch.DeltaR = Event.DeltaR();
    EventSemiBranch.DeltaM = Event.DeltaM();
    EventSemiBranch.DeltaHt = Event.DeltaHt();

    EventSemiBranch.Bdt = Event.Bdt();
    EventSemiBranch.Tag = Event.Tag();

    EventSemiBranch.HiggsMass = Event.Sextet().Jet().m();
    EventSemiBranch.HiggsBdt = Event.Sextet().Bdt();

    EventSemiBranch.RestNumber = Event.RestNumber();
    EventSemiBranch.RestM = Event.RestJet().m();
    EventSemiBranch.RestPt = Event.RestJet().pt();
    EventSemiBranch.RestHt = Event.RestHt();
    EventSemiBranch.RestRap = Event.RestJet().rap();
    if (std::abs(EventSemiBranch.RestRap) > 100) EventSemiBranch.RestRap = 0;
    EventSemiBranch.RestPhi = Event.RestJet().phi();
    EventSemiBranch.RestBdt = Event.RestBdt();

    EventSemiBranch.LeptonHt = Event.LeptonHt();

    return EventSemiBranch;

}

struct SortJetsByBdt {
    inline bool operator()(const fastjet::PseudoJet &Jet1, const fastjet::PseudoJet &Jet2) {
        return (Jet1.user_info<hanalysis::HJetInfo>().Bdt() > Jet2.user_info<hanalysis::HJetInfo>().Bdt());
    }
};

std::vector<hheavyhiggs::HEventTtSemiBranch> hheavyhiggs::HEventTtSemiTagger::GetBranches(hanalysis::HEvent &Event, const HObject::Tag Tag)
{
    Print(HInformation, "Get Event Tags");

    HJets Jets = GetJets(Event);
    Jets = BottomTagger.GetJetBdt(Jets, BottomReader);
    HJets Leptons = Event.GetLeptons()->GetTaggedJets(JetTag);
    fastjet::PseudoJet MissingEt = Event.GetJets()->GetMissingEt();
    std::vector<hanalysis::HDoublet> DoubletsSemi = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);
    std::vector<hanalysis::HTriplet> TripletsSemi = TopSemiTagger.GetBdt(DoubletsSemi, Jets, TopSemiReader);

//     std::vector<hanalysis::HDoublet> DoubletsHadronic = WTagger.GetBdt(Jets, WReader);
//     std::vector<hanalysis::HTriplet> TripletsHadronic = TopHadronicTagger.GetBdt(DoubletsHadronic, Jets, TopHadronicReader);
    std::vector<hanalysis::HTriplet> TripletsHadronic = TopHadronicTagger.GetBdt(Jets, TopHadronicReader, WTagger, WReader, BottomTagger, BottomReader);

    std::vector<hanalysis::HSextet> Sextets = HeavyHiggsSemiTagger.GetBdt(TripletsSemi, TripletsHadronic, HeavyHiggsSemiReader);

    HJets HiggsParticles = Event.GetParticles()->Generator();
    HJets Even = RemoveIfWrongAbsFamily(HiggsParticles, HeavyHiggsId, GluonId);
    HJets Odd = RemoveIfWrongAbsFamily(HiggsParticles, CPOddHiggsId, GluonId);
    HiggsParticles = Even;
    HiggsParticles.insert(HiggsParticles.end(), Odd.begin(), Odd.end());
    fastjet::PseudoJet HiggsBoson;
    if (Tag == kSignal) {
      if (HiggsParticles.size() == 1) HiggsBoson = HiggsParticles.front();
      else Print(HError, "Where is the Higgs?", HiggsParticles.size());
      std::sort(Sextets.begin(), Sextets.end(), MinDeltaR(HiggsParticles.front()));
      if (Sextets.size() > 1) Sextets.erase(Sextets.begin() + 1, Sextets.end());
    }

    std::vector<hheavyhiggs::HEventTtSemiBranch> EventSemiBranches;
    if (Sextets.size() < 1) return EventSemiBranches;

    if (Tag == kSignal && Sextets.size() > 1) {
        Print(HError, "more than one event", Sextets.size());
        std::sort(Sextets.begin(), Sextets.end());
        Sextets.erase(Sextets.begin() + 1, Sextets.end());
    }

    HSextetEvent SextetEvent(Sextets.front());
    HEventStruct EventStruct;
    EventStruct.LeptonNumber = Event.GetLeptons()->GetLeptonJets().size();
    EventStruct.JetNumber = Event.GetJets()->GetJets().size();
    EventStruct.BottomNumber = Event.GetJets()->GetBottomJets().size();
    EventStruct.ScalarHt = Event.GetJets()->GetScalarHt();
    SextetEvent.SetEventStruct(EventStruct);
    SextetEvent.SetLeptons(Leptons);
    SextetEvent.SetTag(Tag);
    for (const auto & Jet : Jets) {
        if (Jet.delta_R(SextetEvent.Sextet().Triplet1().Singlet()) < DetectorGeometry.JetConeSize) continue;
        if (Jet.delta_R(SextetEvent.Sextet().Triplet2().Singlet()) < DetectorGeometry.JetConeSize) continue;
        if (Jet.delta_R(SextetEvent.Sextet().Triplet2().Doublet().Singlet1()) < DetectorGeometry.JetConeSize) continue;
        if (Jet.delta_R(SextetEvent.Sextet().Triplet2().Doublet().Singlet2()) < DetectorGeometry.JetConeSize) continue;
        SextetEvent.AddRestJet(Jet);
    }

    EventSemiBranches.push_back(GetBranch(SextetEvent));
    return EventSemiBranches;
}

std::vector<HSextetEvent> hheavyhiggs::HEventTtSemiTagger::GetBdt(const std::vector< hanalysis::HSextet > &Sextets, HJets &Jets, const HJets &Leptons, HEventStruct &EventStruct, const hanalysis::HReader &EventSemiReader)
{
    Print(HInformation, "Get Event Tags");

    std::vector<HSextetEvent> SextetEvents;
    for (const auto & Sextet : Sextets) {
        HSextetEvent SextetEvent(Sextet, EventStruct);
        for (const auto & Jet : Jets) {
          if (Jet.delta_R(SextetEvent.Sextet().Triplet1().Singlet()) < DetectorGeometry.JetConeSize) continue;
          if (Jet.delta_R(SextetEvent.Sextet().Triplet2().Singlet()) < DetectorGeometry.JetConeSize) continue;
          if (Jet.delta_R(SextetEvent.Sextet().Triplet2().Doublet().Singlet1()) < DetectorGeometry.JetConeSize) continue;
          if (Jet.delta_R(SextetEvent.Sextet().Triplet2().Doublet().Singlet2()) < DetectorGeometry.JetConeSize) continue;
            SextetEvent.AddRestJet(Jet);
        }
        SextetEvent.SetLeptons(Leptons);
        Branch = GetBranch(SextetEvent);
        SextetEvent.SetBdt(EventSemiReader.Bdt());
        SextetEvents.push_back(SextetEvent);
    }

    std::sort(SextetEvents.begin(), SextetEvents.end());
    if (SextetEvents.size() > 1)SextetEvents.erase(SextetEvents.begin() + 1, SextetEvents.end());
    Print(HInformation, "Event Number", SextetEvents.size(), Jets.size());
    return SextetEvents;
}

float hheavyhiggs::HEventTtSemiTagger::ReadBdt(const TClonesArray &EventClonesArray, const int Entry){
  return ((HEventTtSemiBranch *) EventClonesArray.At(Entry))->Bdt;
}
