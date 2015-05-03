# include "HEventSemiTagger.hh"

hheavyhiggs::HEventSemiTagger::HEventSemiTagger()
{
    //   DebugLevel = HDebug;
    Print(HNotification , "Constructor");
    DefineVariables();
}

hheavyhiggs::HEventSemiTagger::~HEventSemiTagger()
{
    Print(HNotification , "Constructor");
}

void hheavyhiggs::HEventSemiTagger::SetTagger(
    const hanalysis::HBottomTagger &NewBottomTagger,
    const hanalysis::HJetPairTagger &NewJetPairTagger,
    const hanalysis::HWSemiTagger &NewWSemiTagger,
    const hanalysis::HWTagger &NewWTagger,
    const hanalysis::HTopSemiTagger &NewTopSemiTagger,
    const hanalysis::HTopHadronicTagger &NewTopHadronicTagger,
    const hanalysis::HHeavyHiggsSemiTagger &NewHeavyHiggsSemiTagger,
    const HSignatureSemiTagger &NewSignatureSemiTagger)
{
    Print(HNotification , "Constructor");

    BottomTagger = NewBottomTagger;
    WSemiTagger = NewWSemiTagger;
    WTagger = NewWTagger;
    TopSemiTagger = NewTopSemiTagger;
    TopHadronicTagger = NewTopHadronicTagger;
    HeavyHiggsSemiTagger = NewHeavyHiggsSemiTagger;
    JetPairTagger = NewJetPairTagger;
    SignatureSemiTagger = NewSignatureSemiTagger;
    DefineVariables();
}

