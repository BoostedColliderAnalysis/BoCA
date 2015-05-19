# include "HChargedEventSemiTagger.hh"

hheavyhiggs::HChargedeventSemiTagger::HChargedeventSemiTagger()
{
//       DebugLevel = kDebug;
    Print(kInformation , "Constructor");
    DefineVariables();
}

void hheavyhiggs::HChargedeventSemiTagger::SetTagger(
    const analysis::BottomTagger &NewBottomTagger,
    const analysis::HChargedJetPairTagger &NewChargedJetPairTagger,
    const analysis::WSemiTagger &Neww_semi_tagger,
    const analysis::WHadronicTagger &NewWTagger,
    const analysis::TopSemiTagger &Newtop_semi_tagger,
    const analysis::TopHadronicTagger &Newtop_hadronic_tagger,
    const analysis::HChargedHiggsSemiTagger &NewChargedHiggsSemiTagger,
    const hheavyhiggs::HChargedSignatureSemiTagger &NewChargedSignatureTagger)
{
    bottom_tagger_ = NewBottomTagger;
    w_semi_tagger = Neww_semi_tagger;
    WTagger = NewWTagger;
    top_hadronic_tagger = Newtop_hadronic_tagger;
    top_semi_tagger = Newtop_semi_tagger;
    ChargedJetPairTagger = NewChargedJetPairTagger;
    ChargedHiggsSemiTagger = NewChargedHiggsSemiTagger;
    SignatureSemiTagger = NewChargedSignatureTagger;
    DefineVariables();
}

void hheavyhiggs::HChargedeventSemiTagger::DefineVariables()
{
    Print(kNotification , "Define Variables");
    set_tagger_name("ChargedeventSemi");
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
    AddVariable(Branch.DeltaHt, "DeltaHt");
    AddVariable(Branch.DeltaM, "DeltaM");
    AddVariable(Branch.DeltaRap, "DeltaRap");
    AddVariable(Branch.DeltaPhi, "DeltaPhi");
    AddVariable(Branch.DeltaR, "DeltaR");

    AddVariable(Branch.HiggsMass, "HiggsMass");
    AddVariable(Branch.PairRap, "PairRap");
    AddVariable(Branch.HiggsBdt, "HiggsBdt");
    AddVariable(Branch.SignatureBdt, "SignatureBdt");
    AddVariable(Branch.BottomBdt, "BottomBdt");
    AddVariable(Branch.PairBottomBdt, "PairBottomBdt");

    AddVariable(Branch.BottomBdt1, "BottomBdt1");
    AddVariable(Branch.BottomBdt2, "BottomBdt2");
    AddVariable(Branch.BottomBdt3, "BottomBdt3");
    AddVariable(Branch.BottomBdt4, "BottomBdt4");
    AddVariable(Branch.BottomBdt5, "BottomBdt5");
    AddVariable(Branch.BottomBdt6, "BottomBdt6");
    AddVariable(Branch.BottomBdt7, "BottomBdt7");
    AddVariable(Branch.BottomBdt8, "BottomBdt8");
    AddVariable(Branch.BottomBdt12, "BottomBdt12");
    AddVariable(Branch.BottomBdt34, "BottomBdt34");
    AddVariable(Branch.BottomBdt56, "BottomBdt56");
    AddVariable(Branch.BottomBdt78, "BottomBdt78");

    AddVariable(Branch.SubBottomBdt1, "SubBottomBdt1");
    AddVariable(Branch.SubBottomBdt2, "SubBottomBdt2");
    AddVariable(Branch.SubBottomBdt3, "SubBottomBdt3");
    AddVariable(Branch.SubBottomBdt4, "SubBottomBdt4");
    AddVariable(Branch.SubBottomBdt5, "SubBottomBdt5");
    AddVariable(Branch.SubBottomBdt6, "SubBottomBdt6");
    AddVariable(Branch.SubBottomBdt7, "SubBottomBdt7");
    AddVariable(Branch.SubBottomBdt8, "SubBottomBdt8");
    AddVariable(Branch.SubBottomBdt12, "SubBottomBdt12");
    AddVariable(Branch.SubBottomBdt34, "SubBottomBdt34");
    AddVariable(Branch.SubBottomBdt56, "SubBottomBdt56");
    AddVariable(Branch.SubBottomBdt78, "SubBottomBdt78");

    AddVariable(Branch.RestNumber, "RestNumber");
    AddVariable(Branch.RestM, "RestM");
    AddVariable(Branch.RestPt, "RestPt");
    AddVariable(Branch.RestHt, "RestHt");
    AddVariable(Branch.RestPhi, "RestPhi");
    AddVariable(Branch.RestRap, "RestRap");
    AddVariable(Branch.RestBdt, "RestBdt");
    AddVariable(Branch.LeptonHt, "LeptonHt");
    AddVariable(Branch.MissingEt, "MissingEt");

    AddVariable(Branch.Bdt, "Bdt");
    AddSpectator(Branch.Tag, "Tag");

    Print(kNotification, "Variables defined");

}

