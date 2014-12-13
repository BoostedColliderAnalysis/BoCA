# include "HEventHadronicTagger.hh"

hheavyhiggs::HEventHadronicTagger::HEventHadronicTagger(hanalysis::HBottomTagger *const NewBottomTagger, hanalysis::HWTagger *const NewWTagger, hanalysis::HTopHadronicTagger *const NewTopTagger, hanalysis::HHeavyHiggsHadronicTagger *const NewHeavyHiggsTagger)
{

    Print(HNotification , "Constructor");

    BottomTagger = NewBottomTagger;
    BottomReader = new hanalysis::HReader(BottomTagger);
    WTagger = NewWTagger;
    WReader = new hanalysis::HReader(WTagger);
    TopHadronicTagger = NewTopTagger;
    TopHadronicReader = new hanalysis::HReader(TopHadronicTagger);
    HeavyHiggsHadronicTagger = NewHeavyHiggsTagger;
    HeavyHiggsReader = new hanalysis::HReader(HeavyHiggsHadronicTagger);

    TaggerName = "HadronicEvent";
    SignalNames = {"HadronicEvent"};
    BackgroundNames = {"NotHadronicEvent"};
    CandidateBranchName = "HadronicEvent";


    Branch = new hheavyhiggs::HEventHadronicBranch();
    JetTag = new hanalysis::HJetTag();

    DefineVariables();

}

hheavyhiggs::HEventHadronicTagger::~HEventHadronicTagger()
{

    Print(HNotification , "Constructor");

    delete Branch;
    delete JetTag;
    delete BottomReader;
    delete TopHadronicReader;
    delete HeavyHiggsReader;

}

void hheavyhiggs::HEventHadronicTagger::FillBranch(hheavyhiggs::HEventHadronicBranch *EventBranch, const HOctet &HeavyHiggsEvent)
{
    Print(HInformation, "FillPairTagger", HeavyHiggsEvent.GetBdt());

    EventBranch->LeptonNumber = HeavyHiggsEvent.GetLeptonNumber();
    EventBranch->JetNumber = HeavyHiggsEvent.GetJetNumber();
    EventBranch->BottomNumber = HeavyHiggsEvent.GetBottomNumber();

    EventBranch->ScalarHt = HeavyHiggsEvent.GetScalarHt();
    EventBranch->HeavyParticleBdt = HeavyHiggsEvent.GetBdt();

    EventBranch->HeavyHiggsBdt = HeavyHiggsEvent.GetSextet().GetBdt();
    EventBranch->HeavyHiggsMass = HeavyHiggsEvent.GetSextet().GetSextetJet().m();
    EventBranch->HeavyHiggsPt = HeavyHiggsEvent.GetSextet().GetSextetJet().pt();

    EventBranch->BottomSumPt = HeavyHiggsEvent.GetJetsJet().pt();
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

void hheavyhiggs::HEventHadronicTagger::FillBranch(const HOctet &HeavyHiggsEvent)
{
    Print(HInformation, "FillPairTagger");

    FillBranch(Branch, HeavyHiggsEvent);

}

void hheavyhiggs::HEventHadronicTagger::DefineVariables()
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
    inline bool operator()(const HOctet &Event1, const HOctet &Event2) {
        return (Event1.GetBdt() > Event2.GetBdt());
    }
};

std::vector<hheavyhiggs::HEventHadronicBranch * > hheavyhiggs::HEventHadronicTagger::GetBranches(hanalysis::HEvent *const Event, const HObject::HState State)
{
    std::vector<hheavyhiggs::HEventHadronicBranch *> EventBranches;
//     int LeptonSum = Event->GetLeptons()->GetLeptonJets().size();

    HJets Jets = Event->GetJets()->GetStructuredJets();
    if (Jets.size() < 8) return EventBranches;

    Jets = BottomTagger->GetBottomBdt(Jets, BottomReader);

//     for (auto & Jet : Jets) {
//         hanalysis::HJetInfo *JetInfo = new hanalysis::HJetInfo;
//         BottomTagger->FillBranch(Jet);
//         JetInfo->SetBdt(BottomReader->GetBdt());
//         Jet.set_user_info(JetInfo);
//     }

    std::vector<hanalysis::HDoublet> Doublets = WTagger->GetWBdt(Jets, WReader, State);

    std::vector<hanalysis::HTriplet> Triplets = TopHadronicTagger->GetTopHadronicBdt(Doublets, Jets, TopHadronicReader, State);

    std::vector<hanalysis::HSextet> Sextets = HeavyHiggsHadronicTagger->GetHeavyHiggsBdt(Triplets, HeavyHiggsReader, State);

    std::vector<HOctet> Octets;

    for (const auto & Jet1 : Jets) for (const auto & Jet2 : Jets) {
            if (Jet1 == Jet2) continue;
            for (const auto & Sextet : Sextets) {
                if (Jet1 == Sextet.GetTriplet1().GetJet()) continue; //TODO implement full check
                Octets.push_back(HOctet(Sextet, Jet1, Jet2));
            }
        }

//     for (auto Jet1 = Jets.begin(), JetsEnd = Jets.end(); Jet1 != JetsEnd; ++Jet1)
//         for (auto Jet2 = Jet1 + 1; Jet2 != JetsEnd; ++Jet2)
//             for (auto Jet3 = Jet2 + 1; Jet3 != JetsEnd; ++Jet3)
//                 for (auto Jet4 = Jet3 + 1; Jet4 != JetsEnd; ++Jet4)
//                     for (auto Jet5 = Jet4 + 1; Jet5 != JetsEnd; ++Jet5)
//                         for (auto Jet6 = Jet5 + 1; Jet6 != JetsEnd; ++Jet6)
//                             for (auto Jet7 = Jet6 + 1; Jet7 != JetsEnd; ++Jet7)
//                                 for (auto Jet8 = Jet7 + 1; Jet8 != JetsEnd; ++Jet8) {
//                                     HJets EventJets {(*Jet1), (*Jet2), (*Jet3), (*Jet4),(*Jet5), (*Jet6), (*Jet7), (*Jet8)};
//                                     std::vector<HHeavyHiggsEvent> NewHeavyHiggsEvents = GetHeavyHiggsEvents(EventJets);
//                                     if (NewHeavyHiggsEvents.size() < 1)continue;
//                                     Octets.insert(Octets.end(), NewHeavyHiggsEvents.begin(), NewHeavyHiggsEvents.end());
//                                 }

    if (Octets.size() > 1) {
        std::sort(Octets.begin(), Octets.end(), SortHeavyHiggsEvents());
        Octets.erase(Octets.begin() + 1, Octets.end());
    }

    for (auto & HeavyHiggsEvent : Octets) {
        hheavyhiggs::HEventHadronicBranch *EventBranch = new hheavyhiggs::HEventHadronicBranch();
        HeavyHiggsEvent.SetLeptonNumber(Event->GetLeptons()->GetLeptonJets().size());
        HeavyHiggsEvent.SetJetNumber(Event->GetJets()->GetJets().size());
        HeavyHiggsEvent.SetBottomNumber(Event->GetJets()->GetBottomJets().size());
        HeavyHiggsEvent.SetScalarHt(Event->GetJets()->GetScalarHt());
        if (State == HSignal) HeavyHiggsEvent.SetTag(1);
        else HeavyHiggsEvent.SetTag(0);
        FillBranch(EventBranch, HeavyHiggsEvent);
        EventBranches.push_back(EventBranch);
    }

    return EventBranches;

}

