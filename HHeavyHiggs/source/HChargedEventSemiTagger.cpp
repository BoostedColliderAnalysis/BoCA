# include "HChargedEventSemiTagger.hh"

hheavyhiggs::HChargedEventSemiTagger::HChargedEventSemiTagger()
{
//       DebugLevel = HDebug;
    Print(HInformation , "Constructor");
    DefineVariables();
}

void hheavyhiggs::HChargedEventSemiTagger::SetTagger(
    const hanalysis::BottomTagger &NewBottomTagger,
    const hanalysis::HChargedJetPairTagger &NewChargedJetPairTagger,
    const hanalysis::HWSemiTagger &NewWSemiTagger,
    const hanalysis::HWHadronicTagger &NewWTagger,
    const hanalysis::HTopSemiTagger &NewTopSemiTagger,
    const hanalysis::HTopHadronicTagger &NewTopHadronicTagger,
    const hanalysis::HChargedHiggsSemiTagger &NewChargedHiggsSemiTagger,
    const hheavyhiggs::HChargedSignatureSemiTagger &NewChargedSignatureTagger)
{
    bottom_tagger_ = NewBottomTagger;
    WSemiTagger = NewWSemiTagger;
    WTagger = NewWTagger;
    TopHadronicTagger = NewTopHadronicTagger;
    TopSemiTagger = NewTopSemiTagger;
    ChargedJetPairTagger = NewChargedJetPairTagger;
    ChargedHiggsSemiTagger = NewChargedHiggsSemiTagger;
    SignatureSemiTagger = NewChargedSignatureTagger;
    DefineVariables();
}

void hheavyhiggs::HChargedEventSemiTagger::DefineVariables()
{
    Print(HNotification , "Define Variables");
    set_tagger_name("ChargedEventSemi");
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

    Print(HNotification, "Variables defined");

}

hheavyhiggs::HChargedSemiBranch hheavyhiggs::HChargedEventSemiTagger::GetBranch(const HEventMultiplet< HOctet44 > &Event) const
{
    Print(HInformation, "FillPairTagger", Event.Bdt());

    HChargedSemiBranch EventSemiBranch;
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
    EventSemiBranch.DeltaHt = Event.DeltaHt();
    EventSemiBranch.DeltaM = Event.DeltaM();
    EventSemiBranch.DeltaRap = Event.DeltaRap();
    EventSemiBranch.DeltaPhi = Event.DeltaPhi();
    EventSemiBranch.DeltaR = Event.DeltaR();

    EventSemiBranch.Bdt = Event.Bdt();
    EventSemiBranch.Tag = Event.Tag();

    EventSemiBranch.HiggsMass = Event.Octet().Quartet1().Jet().m();
    EventSemiBranch.PairRap = Event.Octet().Quartet2().DeltaRap();
    EventSemiBranch.HiggsBdt = Event.Octet().Quartet1().Bdt();
    EventSemiBranch.SignatureBdt = Event.Octet().Bdt();
    EventSemiBranch.BottomBdt = Event.Octet().BottomBdt();
    EventSemiBranch.PairBottomBdt = Event.Octet().PairBottomBdt();

    EventSemiBranch.BottomBdt1 = Event.BottomBdt(1);
    EventSemiBranch.BottomBdt2 = Event.BottomBdt(2);
    EventSemiBranch.BottomBdt3 = Event.BottomBdt(3);
    EventSemiBranch.BottomBdt4 = Event.BottomBdt(4);
    EventSemiBranch.BottomBdt5 = Event.BottomBdt(5);
    EventSemiBranch.BottomBdt6 = Event.BottomBdt(6);
    EventSemiBranch.BottomBdt7 = Event.BottomBdt(7);
    EventSemiBranch.BottomBdt8 = Event.BottomBdt(8);
    EventSemiBranch.BottomBdt12 = Event.BottomBdt(1, 2);
    EventSemiBranch.BottomBdt34 = Event.BottomBdt(3, 4);
    EventSemiBranch.BottomBdt56 = Event.BottomBdt(5, 6);
    EventSemiBranch.BottomBdt78 = Event.BottomBdt(7, 8);

    EventSemiBranch.SubBottomBdt1 = Event.SubBottomBdt(1);
    EventSemiBranch.SubBottomBdt2 = Event.SubBottomBdt(2);
    EventSemiBranch.SubBottomBdt3 = Event.SubBottomBdt(3);
    EventSemiBranch.SubBottomBdt4 = Event.SubBottomBdt(4);
    EventSemiBranch.SubBottomBdt5 = Event.SubBottomBdt(5);
    EventSemiBranch.SubBottomBdt6 = Event.SubBottomBdt(6);
    EventSemiBranch.SubBottomBdt7 = Event.SubBottomBdt(7);
    EventSemiBranch.SubBottomBdt8 = Event.SubBottomBdt(8);
    EventSemiBranch.SubBottomBdt12 = Event.SubBottomBdt(1, 2);
    EventSemiBranch.SubBottomBdt34 = Event.SubBottomBdt(3, 4);
    EventSemiBranch.SubBottomBdt56 = Event.SubBottomBdt(5, 6);
    EventSemiBranch.SubBottomBdt78 = Event.SubBottomBdt(7, 8);

    EventSemiBranch.RestNumber = Event.RestNumber();
    EventSemiBranch.RestM = Event.RestJet().m();
    EventSemiBranch.RestPt = Event.RestJet().pt();
    EventSemiBranch.RestHt = Event.RestHt();
    EventSemiBranch.RestRap = Event.RestJet().rap();
    if (std::abs(EventSemiBranch.RestRap) > 100) EventSemiBranch.RestRap = 0;
    EventSemiBranch.RestPhi = Event.RestJet().phi();
    EventSemiBranch.RestBdt = Event.RestBdt();
    EventSemiBranch.MissingEt = Event.MissingEt();

    EventSemiBranch.LeptonHt = Event.LeptonHt();

    return EventSemiBranch;
}

