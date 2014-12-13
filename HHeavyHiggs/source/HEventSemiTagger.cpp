# include "HEventSemiTagger.hh"

hheavyhiggs::HEventSemiTagger::HEventSemiTagger(hanalysis::HBottomTagger*const NewBottomTagger, hanalysis::HWTagger*const NewWTagger, hanalysis::HTopSemiTagger*const NewTopSemiTagger, hanalysis::HTopHadronicTagger*const NewTopHadronicTagger, hanalysis::HHeavyHiggsSemiTagger*const NewHeavyHiggsMixedTagger)
{
//   DebugLevel = HDebug;

    Print(HNotification , "Constructor");

    BottomTagger = NewBottomTagger;
    BottomReader = new hanalysis::HReader(BottomTagger);
    WTagger = NewWTagger;
    WReader = new hanalysis::HReader(WTagger);
    TopHadronicTagger = NewTopHadronicTagger;
    TopHadronicReader = new hanalysis::HReader(TopHadronicTagger);
    TopSemiTagger = NewTopSemiTagger;
    TopSemiReader = new hanalysis::HReader(TopSemiTagger);
    HeavyHiggsSemiTagger = NewHeavyHiggsMixedTagger;
    HeavyHiggsSemiReader = new hanalysis::HReader(HeavyHiggsSemiTagger);

    TaggerName = "EventSemi";
    SignalNames = {"EventSemi"};
    BackgroundNames = {"NotEventSemi"};
    CandidateBranchName = "EventSemi";


    Branch = new hheavyhiggs::HEventSemiBranch();
    JetTag = new hanalysis::HJetTag();

    DefineVariables();

}

hheavyhiggs::HEventSemiTagger::~HEventSemiTagger()
{

    Print(HNotification , "Constructor");

    delete Branch;
    delete JetTag;
    delete BottomReader;
    delete TopHadronicReader;
    delete HeavyHiggsSemiReader;

}

void hheavyhiggs::HEventSemiTagger::FillBranch(hheavyhiggs::HEventSemiBranch *EventBranch, const HOctet &HeavyHiggsEvent)
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

void hheavyhiggs::HEventSemiTagger::FillBranch(const HOctet &HeavyHiggsEvent)
{
    Print(HInformation, "FillPairTagger");

    FillBranch(Branch, HeavyHiggsEvent);

}

void hheavyhiggs::HEventSemiTagger::DefineVariables()
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

std::vector<hheavyhiggs::HEventSemiBranch * > hheavyhiggs::HEventSemiTagger::GetBranches(hanalysis::HEvent *const Event, const HObject::HState State)
{
  Print(HInformation, "Get Event Tags");

  JetTag->HeavyParticles = {WId, TopId, HeavyHiggsId};
  HJets Jets = Event->GetJets()->GetStructuredTaggedJets(JetTag);

  Jets = BottomTagger->GetBottomBdt(Jets, BottomReader);

  HJets Leptons = Event->GetLeptons()->GetTaggedJets(JetTag);
  fastjet::PseudoJet MissingEt = Event->GetJets()->GetMissingEt();
  std::vector<hanalysis::HTriplet> TripletsSemi = TopSemiTagger->GetTopSemiBdt(Jets, Leptons, MissingEt, TopSemiReader, State);

  std::vector<hanalysis::HDoublet> Doublets = WTagger->GetWBdt(Jets, WReader, State);
  std::vector<hanalysis::HTriplet> TripletsHadronic = TopHadronicTagger->GetTopHadronicBdt(Doublets, Jets, WReader, State);

  std::vector<hanalysis::HSextet> Sextets = HeavyHiggsSemiTagger->GetHeavyHiggsSemiBdt(TripletsSemi,TripletsHadronic,HeavyHiggsSemiReader,State);


  std::vector<HOctet> Octets;
  for (auto Jet1 = Jets.begin(); Jet1 != Jets.end(); ++Jet1) {
    for (auto Jet2 = Jet1 + 1; Jet2 != Jets.end(); ++Jet2) {
      for (const auto & Sextet : Sextets) {
        if (Sextet.GetTriplet1().GetJet() == *Jet1) continue;
        if (Sextet.GetTriplet1().GetJet() == *Jet2) continue;
        if (Sextet.GetTriplet2().GetJet() == *Jet1) continue;
        if (Sextet.GetTriplet2().GetJet() == *Jet2) continue;
        if (Sextet.GetTriplet2().GetDoublet().GetJet1() == *Jet1) continue;
        if (Sextet.GetTriplet2().GetDoublet().GetJet1() == *Jet2) continue;
        if (Sextet.GetTriplet2().GetDoublet().GetJet2() == *Jet1) continue;
        if (Sextet.GetTriplet2().GetDoublet().GetJet2() == *Jet2) continue;
        HOctet Octet(Sextet, *Jet1, *Jet2);
        //                 Octet.SetTag(GetOctetTag(Octet));
        //                 if(Octet.GetTag() != State) continue;
        Octets.push_back(Octet);
      }
    }
  }


  if (State == HSignal && Octets.size() > 1) {
    Print(HError,"more than one event");
      std::sort(Octets.begin(), Octets.end(), SortHeavyHiggsEvents());
        Octets.erase(Octets.begin() + 1, Octets.end());
    }

    std::vector<hheavyhiggs::HEventSemiBranch *> EventSemiBranches;
    for (auto & Octet : Octets) {
        hheavyhiggs::HEventSemiBranch *EventSemiBranch = new hheavyhiggs::HEventSemiBranch();
        Octet.SetLeptonNumber(Event->GetLeptons()->GetLeptonJets().size());
        Octet.SetJetNumber(Event->GetJets()->GetJets().size());
        Octet.SetBottomNumber(Event->GetJets()->GetBottomJets().size());
        Octet.SetScalarHt(Event->GetJets()->GetScalarHt());
        Octet.SetTag(State);
        FillBranch(EventSemiBranch, Octet);
        EventSemiBranches.push_back(EventSemiBranch);
    }

    return EventSemiBranches;

}
/*
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

std::vector<HOctet> hheavyhiggs::HEventSemiTagger::GetHeavyHiggsEvents(HJets &Jets)
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

    if (Triples.size() != 2 || Jets.size() != 2) Print(HError, "Firt Triple", Triples.size(),Jets.size());

    hanalysis::HSextet TriplePair(Triples[0], Triples[1]);
    HeavyHiggsSemiTagger->FillBranch(TriplePair);
    TriplePair.SetBdt(HeavyHiggsSemiReader->GetBdt());
    HeavyHiggsEvents.push_back(HOctet(TriplePair, Jets[0], Jets[1]));

    return HeavyHiggsEvents;

}*/
