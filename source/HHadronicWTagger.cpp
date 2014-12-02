# include "HHadronicWTagger.hh"

hdelphes::HHadronicWTagger::HHadronicWTagger(hdelphes::HBottomTagger *NewBottomTagger)
{
//     DebugLevel = hanalysis::HObject::HDebug;

    Print(HNotification, "Constructor");

    BottomTagger = NewBottomTagger;
    BottomReader = new hmva::HReader(BottomTagger);

    TaggerName = "WTagger";
    SignalNames = {"WTagger"};
    BackgroundNames = {"NotWTagger"};
    CandidateBranchName = "WTagger";

    Branch = new HHadronicWBranch();
    JetTag = new hanalysis::HJetTag();

    DefineVariables();
}

hdelphes::HHadronicWTagger::~HHadronicWTagger()
{
    Print(HNotification, "Destructor");
    delete Branch;
    delete BottomReader;
    delete JetTag;
}

void hdelphes::HHadronicWTagger::DefineVariables()
{

    Print(HNotification , "Define Variables");

    Observables.push_back(NewObservable(&Branch->Mass, "Mass"));
    Observables.push_back(NewObservable(&Branch->PtSum, "PtSum"));
    Observables.push_back(NewObservable(&Branch->PtDiff, "PtDiff"));
    Observables.push_back(NewObservable(&Branch->DeltaPhi, "DeltaPhi"));
    Observables.push_back(NewObservable(&Branch->DeltaRap, "DeltaRap"));
    Observables.push_back(NewObservable(&Branch->DeltaR, "DeltaR"));
    Observables.push_back(NewObservable(&Branch->Pull1, "Pull1"));
    Observables.push_back(NewObservable(&Branch->Pull2, "Pull2"));
    Observables.push_back(NewObservable(&Branch->Pull, "Pull"));
    Observables.push_back(NewObservable(&Branch->BottomBdt, "BottomBdt"));

    Spectators.push_back(NewObservable(&Branch->WTag, "WTag"));

    Print(HNotification, "Variables defined");

}


struct SortPairByMass {
    inline bool operator()(const hdelphes::HSuperStructure &Pair1, const hdelphes::HSuperStructure &Pair2) {
        return (Pair1.GetMassDifference(hanalysis::HObject::WId) > Pair2.GetMassDifference(hanalysis::HObject::WId));
    }
};


std::vector<HHadronicWBranch *> hdelphes::HHadronicWTagger::GetBranches(hanalysis::HEvent *const Event, const hanalysis::HObject::HState State)
{

    Print(HInformation, "Get W Tags");

    JetTag->HeavyParticles = {WId, TopId};
    HJets Jets = Event->GetJets()->GetStructuredTaggedJets(JetTag);

    HJets WJets;
    HJets OtherJets;
    for (auto & Jet : Jets) {

        Print(HInformation, "Dominant Fraction", GetParticleName(Jet.user_info<hanalysis::HJetInfo>().GetMaximalId()));

        hanalysis::HJetInfo *JetInfo = new hanalysis::HJetInfo;
        if (Jet.user_info<hanalysis::HJetInfo>().GetMaximalId() == WId) {
            JetInfo->SetTag(1);
        } else if (Jet.user_info<hanalysis::HJetInfo>().GetMaximalId() == MixedJetId) {
            JetInfo->SetTag(0.5);
        } else {
            JetInfo->SetTag(0);
        }

        BottomTagger->FillBranch(Jet);
        JetInfo->SetBdt(BottomReader->GetBdt());
        Jet.set_user_info(JetInfo);

        if (JetInfo->GetTag() == 1) {
            WJets.push_back(Jet);
        } else {
            OtherJets.push_back(Jet);
        }
    }


    std::vector<hdelphes::HSuperStructure> JetPairs;

    if (State == HSignal) {
        Print(HInformation, "W Jets", WJets.size());
        for (HJets::iterator Jet1 = WJets.begin(); Jet1 != WJets.end(); ++Jet1) {
            for (HJets::iterator Jet2 = Jet1 + 1; Jet2 != WJets.end(); ++Jet2) {
                hdelphes::HSuperStructure JetPair((*Jet1), (*Jet2));
                JetPairs.push_back(JetPair);
            }
        }
//         if (JetPairs.size() > 1) {
//         std::sort(JetPairs.begin(), JetPairs.end(), SortPairByMass());
//             Print(HDebug, "Number of Higgses", JetPairs.size());
//             for (const auto & Pair : JetPairs) Print(HDebug, "Higgs Mass", Pair.GetInvariantMass());
//             JetPairs.erase(JetPairs.begin() + 1, JetPairs.end());
//         }
    }

    if (State == HBackground) {
        for (HJets::iterator Jet1 = OtherJets.begin(); Jet1 != OtherJets.end(); ++Jet1) {
            for (HJets::iterator Jet2 = Jet1 + 1; Jet2 != OtherJets.end(); ++Jet2) {
                hdelphes::HSuperStructure JetPair((*Jet1), (*Jet2));
                JetPairs.push_back(JetPair);
            }
        }
        for (HJets::iterator Jet1 = OtherJets.begin(); Jet1 != OtherJets.end(); ++Jet1) {
            for (HJets::iterator Jet2 = WJets.begin(); Jet2 != WJets.end(); ++Jet2) {
                hdelphes::HSuperStructure JetPair((*Jet1), (*Jet2));
                JetPairs.push_back(JetPair);
            }
        }
    }

    Print(HInformation, "Number of Jet Pairs", JetPairs.size());

    std::vector<HHadronicWBranch *> WBranches;
    for (const auto & JetPair : JetPairs) {
        HHadronicWBranch *WBranch = new HHadronicWBranch();
        FillBranch(WBranch, JetPair);
        WBranches.push_back(WBranch);
    }

    return WBranches;

}

