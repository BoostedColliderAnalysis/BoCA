# include "HChargedEventSemiTagger.hh"

hheavyhiggs::HChargedEventSemiTagger::HChargedEventSemiTagger()
{
//       DebugLevel = HDebug;
    Print(HInformation , "Constructor");
    DefineVariables();
}

hheavyhiggs::HChargedEventSemiTagger::~HChargedEventSemiTagger()
{
    Print(HInformation , "Destructor");
}

void hheavyhiggs::HChargedEventSemiTagger::SetTagger(
    const hanalysis::HBottomTagger &NewBottomTagger,
    const hanalysis::HChargedJetPairTagger &NewChargedJetPairTagger,
    const hanalysis::HWSemiTagger &NewWSemiTagger,
    const hanalysis::HWTagger &NewWTagger,
    const hanalysis::HTopSemiTagger &NewTopSemiTagger,
    const hanalysis::HTopHadronicTagger &NewTopHadronicTagger,
    const hanalysis::HChargedHiggsSemiTagger &NewChargedHiggsSemiTagger,
    const hheavyhiggs::HChargedSignatureSemiTagger &NewChargedSignatureTagger)
{
    BottomTagger = NewBottomTagger;
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
    SetTaggerName("ChargedEventSemi");
    Observables.clear();
    Spectators.clear();

    Observables.push_back(NewObservable(&Branch.LeptonNumber, "LeptonNumber"));
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
    EventSemiBranch.DeltaRap = Event.DeltaRap();
    EventSemiBranch.DeltaPhi = Event.DeltaPhi();
    EventSemiBranch.DeltaR = Event.DeltaR();

    EventSemiBranch.Bdt = Event.Bdt();
    EventSemiBranch.Tag = Event.Tag();

    EventSemiBranch.HiggsMass = Event.Octet().Quartet1().Jet().m();
    EventSemiBranch.PairRap = Event.Octet().Quartet2().DeltaRap();
    EventSemiBranch.HiggsBdt = Event.Octet().Quartet1().Bdt();
    EventSemiBranch.SignatureBdt = Event.Octet().Bdt();

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

std::vector<hheavyhiggs::HChargedSemiBranch> hheavyhiggs::HChargedEventSemiTagger::GetBranches(hanalysis::HEvent *const Event, const HObject::HTag Tag)
{
    Print(HInformation, "Get Event Tags");

    HJets Jets = GetJets(Event);
    Jets = BottomTagger.GetJetBdt(Jets, BottomReader);

    HJets Leptons = Event->GetLeptons()->GetLeptonJets();
    fastjet::PseudoJet MissingEt = Event->GetJets()->GetMissingEt();
    std::vector<hanalysis::HDoublet> DoubletsSemi = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);
    std::vector<hanalysis::HTriplet> TripletsSemi = TopSemiTagger.GetBdt(DoubletsSemi, Jets, TopSemiReader);

    std::vector<hanalysis::HDoublet> DoubletsHadronic = WTagger.GetBdt(Jets, WReader);
    std::vector<hanalysis::HTriplet> TripletsHadronic = TopHadronicTagger.GetBdt(DoubletsHadronic, Jets, TopHadronicReader);

    std::vector<hanalysis::HQuartet31> HiggsQuartets = ChargedHiggsSemiTagger.GetBdt(TripletsSemi, Jets, ChargedHiggsSemiReader);
    std::vector<hanalysis::HQuartet31> JetQuartets = ChargedJetPairTagger.GetBdt(TripletsHadronic, Jets, ChargedJetPairReader);


    HJets HiggsParticles = Event->GetParticles()->GetGeneratorJets();
    HiggsParticles.erase(std::remove_if(HiggsParticles.begin(), HiggsParticles.end(), WrongAbsId(ChargedHiggsId)), HiggsParticles.end());
    if (HiggsParticles.size() != 1) Print(HError, "Where is the Higgs?");
    std::sort(HiggsQuartets.begin(), HiggsQuartets.end(), MinDeltaR(HiggsParticles.front()));
    if (Tag == HSignal && HiggsQuartets.size() > 1) HiggsQuartets.erase(HiggsQuartets.begin() + 1, HiggsQuartets.end());
    if (Tag == HBackground && HiggsQuartets.size() > 0) HiggsQuartets.erase(HiggsQuartets.begin());


    HJets TopParticles = Event->GetParticles()->GetGeneratorJets();
    TopParticles.erase(std::remove_if(TopParticles.begin(), TopParticles.end(), WrongAbsFamily(TopId, GluonId)), TopParticles.end());
    if (TopParticles.size() != 1) Print(HError, "Where is the Top?");
    HJets BottomParticles = Event->GetParticles()->GetGeneratorJets();
    BottomParticles.erase(std::remove_if(BottomParticles.begin(), BottomParticles.end(), WrongAbsFamily(BottomId, GluonId)), BottomParticles.end());
    if (BottomParticles.size() != 1) Print(HError, "Where is the Bottom?");

    if (TopParticles.size() > 0 && BottomParticles.size() > 0) {
        hanalysis::HDoublet ParticlePair(TopParticles.front(), BottomParticles.front());
        std::sort(JetQuartets.begin(), JetQuartets.end(), MinDeltaR(ParticlePair.Jet()));
        if (Tag == HSignal && JetQuartets.size() > 1) JetQuartets.erase(JetQuartets.begin() + 1, JetQuartets.end());
        if (Tag == HBackground && JetQuartets.size() > 0) JetQuartets.erase(JetQuartets.begin());
    }

    std::vector<HOctet44> Octets = SignatureSemiTagger.GetBdt(HiggsQuartets, JetQuartets, SignatureSemiReader);


    std::vector<HEventMultiplet<HOctet44>> Events;
    for (const auto & Octet : Octets) {
      HEventMultiplet<HOctet44> OctetEvent(Octet);
        HEventStruct EventStruct;
        EventStruct.LeptonNumber = Event->GetLeptons()->GetLeptonJets().size();
        EventStruct.JetNumber = Event->GetJets()->GetJets().size();
        EventStruct.BottomNumber = Event->GetJets()->GetBottomJets().size();
        EventStruct.ScalarHt = Event->GetJets()->GetScalarHt();
        OctetEvent.SetEventStruct(EventStruct);
        OctetEvent.SetLeptons(Leptons);
        OctetEvent.SetTag(Tag);
        for (const auto & Jet : Jets) {
            if (Jet.delta_R(OctetEvent.Octet().Quartet1().Singlet()) < .4) continue;
            if (Jet.delta_R(OctetEvent.Octet().Quartet1().Triplet().Singlet()) < .4) continue;
            if (Jet.delta_R(OctetEvent.Octet().Quartet1().Triplet().Doublet().Singlet1()) < .4) continue;
            if (Jet.delta_R(OctetEvent.Octet().Quartet1().Triplet().Doublet().Singlet2()) < .4) continue;
            if (Jet.delta_R(OctetEvent.Octet().Quartet2().Singlet()) < .4) continue;
            if (Jet.delta_R(OctetEvent.Octet().Quartet2().Triplet().Singlet()) < .4) continue;
            OctetEvent.AddRestJet(Jet);
        }
        Events.push_back(OctetEvent);
    }

    std::vector<hheavyhiggs::HChargedSemiBranch> EventSemiBranches;
    for (const auto & event : Events)EventSemiBranches.push_back(GetBranch(event));

    return EventSemiBranches;

}

