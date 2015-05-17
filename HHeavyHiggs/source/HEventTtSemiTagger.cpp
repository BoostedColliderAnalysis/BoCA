# include "HEventTtSemiTagger.hh"

hheavyhiggs::EventTtSemiTagger::EventTtSemiTagger()
{
    //   DebugLevel = kDebug;
    Print(kNotification , "Constructor");
    DefineVariables();
}

void hheavyhiggs::EventTtSemiTagger::SetTagger(
    const analysis::BottomTagger &NewBottomTagger,
    const analysis::HWSemiTagger &NewWSemiTagger,
    const analysis::WHadronicTagger &NewWTagger,
    const analysis::HTopSemiTagger &NewTopSemiTagger,
    const analysis::TopHadronicTagger &Newtop_hadronic_tagger,
    const analysis::HHeavyHiggsSemiTagger &NewHeavyHiggsSemiTagger)
{
    Print(kNotification , "Constructor");
    bottom_tagger_ = NewBottomTagger;
    WSemiTagger = NewWSemiTagger;
    WTagger = NewWTagger;
    TopSemiTagger = NewTopSemiTagger;
    top_hadronic_tagger = Newtop_hadronic_tagger;
    HeavyHiggsSemiTagger = NewHeavyHiggsSemiTagger;
    DefineVariables();
}

void hheavyhiggs::EventTtSemiTagger::DefineVariables()
{
    Print(kNotification , "Define Variables");
    set_tagger_name("eventSemi");
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

hheavyhiggs::EventTtSemiBranch hheavyhiggs::EventTtSemiTagger::GetBranch(const HSextetevent &event) const
{
    Print(kInformation, "FillPairTagger", event.Bdt());

    EventTtSemiBranch eventSemiBranch;
    eventSemiBranch.LeptonNumber = event.LeptonNumber();
    eventSemiBranch.JetNumber = event.JetNumber();
    eventSemiBranch.BottomNumber = event.BottomNumber();
    eventSemiBranch.ScalarHt = event.ScalarHt();

    eventSemiBranch.Mass = event.Jet().m();
    eventSemiBranch.Rap = event.Jet().rap();
    eventSemiBranch.Phi = event.Jet().phi();
    eventSemiBranch.Pt = event.Jet().pt();
    eventSemiBranch.Ht = event.Ht();

    eventSemiBranch.DeltaPt = event.DeltaPt();
    eventSemiBranch.DeltaPhi = event.DeltaPhi();
    eventSemiBranch.DeltaRap = event.DeltaRap();
    eventSemiBranch.DeltaR = event.DeltaR();
    eventSemiBranch.DeltaM = event.DeltaM();
    eventSemiBranch.DeltaHt = event.DeltaHt();

    eventSemiBranch.Bdt = event.Bdt();
    eventSemiBranch.Tag = event.Tag();

    eventSemiBranch.HiggsMass = event.Sextet().Jet().m();
    eventSemiBranch.HiggsBdt = event.Sextet().Bdt();

    eventSemiBranch.RestNumber = event.RestNumber();
    eventSemiBranch.RestM = event.RestJet().m();
    eventSemiBranch.RestPt = event.RestJet().pt();
    eventSemiBranch.RestHt = event.RestHt();
    eventSemiBranch.RestRap = event.RestJet().rap();
    if (std::abs(eventSemiBranch.RestRap) > 100) eventSemiBranch.RestRap = 0;
    eventSemiBranch.RestPhi = event.RestJet().phi();
    eventSemiBranch.RestBdt = event.RestBdt();

    eventSemiBranch.LeptonHt = event.LeptonHt();

    return eventSemiBranch;

}

struct SortJetsByBdt {
    inline bool operator()(const fastjet::PseudoJet &Jet1, const fastjet::PseudoJet &Jet2) {
        return (Jet1.user_info<analysis::JetInfo>().Bdt() > Jet2.user_info<analysis::JetInfo>().Bdt());
    }
};

std::vector<hheavyhiggs::EventTtSemiBranch> hheavyhiggs::EventTtSemiTagger::GetBranches(analysis::Event &event, const Object::Tag Tag)
{
    Print(kInformation, "Get event Tags");

    Jets jets = GetJets(event);
    jets = bottom_tagger_.GetJetBdt(jets, BottomReader.reader());
    Jets Leptons = event.Leptons().GetTaggedJets(JetTag);
    fastjet::PseudoJet MissingEt = event.hadrons().GetMissingEt();
    std::vector<analysis::Doublet> doubletsSemi = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader.reader());
    std::vector<analysis::Triplet> tripletsSemi = TopSemiTagger.GetBdt(doubletsSemi, jets, TopSemiReader);

//     std::vector<analysis::Doublet> doubletsHadronic = WTagger.GetBdt(jets, WReader);
//     std::vector<analysis::Triplet> tripletsHadronic = top_hadronic_tagger.GetBdt(doubletsHadronic, jets, TopHadronicReader);
    std::vector<analysis::Triplet> tripletsHadronic = top_hadronic_tagger.GetBdt(jets, TopHadronicReader, WTagger, WReader, bottom_tagger_, BottomReader);

    std::vector<analysis::HSextet> Sextets = HeavyHiggsSemiTagger.GetBdt(tripletsSemi, tripletsHadronic, HeavyHiggsSemiReader);

    Jets HiggsParticles = event.Partons().Generator();
    Jets Even = RemoveIfWrongAbsFamily(HiggsParticles, HeavyHiggsId, GluonId);
    Jets Odd = RemoveIfWrongAbsFamily(HiggsParticles, CPOddHiggsId, GluonId);
    HiggsParticles = Even;
    HiggsParticles.insert(HiggsParticles.end(), Odd.begin(), Odd.end());
    fastjet::PseudoJet HiggsBoson;
    if (Tag == kSignal) {
      if (HiggsParticles.size() == 1) HiggsBoson = HiggsParticles.front();
      else Print(kError, "Where is the Higgs?", HiggsParticles.size());
      std::sort(Sextets.begin(), Sextets.end(), analysis::MinDeltaRTo(HiggsParticles.front()));
      if (Sextets.size() > 1) Sextets.erase(Sextets.begin() + 1, Sextets.end());
    }

    std::vector<hheavyhiggs::EventTtSemiBranch> eventSemiBranches;
    if (Sextets.empty()) return eventSemiBranches;

    if (Tag == kSignal && Sextets.size() > 1) {
        Print(kError, "more than one event", Sextets.size());
        std::sort(Sextets.begin(), Sextets.end());
        Sextets.erase(Sextets.begin() + 1, Sextets.end());
    }

    HSextetevent Sextetevent(Sextets.front());
    EventStruct eventStruct;
    eventStruct.LeptonNumber = event.Leptons().GetLeptonJets().size();
    eventStruct.JetNumber = event.hadrons().GetJets().size();
    eventStruct.BottomNumber = event.hadrons().GetBottomJets().size();
    eventStruct.ScalarHt = event.hadrons().GetScalarHt();
    Sextetevent.SeteventStruct(eventStruct);
    Sextetevent.SetLeptons(Leptons);
    Sextetevent.SetTag(Tag);
    for (const auto & Jet : jets)  {
        if (Jet.delta_R(Sextetevent.Sextet().triplet1().singlet()) < detector_geometry().JetConeSize) continue;
        if (Jet.delta_R(Sextetevent.Sextet().triplet2().singlet()) < detector_geometry().JetConeSize) continue;
        if (Jet.delta_R(Sextetevent.Sextet().triplet2().doublet().Singlet1()) < detector_geometry().JetConeSize) continue;
        if (Jet.delta_R(Sextetevent.Sextet().triplet2().doublet().Singlet2()) < detector_geometry().JetConeSize) continue;
        Sextetevent.AddRestJet(Jet);
    }

    eventSemiBranches.emplace_back(GetBranch(Sextetevent));
    return eventSemiBranches;
}