struct SortJetsByBdt {
    inline bool operator()(const fastjet::PseudoJet &Jet1, const fastjet::PseudoJet &Jet2) {
        return (Jet1.user_info<hanalysis::HJetInfo>().Bdt() > Jet2.user_info<hanalysis::HJetInfo>().Bdt());
    }
};

std::vector<hheavyhiggs::HChargedSemiBranch> hheavyhiggs::HChargedEventSemiTagger::GetBranches(hanalysis::HEvent &Event, const HObject::Tag Tag)
{
    Print(HInformation, "Get Event Tags");

    HJets PreJets = GetJets(Event);
    HJets Jets = bottom_tagger_.GetJetBdt(PreJets, BottomReader);
    HJets SubJets = bottom_tagger_.GetMultiJetBdt(PreJets, BottomReader);

    HJets Leptons = Event.GetLeptons()->GetLeptonJets();
    fastjet::PseudoJet MissingEt = Event.GetJets()->GetMissingEt();
    std::vector<hanalysis::HDoublet> DoubletsSemi = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);
    std::vector<hanalysis::HTriplet> TripletsSemi = TopSemiTagger.GetBdt(DoubletsSemi, Jets, TopSemiReader);
    std::vector<hanalysis::HQuartet31> HiggsQuartets = ChargedHiggsSemiTagger.GetBdt(TripletsSemi, Jets, ChargedHiggsSemiReader);


    HJets HiggsParticles = Event.GetParticles()->Generator();
    HiggsParticles.erase(std::remove_if(HiggsParticles.begin(), HiggsParticles.end(), WrongAbsId(ChargedHiggsId)), HiggsParticles.end());
    if (Tag == kSignal && HiggsParticles.size() != 1) Print(HError, "Where is the Higgs?");
    std::sort(HiggsQuartets.begin(), HiggsQuartets.end(), MinDeltaRTo(HiggsParticles.front()));
    if (Tag == kSignal && HiggsQuartets.size() > 1) HiggsQuartets.erase(HiggsQuartets.begin() + 1, HiggsQuartets.end());
    if (Tag == kBackground && HiggsQuartets.size() > 0) HiggsQuartets.erase(HiggsQuartets.begin());


    std::vector<hanalysis::HTriplet> TripletsHadronic = TopHadronicTagger.GetBdt(Jets, TopHadronicReader, WTagger, WReader, bottom_tagger_, BottomReader);