void hdelphes::HHadronicWTagger::FillBranch(const hdelphes::HSuperStructure &Pair)
{
    Print(HInformation, "FillPairTagger", Pair.GetBdt());

    FillBranch(Branch, Pair);

}

void hdelphes::HHadronicWTagger::FillBranch(HHadronicWBranch *const WBranch, const hdelphes::HSuperStructure &Pair)
{
    Print(HInformation, "FillPairTagger", Pair.GetBdt());

    WBranch->Mass = Pair.GetInvariantMass();
    WBranch->PtSum = Pair.GetPtSum();
    WBranch->PtDiff = Pair.GetPtDiff();
    WBranch->DeltaR = Pair.GetDeltaR();
    WBranch->DeltaRap = Pair.GetDeltaRap();
    WBranch->DeltaPhi = Pair.GetPhiDelta();
    WBranch->BottomBdt = Pair.GetBdt();
    WBranch->Pull1 = Pair.GetPullAngle1();
    WBranch->Pull2 = Pair.GetPullAngle2();
    WBranch->Pull = Pair.GetPullAngle();
    WBranch->WTag = Pair.GetTag();

}

std::vector<HParticleBranch *> hdelphes::HHadronicWTagger::GetConstituentBranches()
{

    Print(HInformation, "Get Higgs Tags");

    std::vector<hdelphes::HSuperStructure> JetPairs;

    Print(HInformation, "Number of Jet Pairs", JetPairs.size());

    std::vector<HParticleBranch *> ConstituentBranches;
    for (const auto & JetPair : JetPairs) {
        for (const auto & Constituent : JetPair.GetConstituents()) {
            HParticleBranch *ConstituentBranch = new HParticleBranch();
            FillBranch(ConstituentBranch, Constituent);
            ConstituentBranches.push_back(ConstituentBranch);
        }
    }

    return ConstituentBranches;

}

void hdelphes::HHadronicWTagger::FillBranch(const HKinematics &Vector)
{
    Print(HInformation, "FillPairTagger", Vector.GetPt());

    FillBranch(Vector);

}

void hdelphes::HHadronicWTagger::FillBranch(HParticleBranch *const ConstituentBranch, const HKinematics &Vector)
{
    Print(HInformation, "Fill Constituent Branch");

    ConstituentBranch->Pt = Vector.GetPt();
    ConstituentBranch->Rap = Vector.GetRap();
    ConstituentBranch->Phi = Vector.GetPhi();

}
