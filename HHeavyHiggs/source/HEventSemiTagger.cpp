# include "HEventSemiTagger.hh"

hheavyhiggs::EventSemiTagger::EventSemiTagger()
{
    //   DebugLevel = kDebug;
    Print(kNotification , "Constructor");
    DefineVariables();
}

hheavyhiggs::EventSemiTagger::~EventSemiTagger()
{
    Print(kNotification , "Constructor");
}

void hheavyhiggs::EventSemiTagger::SetTagger(
    const hanalysis::BottomTagger &NewBottomTagger,
    const hanalysis::HJetPairTagger &NewJetPairTagger,
    const hanalysis::HWSemiTagger &NewWSemiTagger,
    const hanalysis::WHadronicTagger &NewWTagger,
    const hanalysis::HTopSemiTagger &NewTopSemiTagger,
    const hanalysis::TopHadronicTagger &Newtop_hadronic_tagger,
    const hanalysis::HHeavyHiggsSemiTagger &NewHeavyHiggsSemiTagger,
    const HSignatureSemiTagger &NewSignatureSemiTagger)
{
    Print(kNotification , "Constructor");

    bottom_tagger_ = NewBottomTagger;
    WSemiTagger = NewWSemiTagger;
    WTagger = NewWTagger;
    TopSemiTagger = NewTopSemiTagger;
    top_hadronic_tagger = Newtop_hadronic_tagger;
    HeavyHiggsSemiTagger = NewHeavyHiggsSemiTagger;
    JetPairTagger = NewJetPairTagger;
    SignatureSemiTagger = NewSignatureSemiTagger;
    DefineVariables();
}

void hheavyhiggs::EventSemiTagger::DefineVariables()
{
    Print(kNotification , "Define Variables");
    set_tagger_name("eventSemi");

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

hheavyhiggs::EventSemiBranch hheavyhiggs::EventSemiTagger::GetBranch(const EventMultiplet<HOctet> &event) const
{
    Print(kInformation, "FillPairTagger", event.Bdt());

    EventSemiBranch eventSemiBranch;
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

    eventSemiBranch.HiggsMass = event.Octet().Sextet().Jet().m();
    eventSemiBranch.HiggsBdt = event.Octet().Sextet().Bdt();
    eventSemiBranch.SignatureBdt = event.Octet().Bdt();
    eventSemiBranch.PairRap = event.Octet().doublet().DeltaRap();
    eventSemiBranch.BottomBdt = event.Octet().BottomBdt();
    eventSemiBranch.PairBottomBdt = event.Octet().PairBottomBdt();

    eventSemiBranch.HardTopPt = event.Octet().Sextet().HardTopPt();
    eventSemiBranch.SoftTopPt = event.Octet().Sextet().SoftTopPt();

    eventSemiBranch.MissingEt = event.MissingEt();

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

    eventSemiBranch.LeptonHt = event.LeptonHt();

    return eventSemiBranch;

}

struct SortJetsByBdt {
    inline bool operator()(const fastjet::PseudoJet &Jet1, const fastjet::PseudoJet &Jet2) {
        return (Jet1.user_info<hanalysis::JetInfo>().Bdt() > Jet2.user_info<hanalysis::JetInfo>().Bdt());
    }
};


std::vector<hheavyhiggs::EventSemiBranch> hheavyhiggs::EventSemiTagger::GetBranches(hanalysis::Event &event, const HObject::Tag Tag)
{
    Print(kInformation, "Get event Tags");

    Jets PreJets = GetJets(event);
    Jets jets = bottom_tagger_.GetJetBdt(PreJets, BottomReader);
    Jets SubJets = bottom_tagger_.GetMultiJetBdt(PreJets, BottomReader);

    Jets Leptons = event.Leptons().GetTaggedJets(JetTag);
    fastjet::PseudoJet MissingEt = event.Hadrons().GetMissingEt();
    std::vector<hanalysis::Doublet> doubletsSemi = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader.reader());
    std::vector<hanalysis::Triplet> tripletsSemi = TopSemiTagger.GetBdt(doubletsSemi, jets, TopSemiReader);

//     std::vector<hanalysis::Doublet> doubletsHadronic = WTagger.GetBdt(jets, WReader);
//     std::vector<hanalysis::Triplet> tripletsHadronic = top_hadronic_tagger.GetBdt(doubletsHadronic, jets, TopHadronicReader);
    std::vector<hanalysis::Triplet> tripletsHadronic = top_hadronic_tagger.GetBdt(jets, TopHadronicReader, WTagger, WReader, bottom_tagger_, BottomReader);

    std::vector<hanalysis::HSextet> Sextets = HeavyHiggsSemiTagger.GetBdt(tripletsSemi, tripletsHadronic, HeavyHiggsSemiReader);


    Jets HiggsParticles = event.Partons().Generator();
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
    Jets Particles = event.Partons().Generator();
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


    std::vector<EventMultiplet<HOctet>> events;
    for (const auto & Octet : Octets) {
        EventMultiplet<HOctet> Octetevent(Octet);
        EventStruct eventStruct;
        eventStruct.LeptonNumber = event.Leptons().GetLeptonJets().size();
        eventStruct.JetNumber = event.Hadrons().GetJets().size();
        eventStruct.BottomNumber = event.Hadrons().GetBottomJets().size();
        eventStruct.ScalarHt = event.Hadrons().GetScalarHt();
        eventStruct.MissingEt = event.Hadrons().GetMissingEt().pt();
//         eventStruct.TrackNumber = event.Hadrons().GetScalarHt();
        Octetevent.SeteventStruct(eventStruct);
        Octetevent.SetLeptons(Leptons);
        Octetevent.SetTotalJets(jets);
        Octetevent.SetSubJets(SubJets);
        Octetevent.SetTag(Tag);
        for (const auto & Jet : jets)  {
            if (Jet.delta_R(Octetevent.Octet().Sextet().triplet1().singlet()) < detector_geometry().JetConeSize) continue;
            if (Jet.delta_R(Octetevent.Octet().Sextet().triplet2().singlet()) < detector_geometry().JetConeSize) continue;
            if (Jet.delta_R(Octetevent.Octet().Sextet().triplet2().doublet().Singlet1()) < detector_geometry().JetConeSize) continue;
            if (Jet.delta_R(Octetevent.Octet().Sextet().triplet2().doublet().Singlet2()) < detector_geometry().JetConeSize) continue;
            if (Jet.delta_R(Octetevent.Octet().doublet().Singlet1()) < detector_geometry().JetConeSize) continue;
            if (Jet.delta_R(Octetevent.Octet().doublet().Singlet2()) < detector_geometry().JetConeSize) continue;
            Octetevent.AddRestJet(Jet);
        }
        events.emplace_back(Octetevent);
    }

    std::vector<hheavyhiggs::EventSemiBranch> eventSemiBranches;
    for (const auto & event : events) eventSemiBranches.emplace_back(GetBranch(event));

    return eventSemiBranches;
}