//     std::vector<hanalysis::HDoublet> DoubletsHadronic = WTagger.GetBdt(Jets, WReader);
//     std::vector<hanalysis::HTriplet> TripletsHadronic = TopHadronicTagger.GetBdt(DoubletsHadronic, Jets, TopHadronicReader);
//
//     for (const auto & Jet : Jets) {
//         HJets Pieces = GetSubJets(Jet, 2);
//         Pieces = bottom_tagger_.GetJetBdt(Pieces, BottomReader);
//         std::vector<hanalysis::HDoublet> PieceDoublets = WTagger.GetBdt(Pieces, WReader);
//         std::vector<hanalysis::HTriplet> PieceTriplets = TopHadronicTagger.GetBdt(PieceDoublets, Jets, TopHadronicReader);
//         TripletsHadronic.insert(TripletsHadronic.end(), PieceTriplets.begin(), PieceTriplets.end());
//     }
//
//     for (const auto & Jet : Jets) {
//         HJets Pieces = GetSubJets(Jet, 3);
//         Pieces = bottom_tagger_.GetJetBdt(Pieces, BottomReader);
//         std::vector<hanalysis::HDoublet> PieceDoublets = WTagger.GetBdt(Pieces, WReader);
//         std::vector<hanalysis::HTriplet> PieceTriplets = TopHadronicTagger.GetBdt(PieceDoublets, Jets, TopHadronicReader);
//         TripletsHadronic.insert(TripletsHadronic.end(), PieceTriplets.begin(), PieceTriplets.end());
//     }
    std::vector<hanalysis::HTriplet> FinalTriplets;
    if (Tag == kSignal) {
        HJets Particles = Event.GetParticles()->Generator();
        HJets TopParticles = RemoveIfWrongAbsFamily(Particles, TopId, GluonId);
        if (TopParticles.size() != 1) Print(HError, "Where is the Top?",TopParticles.size());
        else for (const auto & Triplet : TripletsHadronic) if ((Triplet.Jet().delta_R(TopParticles.at(0)) < detector_geometry().JetConeSize)) FinalTriplets.emplace_back(Triplet);
    } else FinalTriplets = TripletsHadronic;

    if (Tag == kSignal && FinalTriplets.size() > 1) {
        std::sort(FinalTriplets.begin(), FinalTriplets.end());
        FinalTriplets.erase(FinalTriplets.begin() + 1, FinalTriplets.end());
    }

    HJets FinalBottoms;
    if (Tag == kSignal) {
        HJets Particles = Event.GetParticles()->Generator();
        HJets BottomParticles = RemoveIfWrongAbsFamily(Particles, BottomId, GluonId);
        if (BottomParticles.size() != 1) Print(HError, "Where is the Bottom?",BottomParticles.size());
        else for (const auto & Jet : Jets) if ((Jet.delta_R(BottomParticles.at(0)) < detector_geometry().JetConeSize)) FinalBottoms.emplace_back(Jet);
    } else FinalBottoms = Jets;


//     std::vector<hanalysis::HDoublet> DoubletsHadronic = WTagger.GetBdt(Jets, WReader);
//     std::vector<hanalysis::HTriplet> TripletsHadronic = TopHadronicTagger.GetBdt(DoubletsHadronic, Jets, TopHadronicReader);

    std::vector<hanalysis::HQuartet31> JetQuartets = ChargedJetPairTagger.GetBdt(TripletsHadronic, Jets, ChargedJetPairReader);


