# include "HEventSemiTagger.hh"

hheavyhiggs::HEventSemiTagger::HEventSemiTagger()
{
    //   DebugLevel = kDebug;
    Print(kNotification , "Constructor");
    DefineVariables();
}

hheavyhiggs::HEventSemiTagger::~HEventSemiTagger()
{
    Print(kNotification , "Constructor");
}

void hheavyhiggs::HEventSemiTagger::SetTagger(
    const hanalysis::BottomTagger &NewBottomTagger,
    const hanalysis::HJetPairTagger &NewJetPairTagger,
    const hanalysis::HWSemiTagger &NewWSemiTagger,
    const hanalysis::HWHadronicTagger &NewWTagger,
    const hanalysis::HTopSemiTagger &NewTopSemiTagger,
    const hanalysis::HTopHadronicTagger &NewTopHadronicTagger,
    const hanalysis::HHeavyHiggsSemiTagger &NewHeavyHiggsSemiTagger,
    const HSignatureSemiTagger &NewSignatureSemiTagger)
{
    Print(kNotification , "Constructor");

    bottom_tagger_ = NewBottomTagger;
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
    Print(kNotification , "Define Variables");
    set_tagger_name("EventSemi");

    ClearVectors();


    AddSpectator(Branch.LeptonNumber, "LeptonNumber");
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

    AddVariable(Branch.HardTopPt, "HardTopPt");
    AddVariable(Branch.SoftTopPt, "SoftTopPt");

    AddVariable(Branch.MissingEt, "MissingEt");

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

    AddVariable(Branch.Bdt, "Bdt");
    AddSpectator(Branch.Tag, "Tag");


    Print(kNotification, "Variables defined");

}

hheavyhiggs::HEventSemiBranch hheavyhiggs::HEventSemiTagger::GetBranch(const HEventMultiplet<HOctet> &Event) const
{
    Print(kInformation, "FillPairTagger", Event.Bdt());

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
    EventSemiBranch.PairRap = Event.Octet().doublet().DeltaRap();
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
        return (Jet1.user_info<hanalysis::JetInfo>().Bdt() > Jet2.user_info<hanalysis::JetInfo>().Bdt());
    }
};


std::vector<hheavyhiggs::HEventSemiBranch> hheavyhiggs::HEventSemiTagger::GetBranches(hanalysis::HEvent &Event, const HObject::Tag Tag)
{
    Print(kInformation, "Get Event Tags");

    Jets PreJets = GetJets(Event);
    Jets jets = bottom_tagger_.GetJetBdt(PreJets, BottomReader);
    Jets SubJets = bottom_tagger_.GetMultiJetBdt(PreJets, BottomReader);

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

    std::vector<hanalysis::Doublet> doublets = JetPairTagger.GetBdt(jets, JetPairReader);

    std::vector<hanalysis::Doublet> Finaldoublets;
    Jets Particles = Event.GetParticles()->Generator();
    if (Tag == kSignal) {
        Particles = RemoveIfWrongAbsFamily(Particles, BottomId, GluonId);
        if (Particles.size() == 2) {
            for (const auto & doublet : doublets) {
                if ((doublet.Singlet1().delta_R(Particles.at(0)) < detector_geometry().JetConeSize && doublet.Singlet2().delta_R(Particles.at(1)) < detector_geometry().JetConeSize) || (doublet.Singlet1().delta_R(Particles.at(1)) < detector_geometry().JetConeSize && doublet.Singlet2().delta_R(Particles.at(0)) < detector_geometry().JetConeSize)) Finaldoublets.emplace_back(doublet);
            }
        } else Print(kError, "Where is the Quark Pair", Particles.size());
    }
    if (Tag == kBackground)
        Finaldoublets = doublets;

    std::vector<HOctet> Octets = SignatureSemiTagger.GetBdt(Sextets, Finaldoublets, SignatureSemiReader);


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
        OctetEvent.SetTotalJets(jets);
        OctetEvent.SetSubJets(SubJets);
        OctetEvent.SetTag(Tag);
        for (const auto & Jet : jets)  {
            if (Jet.delta_R(OctetEvent.Octet().Sextet().triplet1().Singlet()) < detector_geometry().JetConeSize) continue;
            if (Jet.delta_R(OctetEvent.Octet().Sextet().triplet2().Singlet()) < detector_geometry().JetConeSize) continue;
            if (Jet.delta_R(OctetEvent.Octet().Sextet().triplet2().doublet().Singlet1()) < detector_geometry().JetConeSize) continue;
            if (Jet.delta_R(OctetEvent.Octet().Sextet().triplet2().doublet().Singlet2()) < detector_geometry().JetConeSize) continue;
            if (Jet.delta_R(OctetEvent.Octet().doublet().Singlet1()) < detector_geometry().JetConeSize) continue;
            if (Jet.delta_R(OctetEvent.Octet().doublet().Singlet2()) < detector_geometry().JetConeSize) continue;
            OctetEvent.AddRestJet(Jet);
        }
        Events.emplace_back(OctetEvent);
    }

    std::vector<hheavyhiggs::HEventSemiBranch> EventSemiBranches;
    for (const auto & event : Events) EventSemiBranches.emplace_back(GetBranch(event));

    return EventSemiBranches;
}



std::vector<HEventMultiplet<HOctet>> hheavyhiggs::HEventSemiTagger::GetBdt(const std::vector< HOctet > &Octets, const Jets &jets, const Jets &SubJets, const Jets &Leptons, HEventStruct &EventStruct, const hanalysis::Reader &EventSemiReader)
{
    Print(kInformation, "Get Event Tags", Octets.size());

    std::vector<HEventMultiplet<HOctet>> Events;
    for (const auto & Octet : Octets) {
        HEventMultiplet<HOctet> OctetEvent(Octet, EventStruct);
        for (const auto & Jet : jets)  {
            if (Jet.delta_R(OctetEvent.Octet().Sextet().triplet1().Singlet()) < detector_geometry().JetConeSize) continue;
            if (Jet.delta_R(OctetEvent.Octet().Sextet().triplet2().Singlet()) < detector_geometry().JetConeSize) continue;
            if (Jet.delta_R(OctetEvent.Octet().Sextet().triplet2().doublet().Singlet1()) < detector_geometry().JetConeSize) continue;
            if (Jet.delta_R(OctetEvent.Octet().Sextet().triplet2().doublet().Singlet2()) < detector_geometry().JetConeSize) continue;
            if (Jet.delta_R(OctetEvent.Octet().doublet().Singlet1()) < detector_geometry().JetConeSize) continue;
            if (Jet.delta_R(OctetEvent.Octet().doublet().Singlet2()) < detector_geometry().JetConeSize) continue;
            OctetEvent.AddRestJet(Jet);
        }
        OctetEvent.SetLeptons(Leptons);
        OctetEvent.SetTotalJets(jets);
        OctetEvent.SetSubJets(SubJets);
        Branch = GetBranch(OctetEvent);
        OctetEvent.SetBdt(EventSemiReader.Bdt());
        Events.emplace_back(OctetEvent);
    }


    std::sort(Events.begin(), Events.end());
    if (Events.size() > 1) Events.erase(Events.begin() + 1, Events.end());
    Print(kInformation, "Event Number", Events.size(), jets.size());


    return Events;
}

float hheavyhiggs::HEventSemiTagger::ReadBdt(const TClonesArray &EventClonesArray, const int Entry)
{
    return ((HEventSemiBranch *) EventClonesArray.At(Entry))->Bdt;
}
