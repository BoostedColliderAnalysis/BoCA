# include "HEventTtSemiTagger.hh"

hheavyhiggs::HEventTtSemiTagger::HEventTtSemiTagger()
{
    //   DebugLevel = kDebug;
    Print(kNotification , "Constructor");
    DefineVariables();
}

void hheavyhiggs::HEventTtSemiTagger::SetTagger(
    const hanalysis::BottomTagger &NewBottomTagger,
    const hanalysis::HWSemiTagger &NewWSemiTagger,
    const hanalysis::HWHadronicTagger &NewWTagger,
    const hanalysis::HTopSemiTagger &NewTopSemiTagger,
    const hanalysis::HTopHadronicTagger &NewTopHadronicTagger,
    const hanalysis::HHeavyHiggsSemiTagger &NewHeavyHiggsSemiTagger)
{
    Print(kNotification , "Constructor");
    bottom_tagger_ = NewBottomTagger;
    WSemiTagger = NewWSemiTagger;
    WTagger = NewWTagger;
    TopSemiTagger = NewTopSemiTagger;
    TopHadronicTagger = NewTopHadronicTagger;
    HeavyHiggsSemiTagger = NewHeavyHiggsSemiTagger;
    DefineVariables();
}

void hheavyhiggs::HEventTtSemiTagger::DefineVariables()
{
    Print(kNotification , "Define Variables");
    set_tagger_name("EventSemi");
    ClearVectors();

    AddVariable(Branch.LeptonNumber, "LeptonNumber");
    AddVariable(Branch.JetNumber, "JetNumber");
    AddVariable(Branch.BottomNumber, "BottomNumber");
    AddVariable(Branch.ScalarHt, "ScalarHt");

    AddVariable(Branch.Mass, "Mass");
    AddVariable(Branch.Pt, "Pt");
    AddVariable(Branch.Rap, "Rap");
    AddVariable(Branch.Phi, "Phi");
    AddVariable(Branch.Ht, "Ht");

    AddVariable(Branch.DeltaPt, "DeltaPt");
    AddVariable(Branch.DeltaRap, "DeltaRap");
    AddVariable(Branch.DeltaPhi, "DeltaPhi");
    AddVariable(Branch.DeltaR, "DeltaR");
    AddVariable(Branch.DeltaHt, "DeltaHt");
    AddVariable(Branch.DeltaM, "DeltaM");

    AddVariable(Branch.HiggsMass, "HiggsMass");
    AddVariable(Branch.HiggsBdt, "HiggsBdt");

    AddVariable(Branch.RestNumber, "RestNumber");
    AddVariable(Branch.RestM, "RestM");
    AddVariable(Branch.RestPt, "RestPt");
    AddVariable(Branch.RestHt, "RestHt");
    AddVariable(Branch.RestPhi, "RestPhi");
    AddVariable(Branch.RestRap, "RestRap");
    AddVariable(Branch.RestBdt, "RestBdt");
    AddVariable(Branch.LeptonHt, "LeptonHt");

    AddVariable(Branch.Bdt, "Bdt");
    AddSpectator(Branch.Tag, "Tag");


    Print(kNotification, "Variables defined");

}

hheavyhiggs::HEventTtSemiBranch hheavyhiggs::HEventTtSemiTagger::GetBranch(const HSextetEvent &Event) const
{
    Print(kInformation, "FillPairTagger", Event.Bdt());

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
        return (Jet1.user_info<hanalysis::JetInfo>().Bdt() > Jet2.user_info<hanalysis::JetInfo>().Bdt());
    }
};

std::vector<hheavyhiggs::HEventTtSemiBranch> hheavyhiggs::HEventTtSemiTagger::GetBranches(hanalysis::HEvent &Event, const HObject::Tag Tag)
{
    Print(kInformation, "Get Event Tags");

    Jets jets = GetJets(Event);
    jets = bottom_tagger_.GetJetBdt(jets, BottomReader.reader());
    Jets Leptons = Event.GetLeptons()->GetTaggedJets(JetTag);
    fastjet::PseudoJet MissingEt = Event.GetJets()->GetMissingEt();
    std::vector<hanalysis::Doublet> doubletsSemi = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader.reader());
    std::vector<hanalysis::Triplet> tripletsSemi = TopSemiTagger.GetBdt(doubletsSemi, jets, TopSemiReader);

