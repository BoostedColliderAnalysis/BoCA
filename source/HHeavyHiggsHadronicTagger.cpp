# include "HHeavyHiggsHadronicTagger.hh"

hanalysis::HHeavyHiggsHadronicTagger::HHeavyHiggsHadronicTagger(HBottomTagger *const NewBottomTagger, HWTagger *const NewWTagger, HHadronicTopTagger *const NewTopTagger)
{
//     DebugLevel = hanalysis::HObject::HDebug;

    Print(HNotification, "Constructor");

    BottomTagger = NewBottomTagger;
    BottomReader = new HReader(BottomTagger);
    WTagger = NewWTagger;
    WReader = new HReader(WTagger);
    TopHadronicTagger = NewTopTagger;
    TopHadronicReader = new HReader(TopHadronicTagger);

    TaggerName = "HeavyHiggsHadronic";
    SignalNames = {"HeavyHiggsHadronic"};
    BackgroundNames = {"NotHeavyHiggsHadronic"};
    CandidateBranchName = "HeavyHiggsHadronic";

    Branch = new HHeavyHiggsHadronicBranch();
    JetTag = new HJetTag();

    DefineVariables();
}

hanalysis::HHeavyHiggsHadronicTagger::~HHeavyHiggsHadronicTagger()
{
    Print(HNotification, "Destructor");
    delete Branch;
    delete JetTag;
    delete BottomReader;
    delete TopHadronicReader;

}