std::vector<HSextetevent> hheavyhiggs::EventTtSemiTagger::GetBdt(const std::vector< analysis::HSextet > &Sextets, Jets &jets, const Jets &Leptons, EventStruct &eventStruct, const analysis::Reader &eventSemiReader)
{
    Print(kInformation, "Get event Tags");

    std::vector<HSextetevent> Sextetevents;
    for (const auto & Sextet : Sextets) {
        HSextetevent Sextetevent(Sextet, eventStruct);
        for (const auto & Jet : jets)  {
          if (Jet.delta_R(Sextetevent.Sextet().triplet1().singlet()) < detector_geometry().JetConeSize) continue;
          if (Jet.delta_R(Sextetevent.Sextet().triplet2().singlet()) < detector_geometry().JetConeSize) continue;
          if (Jet.delta_R(Sextetevent.Sextet().triplet2().doublet().Singlet1()) < detector_geometry().JetConeSize) continue;
          if (Jet.delta_R(Sextetevent.Sextet().triplet2().doublet().Singlet2()) < detector_geometry().JetConeSize) continue;
            Sextetevent.AddRestJet(Jet);
        }
        Sextetevent.SetLeptons(Leptons);
        Branch = GetBranch(Sextetevent);
        Sextetevent.SetBdt(eventSemiReader.Bdt());
        Sextetevents.emplace_back(Sextetevent);
    }

    std::sort(Sextetevents.begin(), Sextetevents.end());
    if (Sextetevents.size() > 1)Sextetevents.erase(Sextetevents.begin() + 1, Sextetevents.end());
    Print(kInformation, "event Number", Sextetevents.size(), jets.size());
    return Sextetevents;
}

float hheavyhiggs::EventTtSemiTagger::ReadBdt(const TClonesArray &eventClonesArray, const int Entry){
  return ((EventTtSemiBranch *) eventClonesArray.At(Entry))->Bdt;
}