hheavyhiggs::HChargedSemiBranch hheavyhiggs::HChargedeventSemiTagger::GetBranch(const EventMultiplet< HOctet44 > &event) const
{
    Print(kInformation, "FillPairTagger", event.Bdt());

    HChargedSemiBranch eventSemiBranch;
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
    eventSemiBranch.DeltaHt = event.DeltaHt();
    eventSemiBranch.DeltaM = event.DeltaM();
    eventSemiBranch.DeltaRap = event.DeltaRap();
    eventSemiBranch.DeltaPhi = event.DeltaPhi();
    eventSemiBranch.DeltaR = event.DeltaR();

    eventSemiBranch.Bdt = event.Bdt();
    eventSemiBranch.Tag = event.Tag();

    eventSemiBranch.HiggsMass = event.Octet().quartet1().Jet().m();
    eventSemiBranch.PairRap = event.Octet().quartet2().DeltaRap();
    eventSemiBranch.HiggsBdt = event.Octet().quartet1().Bdt();
    eventSemiBranch.SignatureBdt = event.Octet().Bdt();
    eventSemiBranch.BottomBdt = event.Octet().BottomBdt();
    eventSemiBranch.PairBottomBdt = event.Octet().PairBottomBdt();

    eventSemiBranch.BottomBdt1 = event.BottomBdt(1);
    eventSemiBranch.BottomBdt2 = event.BottomBdt(2);
    eventSemiBranch.BottomBdt3 = event.BottomBdt(3);
    eventSemiBranch.BottomBdt4 = event.BottomBdt(4);
    eventSemiBranch.BottomBdt5 = event.BottomBdt(5);
    eventSemiBranch.BottomBdt6 = event.BottomBdt(6);
    eventSemiBranch.BottomBdt7 = event.BottomBdt(7);
    eventSemiBranch.BottomBdt8 = event.BottomBdt(8);
    eventSemiBranch.BottomBdt12 = event.BottomBdt(1, 2);
    eventSemiBranch.BottomBdt34 = event.BottomBdt(3, 4);
    eventSemiBranch.BottomBdt56 = event.BottomBdt(5, 6);
    eventSemiBranch.BottomBdt78 = event.BottomBdt(7, 8);

    eventSemiBranch.SubBottomBdt1 = event.SubBottomBdt(1);
    eventSemiBranch.SubBottomBdt2 = event.SubBottomBdt(2);
    eventSemiBranch.SubBottomBdt3 = event.SubBottomBdt(3);
    eventSemiBranch.SubBottomBdt4 = event.SubBottomBdt(4);
    eventSemiBranch.SubBottomBdt5 = event.SubBottomBdt(5);
    eventSemiBranch.SubBottomBdt6 = event.SubBottomBdt(6);
    eventSemiBranch.SubBottomBdt7 = event.SubBottomBdt(7);
    eventSemiBranch.SubBottomBdt8 = event.SubBottomBdt(8);
    eventSemiBranch.SubBottomBdt12 = event.SubBottomBdt(1, 2);
    eventSemiBranch.SubBottomBdt34 = event.SubBottomBdt(3, 4);
    eventSemiBranch.SubBottomBdt56 = event.SubBottomBdt(5, 6);
    eventSemiBranch.SubBottomBdt78 = event.SubBottomBdt(7, 8);

    eventSemiBranch.RestNumber = event.RestNumber();
    eventSemiBranch.RestM = event.RestJet().m();
    eventSemiBranch.RestPt = event.RestJet().pt();
    eventSemiBranch.RestHt = event.RestHt();
    eventSemiBranch.RestRap = event.RestJet().rap();
    if (std::abs(eventSemiBranch.RestRap) > 100) eventSemiBranch.RestRap = 0;
    eventSemiBranch.RestPhi = event.RestJet().phi();
    eventSemiBranch.RestBdt = event.RestBdt();
    eventSemiBranch.MissingEt = event.MissingEt();

    eventSemiBranch.LeptonHt = event.LeptonHt();

    return eventSemiBranch;
}

