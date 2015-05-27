# include "EventFusionTagger.hh"

heavyhiggs::EventFusionTagger::EventFusionTagger()
{
    //   DebugLevel = kDebug;
    Print(kNotification , "Constructor");
    set_tagger_name("EventFusion");
    bottom_reader_.set_tagger(bottom_tagger_);
    heavy_higgs_semi_reader_.set_tagger(heavy_higgs_semi_tagger_);
    DefineVariables();
}

void heavyhiggs::EventFusionTagger::DefineVariables()
{
    Print(kNotification , "Define Variables");
    AddVariable(branch_.LeptonNumber, "LeptonNumber");
    AddVariable(branch_.JetNumber, "JetNumber");
    AddVariable(branch_.BottomNumber, "BottomNumber");
    AddVariable(branch_.ScalarHt, "ScalarHt");

    AddVariable(branch_.Mass, "Mass");
    AddVariable(branch_.Pt, "Pt");
    AddVariable(branch_.Rap, "Rap");
    AddVariable(branch_.Phi, "Phi");
    AddVariable(branch_.Ht, "Ht");

    AddVariable(branch_.DeltaPt, "DeltaPt");
    AddVariable(branch_.DeltaRap, "DeltaRap");
    AddVariable(branch_.DeltaPhi, "DeltaPhi");
    AddVariable(branch_.DeltaR, "DeltaR");
    AddVariable(branch_.DeltaHt, "DeltaHt");
    AddVariable(branch_.DeltaM, "DeltaM");

    AddVariable(branch_.HiggsMass, "HiggsMass");
    AddVariable(branch_.HiggsBdt, "HiggsBdt");

    AddVariable(branch_.RestNumber, "RestNumber");
    AddVariable(branch_.RestM, "RestM");
    AddVariable(branch_.RestPt, "RestPt");
    AddVariable(branch_.RestHt, "RestHt");
    AddVariable(branch_.RestPhi, "RestPhi");
    AddVariable(branch_.RestRap, "RestRap");
    AddVariable(branch_.RestBdt, "RestBdt");
    AddVariable(branch_.LeptonHt, "LeptonHt");

    AddVariable(branch_.Bdt, "Bdt");
    AddSpectator(branch_.Tag, "Tag");
}

int heavyhiggs::EventFusionTagger::Train(analysis::Event &event, const Tag tag)
{
    Print(kInformation, "event Tags");

//     Jets jets = GetJets(event);
//     jets = bottom_tagger_.GetJetBdt(jets, BottomReader.reader());

    analysis::Jets jets = bottom_reader_.Multiplets<analysis::BottomTagger>(event);
    analysis::Jets Leptons = event.leptons().leptons();
//     fastjet::PseudoJet MissingEt = event.hadrons().GetMissingEt();
//     std::vector<analysis::Doublet> doubletsSemi = w_semi_tagger.GetBdt(Leptons, MissingEt, WSemiReader.reader());
//     std::vector<analysis::Triplet> tripletsSemi = top_semi_tagger.GetBdt(doubletsSemi, jets, TopSemiReader);

//     std::vector<analysis::Doublet> doubletsHadronic = WTagger.GetBdt(jets, WReader);
//     std::vector<analysis::Triplet> tripletsHadronic = top_hadronic_tagger.GetBdt(doubletsHadronic, jets, TopHadronicReader);
//     std::vector<analysis::Triplet> tripletsHadronic = top_hadronic_tagger.GetBdt(jets, TopHadronicReader, WTagger, WReader, bottom_tagger_, BottomReader);

//     std::vector<analysis::Sextet> sextets = heavy_higgs_semi_tagger.GetBdt(tripletsSemi, tripletsHadronic, HeavyHiggsSemiReader);
    std::vector<analysis::Sextet> sextets = heavy_higgs_semi_reader_.Multiplets<analysis::HeavyHiggsSemiTagger>(event);

    analysis::Jets HiggsParticles = event.partons().Generator();
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

//     std::vector<heavyhiggs::EventFusionBranch> eventSemiBranches;
    if (sextets.empty()) return 0;

    if (tag == kSignal && sextets.size() > 1) {
        Print(kError, "more than one event", sextets.size());
        std::sort(sextets.begin(), sextets.end());
        sextets.erase(sextets.begin() + 1, sextets.end());
    }

    analysis::MultipletEvent<analysis::Sextet> sextet_event(sextets.front());
    analysis::GlobalObservables global_observables(event);
//     global_observables.lepton_number = event.leptons().GetLeptonJets().size();
//     global_observables.jet_number = event.hadrons().GetJets().size();
//     global_observables.bottom_number = event.hadrons().GetBottomJets().size();
//     global_observables.scalar_ht = event.hadrons().GetScalarHt();
    sextet_event.Setglobal_observables(global_observables);
    sextet_event.SetLeptons(Leptons);
    sextet_event.SetTag(tag);
    for (const auto & Jet : jets)  {
        if (Jet.delta_R(sextet_event.multiplet().triplet1().singlet()) < detector_geometry().JetConeSize) continue;
        if (Jet.delta_R(sextet_event.multiplet().triplet2().singlet()) < detector_geometry().JetConeSize) continue;
        if (Jet.delta_R(sextet_event.multiplet().triplet2().doublet().Singlet1()) < detector_geometry().JetConeSize) continue;
        if (Jet.delta_R(sextet_event.multiplet().triplet2().doublet().Singlet2()) < detector_geometry().JetConeSize) continue;
        sextet_event.AddRestJet(Jet);
    }

    std::vector<analysis::MultipletEvent<analysis::Sextet>> sextet_events;
    sextet_events.emplace_back(sextet_event);
    return SaveEntries<EventFusionBranch>(sextet_events);
}

std::vector<analysis::MultipletEvent<analysis::Sextet>> heavyhiggs::EventFusionTagger::Multiplets(analysis::Event &event, TMVA::Reader &reader)
{
  Print(kInformation, "event Tags");
  std::vector<analysis::Sextet> sextets = heavy_higgs_semi_reader_.Multiplets<analysis::HeavyHiggsSemiTagger>(event);

  analysis::Jets jets = bottom_reader_.Multiplets<analysis::BottomTagger>(event);
  analysis::Jets Leptons = event.leptons().leptons();
    std::vector<analysis::MultipletEvent<analysis::Sextet>> sextet_events;
    for (const auto & sextet : sextets) {
        analysis::MultipletEvent<analysis::Sextet> sextet_event(sextet, analysis::GlobalObservables(event));
        for (const auto & Jet : jets)  {
            if (Jet.delta_R(sextet_event.multiplet().triplet1().singlet()) < detector_geometry().JetConeSize) continue;
            if (Jet.delta_R(sextet_event.multiplet().triplet2().singlet()) < detector_geometry().JetConeSize) continue;
            if (Jet.delta_R(sextet_event.multiplet().triplet2().doublet().Singlet1()) < detector_geometry().JetConeSize) continue;
            if (Jet.delta_R(sextet_event.multiplet().triplet2().doublet().Singlet2()) < detector_geometry().JetConeSize) continue;
            sextet_event.AddRestJet(Jet);
        }
        sextet_event.SetLeptons(Leptons);
        branch_ = branch<EventFusionBranch>(sextet_event);
        sextet_event.SetBdt(Bdt(reader));
        sextet_events.emplace_back(sextet_event);
    }
    return ReduceResult(sextet_events);
}
