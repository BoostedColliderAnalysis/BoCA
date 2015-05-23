# include "HEventTtSemiTagger.hh"

heavyhiggs::EventTtSemiTagger::EventTtSemiTagger()
{
    //   DebugLevel = kDebug;
    Print(kNotification , "Constructor");
    DefineVariables();
}

void heavyhiggs::EventTtSemiTagger::SetTagger(
    const analysis::BottomTagger &NewBottomTagger,
    const analysis::WSemiTagger &Neww_semi_tagger,
    const analysis::WHadronicTagger &NewWTagger,
    const analysis::TopSemiTagger &Newtop_semi_tagger,
    const analysis::TopHadronicTagger &Newtop_hadronic_tagger,
    const analysis::HHeavyHiggsSemiTagger &NewHeavyHiggsSemiTagger)
{
    Print(kNotification , "Constructor");
    bottom_tagger_ = NewBottomTagger;
    w_semi_tagger = Neww_semi_tagger;
    WTagger = NewWTagger;
    top_semi_tagger = Newtop_semi_tagger;
    top_hadronic_tagger = Newtop_hadronic_tagger;
    HeavyHiggsSemiTagger = NewHeavyHiggsSemiTagger;
    DefineVariables();
}

void heavyhiggs::EventTtSemiTagger::DefineVariables()
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

heavyhiggs::EventTtSemiBranch heavyhiggs::EventTtSemiTagger::GetBranch(const SextetEvent &event) const
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

    eventSemiBranch.HiggsMass = event.sextet().Jet().m();
    eventSemiBranch.HiggsBdt = event.sextet().Bdt();

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

std::vector<heavyhiggs::EventTtSemiBranch> heavyhiggs::EventTtSemiTagger::GetBranches(analysis::Event &event, const Object::Tag Tag)
{
    Print(kInformation, "Get event Tags");

    Jets jets = GetJets(event);
    jets = bottom_tagger_.GetJetBdt(jets, BottomReader.reader());
    Jets Leptons = event.leptons().GetTaggedJets(jet_tag);
    fastjet::PseudoJet MissingEt = event.hadrons().GetMissingEt();
    std::vector<analysis::Doublet> doubletsSemi = w_semi_tagger.GetBdt(Leptons, MissingEt, WSemiReader.reader());
    std::vector<analysis::Triplet> tripletsSemi = top_semi_tagger.GetBdt(doubletsSemi, jets, TopSemiReader);

//     std::vector<analysis::Doublet> doubletsHadronic = WTagger.GetBdt(jets, WReader);
//     std::vector<analysis::Triplet> tripletsHadronic = top_hadronic_tagger.GetBdt(doubletsHadronic, jets, TopHadronicReader);
    std::vector<analysis::Triplet> tripletsHadronic = top_hadronic_tagger.GetBdt(jets, TopHadronicReader, WTagger, WReader, bottom_tagger_, BottomReader);

    std::vector<analysis::Sextet> sextets = HeavyHiggsSemiTagger.GetBdt(tripletsSemi, tripletsHadronic, HeavyHiggsSemiReader);

    Jets HiggsParticles = event.partons().Generator();
    Jets Even = RemoveIfWrongAbsFamily(HiggsParticles, HeavyHiggsId, GluonId);
    Jets Odd = RemoveIfWrongAbsFamily(HiggsParticles, CPOddHiggsId, GluonId);
    HiggsParticles = Even;
    HiggsParticles.insert(HiggsParticles.end(), Odd.begin(), Odd.end());
    fastjet::PseudoJet HiggsBoson;
    if (Tag == kSignal) {
      if (HiggsParticles.size() == 1) HiggsBoson = HiggsParticles.front();
      else Print(kError, "Where is the Higgs?", HiggsParticles.size());
      std::sort(sextets.begin(), sextets.end(), analysis::MinDeltaRTo(HiggsParticles.front()));
      if (sextets.size() > 1) sextets.erase(sextets.begin() + 1, sextets.end());
    }

    std::vector<heavyhiggs::EventTtSemiBranch> eventSemiBranches;
    if (sextets.empty()) return eventSemiBranches;

    if (Tag == kSignal && sextets.size() > 1) {
        Print(kError, "more than one event", sextets.size());
        std::sort(sextets.begin(), sextets.end());
        sextets.erase(sextets.begin() + 1, sextets.end());
    }

    SextetEvent sextet_event(sextets.front());
    GlobalObservables global_observables;
    global_observables.lepton_number = event.leptons().GetLeptonJets().size();
    global_observables.jet_number = event.hadrons().GetJets().size();
    global_observables.bottom_number = event.hadrons().GetBottomJets().size();
    global_observables.scalar_ht = event.hadrons().GetScalarHt();
    sextet_event.SetEventStruct(global_observables);
    sextet_event.SetLeptons(Leptons);
    sextet_event.SetTag(Tag);
    for (const auto & Jet : jets)  {
        if (Jet.delta_R(sextet_event.sextet().triplet1().singlet()) < detector_geometry().JetConeSize) continue;
        if (Jet.delta_R(sextet_event.sextet().triplet2().singlet()) < detector_geometry().JetConeSize) continue;
        if (Jet.delta_R(sextet_event.sextet().triplet2().doublet().Singlet1()) < detector_geometry().JetConeSize) continue;
        if (Jet.delta_R(sextet_event.sextet().triplet2().doublet().Singlet2()) < detector_geometry().JetConeSize) continue;
        sextet_event.AddRestJet(Jet);
    }

    eventSemiBranches.emplace_back(GetBranch(sextet_event));
    return eventSemiBranches;
}

std::vector<SextetEvent> heavyhiggs::EventTtSemiTagger::GetBdt(const std::vector< analysis::Sextet > &sextets, Jets &jets, const Jets &Leptons, GlobalObservables &global_observables, const analysis::Reader &eventSemiReader)
{
    Print(kInformation, "Get event Tags");

    std::vector<SextetEvent> sextet_events;
    for (const auto & sextet : sextets) {
        SextetEvent sextet_event(sextet, global_observables);
        for (const auto & Jet : jets)  {
          if (Jet.delta_R(sextet_event.sextet().triplet1().singlet()) < detector_geometry().JetConeSize) continue;
          if (Jet.delta_R(sextet_event.sextet().triplet2().singlet()) < detector_geometry().JetConeSize) continue;
          if (Jet.delta_R(sextet_event.sextet().triplet2().doublet().Singlet1()) < detector_geometry().JetConeSize) continue;
          if (Jet.delta_R(sextet_event.sextet().triplet2().doublet().Singlet2()) < detector_geometry().JetConeSize) continue;
            sextet_event.AddRestJet(Jet);
        }
        sextet_event.SetLeptons(Leptons);
        Branch = GetBranch(sextet_event);
        sextet_event.SetBdt(eventSemiReader.Bdt());
        sextet_events.emplace_back(sextet_event);
    }

    std::sort(sextet_events.begin(), sextet_events.end());
    if (sextet_events.size() > 1)sextet_events.erase(sextet_events.begin() + 1, sextet_events.end());
    Print(kInformation, "event Number", sextet_events.size(), jets.size());
    return sextet_events;
}

float heavyhiggs::EventTtSemiTagger::ReadBdt(const TClonesArray &eventClonesArray, const int Entry){
  return ((EventTtSemiBranch *) eventClonesArray.At(Entry))->Bdt;
}