//     HJets TopParticles = Event.GetParticles()->Generator();
//     TopParticles.erase(std::remove_if(TopParticles.begin(), TopParticles.end(), WrongAbsFamily(TopId, GluonId)), TopParticles.end());
//     if (Tag== kSignal && TopParticles.size() != 1) Print(HError, "Where is the Top?");
//     HJets BottomParticles = Event.GetParticles()->Generator();
//     BottomParticles.erase(std::remove_if(BottomParticles.begin(), BottomParticles.end(), WrongAbsFamily(BottomId, GluonId)), BottomParticles.end());
//     if (Tag== kSignal && BottomParticles.size() != 1) Print(HError, "Where is the Bottom?");
//
//     if (TopParticles.size() > 0 && BottomParticles.size() > 0) {
//         hanalysis::HDoublet ParticlePair(TopParticles.front(), BottomParticles.front());
//         std::sort(JetQuartets.begin(), JetQuartets.end(), MinDeltaR(ParticlePair.Jet()));
//         if (Tag == kSignal && JetQuartets.size() > 1) JetQuartets.erase(JetQuartets.begin() + 1, JetQuartets.end());
//         if (Tag == HBackground && JetQuartets.size() > 0) JetQuartets.erase(JetQuartets.begin());
//     }

    std::vector<HOctet44> Octets = SignatureSemiTagger.GetBdt(HiggsQuartets, JetQuartets, SignatureSemiReader);


    std::vector<HEventMultiplet<HOctet44>> Events;
    for (const auto & Octet : Octets) {
        HEventMultiplet<HOctet44> OctetEvent(Octet);
        HEventStruct EventStruct;
        EventStruct.LeptonNumber = Event.GetLeptons()->GetLeptonJets().size();
        EventStruct.JetNumber = Event.GetJets()->GetJets().size();
        EventStruct.BottomNumber = Event.GetJets()->GetBottomJets().size();
        EventStruct.ScalarHt = Event.GetJets()->GetScalarHt();
        EventStruct.MissingEt = Event.GetJets()->GetMissingEt().pt();
        OctetEvent.SetEventStruct(EventStruct);
        OctetEvent.SetLeptons(Leptons);
        OctetEvent.SetTotalJets(Jets);
        OctetEvent.SetSubJets(SubJets);
        OctetEvent.SetTag(Tag);
        for (const auto & Jet : Jets) {
            if (Jet.delta_R(OctetEvent.Octet().Quartet1().Singlet()) < detector_geometry().JetConeSize) continue;
            if (Jet.delta_R(OctetEvent.Octet().Quartet1().Triplet().Singlet()) < detector_geometry().JetConeSize) continue;
            if (Jet.delta_R(OctetEvent.Octet().Quartet1().Triplet().Doublet().Singlet1()) < detector_geometry().JetConeSize) continue;
            if (Jet.delta_R(OctetEvent.Octet().Quartet1().Triplet().Doublet().Singlet2()) < detector_geometry().JetConeSize) continue;
            if (Jet.delta_R(OctetEvent.Octet().Quartet2().Singlet()) < detector_geometry().JetConeSize) continue;
            if (Jet.delta_R(OctetEvent.Octet().Quartet2().Triplet().Singlet()) < detector_geometry().JetConeSize) continue;
            OctetEvent.AddRestJet(Jet);
        }
        Events.emplace_back(OctetEvent);
    }

    std::vector<hheavyhiggs::HChargedSemiBranch> EventSemiBranches;
    for (const auto & event : Events)EventSemiBranches.emplace_back(GetBranch(event));

    return EventSemiBranches;

}

std::vector<HEventMultiplet<HOctet44>> hheavyhiggs::HChargedEventSemiTagger::GetBdt(const std::vector<HOctet44> &Octets, HJets &Jets, const HJets &SubJets, HJets &Leptons, HEventStruct &EventStruct, const hanalysis::Reader &EventSemiReader)
{
    Print(HInformation, "Get Event Tags");


    std::vector<HEventMultiplet<HOctet44>> Events;
    for (auto & Octet : Octets) {
        HEventMultiplet<HOctet44> OctetEvent(Octet, EventStruct);
        for (const auto & Jet : Jets) {
            if (Octet.Quartet1().Singlet().delta_R(Jet) < detector_geometry().JetConeSize) continue;
            if (Octet.Quartet1().Triplet().Singlet().delta_R(Jet) < detector_geometry().JetConeSize) continue;
            if (Octet.Quartet1().Triplet().Doublet().Singlet1().delta_R(Jet) < detector_geometry().JetConeSize) continue;
            if (Octet.Quartet1().Triplet().Doublet().Singlet2().delta_R(Jet) < detector_geometry().JetConeSize) continue;
            if (Octet.Quartet2().Singlet().delta_R(Jet) < detector_geometry().JetConeSize) continue;
            if (Octet.Quartet2().Triplet().Singlet().delta_R(Jet) < detector_geometry().JetConeSize) continue;
            if (Octet.Quartet2().Triplet().Doublet().Singlet1().delta_R(Jet) < detector_geometry().JetConeSize) continue;
            if (Octet.Quartet2().Triplet().Doublet().Singlet2().delta_R(Jet) < detector_geometry().JetConeSize) continue;
            OctetEvent.AddRestJet(Jet);
        }
        OctetEvent.SetLeptons(Leptons);
        OctetEvent.SetTotalJets(Jets);
        OctetEvent.SetSubJets(SubJets);
        Branch = GetBranch(OctetEvent);
        OctetEvent.SetBdt(EventSemiReader.Bdt());
        Events.emplace_back(OctetEvent);
    }

    std::sort(Events.begin(), Events.end());
    if (Events.size() > 1)Events.erase(Events.begin() + 1, Events.end());
    Print(HInformation, "Event Number", Events.size(), Jets.size());

    return Events;
}

float hheavyhiggs::HChargedEventSemiTagger::ReadBdt(const TClonesArray &EventClonesArray, const int Entry)
{
    return ((HChargedSemiBranch *) EventClonesArray.At(Entry))->Bdt;
}


