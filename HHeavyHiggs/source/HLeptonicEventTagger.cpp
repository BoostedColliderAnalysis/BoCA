# include "HLeptonicEventTagger.hh"

hheavyhiggs::HLeptonicEventTagger::HLeptonicEventTagger(hanalysis::HBottomTagger *const NewBottomTagger, hanalysis::HLeptonicTopTagger *const NewTopTagger, hanalysis::HHeavyHiggsLeptonicTagger *const NewHeavyHiggsTagger)
{

    Print(HNotification , "Constructor");

    BottomTagger = NewBottomTagger;
    BottomReader = new hanalysis::HReader(BottomTagger);
    LeptonicTopTagger = NewTopTagger;
    TopReader = new hanalysis::HReader(LeptonicTopTagger);
    HeavyHiggsTagger = NewHeavyHiggsTagger;
    HeavyHiggsReader = new hanalysis::HReader(HeavyHiggsTagger);

    TaggerName = "LeptonicEvent";
    SignalNames = {"LeptonicEvent"};
    BackgroundNames = {"NotLeptonicEvent"};
    CandidateBranchName = "LeptonicEvent";


    Branch = new hheavyhiggs::HLeptonicEventBranch();
    JetTag = new hanalysis::HJetTag();

    DefineVariables();

}

hheavyhiggs::HLeptonicEventTagger::~HLeptonicEventTagger()
{

    Print(HNotification , "Constructor");

    delete Branch;
    delete JetTag;
    delete BottomReader;
    delete TopReader;
    delete HeavyHiggsReader;

}

void hheavyhiggs::HLeptonicEventTagger::FillBranch(hheavyhiggs::HLeptonicEventBranch *EventBranch, const HHeavyHiggsEvent &HeavyHiggsEvent)
{
    Print(HInformation, "FillPairTagger", HeavyHiggsEvent.GetBdt());

    EventBranch->LeptonNumber = HeavyHiggsEvent.GetLeptonNumber();
    EventBranch->JetNumber = HeavyHiggsEvent.GetJetNumber();
    EventBranch->BottomNumber = HeavyHiggsEvent.GetBottomNumber();

    EventBranch->ScalarHt = HeavyHiggsEvent.GetScalarHt();
    EventBranch->HeavyParticleBdt = HeavyHiggsEvent.GetBdt();

    EventBranch->HeavyHiggsBdt = HeavyHiggsEvent.GetHeavyHiggs().GetBdt();
    EventBranch->HeavyHiggsMass = HeavyHiggsEvent.GetHeavyHiggs().GetInvariantMass();
    EventBranch->HeavyHiggsPt = HeavyHiggsEvent.GetHeavyHiggs().GetPtSum();

    EventBranch->BottomSumPt = HeavyHiggsEvent.GetBottomSumPt();
    EventBranch->BottomDeltaPt = HeavyHiggsEvent.GetBottomDeltaPt();

    EventBranch->BottomDeltaRap = HeavyHiggsEvent.GetBottomDeltaRap();
    EventBranch->BottomDeltaPhi = HeavyHiggsEvent.BottomDeltaPhi();
    EventBranch->BottomDeltaR = HeavyHiggsEvent.GetBottomDeltaR();

    EventBranch->HbSumDeltaRap = HeavyHiggsEvent.GetHbSumDeltaRap();
    EventBranch->HbSumDeltaPhi = HeavyHiggsEvent.GetHbSumDeltaPhi();
    EventBranch->HbSumDeltaR = HeavyHiggsEvent.GetHbSumDeltaR();

    EventBranch->HbDeltaDeltaRap = HeavyHiggsEvent.GetHbDeltaDeltaRap();
    EventBranch->HbDeltaDeltaPhi = HeavyHiggsEvent.GetHbDeltaDeltaPhi();
    EventBranch->HbDeltaDeltaR = HeavyHiggsEvent.GetHbDeltaDeltaR();

    EventBranch->EventTag = HeavyHiggsEvent.GetTag();
}

void hheavyhiggs::HLeptonicEventTagger::FillBranch(const HHeavyHiggsEvent &HeavyHiggsEvent)
{
    Print(HInformation, "FillPairTagger");

    FillBranch(Branch, HeavyHiggsEvent);

}

