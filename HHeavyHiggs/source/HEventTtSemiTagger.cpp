# include "HEventTtSemiTagger.hh"

hheavyhiggs::HEventTtSemiTagger::HEventTtSemiTagger()
{
    //   DebugLevel = HDebug;
    Print(HNotification , "Constructor");
    DefineVariables();
}

hheavyhiggs::HEventTtSemiTagger::~HEventTtSemiTagger()
{
    Print(HNotification , "Constructor");
}

void hheavyhiggs::HEventTtSemiTagger::SetTagger(
    const hanalysis::HBottomTagger &NewBottomTagger,
    const hanalysis::HWSemiTagger &NewWSemiTagger,
    const hanalysis::HWTagger &NewWTagger,
    const hanalysis::HTopSemiTagger &NewTopSemiTagger,
    const hanalysis::HTopHadronicTagger &NewTopHadronicTagger,
    const hanalysis::HHeavyHiggsSemiTagger &NewHeavyHiggsSemiTagger)
{
    Print(HNotification , "Constructor");
    BottomTagger = NewBottomTagger;
    WSemiTagger = NewWSemiTagger;
    WTagger = NewWTagger;
    TopSemiTagger = NewTopSemiTagger;
    TopHadronicTagger = NewTopHadronicTagger;
    HeavyHiggsSemiTagger = NewHeavyHiggsSemiTagger;
    DefineVariables();
}