void hheavyhiggs::HEventSemiTagger::DefineVariables()
{
    Print(HNotification , "Define Variables");
    SetTaggerName("EventSemi");

    ClearVectors();


    AddSpectator(Branch.LeptonNumber, "LeptonNumber");
    AddObservable(Branch.JetNumber, "JetNumber");
    AddObservable(Branch.BottomNumber, "BottomNumber");
    AddObservable(Branch.ScalarHt, "ScalarHt");

    AddObservable(Branch.Mass, "Mass");
    AddObservable(Branch.Pt, "Pt");
    AddObservable(Branch.Rap, "Rap");
    AddObservable(Branch.Phi, "Phi");
    AddObservable(Branch.Ht, "Ht");

    AddObservable(Branch.DeltaPt, "DeltaPt");
    AddObservable(Branch.DeltaHt, "DeltaHt");
    AddObservable(Branch.DeltaM, "DeltaM");
    AddObservable(Branch.DeltaRap, "DeltaRap");
    AddObservable(Branch.DeltaPhi, "DeltaPhi");
    AddObservable(Branch.DeltaR, "DeltaR");

    AddObservable(Branch.HiggsMass, "HiggsMass");
    AddObservable(Branch.PairRap, "PairRap");
    AddObservable(Branch.HiggsBdt, "HiggsBdt");
    AddObservable(Branch.SignatureBdt, "SignatureBdt");
    AddObservable(Branch.BottomBdt, "BottomBdt");
    AddObservable(Branch.PairBottomBdt, "PairBottomBdt");

    AddObservable(Branch.HardTopPt, "HardTopPt");
    AddObservable(Branch.SoftTopPt, "SoftTopPt");

    AddObservable(Branch.MissingEt, "MissingEt");

    AddObservable(Branch.BottomBdt1, "BottomBdt1");
    AddObservable(Branch.BottomBdt2, "BottomBdt2");
    AddObservable(Branch.BottomBdt3, "BottomBdt3");
    AddObservable(Branch.BottomBdt4, "BottomBdt4");
    AddObservable(Branch.BottomBdt5, "BottomBdt5");
    AddObservable(Branch.BottomBdt6, "BottomBdt6");
    AddObservable(Branch.BottomBdt7, "BottomBdt7");
    AddObservable(Branch.BottomBdt8, "BottomBdt8");
    AddObservable(Branch.BottomBdt12, "BottomBdt12");
    AddObservable(Branch.BottomBdt34, "BottomBdt34");
    AddObservable(Branch.BottomBdt56, "BottomBdt56");
    AddObservable(Branch.BottomBdt78, "BottomBdt78");

    AddObservable(Branch.SubBottomBdt1, "SubBottomBdt1");
    AddObservable(Branch.SubBottomBdt2, "SubBottomBdt2");
    AddObservable(Branch.SubBottomBdt3, "SubBottomBdt3");
    AddObservable(Branch.SubBottomBdt4, "SubBottomBdt4");
    AddObservable(Branch.SubBottomBdt5, "SubBottomBdt5");
    AddObservable(Branch.SubBottomBdt6, "SubBottomBdt6");
    AddObservable(Branch.SubBottomBdt7, "SubBottomBdt7");
    AddObservable(Branch.SubBottomBdt8, "SubBottomBdt8");
    AddObservable(Branch.SubBottomBdt12, "SubBottomBdt12");
    AddObservable(Branch.SubBottomBdt34, "SubBottomBdt34");
    AddObservable(Branch.SubBottomBdt56, "SubBottomBdt56");
    AddObservable(Branch.SubBottomBdt78, "SubBottomBdt78");

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

hheavyhiggs::HEventSemiBranch hheavyhiggs::HEventSemiTagger::GetBranch(const HEventMultiplet<HOctet> &Event) const
{
    Print(HInformation, "FillPairTagger", Event.Bdt());

    HEventSemiBranch EventSemiBranch;
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

    EventSemiBranch.HiggsMass = Event.Octet().Sextet().Jet().m();
    EventSemiBranch.HiggsBdt = Event.Octet().Sextet().Bdt();
    EventSemiBranch.SignatureBdt = Event.Octet().Bdt();
    EventSemiBranch.PairRap = Event.Octet().Doublet().DeltaRap();
    EventSemiBranch.BottomBdt = Event.Octet().BottomBdt();
    EventSemiBranch.PairBottomBdt = Event.Octet().PairBottomBdt();

    EventSemiBranch.HardTopPt = Event.Octet().Sextet().HardTopPt();
    EventSemiBranch.SoftTopPt = Event.Octet().Sextet().SoftTopPt();

    EventSemiBranch.MissingEt = Event.MissingEt();

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

    EventSemiBranch.LeptonHt = Event.LeptonHt();

    return EventSemiBranch;

}

struct SortJetsByBdt {
    inline bool operator()(const fastjet::PseudoJet &Jet1, const fastjet::PseudoJet &Jet2) {
        return (Jet1.user_info<hanalysis::HJetInfo>().Bdt() > Jet2.user_info<hanalysis::HJetInfo>().Bdt());
    }
};


std::vector<hheavyhiggs::HEventSemiBranch> hheavyhiggs::HEventSemiTagger::GetBranches(hanalysis::HEvent &Event, const HObject::HTag Tag)
{
    Print(HInformation, "Get Event Tags");

    HJets PreJets = GetJets(Event);
    HJets Jets = BottomTagger.GetJetBdt(PreJets, BottomReader);
    HJets SubJets = BottomTagger.GetMultiJetBdt(PreJets, BottomReader);

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
    if (Tag == HSignal) {
        if (HiggsParticles.size() == 1) HiggsBoson = HiggsParticles.front();
        else Print(HError, "Where is the Higgs?", HiggsParticles.size());
        std::sort(Sextets.begin(), Sextets.end(), MinDeltaR(HiggsParticles.front()));
        if (Sextets.size() > 1) Sextets.erase(Sextets.begin() + 1, Sextets.end());
    }

    std::vector<hanalysis::HDoublet> Doublets = JetPairTagger.GetBdt(Jets, JetPairReader);

    std::vector<hanalysis::HDoublet> FinalDoublets;
    HJets Particles = Event.GetParticles()->Generator();
    if (Tag == HSignal) {
        Particles = RemoveIfWrongAbsFamily(Particles, BottomId, GluonId);
        if (Particles.size() == 2) {
            for (const auto & Doublet : Doublets) {
                if ((Doublet.Singlet1().delta_R(Particles.at(0)) < DetectorGeometry.JetConeSize && Doublet.Singlet2().delta_R(Particles.at(1)) < DetectorGeometry.JetConeSize) || (Doublet.Singlet1().delta_R(Particles.at(1)) < DetectorGeometry.JetConeSize && Doublet.Singlet2().delta_R(Particles.at(0)) < DetectorGeometry.JetConeSize)) FinalDoublets.push_back(Doublet);
            }
        } else Print(HError, "Where is the Quark Pair", Particles.size());
    }
    if (Tag == HBackground)
        FinalDoublets = Doublets;

    std::vector<HOctet> Octets = SignatureSemiTagger.GetBdt(Sextets, FinalDoublets, SignatureSemiReader);


    std::vector<HEventMultiplet<HOctet>> Events;
    for (const auto & Octet : Octets) {
        HEventMultiplet<HOctet> OctetEvent(Octet);
        HEventStruct EventStruct;
        EventStruct.LeptonNumber = Event.GetLeptons()->GetLeptonJets().size();
        EventStruct.JetNumber = Event.GetJets()->GetJets().size();
        EventStruct.BottomNumber = Event.GetJets()->GetBottomJets().size();
        EventStruct.ScalarHt = Event.GetJets()->GetScalarHt();
        EventStruct.MissingEt = Event.GetJets()->GetMissingEt().pt();
//         EventStruct.TrackNumber = Event.GetJets()->GetScalarHt();
        OctetEvent.SetEventStruct(EventStruct);
        OctetEvent.SetLeptons(Leptons);
        OctetEvent.SetTotalJets(Jets);
        OctetEvent.SetSubJets(SubJets);
        OctetEvent.SetTag(Tag);
        for (const auto & Jet : Jets) {
            if (Jet.delta_R(OctetEvent.Octet().Sextet().Triplet1().Singlet()) < DetectorGeometry.JetConeSize) continue;
            if (Jet.delta_R(OctetEvent.Octet().Sextet().Triplet2().Singlet()) < DetectorGeometry.JetConeSize) continue;
            if (Jet.delta_R(OctetEvent.Octet().Sextet().Triplet2().Doublet().Singlet1()) < DetectorGeometry.JetConeSize) continue;
            if (Jet.delta_R(OctetEvent.Octet().Sextet().Triplet2().Doublet().Singlet2()) < DetectorGeometry.JetConeSize) continue;
            if (Jet.delta_R(OctetEvent.Octet().Doublet().Singlet1()) < DetectorGeometry.JetConeSize) continue;
            if (Jet.delta_R(OctetEvent.Octet().Doublet().Singlet2()) < DetectorGeometry.JetConeSize) continue;
            OctetEvent.AddRestJet(Jet);
        }
        Events.push_back(OctetEvent);
    }

    std::vector<hheavyhiggs::HEventSemiBranch> EventSemiBranches;
    for (const auto & event : Events) EventSemiBranches.push_back(GetBranch(event));

    return EventSemiBranches;
}



std::vector<HEventMultiplet<HOctet>> hheavyhiggs::HEventSemiTagger::GetBdt(const std::vector< HOctet > &Octets, const HJets &Jets, const HJets &SubJets, const HJets &Leptons, HEventStruct &EventStruct, const hanalysis::HReader &EventSemiReader)
{
    Print(HInformation, "Get Event Tags", Octets.size());

    std::vector<HEventMultiplet<HOctet>> Events;
    for (const auto & Octet : Octets) {
        HEventMultiplet<HOctet> OctetEvent(Octet, EventStruct);
        for (const auto & Jet : Jets) {
            if (Jet.delta_R(OctetEvent.Octet().Sextet().Triplet1().Singlet()) < DetectorGeometry.JetConeSize) continue;
            if (Jet.delta_R(OctetEvent.Octet().Sextet().Triplet2().Singlet()) < DetectorGeometry.JetConeSize) continue;
            if (Jet.delta_R(OctetEvent.Octet().Sextet().Triplet2().Doublet().Singlet1()) < DetectorGeometry.JetConeSize) continue;
            if (Jet.delta_R(OctetEvent.Octet().Sextet().Triplet2().Doublet().Singlet2()) < DetectorGeometry.JetConeSize) continue;
            if (Jet.delta_R(OctetEvent.Octet().Doublet().Singlet1()) < DetectorGeometry.JetConeSize) continue;
            if (Jet.delta_R(OctetEvent.Octet().Doublet().Singlet2()) < DetectorGeometry.JetConeSize) continue;
            OctetEvent.AddRestJet(Jet);
        }
        OctetEvent.SetLeptons(Leptons);
        OctetEvent.SetTotalJets(Jets);
        OctetEvent.SetSubJets(SubJets);
        Branch = GetBranch(OctetEvent);
        OctetEvent.SetBdt(EventSemiReader.Bdt());
        Events.push_back(OctetEvent);
    }


    std::sort(Events.begin(), Events.end());
    if (Events.size() > 1) Events.erase(Events.begin() + 1, Events.end());
    Print(HInformation, "Event Number", Events.size(), Jets.size());


    return Events;
}

float hheavyhiggs::HEventSemiTagger::ReadBdt(const TClonesArray &EventClonesArray, const int Entry)
{
    return ((HEventSemiBranch *) EventClonesArray.At(Entry))->Bdt;
}