void hanalysis::HHeavyHiggsHadronicTagger::FillBranch(HHeavyHiggsHadronicBranch *HeavyHiggsBranch, const hanalysis::HTriplePair &TriplePair)
{
    Print(HInformation, "FillPairTagger", TriplePair.GetBdt());

    HeavyHiggsBranch->HeavyHiggsMass = TriplePair.GetInvariantMass();
    HeavyHiggsBranch->HeavyHiggsPt = TriplePair.GetPtSum();

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

void hanalysis::HHeavyHiggsHadronicTagger::DefineVariables()
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


std::vector< HHeavyHiggsHadronicBranch * > hanalysis::HHeavyHiggsHadronicTagger::GetBranches(hanalysis::HEvent *const Event, const hanalysis::HObject::HState State)
{
    Print(HInformation, "Get Higgs Tags");

    std::vector<HHeavyHiggsHadronicBranch *> HeavyHiggsBranches;

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
    if (Jets.size() < 6) {
        Print(HInformation, "Not enough jets", Jets.size());
        return HeavyHiggsBranches;
    }


    Print(HDebug, "Jets", Jets.size());
    std::vector<HTriplePair > TriplePairs;
    for (auto Jet1 = Jets.begin(), JetEnd = Jets.end(); Jet1 != JetEnd; ++Jet1)
        for (auto Jet2 = Jet1 + 1; Jet2 != JetEnd; ++Jet2)
            for (auto Jet3 = Jet2 + 1; Jet3 != JetEnd; ++Jet3)
                for (auto Jet4 = Jet3 + 1; Jet4 != JetEnd; ++Jet4)
                    for (auto Jet5 = Jet4 + 1; Jet5 != JetEnd; ++Jet5)
                        for (auto Jet6 = Jet5 + 1; Jet6 != JetEnd; ++Jet6) {
                            HJets HiggsJets {(*Jet1), (*Jet2), (*Jet3), (*Jet4), (*Jet5), (*Jet6)};
                            HTriplePair Pair = GetTriplePair(HiggsJets, State);
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
        HHeavyHiggsHadronicBranch *HeavyHiggsBranch = new HHeavyHiggsHadronicBranch();
        FillBranch(HeavyHiggsBranch, TriplePair);
        HeavyHiggsBranches.push_back(HeavyHiggsBranch);
    }


    return HeavyHiggsBranches;

}

class HBestPair
{

public:
    void Fill(const hanalysis::HSuperStructure &NewPair, const int Pos1, const int Pos2, const float NewBdt) {
        Pair = NewPair;
        First = Pos1;
        Second = Pos2;
        Bdt = NewBdt;
    }
    hanalysis::HSuperStructure Pair;
    float Bdt = -1;
    int First = -1;
    int Second = -1;

};

class HBestTriple
{

public:
    void Fill(const hanalysis::HPairJetPair &NewTriple, const int Pos, const float NewBdt) {
        Triple = NewTriple;
        Position = Pos;
        Bdt = NewBdt;
    }
    hanalysis::HPairJetPair Triple;
    float Bdt = -1;
    int Position = -1;

};

hanalysis::HTriplePair hanalysis::HHeavyHiggsHadronicTagger::GetTriplePair(HJets &Jets, const hanalysis::HObject::HState State)
{

    Print(HDebug, "Get Triple Pairs", Jets.size());
    HTriplePair TriplePair;

    std::vector<HSuperStructure> Pairs;
    for (int i = 0; i < 2; ++i) {
        HBestPair BestPair;
        for (auto Jet1 = Jets.begin(); Jet1 != Jets.end(); ++Jet1) {
            if (State == HSignal && std::abs((*Jet1).user_index()) != WId) continue;
            for (auto Jet2 = Jets.begin(); Jet2 != Jets.end(); ++Jet2) {
                if (Jet2 == Jet1) continue;
                if (State == HSignal && (*Jet2).user_index() != (*Jet1).user_index()) continue;
                HSuperStructure Pair(*Jet1, *Jet2);
                Print(HDebug, "Pair");
                WTagger->FillBranch(Pair);
                Print(HDebug, "Bdt");
                const float Bdt = WReader->GetBdt();
                Pair.SetBdt(Bdt);
                if (Bdt > BestPair.Bdt) BestPair.Fill(Pair, std::distance(Jets.begin(), Jet1), std::distance(Jets.begin(), Jet2), Bdt);
            }
        }
        Print(HDebug, "WPosition", BestPair.First, BestPair.Second);
        if (BestPair.First == -1 || BestPair.Second == -1) return TriplePair;
        Jets.erase(Jets.begin() + BestPair.First);
        Jets.erase(Jets.begin() + BestPair.Second);
        Pairs.push_back(BestPair.Pair);
    }

    Print(HDebug, "Got 2 Ws", Jets.size());

    std::vector<HPairJetPair> Triples;
    for (int i = 0; i < 2; ++i) {
        Print(HDebug, "Tops");
        HBestTriple BestTriple;
        for (auto Pair = Pairs.begin(); Pair != Pairs.end(); ++Pair) {
            Print(HDebug, "Ws");
            for (auto Jet = Jets.begin(); Jet != Jets.end(); ++Jet) {
                Print(HDebug, "Bottoms");
                if (State == HSignal && (*Jet).user_index() != (*Pair).GetJet1().user_index()) continue;
                HPairJetPair Triple(*Pair, *Jet);
                TopHadronicTagger->FillBranch(Triple);
                const float Bdt = TopHadronicReader->GetBdt();
                Triple.SetBdt(Bdt);
                Print(HDebug, "Bdt", Bdt, BestTriple.Bdt);
                if (Bdt > BestTriple.Bdt) BestTriple.Fill(Triple, std::distance(Jets.begin(), Jet), Bdt);
            }
        }
        Print(HDebug, "BottomPosition", BestTriple.Position);
        if (BestTriple.Position == -1) return TriplePair;
        Print(HDebug, "Erase");
        Jets.erase(Jets.begin() + BestTriple.Position);
        Triples.push_back(BestTriple.Triple);
    }

        Print(HDebug, "Firt Triple",Triples.size());
    HTriplePair TriplePair2(Triples[0], Triples[1]);

    Print(HDebug, "Got TripelPair");

    return TriplePair2;

}

void hanalysis::HHeavyHiggsHadronicTagger::FillBranch(const hanalysis::HTriplePair &TriplePair)
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
//         HSuperStructure Pair1(*W1Jet1, *W1Jet2);
//         WTagger->FillBranch(Pair1);
//         Pair1.SetBdt(WReader->GetBdt());
//         if (HBackground && Pair1.GetBdt() < 0) continue;
//
//         for (auto Bottom1 = JetsBegin; Bottom1 != JetsEnd; ++Bottom1) {
//             Print(HDebug, "Third Loop", std::distance(JetsBegin, Bottom1));
//             if (Bottom1 == W1Jet2)continue;
//             if (State == HSignal && std::abs((*Bottom1).user_index()) != TopId) continue;
//             if (State == HSignal && sgn((*Bottom1).user_index()) != sgn((*W1Jet1).user_index())) continue;
//             HPairJetPair Triple1(Pair1, *Bottom1);
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
//                     HSuperStructure Pair2(*W2Jet1, *W2Jet2);
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
//                         HPairJetPair Triple2(Pair2, *Bottom2);
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