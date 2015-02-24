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

    Observables.clear();
    Spectators.clear();

    Spectators.push_back(NewObservable(&Branch.LeptonNumber, "LeptonNumber"));
    Observables.push_back(NewObservable(&Branch.JetNumber, "JetNumber"));
    Observables.push_back(NewObservable(&Branch.BottomNumber, "BottomNumber"));
    Observables.push_back(NewObservable(&Branch.ScalarHt, "ScalarHt"));

    Observables.push_back(NewObservable(&Branch.Mass, "Mass"));
    Observables.push_back(NewObservable(&Branch.Pt, "Pt"));
    Observables.push_back(NewObservable(&Branch.Rap, "Rap"));
    Observables.push_back(NewObservable(&Branch.Phi, "Phi"));
    Observables.push_back(NewObservable(&Branch.Ht, "Ht"));

    Observables.push_back(NewObservable(&Branch.DeltaPt, "DeltaPt"));
    Observables.push_back(NewObservable(&Branch.DeltaRap, "DeltaRap"));
    Observables.push_back(NewObservable(&Branch.DeltaPhi, "DeltaPhi"));
    Observables.push_back(NewObservable(&Branch.DeltaR, "DeltaR"));

    Observables.push_back(NewObservable(&Branch.HiggsMass, "HiggsMass"));
    Observables.push_back(NewObservable(&Branch.PairRap, "PairRap"));
    Observables.push_back(NewObservable(&Branch.HiggsBdt, "HiggsBdt"));
    Observables.push_back(NewObservable(&Branch.SignatureBdt, "SignatureBdt"));

    Observables.push_back(NewObservable(&Branch.RestNumber, "RestNumber"));
    Observables.push_back(NewObservable(&Branch.RestM, "RestM"));
    Observables.push_back(NewObservable(&Branch.RestPt, "RestPt"));
    Observables.push_back(NewObservable(&Branch.RestHt, "RestHt"));
    Observables.push_back(NewObservable(&Branch.RestPhi, "RestPhi"));
    Observables.push_back(NewObservable(&Branch.RestRap, "RestRap"));
    Observables.push_back(NewObservable(&Branch.RestBdt, "RestBdt"));
    Observables.push_back(NewObservable(&Branch.LeptonHt, "LeptonHt"));

    Observables.push_back(NewObservable(&Branch.Bdt, "Bdt"));
    Spectators.push_back(NewObservable(&Branch.Tag, "Tag"));


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
    EventSemiBranch.DeltaRap = Event.DeltaRap();
    EventSemiBranch.DeltaPhi = Event.DeltaPhi();
    EventSemiBranch.DeltaR = Event.DeltaR();

    EventSemiBranch.Bdt = Event.Bdt();
    EventSemiBranch.Tag = Event.Tag();

    EventSemiBranch.HiggsMass = Event.Octet().Sextet().Jet().m();
    EventSemiBranch.HiggsBdt = Event.Octet().Sextet().Bdt();
    EventSemiBranch.SignatureBdt = Event.Octet().Bdt();
    EventSemiBranch.PairRap = Event.Octet().Doublet().DeltaRap();

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