std::vector<HEventMultiplet<HOctet44>> hheavyhiggs::HChargedEventSemiTagger::GetBdt(
    const std::vector< HOctet44 > &Octets, HJets &Jets, HJets &Leptons, HEventStruct &EventStruct, const hanalysis::HReader &EventSemiReader)
{
    Print(HInformation, "Get Event Tags");


    std::vector<HEventMultiplet<HOctet44>> Events;
    for (auto & Octet : Octets) {
      HEventMultiplet<HOctet44> OctetEvent(Octet, EventStruct);
        for (const auto & Jet : Jets) {
            if (Octet.Quartet1().Singlet().delta_R(Jet) < 0.4) continue;
            if (Octet.Quartet1().Triplet().Singlet().delta_R(Jet) < 0.4) continue;
            if (Octet.Quartet1().Triplet().Doublet().Singlet1().delta_R(Jet) < 0.4) continue;
            if (Octet.Quartet1().Triplet().Doublet().Singlet2().delta_R(Jet) < 0.4) continue;
            if (Octet.Quartet2().Singlet().delta_R(Jet) < 0.4) continue;
            if (Octet.Quartet2().Triplet().Singlet().delta_R(Jet) < 0.4) continue;
            if (Octet.Quartet2().Triplet().Doublet().Singlet1().delta_R(Jet) < 0.4) continue;
            if (Octet.Quartet2().Triplet().Doublet().Singlet2().delta_R(Jet) < 0.4) continue;
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

std::vector<int> hheavyhiggs::HChargedEventSemiTagger::ApplyBdt2(const ExRootTreeReader *const TreeReader, const std::string TreeName, const TFile *const ExportFile)
{
    Print(HNotification, "Apply Bdt", EventBranchName);

    std::string Temp = EventBranchName; // TODO remove this dirty trick
    EventBranchName += "Reader";

    const int Steps = 20;
    std::vector<int> EventNumbers(Steps, 0);

    const TClonesArray *const EventClonesArray = const_cast<ExRootTreeReader *>(TreeReader)->UseBranch(EventBranchName.c_str());
    ExRootTreeWriter *TreeWriter = new ExRootTreeWriter(const_cast<TFile *>(ExportFile), TreeName.c_str());
    ExRootTreeBranch *ResultBranch = TreeWriter->NewBranch(EventBranchName.c_str(), HResultBranch::Class());
    for (const int EventNumber : HRange(const_cast<ExRootTreeReader *>(TreeReader)->GetEntries())) {
        const_cast<ExRootTreeReader *>(TreeReader)->ReadEntry(EventNumber);
        for (const int Entry : HRange(EventClonesArray->GetEntriesFast())) {
            HChargedSemiBranch *Test = (HChargedSemiBranch *) EventClonesArray->At(Entry);
            const float Bdt = Test->Bdt;
            HResultBranch *Export = static_cast<HResultBranch *>(ResultBranch->NewEntry());
            Export->Bdt = Bdt;
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
    EventBranchName = Temp;
    return EventNumbers;
}