struct SortJetsByBdt {
    inline bool operator()(const fastjet::PseudoJet &Jet1, const fastjet::PseudoJet &Jet2) {
        return (Jet1.user_info<analysis::JetInfo>().Bdt() > Jet2.user_info<analysis::JetInfo>().Bdt());
    }
};

std::vector<hheavyhiggs::HChargedSemiBranch> hheavyhiggs::HChargedeventSemiTagger::GetBranches(analysis::Event &event, const Object::Tag Tag)
{
    Print(kInformation, "Get event Tags");

    Jets PreJets = GetJets(event);
    Jets jets = bottom_tagger_.GetJetBdt(PreJets, BottomReader);
    Jets SubJets = bottom_tagger_.GetMultiJetBdt(PreJets, BottomReader);

    Jets Leptons = event.leptons().GetLeptonJets();
    fastjet::PseudoJet MissingEt = event.hadrons().GetMissingEt();
    std::vector<analysis::Doublet> doubletsSemi = w_semi_tagger.GetBdt(Leptons, MissingEt, WSemiReader);
    std::vector<analysis::Triplet> tripletsSemi = top_semi_tagger.GetBdt(doubletsSemi, jets, TopSemiReader);
    std::vector<analysis::Quartet31> Higgsquartets = ChargedHiggsSemiTagger.GetBdt(tripletsSemi, jets, ChargedHiggsSemiReader);


    Jets HiggsParticles = event.partons().Generator();
    HiggsParticles.erase(std::remove_if(HiggsParticles.begin(), HiggsParticles.end(), analysis::WrongAbsId(ChargedHiggsId)), HiggsParticles.end());
    if (Tag == kSignal && HiggsParticles.size() != 1) Print(kError, "Where is the Higgs?");
    std::sort(Higgsquartets.begin(), Higgsquartets.end(), analysis::MinDeltaRTo(HiggsParticles.front()));
    if (Tag == kSignal && Higgsquartets.size() > 1) Higgsquartets.erase(Higgsquartets.begin() + 1, Higgsquartets.end());
    if (Tag == kBackground && Higgsquartets.size() > 0) Higgsquartets.erase(Higgsquartets.begin());


    std::vector<analysis::Triplet> tripletsHadronic = top_hadronic_tagger.GetBdt(jets, TopHadronicReader, WTagger, WReader, bottom_tagger_, BottomReader);
//     std::vector<analysis::Doublet> doubletsHadronic = WTagger.GetBdt(jets, WReader);
//     std::vector<analysis::Triplet> tripletsHadronic = top_hadronic_tagger.GetBdt(doubletsHadronic, jets, TopHadronicReader);
//
//     for (const auto & Jet : jets)  {
//         Jets Pieces = GetSubJets(Jet, 2);
//         Pieces = bottom_tagger_.GetJetBdt(Pieces, BottomReader);
//         std::vector<analysis::Doublet> Piecedoublets = WTagger.GetBdt(Pieces, WReader);
//         std::vector<analysis::Triplet> Piecetriplets = top_hadronic_tagger.GetBdt(Piecedoublets, jets, TopHadronicReader);
//         tripletsHadronic.insert(tripletsHadronic.end(), Piecetriplets.begin(), Piecetriplets.end());
//     }
//
//     for (const auto & Jet : jets)  {
//         Jets Pieces = GetSubJets(Jet, 3);
//         Pieces = bottom_tagger_.GetJetBdt(Pieces, BottomReader);
//         std::vector<analysis::Doublet> Piecedoublets = WTagger.GetBdt(Pieces, WReader);
//         std::vector<analysis::Triplet> Piecetriplets = top_hadronic_tagger.GetBdt(Piecedoublets, jets, TopHadronicReader);
//         tripletsHadronic.insert(tripletsHadronic.end(), Piecetriplets.begin(), Piecetriplets.end());
//     }
    std::vector<analysis::Triplet> Finaltriplets;
    if (Tag == kSignal) {
        Jets Particles = event.partons().Generator();
        Jets TopParticles = RemoveIfWrongAbsFamily(Particles, TopId, GluonId);
        if (TopParticles.size() != 1) Print(kError, "Where is the Top?",TopParticles.size());
        else for (const auto & triplet : tripletsHadronic) if ((triplet.Jet().delta_R(TopParticles.at(0)) < detector_geometry().JetConeSize)) Finaltriplets.emplace_back(triplet);
    } else Finaltriplets = tripletsHadronic;

    if (Tag == kSignal && Finaltriplets.size() > 1) {
        std::sort(Finaltriplets.begin(), Finaltriplets.end());
        Finaltriplets.erase(Finaltriplets.begin() + 1, Finaltriplets.end());
    }

    Jets FinalBottoms;
    if (Tag == kSignal) {
        Jets Particles = event.partons().Generator();
        Jets BottomParticles = RemoveIfWrongAbsFamily(Particles, BottomId, GluonId);
        if (BottomParticles.size() != 1) Print(kError, "Where is the Bottom?",BottomParticles.size());
        else for (const auto & Jet : jets)  if ((Jet.delta_R(BottomParticles.at(0)) < detector_geometry().JetConeSize)) FinalBottoms.emplace_back(Jet);
    } else FinalBottoms = jets;


//     std::vector<analysis::Doublet> doubletsHadronic = WTagger.GetBdt(jets, WReader);
//     std::vector<analysis::Triplet> tripletsHadronic = top_hadronic_tagger.GetBdt(doubletsHadronic, jets, TopHadronicReader);

    std::vector<analysis::Quartet31> Jetquartets = ChargedJetPairTagger.GetBdt(tripletsHadronic, jets, ChargedJetPairReader);


//     Jets TopParticles = event.partons().Generator();
//     TopParticles.erase(std::remove_if(TopParticles.begin(), TopParticles.end(), WrongAbsFamily(TopId, GluonId)), TopParticles.end());
//     if (Tag== kSignal && TopParticles.size() != 1) Print(kError, "Where is the Top?");
//     Jets BottomParticles = event.partons().Generator();
//     BottomParticles.erase(std::remove_if(BottomParticles.begin(), BottomParticles.end(), WrongAbsFamily(BottomId, GluonId)), BottomParticles.end());
//     if (Tag== kSignal && BottomParticles.size() != 1) Print(kError, "Where is the Bottom?");
//
//     if (TopParticles.size() > 0 && BottomParticles.size() > 0) {
//         analysis::Doublet ParticlePair(TopParticles.front(), BottomParticles.front());
//         std::sort(Jetquartets.begin(), Jetquartets.end(), MinDeltaR(ParticlePair.Jet()));
//         if (Tag == kSignal && Jetquartets.size() > 1) Jetquartets.erase(Jetquartets.begin() + 1, Jetquartets.end());
//         if (Tag == HBackground && Jetquartets.size() > 0) Jetquartets.erase(Jetquartets.begin());
//     }

    std::vector<HOctet44> Octets = SignatureSemiTagger.GetBdt(Higgsquartets, Jetquartets, SignatureSemiReader);


    std::vector<EventMultiplet<HOctet44>> events;
    for (const auto & Octet : Octets) {
        EventMultiplet<HOctet44> Octetevent(Octet);
        EventStruct event_struct;
        event_struct.LeptonNumber = event.leptons().GetLeptonJets().size();
        event_struct.JetNumber = event.hadrons().GetJets().size();
        event_struct.BottomNumber = event.hadrons().GetBottomJets().size();
        event_struct.ScalarHt = event.hadrons().GetScalarHt();
        event_struct.MissingEt = event.hadrons().GetMissingEt().pt();
        Octetevent.Setevent_struct(event_struct);
        Octetevent.SetLeptons(Leptons);
        Octetevent.SetTotalJets(jets);
        Octetevent.SetSubJets(SubJets);
        Octetevent.SetTag(Tag);
        for (const auto & Jet : jets)  {
            if (Jet.delta_R(Octetevent.Octet().quartet1().singlet()) < detector_geometry().JetConeSize) continue;
            if (Jet.delta_R(Octetevent.Octet().quartet1().triplet().singlet()) < detector_geometry().JetConeSize) continue;
            if (Jet.delta_R(Octetevent.Octet().quartet1().triplet().doublet().Singlet1()) < detector_geometry().JetConeSize) continue;
            if (Jet.delta_R(Octetevent.Octet().quartet1().triplet().doublet().Singlet2()) < detector_geometry().JetConeSize) continue;
            if (Jet.delta_R(Octetevent.Octet().quartet2().singlet()) < detector_geometry().JetConeSize) continue;
            if (Jet.delta_R(Octetevent.Octet().quartet2().triplet().singlet()) < detector_geometry().JetConeSize) continue;
            Octetevent.AddRestJet(Jet);
        }
        events.emplace_back(Octetevent);
    }

    std::vector<hheavyhiggs::HChargedSemiBranch> eventSemiBranches;
    for (const auto & event : events)eventSemiBranches.emplace_back(GetBranch(event));

    return eventSemiBranches;

}