//     JetTag.HeavyParticles = {GluonId, TopId};
    HJets Jets = GetJets(Event);
    Jets = BottomTagger.GetJetBdt(Jets, BottomReader);

    HJets Leptons = Event.GetLeptons()->GetTaggedJets(JetTag);
    fastjet::PseudoJet MissingEt = Event.GetJets()->GetMissingEt();
    std::vector<hanalysis::HDoublet> DoubletsSemi = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);
    std::vector<hanalysis::HTriplet> TripletsSemi = TopSemiTagger.GetBdt(DoubletsSemi, Jets, TopSemiReader);

    std::vector<hanalysis::HDoublet> DoubletsHadronic = WTagger.GetBdt(Jets, WReader);
    std::vector<hanalysis::HTriplet> TripletsHadronic = TopHadronicTagger.GetBdt(DoubletsHadronic, Jets, TopHadronicReader);

    std::vector<hanalysis::HSextet> Sextets = HeavyHiggsSemiTagger.GetBdt(TripletsSemi, TripletsHadronic, HeavyHiggsSemiReader);

    std::vector<hanalysis::HDoublet> Doublets = JetPairTagger.GetBdt(Jets, JetPairReader);


    HJets HiggsParticles = Event.GetParticles()->Generator();
    HJets Even = HiggsParticles;
    Even.erase(std::remove_if(Even.begin(), Even.end(), WrongAbsFamily(HeavyHiggsId, GluonId)), Even.end());
    HJets Odd = HiggsParticles;
    Odd.erase(std::remove_if(Odd.begin(), Odd.end(), WrongAbsFamily(CPOddHiggsId, GluonId)), Odd.end());
    HiggsParticles = Even;
    HiggsParticles.insert(HiggsParticles.end(), Odd.begin(), Odd.end());
    if (HiggsParticles.size() != 1) Print(HError, "Where is the Higgs?");
    std::sort(Sextets.begin(), Sextets.end(), MinDeltaR(HiggsParticles.front()));
    if (Tag == HSignal && Sextets.size() > 1) Sextets.erase(Sextets.begin() + 1, Sextets.end());

    HJets BottomParticles = Event.GetParticles()->Generator();
    BottomParticles.erase(std::remove_if(BottomParticles.begin(), BottomParticles.end(), WrongAbsFamily(BottomId, GluonId)), BottomParticles.end());
    if (BottomParticles.size() != 2) Print(HError, "Where is the Bottom?", BottomParticles.size());

    if (BottomParticles.size() > 1) {
        hanalysis::HDoublet ParticleDoublet(BottomParticles.at(0), BottomParticles.at(1));
        std::sort(Doublets.begin(), Doublets.end(), MinDeltaR(ParticleDoublet.Jet()));
        if (Tag == HSignal && Doublets.size() > 1) Doublets.erase(Doublets.begin() + 1, Doublets.end());
    }

    std::vector<HOctet> Octets = SignatureSemiTagger.GetBdt(Sextets, Doublets, SignatureSemiReader);


    std::vector<HEventMultiplet<HOctet>> Events;
    for (const auto & Octet : Octets) {
        HEventMultiplet<HOctet> OctetEvent(Octet);
        HEventStruct EventStruct;
        EventStruct.LeptonNumber = Event.GetLeptons()->GetLeptonJets().size();
        EventStruct.JetNumber = Event.GetJets()->GetJets().size();
        EventStruct.BottomNumber = Event.GetJets()->GetBottomJets().size();
        EventStruct.ScalarHt = Event.GetJets()->GetScalarHt();
        OctetEvent.SetEventStruct(EventStruct);
        OctetEvent.SetLeptons(Leptons);
        OctetEvent.SetTag(Tag);
        for (const auto & Jet : Jets) {
            if (Jet.delta_R(OctetEvent.Octet().Sextet().Triplet1().Singlet()) < .4) continue;
            if (Jet.delta_R(OctetEvent.Octet().Sextet().Triplet2().Singlet()) < .4) continue;
            if (Jet.delta_R(OctetEvent.Octet().Sextet().Triplet2().Doublet().Singlet1()) < .4) continue;
            if (Jet.delta_R(OctetEvent.Octet().Sextet().Triplet2().Doublet().Singlet2()) < .4) continue;
            if (Jet.delta_R(OctetEvent.Octet().Doublet().Singlet1()) < .4) continue;
            if (Jet.delta_R(OctetEvent.Octet().Doublet().Singlet2()) < .4) continue;
            OctetEvent.AddRestJet(Jet);
        }
        Events.push_back(OctetEvent);
    }


    std::vector<hheavyhiggs::HEventSemiBranch> EventSemiBranches;
    for (const auto & event : Events) EventSemiBranches.push_back(GetBranch(event));

    return EventSemiBranches;
}



