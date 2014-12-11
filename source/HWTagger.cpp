# include "HWTagger.hh"

hanalysis::HWTagger::HWTagger(HBottomTagger *NewBottomTagger)
{
//     DebugLevel = hanalysis::HObject::HDebug;

    Print(HNotification, "Constructor");

    BottomTagger = NewBottomTagger;
    BottomReader = new HReader(BottomTagger);

    TaggerName = "W";
    SignalNames = {"W"};
    BackgroundNames = {"NotW"};
    CandidateBranchName = "W";

    Branch = new HHadronicWBranch();
    JetTag = new HJetTag();

    DefineVariables();
}

hanalysis::HWTagger::~HWTagger()
{
    Print(HNotification, "Destructor");
    delete Branch;
    delete BottomReader;
    delete JetTag;
}

void hanalysis::HWTagger::FillBranch(const HDoublet &Pair)
{
    Print(HInformation, "FillPairTagger", Pair.GetBdt());

    FillBranch(Branch, Pair);

}

void hanalysis::HWTagger::FillBranch(HHadronicWBranch *const WBranch, const HDoublet &Pair)
{
    Print(HInformation, "FillPairTagger", Pair.GetBdt());

    WBranch->Mass = Pair.GetDoubletJet().m();
    WBranch->PtSum = Pair.GetDoubletJet().pt();
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

void hanalysis::HWTagger::DefineVariables()
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
    inline bool operator()(const hanalysis::HDoublet &Pair1, const hanalysis::HDoublet &Pair2) {
        return (Pair1.GetMassDifference(hanalysis::HObject::WId) > Pair2.GetMassDifference(hanalysis::HObject::WId));
    }
};


std::vector<HHadronicWBranch *> hanalysis::HWTagger::GetBranches(hanalysis::HEvent *const Event, const hanalysis::HObject::HState State)
{

    Print(HInformation, "Get W Tags");

    JetTag->HeavyParticles = {WId, TopId};
    HJets Jets = Event->GetJets()->GetStructuredTaggedJets(JetTag);

    HJets WJets;
    HJets OtherJets;
    for (auto & Jet : Jets) {
        Print(HInformation, "Dominant Fraction", GetParticleName(Jet.user_index()));
        if (Jet.user_index() == MixedJetId) continue;
        hanalysis::HJetInfo *JetInfo = new hanalysis::HJetInfo;
        if (std::abs(Jet.user_index()) == WId) JetInfo->SetTag(1);
        else JetInfo->SetTag(0);

        BottomTagger->FillBranch(Jet);
        JetInfo->SetBdt(BottomReader->GetBdt());
        Jet.set_user_info(JetInfo);

        if (JetInfo->GetTag() == 1) {
            WJets.push_back(Jet);
        } else {
            OtherJets.push_back(Jet);
        }
    }


    std::vector<HDoublet> JetPairs;

    if (State == HSignal) {
        Print(HInformation, "W Jets", WJets.size());
        for (auto Jet1 = WJets.begin(); Jet1 != WJets.end(); ++Jet1) {
            for (auto Jet2 = Jet1 + 1; Jet2 != WJets.end(); ++Jet2) {
                if ((*Jet1).user_index() != (*Jet2).user_index()) continue;
                if (std::abs((*Jet1).user_index()) != WId) continue;
                HDoublet JetPair((*Jet1), (*Jet2));
                JetPairs.push_back(JetPair);
            }
        }
    }

    if (State == HBackground) {
        for (auto Jet1 = OtherJets.begin(); Jet1 != OtherJets.end(); ++Jet1) {
            for (auto Jet2 = Jet1 + 1; Jet2 != OtherJets.end(); ++Jet2) {
                if ((*Jet1).user_index() == (*Jet2).user_index() && std::abs((*Jet1).user_index()) == WId) continue;
                HDoublet JetPair((*Jet1), (*Jet2));
                JetPairs.push_back(JetPair);
            }
        }
        for (auto Jet1 = OtherJets.begin(); Jet1 != OtherJets.end(); ++Jet1) {
            for (auto Jet2 = WJets.begin(); Jet2 != WJets.end(); ++Jet2) {
                if ((*Jet1).user_index() == (*Jet2).user_index() && std::abs((*Jet1).user_index()) == WId) continue;
                HDoublet JetPair((*Jet1), (*Jet2));
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







std::vector<HParticleBranch *> hanalysis::HWTagger::GetConstituentBranches()
{

    Print(HInformation, "Get Higgs Tags");

    std::vector<HDoublet> JetPairs;

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

void hanalysis::HWTagger::FillBranch(const HKinematics &Vector)
{
    Print(HInformation, "FillPairTagger", Vector.GetPt());

    FillBranch(Vector);

}

void hanalysis::HWTagger::FillBranch(HParticleBranch *const ConstituentBranch, const HKinematics &Vector)
{
    Print(HInformation, "Fill Constituent Branch");

    ConstituentBranch->Pt = Vector.GetPt();
    ConstituentBranch->Rap = Vector.GetRap();
    ConstituentBranch->Phi = Vector.GetPhi();

}
