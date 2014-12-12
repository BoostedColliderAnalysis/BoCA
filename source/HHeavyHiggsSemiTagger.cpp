# include "HHeavyHiggsSemiTagger.hh"

hanalysis::HHeavyHiggsSemiTagger::HHeavyHiggsSemiTagger(HBottomTagger *const NewBottomTagger, HWTagger *const NewWTagger, HTopSemiTagger *const NewTopSemiTagger, HTopHadronicTagger *const NewTopHadronicTagger)
{
//     DebugLevel = hanalysis::HObject::HDebug;

    Print(HNotification, "Constructor");

    BottomTagger = NewBottomTagger;
    BottomReader = new HReader(BottomTagger);
    WTagger = NewWTagger;
    WReader = new HReader(WTagger);
    TopSemiTagger = NewTopSemiTagger;
    TopSemiReader = new HReader(TopSemiTagger);
    TopHadronicTagger = NewTopHadronicTagger;
    TopHadronicReader = new HReader(TopHadronicTagger);

    TaggerName = "HeavyHiggsSemi";
    SignalNames = {"HeavyHiggsSemi"};
    BackgroundNames = {"NotHeavyHiggsSemi"};
    CandidateBranchName = "HeavyHiggsSemi";

    Branch = new HHeavyHiggsSemiBranch();
    JetTag = new HJetTag();

    DefineVariables();
}

hanalysis::HHeavyHiggsSemiTagger::~HHeavyHiggsSemiTagger()
{
    Print(HNotification, "Destructor");
    delete Branch;
    delete JetTag;
    delete BottomReader;
    delete TopHadronicReader;
    delete TopSemiReader;

}

void hanalysis::HHeavyHiggsSemiTagger::FillBranch(HHeavyHiggsSemiBranch *HeavyHiggsBranch, const HSextet &TriplePair)
{
    Print(HInformation, "FillPairTagger", TriplePair.GetBdt());

    HeavyHiggsBranch->HeavyHiggsMass = TriplePair.GetSextetJet().m();
    HeavyHiggsBranch->HeavyHiggsPt = TriplePair.GetSextetJet().pt();

    HeavyHiggsBranch->TopDeltaR = TriplePair.GetDeltaR();
    HeavyHiggsBranch->TopDeltaRap = TriplePair.GetDeltaRap();
    HeavyHiggsBranch->TopDeltaPhi = TriplePair.GetDeltaPhi();

//     HeavyHiggsBranch->LargerWDeltaR = TriplePair.GetLargerTripleDeltaR();
//     HeavyHiggsBranch->LargerWDeltaRap = TriplePair.GetLargerTripleDeltaRap();
//     HeavyHiggsBranch->LargerWDeltaPhi = TriplePair.GetLargerTripleDeltaPhi();
//
//     HeavyHiggsBranch->SmallerWDeltaR = TriplePair.GetSmallerTripleDeltaR();
//     HeavyHiggsBranch->SmallerWDeltaRap = TriplePair.GetSmallerTripleDeltaRap();
//     HeavyHiggsBranch->SmallerWDeltaPhi = TriplePair.GetSmallerTripleDeltaPhi();
//
//     HeavyHiggsBranch->LargerNeutrinoDeltaR = TriplePair.GetLargerTripleDeltaR();
//     HeavyHiggsBranch->LargerNeutrinoDeltaRap = TriplePair.GetLargerTripleDeltaRap();
//     HeavyHiggsBranch->LargerNeutrinoDeltaPhi = TriplePair.GetLargerTripleDeltaPhi();
//
//     HeavyHiggsBranch->SmallerNeutrinoDeltaR = TriplePair.GetSmallerTripleDeltaR();
//     HeavyHiggsBranch->SmallerNeutrinoDeltaRap = TriplePair.GetSmallerTripleDeltaRap();
//     HeavyHiggsBranch->SmallerNeutrinoDeltaPhi = TriplePair.GetSmallerTripleDeltaPhi();

    HeavyHiggsBranch->TopBdt = TriplePair.GetBdt();
    HeavyHiggsBranch->HeavyHiggsTag = TriplePair.GetTag();

}