//     std::vector<hanalysis::Doublet> doubletsHadronic = WTagger.GetBdt(jets, WReader);
//     std::vector<hanalysis::Triplet> tripletsHadronic = TopHadronicTagger.GetBdt(doubletsHadronic, jets, TopHadronicReader);
    std::vector<hanalysis::Triplet> tripletsHadronic = TopHadronicTagger.GetBdt(jets, TopHadronicReader, WTagger, WReader, bottom_tagger_, BottomReader);

    std::vector<hanalysis::HSextet> Sextets = HeavyHiggsSemiTagger.GetBdt(tripletsSemi, tripletsHadronic, HeavyHiggsSemiReader);

    Jets HiggsParticles = Event.GetParticles()->Generator();
    Jets Even = RemoveIfWrongAbsFamily(HiggsParticles, HeavyHiggsId, GluonId);
    Jets Odd = RemoveIfWrongAbsFamily(HiggsParticles, CPOddHiggsId, GluonId);
    HiggsParticles = Even;
    HiggsParticles.insert(HiggsParticles.end(), Odd.begin(), Odd.end());
    fastjet::PseudoJet HiggsBoson;
    if (Tag == kSignal) {
      if (HiggsParticles.size() == 1) HiggsBoson = HiggsParticles.front();
      else Print(kError, "Where is the Higgs?", HiggsParticles.size());
      std::sort(Sextets.begin(), Sextets.end(), MinDeltaRTo(HiggsParticles.front()));
      if (Sextets.size() > 1) Sextets.erase(Sextets.begin() + 1, Sextets.end());
    }

    std::vector<hheavyhiggs::HEventTtSemiBranch> EventSemiBranches;
    if (Sextets.empty()) return EventSemiBranches;

    if (Tag == kSignal && Sextets.size() > 1) {
        Print(kError, "more than one event", Sextets.size());
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
    for (const auto & Jet : jets)  {
        if (Jet.delta_R(SextetEvent.Sextet().triplet1().Singlet()) < detector_geometry().JetConeSize) continue;
        if (Jet.delta_R(SextetEvent.Sextet().triplet2().Singlet()) < detector_geometry().JetConeSize) continue;
        if (Jet.delta_R(SextetEvent.Sextet().triplet2().doublet().Singlet1()) < detector_geometry().JetConeSize) continue;
        if (Jet.delta_R(SextetEvent.Sextet().triplet2().doublet().Singlet2()) < detector_geometry().JetConeSize) continue;
        SextetEvent.AddRestJet(Jet);
    }

    EventSemiBranches.emplace_back(GetBranch(SextetEvent));
    return EventSemiBranches;
}

std::vector<HSextetEvent> hheavyhiggs::HEventTtSemiTagger::GetBdt(const std::vector< hanalysis::HSextet > &Sextets, Jets &jets, const Jets &Leptons, HEventStruct &EventStruct, const hanalysis::Reader &EventSemiReader)
{
    Print(kInformation, "Get Event Tags");

    std::vector<HSextetEvent> SextetEvents;
    for (const auto & Sextet : Sextets) {
        HSextetEvent SextetEvent(Sextet, EventStruct);
        for (const auto & Jet : jets)  {
          if (Jet.delta_R(SextetEvent.Sextet().triplet1().Singlet()) < detector_geometry().JetConeSize) continue;
          if (Jet.delta_R(SextetEvent.Sextet().triplet2().Singlet()) < detector_geometry().JetConeSize) continue;
          if (Jet.delta_R(SextetEvent.Sextet().triplet2().doublet().Singlet1()) < detector_geometry().JetConeSize) continue;
          if (Jet.delta_R(SextetEvent.Sextet().triplet2().doublet().Singlet2()) < detector_geometry().JetConeSize) continue;
            SextetEvent.AddRestJet(Jet);
        }
        SextetEvent.SetLeptons(Leptons);
        Branch = GetBranch(SextetEvent);
        SextetEvent.SetBdt(EventSemiReader.Bdt());
        SextetEvents.emplace_back(SextetEvent);
    }

    std::sort(SextetEvents.begin(), SextetEvents.end());
    if (SextetEvents.size() > 1)SextetEvents.erase(SextetEvents.begin() + 1, SextetEvents.end());
    Print(kInformation, "Event Number", SextetEvents.size(), jets.size());
    return SextetEvents;
}

float hheavyhiggs::HEventTtSemiTagger::ReadBdt(const TClonesArray &EventClonesArray, const int Entry){
  return ((HEventTtSemiBranch *) EventClonesArray.At(Entry))->Bdt;
}