void hheavyhiggs::HLeptonicEventTagger::DefineVariables()
{

    Print(HNotification , "Define Variables");

    Observables.push_back(NewObservable(&Branch->LeptonNumber, "LeptonNumber"));
    Observables.push_back(NewObservable(&Branch->JetNumber, "JetNumber"));
    Observables.push_back(NewObservable(&Branch->BottomNumber, "BottomNumber"));

    Observables.push_back(NewObservable(&Branch->ScalarHt, "ScalarHt"));
    Observables.push_back(NewObservable(&Branch->HeavyParticleBdt, "HeavyParticleBdt"));

    Observables.push_back(NewObservable(&Branch->HeavyHiggsBdt, "HeavyHiggsBdt"));
    Observables.push_back(NewObservable(&Branch->HeavyHiggsPt, "HeavyHiggsPt"));

    Observables.push_back(NewObservable(&Branch->BottomSumPt, "BottomSumPt"));
    Observables.push_back(NewObservable(&Branch->BottomDeltaPt, "BottomDeltaPt"));

    Observables.push_back(NewObservable(&Branch->BottomDeltaRap, "BottomDeltaRap"));
    Observables.push_back(NewObservable(&Branch->BottomDeltaPhi, "BottomDeltaPhi"));
    Observables.push_back(NewObservable(&Branch->BottomDeltaR, "BottomDeltaR"));

    Observables.push_back(NewObservable(&Branch->HbSumDeltaRap, "HbSumDeltaRap"));
    Observables.push_back(NewObservable(&Branch->HbSumDeltaPhi, "HbSumDeltaPhi"));
    Observables.push_back(NewObservable(&Branch->HbSumDeltaR, "HbSumDeltaR"));

    Observables.push_back(NewObservable(&Branch->HbDeltaDeltaRap, "HbDeltaDeltaRap"));
    Observables.push_back(NewObservable(&Branch->HbDeltaDeltaPhi, "HbDeltaDeltaPhi"));
    Observables.push_back(NewObservable(&Branch->HbDeltaDeltaR, "HbDeltaDeltaR"));

    Spectators.push_back(NewObservable(&Branch->EventTag, "EventTag"));
    Spectators.push_back(NewObservable(&Branch->HeavyHiggsMass, "HeavyHiggsMass"));

    Print(HNotification, "Variables defined");

}



struct SortHeavyHiggsEvents {
    inline bool operator()(const HHeavyHiggsEvent &Event1, const HHeavyHiggsEvent &Event2) {
        return (Event1.GetBdt() > Event2.GetBdt());
    }
};

std::vector<hheavyhiggs::HLeptonicEventBranch * > hheavyhiggs::HLeptonicEventTagger::GetBranches(hanalysis::HEvent *const Event, const HObject::HState State)
{
    std::vector<hheavyhiggs::HLeptonicEventBranch*> EventBranches;
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
    for (auto Lepton1 = Leptons.begin(); Lepton1 != Leptons.end(); ++Lepton1) {
        for (auto Lepton2 = Lepton1 + 1; Lepton2 != Leptons.end(); ++Lepton2) {
            HJets EventLeptons  {(*Lepton1), (*Lepton2)};
            for (auto Jet1 = Jets.begin(); Jet1 != Jets.end(); ++Jet1) {
                for (auto Jet2 = Jet1 + 1; Jet2 != Jets.end(); ++Jet2) {
                    for (auto Jet3 = Jet2 + 1; Jet3 != Jets.end(); ++Jet3) {
                        for (auto Jet4 = Jet3 + 1; Jet4 != Jets.end(); ++Jet4) {
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
    hheavyhiggs::HLeptonicEventBranch *EventBranch = new hheavyhiggs::HLeptonicEventBranch();
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



std::vector<HHeavyHiggsEvent> hheavyhiggs::HLeptonicEventTagger::GetHeavyHiggsEvents(const HJets &Jets, const HJets &Leptons)
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
    
    if (HeavyHiggsEvents.size() > 1) {
        std::sort(HeavyHiggsEvents.begin(), HeavyHiggsEvents.end(), SortHeavyHiggsEvents());
        HeavyHiggsEvents.erase(HeavyHiggsEvents.begin() + 1, HeavyHiggsEvents.end());
    }

    return HeavyHiggsEvents;

}
