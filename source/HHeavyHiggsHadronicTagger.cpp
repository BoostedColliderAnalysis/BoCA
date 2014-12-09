# include "HHeavyHiggsHadronicTagger.hh"

hanalysis::HHeavyHiggsHadronicTagger::HHeavyHiggsHadronicTagger(HBottomTagger *const NewBottomTagger,HWTagger *const NewWTagger, HHadronicTopTagger *const NewTopTagger)
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

    JetTag->HeavyParticles = {TopId};
    HJets Jets = Event->GetJets()->GetStructuredTaggedJets(JetTag);
    if (Jets.size() < 2) {
        Print(HInformation, "Not enough jets", Jets.size());
        return HeavyHiggsBranches;
    }

    for (auto Jet = Jets.begin(); Jet != Jets.end();) {
        if (std::abs((*Jet).user_index()) == MixedJetId) {
            Jet = Jets.erase(Jet);
        } else {
            HJetInfo *JetInfo = new HJetInfo;
            BottomTagger->FillBranch(*Jet);
            JetInfo->SetBdt(BottomReader->GetBdt());
            JetInfo->SetTag((*Jet).user_info<HJetInfo>().GetMaximalId());
            (*Jet).set_user_info(JetInfo);
            ++Jet;
        }
    }

    if (Jets.size() < 6)  {
        Print(HInformation, "Not jets", Jets.size());
        return HeavyHiggsBranches;
    }
    Print(HDebug, "Jets", Jets.size());
    std::vector< hanalysis::HTriplePair > TriplePairs;
    for (auto Jet1 = Jets.begin(); Jet1 != Jets.end(); ++Jet1) {
        for (auto Jet2 = Jet1 + 1; Jet2 != Jets.end(); ++Jet2) {
            for (auto Jet3 = Jet2 + 1; Jet3 != Jets.end(); ++Jet3) {
                for (auto Jet4 = Jet3 + 1; Jet4 != Jets.end(); ++Jet4) {
                    for (auto Jet5 = Jet4 + 1; Jet5 != Jets.end(); ++Jet5) {
                        for (auto Jet6 = Jet5 + 1; Jet6 != Jets.end(); ++Jet6) {
                            HJets HiggsJets {(*Jet1),(*Jet2),(*Jet3),(*Jet4),(*Jet5),(*Jet6)};
                            std::vector< hanalysis::HTriplePair > Pairs = GetTriplePairs(Jets, State);
                            TriplePairs.insert(TriplePairs.end(),Pairs.begin(),Pairs.end());
                        }
                    }
                }
            }
        }
    }


    Print(HInformation, "Number of Heavy Higgses", TriplePairs.size());
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

std::vector< hanalysis::HTriplePair > hanalysis::HHeavyHiggsHadronicTagger::GetTriplePairs(const HJets &Jets, const hanalysis::HObject::HState State)
{

    Print(HDebug, "Get Triple Pairs");

    std::vector<HTriplePair> TriplePairs;
    // W1
    for (auto Jet1 = Jets.begin(); Jet1 != Jets.end(); ++Jet1) {
        if (State == HSignal && std::abs((*Jet1).user_index()) != WId) continue;

        for (auto Jet2 = Jet1 + 1; Jet2 != Jets.end(); ++Jet2) {

            if (Jet2 == Jet1)continue;
            if (State == HSignal && (*Jet2).user_index() != (*Jet1).user_index()) continue;
            HSuperStructure Pair1(*Jet1, *Jet2);
            WTagger->FillBranch(Pair1);
            Pair1.SetBdt(WReader->GetBdt());

            // B1
            for (auto Jet3 = Jet2 + 1; Jet3 != Jets.end(); ++Jet3) {

                if (Jet3 == Jet2)continue;
                if (State == HSignal && std::abs((*Jet3).user_index()) != TopId) continue;
                if (State == HSignal && sgn((*Jet3).user_index()) != sgn((*Jet1).user_index())) continue;
                HPairJetPair Triple1(Pair1, *Jet3);
                TopHadronicTagger->FillBranch(Triple1);
                Triple1.SetBdt(TopHadronicReader->GetBdt());

                // W2
                for (auto Jet4 = Jet3 + 1; Jet4 != Jets.end(); ++Jet4) {

                    if (Jet4 == Jet3)continue;
                    if (State == HSignal && (*Jet4).user_index() != -(*Jet1).user_index()) continue;

                    for (auto Jet5 = Jet4 + 1; Jet5 != Jets.end(); ++Jet5) {

                        if (Jet5 == Jet4)continue;
                        if (State == HSignal && (*Jet5).user_index() != (*Jet4).user_index()) continue;
                        HSuperStructure Pair2(*Jet4, *Jet5);
                        WTagger->FillBranch(Pair2);
                        Pair2.SetBdt(WReader->GetBdt());

                        // B3
                        for (auto Jet6 = Jet5 + 1; Jet6 != Jets.end(); ++Jet6) {

                            if (Jet6 == Jet5)continue;
                            if (State == HSignal && (*Jet6).user_index() != (*Jet3).user_index()) continue;
                            if (State == HBackground && std::abs((*Jet1).user_index()) == WId && (*Jet2).user_index() == (*Jet1).user_index() && (*Jet4).user_index() == -(*Jet1).user_index() && (*Jet5).user_index() == (*Jet1).user_index() && std::abs((*Jet3).user_index()) == TopId && sgn((*Jet3).user_index()) == sgn((*Jet1).user_index()) && (*Jet6).user_index() == - (*Jet3).user_index()) continue;
                            HPairJetPair Triple2(Pair2, *Jet6);
                            TopHadronicTagger->FillBranch(Triple2);
                            Triple2.SetBdt(TopHadronicReader->GetBdt());

                            HTriplePair TriplePair(Triple1, Triple2);
                            TriplePairs.push_back(TriplePair);

                        }
                    }
                }
            }
        }
    }

    return TriplePairs;

}

void hanalysis::HHeavyHiggsHadronicTagger::FillBranch(const hanalysis::HTriplePair &TriplePair)
{
    Print(HInformation, "FillPairTagger", TriplePair.GetBdt());

    FillBranch(Branch, TriplePair);

}