std::vector<EventMultiplet<HOctet>> hheavyhiggs::EventSemiTagger::GetBdt(const std::vector< HOctet > &Octets, const Jets &jets, const Jets &SubJets, const Jets &Leptons, EventStruct &eventStruct, const hanalysis::Reader &eventSemiReader)
{
    Print(kInformation, "Get event Tags", Octets.size());

    std::vector<EventMultiplet<HOctet>> events;
    for (const auto & Octet : Octets) {
        EventMultiplet<HOctet> Octetevent(Octet, eventStruct);
        for (const auto & Jet : jets)  {
            if (Jet.delta_R(Octetevent.Octet().Sextet().triplet1().singlet()) < detector_geometry().JetConeSize) continue;
            if (Jet.delta_R(Octetevent.Octet().Sextet().triplet2().singlet()) < detector_geometry().JetConeSize) continue;
            if (Jet.delta_R(Octetevent.Octet().Sextet().triplet2().doublet().Singlet1()) < detector_geometry().JetConeSize) continue;
            if (Jet.delta_R(Octetevent.Octet().Sextet().triplet2().doublet().Singlet2()) < detector_geometry().JetConeSize) continue;
            if (Jet.delta_R(Octetevent.Octet().doublet().Singlet1()) < detector_geometry().JetConeSize) continue;
            if (Jet.delta_R(Octetevent.Octet().doublet().Singlet2()) < detector_geometry().JetConeSize) continue;
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
    if (events.size() > 1) events.erase(events.begin() + 1, events.end());
    Print(kInformation, "event Number", events.size(), jets.size());


    return events;
}

float hheavyhiggs::EventSemiTagger::ReadBdt(const TClonesArray &eventClonesArray, const int Entry)
{
    return ((EventSemiBranch *) eventClonesArray.At(Entry))->Bdt;
}