class HBestPair
{

public:
    void Fill(const hanalysis::HDoublet &NewPair, const int Pos1, const int Pos2, const float NewBdt) {
        Pair = NewPair;
        First = Pos1;
        Second = Pos2;
        Bdt = NewBdt;
    }
    hanalysis::HDoublet Pair;
    float Bdt = -1;
    int First = -1;
    int Second = -1;

};

class HBestTriple
{

public:
    void Fill(const hanalysis::HTriplet &NewTriple, const int Pos, const float NewBdt) {
        Triple = NewTriple;
        Position = Pos;
        Bdt = NewBdt;
    }
    hanalysis::HTriplet Triple;
    float Bdt = -1;
    int Position = -1;

};

std::vector<HOctet> hheavyhiggs::HEventHadronicTagger::GetHeavyHiggsEvents(HJets &Jets)
{
    Print(HInformation, "Get Heavy Higgs Event");

    std::vector<HOctet> HeavyHiggsEvents;

    std::vector<hanalysis::HDoublet> Pairs;
    for (int i = 0; i < 2; ++i) {
        HBestPair BestPair;
        for (auto Jet1 = Jets.begin(); Jet1 != Jets.end(); ++Jet1) {
            for (auto Jet2 = Jets.begin(); Jet2 != Jets.end(); ++Jet2) {
                if (Jet2 == Jet1) continue;
                hanalysis::HDoublet Pair(*Jet1, *Jet2);
                WTagger->FillBranch(Pair);
                const float Bdt = WReader->GetBdt();
                Pair.SetBdt(Bdt);
                if (Bdt > BestPair.Bdt) BestPair.Fill(Pair, std::distance(Jets.begin(), Jet1), std::distance(Jets.begin(), Jet2), Bdt);
            }
        }
        if (BestPair.First == -1 || BestPair.Second == -1) {
            Print(HError, "W at wrong position");
            return HeavyHiggsEvents;
        }
        Jets.erase(Jets.begin() + BestPair.First);
        Jets.erase(Jets.begin() + BestPair.Second);
        Pairs.push_back(BestPair.Pair);
    }

    std::vector<hanalysis::HTriplet> Triples;
    for (int i = 0; i < 2; ++i) {
        Print(HDebug, "Tops");
        HBestTriple BestTriple;
        for (auto Pair = Pairs.begin(); Pair != Pairs.end(); ++Pair) {
            Print(HDebug, "Ws");
            for (auto Jet = Jets.begin(); Jet != Jets.end(); ++Jet) {
                Print(HDebug, "Bottoms");
                hanalysis::HTriplet Triple(*Pair, *Jet);
                TopHadronicTagger->FillBranch(Triple);
                const float Bdt = TopHadronicReader->GetBdt();
                Triple.SetBdt(Bdt);
                Print(HDebug, "Bdt", Bdt, BestTriple.Bdt);
                if (Bdt > BestTriple.Bdt) BestTriple.Fill(Triple, std::distance(Jets.begin(), Jet), Bdt);
            }
        }
        Print(HDebug, "BottomPosition", BestTriple.Position);
        if (BestTriple.Position == -1)         {
            Print(HError, "W at wrong position");
            return HeavyHiggsEvents;
        }
        Print(HDebug, "Erase");
        Jets.erase(Jets.begin() + BestTriple.Position);
        Triples.push_back(BestTriple.Triple);
    }

    if (Triples.size() != 2 || Jets.size() != 2) Print(HError, "Firt Triple", Triples.size(), Jets.size());

    hanalysis::HSextet TriplePair(Triples[0], Triples[1]);
    HeavyHiggsHadronicTagger->FillBranch(TriplePair);
    TriplePair.SetBdt(HeavyHiggsReader->GetBdt());
    HeavyHiggsEvents.push_back(HOctet(TriplePair, Jets[0], Jets[1]));

    return HeavyHiggsEvents;

}
