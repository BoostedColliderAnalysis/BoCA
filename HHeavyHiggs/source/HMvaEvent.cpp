# include "HMvaEvent.hh"

hheavyhiggs::HMvaEvent::HMvaEvent(hanalysis::HBottomTagger *const NewBottomTagger, hanalysis::HLeptonicTopTagger *const NewTopTagger, hanalysis::HHeavyHiggsTagger *const NewHeavyHiggsTagger)
{

    Print(HNotification , "Constructor");

    BottomTagger = NewBottomTagger;
    BottomReader = new hanalysis::HReader(BottomTagger);
    LeptonicTopTagger = NewTopTagger;
    TopReader = new hanalysis::HReader(LeptonicTopTagger);
    HeavyHiggsTagger = NewHeavyHiggsTagger;
    HeavyHiggsReader = new hanalysis::HReader(HeavyHiggsTagger);

    TaggerName = "Event";
    SignalNames = {"Signal"};
    BackgroundNames = {"Background"};
    CandidateBranchName = "Event";
    

    Branch = new hheavyhiggs::HEventBranch();
    JetTag = new hanalysis::HJetTag();

    DefineVariables();

}

hheavyhiggs::HMvaEvent::~HMvaEvent()
{

    Print(HNotification , "Constructor");

    delete Branch;
    delete JetTag;
    delete BottomReader;
    delete TopReader;
    delete HeavyHiggsReader;

}

void hheavyhiggs::HMvaEvent::FillBranch(hheavyhiggs::HEventBranch *EventBranch, const HHeavyHiggsEvent &HeavyHiggsEvent)
{
    Print(HInformation, "FillPairTagger", HeavyHiggsEvent.GetBdt());

    EventBranch->ScalarHt = HeavyHiggsEvent.GetScalarHt();

    EventBranch->JetNumber = HeavyHiggsEvent.GetJetNumber();
    EventBranch->BottomNumber = HeavyHiggsEvent.GetBottomNumber();
    EventBranch->LeptonNumber = HeavyHiggsEvent.GetLeptonNumber();

    EventBranch->DeltaRap = HeavyHiggsEvent.GetDeltaRap();
    EventBranch->DeltaPhi = HeavyHiggsEvent.DeltaPhi();
    EventBranch->DeltaR = HeavyHiggsEvent.GetDeltaR();

    EventBranch->DeltaRapSum = HeavyHiggsEvent.GetDeltaRapSum();
    EventBranch->DeltaPhiSum = HeavyHiggsEvent.GetDeltaPhiSum();
    EventBranch->DeltaRSum = HeavyHiggsEvent.GetDeltaRSum();

    EventBranch->DeltaRapDiff = HeavyHiggsEvent.GetDeltaRapDiff();
    EventBranch->DeltaPhiDiff = HeavyHiggsEvent.GetDeltaPhiDiff();
    EventBranch->DeltaRDiff = HeavyHiggsEvent.GetDeltaRDiff();

    EventBranch->HeavyHiggsBdt = HeavyHiggsEvent.GetHeavyHiggs().GetBdt();
    EventBranch->HeavyParticleBdt = HeavyHiggsEvent.GetBdt();
    EventBranch->Signal = HeavyHiggsEvent.GetTag();
}

void hheavyhiggs::HMvaEvent::FillBranch(const HHeavyHiggsEvent &HeavyHiggsEvent)
{
    Print(HInformation, "FillPairTagger");

    FillBranch(Branch, HeavyHiggsEvent);

}

