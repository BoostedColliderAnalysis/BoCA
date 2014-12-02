# include "HMvaHiggsTagger.hh"

hanalysis::HMvaHiggsTagger::HMvaHiggsTagger(HBottomTagger *NewBottomTagger)
{
//     DebugLevel = hanalysis::HObject::HDebug;

    Print(HNotification, "Constructor");

    BottomTagger = NewBottomTagger;
    BottomReader = new HReader(BottomTagger);

    TaggerName = "Higgs";
    SignalNames = {"Higgs"};
    BackgroundNames = {"NotHiggs"};
    CandidateBranchName = "Higgs";

    Branch = new HHiggsBranch();
    JetTag = new hanalysis::HJetTag();

    DefineVariables();
}

hanalysis::HMvaHiggsTagger::~HMvaHiggsTagger()
{
    Print(HNotification, "Destructor");
    delete Branch;
    delete BottomReader;
    delete JetTag;
}

void hanalysis::HMvaHiggsTagger::DefineVariables()
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

    Spectators.push_back(NewObservable(&Branch->HiggsTag, "HiggsTag"));

    Print(HNotification, "Variables defined");

}


struct SortPairByMass {
  inline bool operator()(const hanalysis::HSuperStructure &Pair1, const hanalysis::HSuperStructure &Pair2) {
        return (Pair1.GetMassDifference(hanalysis::HObject::HiggsId) > Pair2.GetMassDifference(hanalysis::HObject::HiggsId));
    }
};


std::vector<HHiggsBranch *> hanalysis::HMvaHiggsTagger::GetBranches(hanalysis::HEvent *const Event, const hanalysis::HObject::HState State)
{

    Print(HInformation, "Get Higgs Tags");

    JetTag->HeavyParticles = {CpvHiggsId, HiggsId,TopId};
    HJets Jets = Event->GetJets()->GetStructuredTaggedJets(JetTag);

    HJets HiggsJets;
    HJets OtherJets;
    for (auto & Jet : Jets) {

        Print(HInformation, "Dominant Fraction", GetParticleName(Jet.user_info<hanalysis::HJetInfo>().GetMaximalId()));

        hanalysis::HJetInfo *JetInfo = new hanalysis::HJetInfo;
        if (Jet.user_info<hanalysis::HJetInfo>().GetMaximalId() == HiggsId || Jet.user_info<hanalysis::HJetInfo>().GetMaximalId() == CpvHiggsId) {
            JetInfo->SetTag(1);
        } else if (Jet.user_info<hanalysis::HJetInfo>().GetMaximalId() == MixedJetId ){
            JetInfo->SetTag(0.5);
        } else {
            JetInfo->SetTag(0);
        }

        BottomTagger->FillBranch(Jet);
        JetInfo->SetBdt(BottomReader->GetBdt());
        Jet.set_user_info(JetInfo);

        if (JetInfo->GetTag()==1) {
            HiggsJets.push_back(Jet);
        } else {
            OtherJets.push_back(Jet);
        }
    }


    std::vector<HSuperStructure> JetPairs;

    if (State == HSignal) {
        Print(HInformation, "Higgs Jets", HiggsJets.size());
        for (HJets::iterator Jet1 = HiggsJets.begin(); Jet1 != HiggsJets.end(); ++Jet1) {
            for (HJets::iterator Jet2 = Jet1 + 1; Jet2 != HiggsJets.end(); ++Jet2) {
                HSuperStructure JetPair((*Jet1), (*Jet2));
//                 JetPair.SetTag(1);
                JetPairs.push_back(JetPair);
            }
        }
        std::sort(JetPairs.begin(), JetPairs.end(), SortPairByMass());
        if (JetPairs.size() > 1) {
            Print(HDebug, "Number of Higgses", JetPairs.size());
            for (const auto & Pair : JetPairs) Print(HDebug, "Higgs Mass", Pair.GetInvariantMass());
            JetPairs.erase(JetPairs.begin() + 1, JetPairs.end());
        }
    }

    if (State == HBackground) {
        for (HJets::iterator Jet1 = OtherJets.begin(); Jet1 != OtherJets.end(); ++Jet1) {
            for (HJets::iterator Jet2 = Jet1 + 1; Jet2 != OtherJets.end(); ++Jet2) {
                HSuperStructure JetPair((*Jet1), (*Jet2));
//                 JetPair.SetTag(0);
                JetPairs.push_back(JetPair);
            }
        }
        for (HJets::iterator Jet1 = OtherJets.begin(); Jet1 != OtherJets.end(); ++Jet1) {
            for (HJets::iterator Jet2 = HiggsJets.begin(); Jet2 != HiggsJets.end(); ++Jet2) {
                HSuperStructure JetPair((*Jet1), (*Jet2));
//                 JetPair.SetTag(0);
                JetPairs.push_back(JetPair);
            }
        }
    }

    Print(HInformation, "Number of Jet Pairs", JetPairs.size());

    std::vector<HHiggsBranch *> HiggsBranches;
    for (const auto & JetPair : JetPairs) {
        HHiggsBranch *HiggsBranch = new HHiggsBranch();
        FillBranch(HiggsBranch, JetPair);
        HiggsBranches.push_back(HiggsBranch);
    }

    return HiggsBranches;

}

void hanalysis::HMvaHiggsTagger::FillBranch(const HSuperStructure &Pair)
{
    Print(HInformation, "FillPairTagger", Pair.GetBdt());

    FillBranch(Branch, Pair);

}

void hanalysis::HMvaHiggsTagger::FillBranch(HHiggsBranch *const HiggsBranch, const HSuperStructure &Pair)
{
    Print(HInformation, "FillPairTagger", Pair.GetBdt());

    HiggsBranch->Mass = Pair.GetInvariantMass();
    HiggsBranch->PtSum = Pair.GetPtSum();
    HiggsBranch->PtDiff = Pair.GetPtDiff();
    HiggsBranch->DeltaR = Pair.GetDeltaR();
    HiggsBranch->DeltaRap = Pair.GetDeltaRap();
    HiggsBranch->DeltaPhi = Pair.GetPhiDelta();
    HiggsBranch->BottomBdt = Pair.GetBdt();
    HiggsBranch->Pull1 = Pair.GetPullAngle1();
    HiggsBranch->Pull2 = Pair.GetPullAngle2();
    HiggsBranch->Pull = Pair.GetPullAngle();
    HiggsBranch->HiggsTag = Pair.GetTag();

}

std::vector<HParticleBranch *> hanalysis::HMvaHiggsTagger::GetConstituentBranches()
{

    Print(HInformation, "Get Higgs Tags");

    std::vector<HSuperStructure> JetPairs;

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

void hanalysis::HMvaHiggsTagger::FillBranch(const HKinematics &Vector)
{
    Print(HInformation, "FillPairTagger", Vector.GetPt());

    FillBranch(Vector);

}

void hanalysis::HMvaHiggsTagger::FillBranch(HParticleBranch *const ConstituentBranch, const HKinematics &Vector)
{
    Print(HInformation, "Fill Constituent Branch");

    ConstituentBranch->Pt = Vector.GetPt();
    ConstituentBranch->Rap = Vector.GetRap();
    ConstituentBranch->Phi = Vector.GetPhi();

}