void hheavyhiggs::HEventTtSemiTagger::DefineVariables()
{
    Print(HNotification , "Define Variables");
    SetTaggerName("EventSemi");
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
    Observables.push_back(NewObservable(&Branch.HiggsBdt, "HiggsBdt"));

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

hheavyhiggs::HEventTtSemiBranch hheavyhiggs::HEventTtSemiTagger::GetBranch(const HSextetEvent &Event) const
{
    Print(HInformation, "FillPairTagger", Event.Bdt());

    HEventTtSemiBranch EventSemiBranch;
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
    EventSemiBranch.DeltaPhi = Event.DeltaPhi();
    EventSemiBranch.DeltaRap = Event.DeltaRap();
    EventSemiBranch.DeltaR = Event.DeltaR();

    EventSemiBranch.Bdt = Event.Bdt();
    EventSemiBranch.Tag = Event.Tag();

    EventSemiBranch.HiggsMass = Event.Sextet().Jet().m();
    EventSemiBranch.HiggsBdt = Event.Sextet().Bdt();

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

std::vector<hheavyhiggs::HEventTtSemiBranch> hheavyhiggs::HEventTtSemiTagger::GetBranches(hanalysis::HEvent *const Event, const HObject::HTag Tag)
{
    Print(HInformation, "Get Event Tags");

    HJets Jets = GetJets(Event);
    Jets = BottomTagger.GetJetBdt(Jets, BottomReader);
    HJets Leptons = Event->GetLeptons()->GetTaggedJets(JetTag);
    fastjet::PseudoJet MissingEt = Event->GetJets()->GetMissingEt();
    std::vector<hanalysis::HDoublet> DoubletsSemi = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);
    std::vector<hanalysis::HTriplet> TripletsSemi = TopSemiTagger.GetBdt(DoubletsSemi, Jets, TopSemiReader);

    std::vector<hanalysis::HDoublet> DoubletsHadronic = WTagger.GetBdt(Jets, WReader);
    std::vector<hanalysis::HTriplet> TripletsHadronic = TopHadronicTagger.GetBdt(DoubletsHadronic, Jets, TopHadronicReader);

    std::vector<hanalysis::HSextet> Sextets = HeavyHiggsSemiTagger.GetBdt(TripletsSemi, TripletsHadronic, HeavyHiggsSemiReader);

    std::vector<hheavyhiggs::HEventTtSemiBranch> EventSemiBranches;
    if (Sextets.size() < 1) return EventSemiBranches;

    if (Tag == HSignal && Sextets.size() > 1) {
        Print(HError, "more than one event", Sextets.size());
        std::sort(Sextets.begin(), Sextets.end());
        Sextets.erase(Sextets.begin() + 1, Sextets.end());
    }

    HSextetEvent SextetEvent(Sextets.front());
    HEventStruct EventStruct;
    EventStruct.LeptonNumber = Event->GetLeptons()->GetLeptonJets().size();
    EventStruct.JetNumber = Event->GetJets()->GetJets().size();
    EventStruct.BottomNumber = Event->GetJets()->GetBottomJets().size();
    EventStruct.ScalarHt = Event->GetJets()->GetScalarHt();
    SextetEvent.SetEventStruct(EventStruct);
    SextetEvent.SetLeptons(Leptons);
    SextetEvent.SetTag(Tag);
    for (const auto & Jet : Jets) {
        if (Jet.delta_R(SextetEvent.Sextet().Triplet1().Singlet()) < .4) continue;
        if (Jet.delta_R(SextetEvent.Sextet().Triplet2().Singlet()) < .4) continue;
        if (Jet.delta_R(SextetEvent.Sextet().Triplet2().Doublet().Singlet1()) < .4) continue;
        if (Jet.delta_R(SextetEvent.Sextet().Triplet2().Doublet().Singlet2()) < .4) continue;
        SextetEvent.AddRestJet(Jet);
    }

    EventSemiBranches.push_back(GetBranch(SextetEvent));
    return EventSemiBranches;
}



std::vector<HSextetEvent> hheavyhiggs::HEventTtSemiTagger::GetBdt(const std::vector< hanalysis::HSextet > &Sextets, HJets &Jets, const HJets &Leptons, HEventStruct &EventStruct, const hanalysis::HReader &EventSemiReader)
{
    Print(HInformation, "Get Event Tags");

    std::vector<HSextetEvent> SextetEvents;
    for (const auto & Sextet : Sextets) {
        HSextetEvent SextetEvent(Sextet, EventStruct);
        for (const auto & Jet : Jets) {
            if (Jet.delta_R(SextetEvent.Sextet().Triplet1().Singlet()) < .4) continue;
            if (Jet.delta_R(SextetEvent.Sextet().Triplet2().Singlet()) < .4) continue;
            if (Jet.delta_R(SextetEvent.Sextet().Triplet2().Doublet().Singlet1()) < .4) continue;
            if (Jet.delta_R(SextetEvent.Sextet().Triplet2().Doublet().Singlet2()) < .4) continue;
            SextetEvent.AddRestJet(Jet);
        }
        SextetEvent.SetLeptons(Leptons);
        Branch = GetBranch(SextetEvent);
        SextetEvent.SetBdt(EventSemiReader.Bdt());
        SextetEvents.push_back(SextetEvent);
    }

    std::sort(SextetEvents.begin(), SextetEvents.end());
    if (SextetEvents.size() > 1)SextetEvents.erase(SextetEvents.begin() + 1, SextetEvents.end());
    Print(HInformation, "Event Number", SextetEvents.size(), Jets.size());
    return SextetEvents;
}

std::vector<int> hheavyhiggs::HEventTtSemiTagger::ApplyBdt2(const ExRootTreeReader *const TreeReader, const std::string TreeName, const TFile *const ExportFile)
{
    Print(HNotification, "Apply Bdt", EventBranchName);
    std::string Temp = EventBranchName; // TODO remove this dirty trick
    EventBranchName += "Reader";

    const int Steps = 20;
    std::vector<int> EventNumbers(Steps, 0);

    const TClonesArray *const EventClonesArray = const_cast<ExRootTreeReader *>(TreeReader)->UseBranch(EventBranchName.c_str());
    ExRootTreeWriter TreeWriter(const_cast<TFile *>(ExportFile), TreeName.c_str());
    ExRootTreeBranch *ResultBranch = TreeWriter.NewBranch(EventBranchName.c_str(), HResultBranch::Class());
    for (const int EventNumber : HRange(const_cast<ExRootTreeReader *>(TreeReader)->GetEntries())) {
        const_cast<ExRootTreeReader *>(TreeReader)->ReadEntry(EventNumber);
        for (const int Entry : HRange(EventClonesArray->GetEntriesFast())) {
            const float Bdt = ((HEventTtSemiBranch *) EventClonesArray->At(Entry))->Bdt;
            static_cast<HResultBranch *>(ResultBranch->NewEntry())->Bdt = Bdt;
            for (int Step = 0; Step < Steps; ++Step) {
                const float CutValue = (float(Step) / Steps + 1);
                if (Bdt > CutValue) ++EventNumbers.at(Step);
            }
        }
        TreeWriter.Fill();
        TreeWriter.Clear();
    }
    TreeWriter.Write();
    EventBranchName = Temp;
    return EventNumbers;
}