void hheavyhiggs::HMvaEvent::DefineVariables()
{

    Print(HNotification , "Define Variables");

    Observables.push_back(NewObservable(&Branch->ScalarHt, "ScalarHt"));

    Observables.push_back(NewObservable(&Branch->JetNumber, "JetNumber"));
    Observables.push_back(NewObservable(&Branch->BottomNumber, "BottomNumber"));
    Observables.push_back(NewObservable(&Branch->LeptonNumber, "LeptonNumber"));

    Observables.push_back(NewObservable(&Branch->DeltaRap, "DeltaRap"));
    Observables.push_back(NewObservable(&Branch->DeltaPhi, "DeltaPhi"));
    Observables.push_back(NewObservable(&Branch->DeltaR, "DeltaR"));

    Observables.push_back(NewObservable(&Branch->DeltaRapSum, "DeltaRapSum"));
    Observables.push_back(NewObservable(&Branch->DeltaPhiSum, "DeltaPhiSum"));
    Observables.push_back(NewObservable(&Branch->DeltaRSum, "DeltaRSum"));

    Observables.push_back(NewObservable(&Branch->DeltaRapDiff, "DeltaRapDiff"));
    Observables.push_back(NewObservable(&Branch->DeltaPhiDiff, "DeltaPhiDiff"));
    Observables.push_back(NewObservable(&Branch->DeltaRDiff, "DeltaRDiff"));

    Observables.push_back(NewObservable(&Branch->HeavyHiggsBdt, "HeavyHiggsBdt"));
    Observables.push_back(NewObservable(&Branch->HeavyParticleBdt, "HeavyParticleBdt"));
    Spectators.push_back(NewObservable(&Branch->Signal, "Signal"));

    Print(HNotification, "Variables defined");

}



struct SortHeavyHiggsEvents {
    inline bool operator()(const HHeavyHiggsEvent &Event1, const HHeavyHiggsEvent &Event2) {
        return (Event1.GetBdt() > Event2.GetBdt());
    }
};

std::vector<hheavyhiggs::HEventBranch * > hheavyhiggs::HMvaEvent::GetBranches(hanalysis::HEvent *const Event, const HObject::HState State)
{
    std::vector<hheavyhiggs::HEventBranch*> EventBranches;
    HJets Leptons = Event->GetLeptons()->GetLeptonJets();
    if (Leptons.size() < 2) return EventBranches;

    HJets Jets = Event->GetJets()->GetStructuredJets();
    if (Jets.size() < 4) return EventBranches;

    for (auto & Jet : Jets) {
        hanalysis::HJetInfo *JetInfo = new hanalysis::HJetInfo;
        BottomTagger->FillBranch(Jet);
        JetInfo->SetBdt(BottomReader->GetBdt());
        Jet.set_user_info(JetInfo);
//         Jet.user_index(JetInfo->GetBdt());
    }

    std::vector<HHeavyHiggsEvent> HeavyHiggsEvents;
    for (HJets::iterator Lepton1 = Leptons.begin(); Lepton1 != Leptons.end(); ++Lepton1) {
        for (HJets::iterator Lepton2 = Lepton1 + 1; Lepton2 != Leptons.end(); ++Lepton2) {
            HJets EventLeptons  {(*Lepton1), (*Lepton2)};
            for (HJets::iterator Jet1 = Jets.begin(); Jet1 != Jets.end(); ++Jet1) {
                for (HJets::iterator Jet2 = Jet1 + 1; Jet2 != Jets.end(); ++Jet2) {
                    for (HJets::iterator Jet3 = Jet2 + 1; Jet3 != Jets.end(); ++Jet3) {
                        for (HJets::iterator Jet4 = Jet3 + 1; Jet4 != Jets.end(); ++Jet4) {
                            HJets EventJets {(*Jet1), (*Jet2), (*Jet3), (*Jet4)};
                            std::vector<HHeavyHiggsEvent> NewHeavyHiggsEvents = GetHeavyHiggsEvents(EventJets, EventLeptons);
                            if (NewHeavyHiggsEvents.size() < 1)continue;
                            HeavyHiggsEvents.insert(HeavyHiggsEvents.end(), NewHeavyHiggsEvents.begin(), NewHeavyHiggsEvents.end());
                        }
                    }
                }
            }
        }
    }

    if (HeavyHiggsEvents.size() > 1) {
        std::sort(HeavyHiggsEvents.begin(), HeavyHiggsEvents.end(), SortHeavyHiggsEvents());
        HeavyHiggsEvents.erase(HeavyHiggsEvents.begin() + 1, HeavyHiggsEvents.end());
    }

    for (auto & HeavyHiggsEvent : HeavyHiggsEvents) {
    hheavyhiggs::HEventBranch *EventBranch = new hheavyhiggs::HEventBranch();
    HeavyHiggsEvent.SetLeptonNumber(Event->GetLeptons()->GetLeptonJets().size());
    HeavyHiggsEvent.SetJetNumber(Event->GetJets()->GetJets().size());
    HeavyHiggsEvent.SetBottomNumber(Event->GetJets()->GetBottomJets().size());
    HeavyHiggsEvent.SetScalarHt(Event->GetJets()->GetScalarHt());
    if(State==HSignal) HeavyHiggsEvent.SetTag(1);
    else HeavyHiggsEvent.SetTag(0);
        FillBranch(EventBranch, HeavyHiggsEvent);
        EventBranches.push_back(EventBranch);
    }

    return EventBranches;

}