void hanalysis::HHeavyHiggsSemiTagger::DefineVariables()
{

    Print(HNotification , "Define Variables");

    Observables.push_back(NewObservable(&Branch->HeavyHiggsPt, "HeavyHiggsPt"));

    Observables.push_back(NewObservable(&Branch->TopDeltaR, "TopDeltaR"));
    Observables.push_back(NewObservable(&Branch->TopDeltaRap, "TopDeltaRap"));
    Observables.push_back(NewObservable(&Branch->TopDeltaPhi, "TopDeltaPhi"));

//     Observables.push_back(NewObservable(&Branch->LargerWDeltaR, "LargerWDeltaR"));
//     Observables.push_back(NewObservable(&Branch->LargerWDeltaRap, "LargerWDeltaRap"));
//     Observables.push_back(NewObservable(&Branch->LargerWDeltaPhi, "LargerWDeltaPhi"));
//
//     Observables.push_back(NewObservable(&Branch->SmallerWDeltaR, "SmallerWDeltaR"));
//     Observables.push_back(NewObservable(&Branch->SmallerWDeltaRap, "SmallerWDeltaRap"));
//     Observables.push_back(NewObservable(&Branch->SmallerWDeltaPhi, "SmallerWDeltaPhi"));
//
//     Observables.push_back(NewObservable(&Branch->LargerNeutrinoDeltaR, "LargerNeutrinoDeltaR"));
//     Observables.push_back(NewObservable(&Branch->LargerNeutrinoDeltaRap, "LargerNeutrinoDeltaRap"));
//     Observables.push_back(NewObservable(&Branch->LargerNeutrinoDeltaPhi, "LargerNeutrinoDeltaPhi"));
//
//     Observables.push_back(NewObservable(&Branch->SmallerNeutrinoDeltaR, "SmallerNeutrinoDeltaR"));
//     Observables.push_back(NewObservable(&Branch->SmallerNeutrinoDeltaRap, "SmallerNeutrinoDeltaRap"));
//     Observables.push_back(NewObservable(&Branch->SmallerNeutrinoDeltaPhi, "SmallerNeutrinoDeltaPhi"));

    Observables.push_back(NewObservable(&Branch->TopBdt, "TopBdt"));

    Spectators.push_back(NewObservable(&Branch->HeavyHiggsTag, "HeavyHiggsTag"));
    Spectators.push_back(NewObservable(&Branch->HeavyHiggsMass, "HeavyHiggsMass"));

    Print(HNotification, "Variables defined");

}