std::vector<EventMultiplet<HOctet44>> hheavyhiggs::HChargedeventSemiTagger::GetBdt(const std::vector<HOctet44> &Octets, Jets &jets, const Jets &SubJets, Jets &Leptons, EventStruct &event_struct, const analysis::Reader &eventSemiReader)
{
    Print(kInformation, "Get event Tags");


    std::vector<EventMultiplet<HOctet44>> events;
    for (auto & Octet : Octets) {
        EventMultiplet<HOctet44> Octetevent(Octet, event_struct);
        for (const auto & Jet : jets)  {
            if (Octet.quartet1().singlet().delta_R(Jet) < detector_geometry().JetConeSize) continue;
            if (Octet.quartet1().triplet().singlet().delta_R(Jet) < detector_geometry().JetConeSize) continue;
            if (Octet.quartet1().triplet().doublet().Singlet1().delta_R(Jet) < detector_geometry().JetConeSize) continue;
            if (Octet.quartet1().triplet().doublet().Singlet2().delta_R(Jet) < detector_geometry().JetConeSize) continue;
            if (Octet.quartet2().singlet().delta_R(Jet) < detector_geometry().JetConeSize) continue;
            if (Octet.quartet2().triplet().singlet().delta_R(Jet) < detector_geometry().JetConeSize) continue;
            if (Octet.quartet2().triplet().doublet().Singlet1().delta_R(Jet) < detector_geometry().JetConeSize) continue;
            if (Octet.quartet2().triplet().doublet().Singlet2().delta_R(Jet) < detector_geometry().JetConeSize) continue;
            Octetevent.AddRestJet(Jet);
        }
        Octetevent.SetLeptons(Leptons);
        Octetevent.SetTotalJets(jets);
        Octetevent.SetSubJets(SubJets);
        Branch = GetBranch(Octetevent);
        Octetevent.SetBdt(eventSemiReader.Bdt());
        events.emplace_back(Octetevent);
    }

    std::sort(events.begin(), events.end());
    if (events.size() > 1)events.erase(events.begin() + 1, events.end());
    Print(kInformation, "event Number", events.size(), jets.size());

    return events;
}

float hheavyhiggs::HChargedeventSemiTagger::ReadBdt(const TClonesArray &eventClonesArray, const int Entry)
{
    return ((HChargedSemiBranch *) eventClonesArray.At(Entry))->Bdt;
}