std::vector<HHeavyHiggsEvent> hheavyhiggs::HMvaEvent::GetHeavyHiggsEvents(const HJets &Jets, const HJets &Leptons)
{
    Print(HInformation, "Get Heavy Higgs Event");

    std::vector<HHeavyHiggsEvent> HeavyHiggsEvents;

    std::vector<hanalysis::HJetLeptonPair> Tops;
    for (const auto & Jet : Jets) {
        hanalysis::HJetLeptonPair Top = hanalysis::HJetLeptonPair(Jet, Leptons[0]);
        LeptonicTopTagger->FillBranch(Top);
        Top.SetBdt(TopReader->GetBdt());
        Tops.push_back(Top);
    }

    std::vector<hanalysis::HJetLeptonPair> AntiTops;
    for (const auto & Jet : Jets) {
        hanalysis::HJetLeptonPair AntiTop = hanalysis::HJetLeptonPair(Jet, Leptons[1]);
        LeptonicTopTagger->FillBranch(AntiTop);
        AntiTop.SetBdt(TopReader->GetBdt());
        AntiTops.push_back(AntiTop);
    }

    Print(HDebug, "Get Heavy Higgses", Tops.size(), AntiTops.size());

    std::vector<hanalysis::HTriplePair> HeavyHiggses;

    for (const auto & Top : Tops) {
        for (const auto & AntiTop : AntiTops) {
            if (Top.GetJet() == AntiTop.GetJet()) continue;
            hanalysis::HPairPair TopPair = hanalysis::HPairPair(Top, AntiTop);
            std::vector<hanalysis::HTriplePair> TriplePairs = TopPair.GetTriplePairs();
            Print(HDebug, "Got Triple Pairs", TriplePairs.size());
            if (TriplePairs.size() < 1)continue;

            for (auto & TriplePair : TriplePairs) {
                Print(HDebug, "FillBranch", TriplePair.GetInvariantMass());
                HeavyHiggsTagger->FillBranch(TriplePair);
                TriplePair.SetBdt(HeavyHiggsReader->GetBdt());
                Print(HDebug, "NewHiggs", TriplePair.GetBdt());
                HeavyHiggses.push_back(TriplePair);
            }
        }
    }

    Print(HDebug, "Get Heavy Higgs Events", HeavyHiggses.size());
    if (HeavyHiggses.size() < 1) return HeavyHiggsEvents;

    for (const auto HeavyHiggs : HeavyHiggses) {
        for (const auto & Jet1 : Jets) {
            if (Jet1 == HeavyHiggs.GetTriple1().GetJet3())continue;
            if (Jet1 == HeavyHiggs.GetTriple2().GetJet3()) continue;
            for (const auto & Jet2 : Jets) {
                Print(HDebug, "New Triple",HeavyHiggs.GetBdt(),Jet1.user_info<hanalysis::HJetInfo>().GetBdt(),Jet2.user_info<hanalysis::HJetInfo>().GetBdt());
                if (Jet1 == Jet2) continue;
                if (Jet2 == HeavyHiggs.GetTriple1().GetJet3())continue;
                if (Jet2 == HeavyHiggs.GetTriple2().GetJet3())continue;
                HeavyHiggsEvents.push_back(HHeavyHiggsEvent(HeavyHiggs, Jet1, Jet2));
            }
        }
    }

    return HeavyHiggsEvents;

}
