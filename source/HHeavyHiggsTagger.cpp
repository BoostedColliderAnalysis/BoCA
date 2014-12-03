# include "HHeavyHiggsTagger.hh"

hanalysis::HHeavyHiggsTagger::HHeavyHiggsTagger(HBottomTagger *const NewBottomTagger, HLeptonicTopTagger *const NewTopTagger)
{
//     DebugLevel = hanalysis::HObject::HDebug;

    Print(HNotification, "Constructor");

    BottomTagger = NewBottomTagger;
    BottomReader = new HReader(BottomTagger);
    TopTagger = NewTopTagger;
    TopReader = new HReader(TopTagger);

    TaggerName = "HeavyHiggs";
    SignalNames = {"HeavyHiggs"};
    BackgroundNames = {"NotHeavyHiggs"};
    CandidateBranchName = "HeavyHiggs";

    Branch = new HHeavyHiggsBranch();
    JetTag = new HJetTag();

    DefineVariables();
}

hanalysis::HHeavyHiggsTagger::~HHeavyHiggsTagger()
{
    Print(HNotification, "Destructor");
    delete Branch;
    delete JetTag;
    delete BottomReader;
    delete TopReader;

}

void hanalysis::HHeavyHiggsTagger::FillBranch(HHeavyHiggsBranch *HeavyHiggsBranch, const HPairPair &PairPair)
{
    Print(HInformation, "FillPairTagger", PairPair.GetBdt());

    HeavyHiggsBranch->Mass = PairPair.GetInvariantMass();
    HeavyHiggsBranch->Pt = PairPair.GetPtSum();
    HeavyHiggsBranch->DeltaR = PairPair.GetDeltaR();
    HeavyHiggsBranch->DeltaRap = PairPair.GetDeltaRap();
    HeavyHiggsBranch->DeltaPhi = PairPair.GetDeltaPhi();
    HeavyHiggsBranch->TopBdt = PairPair.GetBdt();
    HeavyHiggsBranch->HeavyHiggsTag = PairPair.GetTag();
}

void hanalysis::HHeavyHiggsTagger::DefineVariables()
{

    Print(HNotification , "Define Variables");

    Observables.push_back(NewObservable(&Branch->Mass, "Mass"));
    Observables.push_back(NewObservable(&Branch->Pt, "Pt"));
    Observables.push_back(NewObservable(&Branch->DeltaPhi, "DeltaPhi"));
    Observables.push_back(NewObservable(&Branch->DeltaRap, "DeltaRap"));
    Observables.push_back(NewObservable(&Branch->DeltaR, "DeltaR"));
    Observables.push_back(NewObservable(&Branch->TopBdt, "TopBdt"));

    Spectators.push_back(NewObservable(&Branch->HeavyHiggsTag, "HeavyHiggsTag"));

    Print(HNotification, "Variables defined");

}

struct SortPairByMass {
    inline bool operator()(const hanalysis::HPairPair &Pair1, const hanalysis::HPairPair &Pair2) {
        return (Pair1.GetMassDifference(400) > Pair2.GetMassDifference(400));
    }
};



std::vector< HHeavyHiggsBranch * > hanalysis::HHeavyHiggsTagger::GetBranches(HEvent *const Event, const HObject::HState State)
{

    Print(HInformation, "Get Higgs Tags");

    JetTag->HeavyParticles = {HeavyHiggsId};
    HJets Jets = Event->GetJets()->GetStructuredTaggedJets(JetTag);

    HJets HeavyHiggsJets;
    HJets OtherJets;
    for (HJets::iterator Jet = Jets.begin(); Jet != Jets.end();) {
        Print(HInformation, "Jet Id", GetParticleName((*Jet).user_info<HJetInfo>().GetMaximalId()));

        if (std::abs((*Jet).user_index()) == MixedJetId) {
            Jet = Jets.erase(Jet);
        } else {
            const int JetId = (*Jet).user_info<HJetInfo>().GetMaximalId();
            HJetInfo *JetInfo = new HJetInfo;
            BottomTagger->FillBranch(*Jet);
            JetInfo->SetBdt(BottomReader->GetBdt());
            (*Jet).set_user_info(JetInfo);
            if (JetId == HeavyHiggsId) {
                HeavyHiggsJets.push_back(*Jet);
            } else {
                OtherJets.push_back(*Jet);
            }
            ++Jet;
        }
    }
    Print(HInformation, "Number of Higgs Jets", HeavyHiggsJets.size());

    HJets Leptons = Event->GetLeptons()->GetTaggedJets(JetTag);
    HJets HeavyHiggsLeptons;
    HJets OtherLeptons;
    for (auto & Lepton : Leptons) {

        if (std::abs(Lepton.user_index()) == HeavyHiggsId) {
            HeavyHiggsLeptons.push_back(Lepton);
        } else {
            OtherLeptons.push_back(Lepton);
        }

    }

    std::vector<HJetLeptonPair> JetLeptonPairs;
    if (State == HObject::HSignal) {
        Print(HInformation, "Higgs Jets", HeavyHiggsJets.size());
        for (auto & Jet : HeavyHiggsJets) {
            for (const auto & Lepton : HeavyHiggsLeptons) {
                HJetLeptonPair JetPair(Jet, Lepton);
                JetPair.SetTag(1);
                JetLeptonPairs.push_back(JetPair);
            }
        }
    } else if (State == HObject::HBackground) {
        for (const auto & Jet : OtherJets) {
            for (const auto & Lepton : HeavyHiggsLeptons) {
                HJetLeptonPair JetPair(Jet, Lepton);
                JetPair.SetTag(0);
                JetLeptonPairs.push_back(JetPair);
            }
        }
        for (const auto & Jet : HeavyHiggsJets) {
            for (const auto & Lepton : OtherLeptons) {
                HJetLeptonPair JetPair(Jet, Lepton);
                JetPair.SetTag(0);
                JetLeptonPairs.push_back(JetPair);
            }
        }
        for (const auto & Jet : OtherJets) {
            for (const auto & Lepton : OtherLeptons) {
                HJetLeptonPair JetPair(Jet, Lepton);
                JetPair.SetTag(0);
                JetLeptonPairs.push_back(JetPair);
            }
        }
    }

    for (auto & JetPair : JetLeptonPairs) {
        TopTagger->FillBranch(JetPair);
        JetPair.SetBdt(TopReader->GetBdt());
    }

    std::vector<HPairPair> PairPairs;

    for (auto Pair1 = JetLeptonPairs.begin(); Pair1 != JetLeptonPairs.end(); ++Pair1) {
        for (auto Pair2 = Pair1 + 1; Pair2 != JetLeptonPairs.end(); ++Pair2) {
            HPairPair PairPair((*Pair1), (*Pair2));
            PairPairs.push_back(PairPair);
        }
    }

    Print(HInformation, "Number of Heavy Higgses", PairPairs.size());

    std::vector<HHeavyHiggsBranch *> HeavyHiggsBranches;
    for (const auto & PairPair : PairPairs) {
        HHeavyHiggsBranch *HeavyHiggsBranch = new HHeavyHiggsBranch();
        FillBranch(HeavyHiggsBranch, PairPair);
        HeavyHiggsBranches.push_back(HeavyHiggsBranch);
    }


    return HeavyHiggsBranches;

}

void hanalysis::HHeavyHiggsTagger::FillBranch(const hanalysis::HPairPair &PairPair)
{
    Print(HInformation, "FillPairTagger", PairPair.GetBdt());

    FillBranch(Branch, PairPair);

}