std::vector<HEventMultiplet<HOctet>> hheavyhiggs::HEventSemiTagger::GetBdt(const std::vector< HOctet > &Octets, const HJets &Jets, const HJets &Leptons, HEventStruct &EventStruct, const hanalysis::HReader &EventSemiReader)
{
    Print(HInformation, "Get Event Tags");

    std::vector<HEventMultiplet<HOctet>> Events;
    for (const auto & Octet : Octets) {
        HEventMultiplet<HOctet> OctetEvent(Octet, EventStruct);
        for (const auto & Jet : Jets) {
            if (Jet.delta_R(OctetEvent.Octet().Sextet().Triplet1().Singlet()) < .4) continue;
            if (Jet.delta_R(OctetEvent.Octet().Sextet().Triplet2().Singlet()) < .4) continue;
            if (Jet.delta_R(OctetEvent.Octet().Sextet().Triplet2().Doublet().Singlet1()) < .4) continue;
            if (Jet.delta_R(OctetEvent.Octet().Sextet().Triplet2().Doublet().Singlet2()) < .4) continue;
            if (Jet.delta_R(OctetEvent.Octet().Doublet().Singlet1()) < .4) continue;
            if (Jet.delta_R(OctetEvent.Octet().Doublet().Singlet2()) < .4) continue;
            OctetEvent.AddRestJet(Jet);
        }
        OctetEvent.SetLeptons(Leptons);
        Branch = GetBranch(OctetEvent);
        OctetEvent.SetBdt(EventSemiReader.Bdt());
        Events.push_back(OctetEvent);
    }


    std::sort(Events.begin(), Events.end());
    if (Events.size() > 1)Events.erase(Events.begin() + 1, Events.end());
    Print(HInformation, "Event Number", Events.size(), Jets.size());


    return Events;
}

float hheavyhiggs::HEventSemiTagger::ReadBdt(const TClonesArray &EventClonesArray, const int Entry){
  HEventSemiBranch *Test = (HEventSemiBranch *) EventClonesArray.At(Entry);
  return Test->Bdt;
}


std::vector<int> hheavyhiggs::HEventSemiTagger::ApplyBdt2(const ExRootTreeReader *const TreeReader, const std::string TreeName, const TFile *const ExportFile)
{
    Print(HNotification, "Apply Bdt", EventBranchName);
    std::string NewEventBranchName = EventBranchName + "Reader";
    const int Steps = 20;
    std::vector<int> EventNumbers(Steps, 0);

    const int BinSum = 100;
    std::vector<int> Bins(BinSum, 0);

    const TClonesArray *const EventClonesArray = const_cast<ExRootTreeReader *>(TreeReader)->UseBranch(NewEventBranchName.c_str());
    ExRootTreeWriter *TreeWriter = new ExRootTreeWriter(const_cast<TFile *>(ExportFile), TreeName.c_str());
    ExRootTreeBranch *ResultBranch = TreeWriter->NewBranch(NewEventBranchName.c_str(), HResultBranch::Class());
    for (const int EventNumber : HRange(const_cast<ExRootTreeReader *>(TreeReader)->GetEntries())) {
        const_cast<ExRootTreeReader *>(TreeReader)->ReadEntry(EventNumber);
        for (const int Entry : HRange(EventClonesArray->GetEntriesFast())) {
            HEventSemiBranch *Test = (HEventSemiBranch *) EventClonesArray->At(Entry);
            const float Bdt = Test->Bdt;
            HResultBranch *Export = static_cast<HResultBranch *>(ResultBranch->NewEntry());
            Export->Bdt = Bdt;

            ++Bins.at(floor(Bdt * BinSum / 2));

            for (int Step = 0; Step < Steps; ++Step) {
                const float CutValue = (float(Step) / Steps + 1);
                if (Bdt > CutValue) ++EventNumbers.at(Step);
            }
        }
        TreeWriter->Fill();
        TreeWriter->Clear();
    }
    TreeWriter->Write();
    delete TreeWriter;

    return EventNumbers;
}
