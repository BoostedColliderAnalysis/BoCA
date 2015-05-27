# include "EventNeutralTagger.hh"

heavyhiggs::EventNeutralTagger::EventNeutralTagger()
{
    //   DebugLevel = kDebug;
    Print(kNotification , "Constructor");
    set_tagger_name("EventNeutral");
    bottom_reader_.set_tagger(bottom_tagger_);
    signature_neutral_reader_.set_tagger(signature_neutral_tagger_);
    DefineVariables();
}

void heavyhiggs::EventNeutralTagger::DefineVariables()
{
    Print(kNotification , "Define Variables");

    AddSpectator(branch_.LeptonNumber, "LeptonNumber");
    AddVariable(branch_.JetNumber, "JetNumber");
    AddVariable(branch_.BottomNumber, "BottomNumber");
    AddVariable(branch_.ScalarHt, "ScalarHt");

    AddVariable(branch_.Mass, "Mass");
    AddVariable(branch_.Pt, "Pt");
    AddVariable(branch_.Rap, "Rap");
    AddVariable(branch_.Phi, "Phi");
    AddVariable(branch_.Ht, "Ht");

    AddVariable(branch_.DeltaPt, "DeltaPt");
    AddVariable(branch_.DeltaHt, "DeltaHt");
    AddVariable(branch_.DeltaM, "DeltaM");
    AddVariable(branch_.DeltaRap, "DeltaRap");
    AddVariable(branch_.DeltaPhi, "DeltaPhi");
    AddVariable(branch_.DeltaR, "DeltaR");

    AddVariable(branch_.HiggsMass, "HiggsMass");
    AddVariable(branch_.PairRap, "PairRap");
    AddVariable(branch_.HiggsBdt, "HiggsBdt");
    AddVariable(branch_.SignatureBdt, "SignatureBdt");
    AddVariable(branch_.BottomBdt, "BottomBdt");
    AddVariable(branch_.PairBottomBdt, "PairBottomBdt");

    AddVariable(branch_.HardTopPt, "HardTopPt");
    AddVariable(branch_.SoftTopPt, "SoftTopPt");

    AddVariable(branch_.MissingEt, "MissingEt");

    AddVariable(branch_.BottomBdt1, "BottomBdt1");
    AddVariable(branch_.BottomBdt2, "BottomBdt2");
    AddVariable(branch_.BottomBdt3, "BottomBdt3");
    AddVariable(branch_.BottomBdt4, "BottomBdt4");
    AddVariable(branch_.BottomBdt5, "BottomBdt5");
    AddVariable(branch_.BottomBdt6, "BottomBdt6");
    AddVariable(branch_.BottomBdt7, "BottomBdt7");
    AddVariable(branch_.BottomBdt8, "BottomBdt8");
    AddVariable(branch_.BottomBdt12, "BottomBdt12");
    AddVariable(branch_.BottomBdt34, "BottomBdt34");
    AddVariable(branch_.BottomBdt56, "BottomBdt56");
    AddVariable(branch_.BottomBdt78, "BottomBdt78");

    AddVariable(branch_.SubBottomBdt1, "SubBottomBdt1");
    AddVariable(branch_.SubBottomBdt2, "SubBottomBdt2");
    AddVariable(branch_.SubBottomBdt3, "SubBottomBdt3");
    AddVariable(branch_.SubBottomBdt4, "SubBottomBdt4");
    AddVariable(branch_.SubBottomBdt5, "SubBottomBdt5");
    AddVariable(branch_.SubBottomBdt6, "SubBottomBdt6");
    AddVariable(branch_.SubBottomBdt7, "SubBottomBdt7");
    AddVariable(branch_.SubBottomBdt8, "SubBottomBdt8");
    AddVariable(branch_.SubBottomBdt12, "SubBottomBdt12");
    AddVariable(branch_.SubBottomBdt34, "SubBottomBdt34");
    AddVariable(branch_.SubBottomBdt56, "SubBottomBdt56");
    AddVariable(branch_.SubBottomBdt78, "SubBottomBdt78");

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

int heavyhiggs::EventNeutralTagger::Train(analysis::Event &event, const Tag tag)
{
    Print(kInformation, "event Tags");

    analysis::Jets jets = bottom_reader_.Multiplets<analysis::BottomTagger>(event);
//     Jets jets = bottom_tagger_.GetJetBdt(PreJets, BottomReader);
//     Jets SubJets = bottom_tagger_.GetMultiJetBdt(PreJets, BottomReader);
//
    analysis::Jets Leptons = event.leptons().leptons();
//     fastjet::PseudoJet MissingEt = event.hadrons().GetMissingEt();
//     std::vector<analysis::Doublet> doubletsSemi = w_semi_tagger.GetBdt(Leptons, MissingEt, WSemiReader.reader());
//     std::vector<analysis::Triplet> tripletsSemi = top_semi_tagger.GetBdt(doubletsSemi, jets, TopSemiReader);
//
//     std::vector<analysis::Doublet> doubletsHadronic = WTagger.GetBdt(jets, WReader);
//     std::vector<analysis::Triplet> tripletsHadronic = top_hadronic_tagger.GetBdt(doubletsHadronic, jets, TopHadronicReader);
//     std::vector<analysis::Triplet> tripletsHadronic = top_hadronic_tagger.GetBdt(jets, TopHadronicReader, WTagger, WReader, bottom_tagger_, BottomReader);
//
//     std::vector<analysis::Sextet> sextets = heavy_higgs_semi_tagger.GetBdt(tripletsSemi, tripletsHadronic, HeavyHiggsSemiReader);
//
//
//     Jets HiggsParticles = event.partons().Generator();
//     Jets Even = RemoveIfWrongAbsFamily(HiggsParticles, HeavyHiggsId, GluonId);
//     Jets Odd = RemoveIfWrongAbsFamily(HiggsParticles, CPOddHiggsId, GluonId);
//     HiggsParticles = Even;
//     HiggsParticles.insert(HiggsParticles.end(), Odd.begin(), Odd.end());
//     fastjet::PseudoJet HiggsBoson;
//     if (Tag == kSignal) {
//         if (HiggsParticles.size() == 1) HiggsBoson = HiggsParticles.front();
//         else Print(kError, "Where is the Higgs?", HiggsParticles.size());
//         std::sort(sextets.begin(), sextets.end(), analysis::MinDeltaRTo(HiggsParticles.front()));
//         if (sextets.size() > 1) sextets.erase(sextets.begin() + 1, sextets.end());
//     }
//
//     std::vector<analysis::Doublet> doublets = jet_pair_tagger.GetBdt(jets, JetPairReader);
//
//     std::vector<analysis::Doublet> Finaldoublets;
//     Jets Particles = event.partons().Generator();
//     if (Tag == kSignal) {
//         Particles = RemoveIfWrongAbsFamily(Particles, BottomId, GluonId);
//         if (Particles.size() == 2) {
//             for (const auto & doublet : doublets) {
//                 if ((doublet.Singlet1().delta_R(Particles.at(0)) < detector_geometry().JetConeSize && doublet.Singlet2().delta_R(Particles.at(1)) < detector_geometry().JetConeSize) || (doublet.Singlet1().delta_R(Particles.at(1)) < detector_geometry().JetConeSize && doublet.Singlet2().delta_R(Particles.at(0)) < detector_geometry().JetConeSize)) Finaldoublets.emplace_back(doublet);
//             }
//         } else Print(kError, "Where is the Quark Pair", Particles.size());
//     }
//     if (Tag == kBackground)
//         Finaldoublets = doublets;

//     std::vector<Octet62> octets = signature_neutral_tagger_.GetBdt(sextets, Finaldoublets, signature_neutral_reader_);
    std::vector<Octet62> octets = signature_neutral_reader_.Multiplets<SignatureNeutralTagger>(event);

    std::vector<analysis::MultipletEvent<Octet62>> events;
    for (const auto & octet : octets) {
      analysis::MultipletEvent<Octet62> octetevent(octet);
//       analysis::GlobalObservables global_observables;
//         global_observables.lepton_number = event.leptons().GetLeptonJets().size();
//         global_observables.jet_number = event.hadrons().GetJets().size();
//         global_observables.bottom_number = event.hadrons().GetBottomJets().size();
//         global_observables.scalar_ht = event.hadrons().GetScalarHt();
//         global_observables.missing_et = event.hadrons().GetMissingEt().pt();
//         global_observables.TrackNumber = event.hadrons().GetScalarHt();
        octetevent.Setglobal_observables(analysis::GlobalObservables(event));
        octetevent.SetLeptons(Leptons);
        octetevent.SetTotalJets(jets);
//         octetevent.SetSubJets(SubJets);
        octetevent.SetTag(tag);
        for (const auto & Jet : jets)  {
            if (Jet.delta_R(octetevent.multiplet().sextet().triplet1().singlet()) < detector_geometry().JetConeSize) continue;
            if (Jet.delta_R(octetevent.multiplet().sextet().triplet2().singlet()) < detector_geometry().JetConeSize) continue;
            if (Jet.delta_R(octetevent.multiplet().sextet().triplet2().doublet().Singlet1()) < detector_geometry().JetConeSize) continue;
            if (Jet.delta_R(octetevent.multiplet().sextet().triplet2().doublet().Singlet2()) < detector_geometry().JetConeSize) continue;
            if (Jet.delta_R(octetevent.multiplet().doublet().Singlet1()) < detector_geometry().JetConeSize) continue;
            if (Jet.delta_R(octetevent.multiplet().doublet().Singlet2()) < detector_geometry().JetConeSize) continue;
            octetevent.AddRestJet(Jet);
        }
        events.emplace_back(octetevent);
    }

//     std::vector<heavyhiggs::EventNeutralBranch> eventSemiBranches;
//     for (const auto & event : events) eventSemiBranches.emplace_back(GetBranch(event));

//     return eventSemiBranches;
return SaveEntries<EventNeutralBranch>(events);
}

// analysis::GlobalObservables heavyhiggs::EventNeutralTagger::global_observables(analysis::Event &event){
//   analysis::GlobalObservables global_observables;
//   global_observables.lepton_number = event.leptons().GetLeptonJets().size();
//   global_observables.jet_number = event.hadrons().GetJets().size();
//   global_observables.bottom_number = event.hadrons().GetBottomJets().size();
//   global_observables.scalar_ht = event.hadrons().GetScalarHt();
//   global_observables.missing_et = event.hadrons().GetMissingEt().pt();
//   return global_observables;
// }



std::vector<analysis::MultipletEvent<Octet62>> heavyhiggs::EventNeutralTagger::Multiplets(analysis::Event &event, const TMVA::Reader &reader)
{
  Print(kInformation, "event Tags");
  std::vector<Octet62> octets = signature_neutral_reader_.Multiplets<SignatureNeutralTagger>(event);


  analysis::Jets jets = bottom_reader_.Multiplets<analysis::BottomTagger>(event);
  analysis::Jets Leptons = event.leptons().leptons();

    std::vector<analysis::MultipletEvent<Octet62>> events;
    for (const auto & octet : octets) {
      analysis::MultipletEvent<Octet62> octetevent(octet, analysis::GlobalObservables(event));
        for (const auto & Jet : jets)  {
            if (Jet.delta_R(octetevent.multiplet().sextet().triplet1().singlet()) < detector_geometry().JetConeSize) continue;
            if (Jet.delta_R(octetevent.multiplet().sextet().triplet2().singlet()) < detector_geometry().JetConeSize) continue;
            if (Jet.delta_R(octetevent.multiplet().sextet().triplet2().doublet().Singlet1()) < detector_geometry().JetConeSize) continue;
            if (Jet.delta_R(octetevent.multiplet().sextet().triplet2().doublet().Singlet2()) < detector_geometry().JetConeSize) continue;
            if (Jet.delta_R(octetevent.multiplet().doublet().Singlet1()) < detector_geometry().JetConeSize) continue;
            if (Jet.delta_R(octetevent.multiplet().doublet().Singlet2()) < detector_geometry().JetConeSize) continue;
            octetevent.AddRestJet(Jet);
        }
        octetevent.SetLeptons(Leptons);
        octetevent.SetTotalJets(jets);
//         octetevent.SetSubJets(SubJets);
        branch_ = branch<EventNeutralBranch>(octetevent);
        octetevent.SetBdt(Bdt(reader));
        events.emplace_back(octetevent);
    }


    std::sort(events.begin(), events.end());
    if (events.size() > 1) events.erase(events.begin() + 1, events.end());
    Print(kInformation, "event Number", events.size(), jets.size());


    return events;
}