std::vector< HHeavyHiggsSemiBranch * > hanalysis::HHeavyHiggsSemiTagger::GetBranches(hanalysis::HEvent *const Event, const hanalysis::HObject::HState State)
{
    Print(HInformation, "Get Higgs Tags");

    std::vector<HHeavyHiggsSemiBranch *> HeavyHiggsBranches;

    JetTag->HeavyParticles = {WId, TopId, HeavyHiggsId};
    HJets Jets = Event->GetJets()->GetStructuredTaggedJets(JetTag);

    for (auto Jet = Jets.begin(); Jet != Jets.end();) {
        if (std::abs((*Jet).user_index()) == MixedJetId) {
            Jet = Jets.erase(Jet);
        } else {
            HJetInfo *JetInfo = new HJetInfo;
            BottomTagger->FillBranch(*Jet);
            JetInfo->SetBdt(BottomReader->GetBdt());
            (*Jet).set_user_info(JetInfo);
            ++Jet;
        }
    }
    if (Jets.size() < 4) {
        Print(HInformation, "Not enough jets", Jets.size());
        return HeavyHiggsBranches;
    }

    HJets Leptons = Event->GetLeptons()->GetTaggedJets(JetTag);
    for (auto Lepton = Leptons.begin(); Lepton != Leptons.end();) {
        if (std::abs((*Lepton).user_index()) == MixedJetId) {
            Lepton = Jets.erase(Lepton);
        } else {
            ++Lepton;
        }
    }
    if (Leptons.size() < 2) {
        Print(HInformation, "Not enough leptons", Leptons.size());
        return HeavyHiggsBranches;
    }

    fastjet::PseudoJet Met = Event->GetJets()->GetMissingEt();


    Print(HDebug, "Jets", Jets.size());
    std::vector<HSextet > TriplePairs;
    for (auto Lepton = Leptons.begin(); Lepton != Leptons.end(); ++Lepton)
        for (auto Jet1 = Jets.begin(), JetEnd = Jets.end(); Jet1 != JetEnd; ++Jet1)
            for (auto Jet2 = Jet1 + 1; Jet2 != JetEnd; ++Jet2)
                for (auto Jet3 = Jet2 + 1; Jet3 != JetEnd; ++Jet3)
                    for (auto Jet4 = Jet3 + 1; Jet4 != JetEnd; ++Jet4) {
                        HJets HiggsJets {(*Jet1), (*Jet2), (*Jet3), (*Jet4)};
                        HSextet Pair = GetTriplePair(HiggsJets, *Lepton, Met, State);
                        Print(HDebug, "Got Triple Pairs");
                        if (Pair.GetBdt() > -1)TriplePairs.push_back(Pair);
                    }







    Print(HError, "Number of Heavy Higgses", TriplePairs.size());
    if (TriplePairs.size() < 1) return HeavyHiggsBranches;

    if (State == HSignal && TriplePairs.size() > 1) {
        Print(HError, "Higgs Candidates", TriplePairs.size());
//         std::sort(TriplePairs.begin(), TriplePairs.end(), SortByError());
//         TriplePairs.erase(TriplePairs.begin() + 1, TriplePairs.end());
    }

    for (const auto & TriplePair : TriplePairs) {
        HHeavyHiggsSemiBranch *HeavyHiggsBranch = new HHeavyHiggsSemiBranch();
        FillBranch(HeavyHiggsBranch, TriplePair);
        HeavyHiggsBranches.push_back(HeavyHiggsBranch);
    }


    return HeavyHiggsBranches;

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

hanalysis::HSextet hanalysis::HHeavyHiggsSemiTagger::GetTriplePair(HJets &Jets, fastjet::PseudoJet Lepton, fastjet::PseudoJet MissingEt, const hanalysis::HObject::HState State)
{

    Print(HDebug, "Get Triple Pairs", Jets.size());
    HSextet TriplePair;

    HDoublet Doublet1(Lepton,MissingEt);

    HBestPair WPair;
    for (auto Jet1 = Jets.begin(); Jet1 != Jets.end(); ++Jet1) {
        if (State == HSignal && std::abs((*Jet1).user_index()) != WId) continue;
        for (auto Jet2 = Jets.begin(); Jet2 != Jets.end(); ++Jet2) {
            if (Jet2 == Jet1) continue;
            if (State == HSignal && (*Jet2).user_index() != (*Jet1).user_index()) continue;
            HDoublet Pair(*Jet1, *Jet2);
            Print(HDebug, "Pair");
            WTagger->FillBranch(Pair);
            Print(HDebug, "Bdt");
            const float Bdt = WReader->GetBdt();
            Pair.SetBdt(Bdt);
            if (Bdt > WPair.Bdt) WPair.Fill(Pair, std::distance(Jets.begin(), Jet1), std::distance(Jets.begin(), Jet2), Bdt);
        }
    }
    Print(HDebug, "WPosition", WPair.First, WPair.Second);
    if (WPair.First == -1 || WPair.Second == -1) return TriplePair;
    Jets.erase(Jets.begin() + WPair.First);
    Jets.erase(Jets.begin() + WPair.Second);

    HBestTriple TopTriple;
    for (auto Jet = Jets.begin(); Jet != Jets.end(); ++Jet) {
        if (State == HSignal && std::abs((*Jet).user_index()) != TopId) continue;
        HTriplet Triplet(Doublet1,*Jet);
        HJets Neutrinos = TopSemiTagger->GetNeutrinos(Triplet);
        for (const auto & Neutrino : Neutrinos) {
          HDoublet Doublet(Neutrino, Lepton);
            HTriplet Triple(Doublet, *Jet);
            TopSemiTagger->FillBranch(Triple);
            const float Bdt = TopSemiReader->GetBdt();
            Triple.SetBdt(Bdt);

            if (Bdt > TopTriple.Bdt) TopTriple.Fill(Triple, std::distance(Jets.begin(), Jet), Bdt);
        }

    }
    if (TopTriple.Position == -1) return TriplePair;
    Jets.erase(Jets.begin() + TopTriple.Position);


    Print(HDebug, "Got 2 Ws", Jets.size());

    HTriplet Triple(WPair.Pair,Jets[0]);
    TopHadronicTagger->FillBranch(Triple);
    const float Bdt = TopHadronicReader->GetBdt();
    Triple.SetBdt(Bdt);

    HSextet TriplePair2(TopTriple.Triple, Triple);

    Print(HDebug, "Got TripelPair");

    return TriplePair2;

}

void hanalysis::HHeavyHiggsSemiTagger::FillBranch(const hanalysis::HSextet &TriplePair)
{
    Print(HInformation, "FillPairTagger", TriplePair.GetBdt());

    FillBranch(Branch, TriplePair);

}



// for (auto JetsBegin = Jets.begin(), W1Jet1 = JetsBegin, JetsEnd = Jets.end(); W1Jet1 != JetsEnd; ++W1Jet1) {
//     Print(HDebug, "First Loop", std::distance(JetsBegin, W1Jet1), (*W1Jet1).user_index());
//     if (State == HSignal && std::abs((*W1Jet1).user_index()) != WId) continue;
//
//
//     for (auto W1Jet2 = JetsBegin; W1Jet2 != JetsEnd; ++W1Jet2) {
//         Print(HDebug, "Second Loop", std::distance(JetsBegin, W1Jet2));
//         if (W1Jet2 == W1Jet1)continue;
//         if (State == HSignal && (*W1Jet2).user_index() != (*W1Jet1).user_index()) continue;
//         HDoublet Pair1(*W1Jet1, *W1Jet2);
//         WTagger->FillBranch(Pair1);
//         Pair1.SetBdt(WReader->GetBdt());
//         if (HBackground && Pair1.GetBdt() < 0) continue;
//
//         for (auto Bottom1 = JetsBegin; Bottom1 != JetsEnd; ++Bottom1) {
//             Print(HDebug, "Third Loop", std::distance(JetsBegin, Bottom1));
//             if (Bottom1 == W1Jet2)continue;
//             if (State == HSignal && std::abs((*Bottom1).user_index()) != TopId) continue;
//             if (State == HSignal && sgn((*Bottom1).user_index()) != sgn((*W1Jet1).user_index())) continue;
//             HTriplet Triple1(Pair1, *Bottom1);
//             TopHadronicTagger->FillBranch(Triple1);
//             Triple1.SetBdt(TopHadronicReader->GetBdt());
//             if (HBackground && Triple1.GetBdt() < 0) continue;
//
//             for (auto W2Jet1 = JetsBegin; W2Jet1 != JetsEnd; ++W2Jet1) {
//                 Print(HDebug, "Fourth Loop", std::distance(JetsBegin, W2Jet1));
//                 if (W2Jet1 == Bottom1) continue;
//                 if (State == HSignal && (*W2Jet1).user_index() != -(*W1Jet1).user_index()) continue;
//
//                 for (auto W2Jet2 = JetsBegin; W2Jet2 != JetsEnd; ++W2Jet2) {
//                     Print(HDebug, "Fifth Loop", std::distance(JetsBegin, W2Jet2));
//                     if (W2Jet2 == W2Jet1)continue;
//                     if (State == HSignal && (*W2Jet2).user_index() != (*W2Jet1).user_index()) continue;
//                     HDoublet Pair2(*W2Jet1, *W2Jet2);
//                     WTagger->FillBranch(Pair2);
//                     Pair2.SetBdt(WReader->GetBdt());
//                     if (HBackground && Pair2.GetBdt() < 0) continue;
//
//                     for (auto Bottom2 = JetsBegin; Bottom2 != JetsEnd; ++Bottom2) {
//                         Print(HDebug, "Sixth Loop", std::distance(JetsBegin, Bottom2));
//                         if (Bottom2 == W2Jet2)continue;
//                         if (State == HSignal && (*Bottom2).user_index() != (*Bottom1).user_index()) continue;
//                         if (
//                             State == HBackground &&
//                             std::abs((*W1Jet1).user_index()) == WId &&
//                             (*W1Jet2).user_index() == (*W1Jet1).user_index() &&
//                             (*W2Jet1).user_index() == -(*W1Jet1).user_index() &&
//                             (*W2Jet2).user_index() == (*W1Jet1).user_index() &&
//                             std::abs((*Bottom1).user_index()) == TopId &&
//                             sgn((*Bottom1).user_index()) == sgn((*W1Jet1).user_index()) &&
//                             (*Bottom2).user_index() == - (*Bottom1).user_index()
//                         ) continue;
//
//                         HTriplet Triple2(Pair2, *Bottom2);
//                         TopHadronicTagger->FillBranch(Triple2);
//                         Triple2.SetBdt(TopHadronicReader->GetBdt());
//                         if (HBackground && Triple2.GetBdt() < 0) continue;
//
//                         HTriplePair TriplePair(Triple1, Triple2);
//                         TriplePairs.push_back(TriplePair);
//
//                     }
//                 }
//             }
//         }
//     }
// }
