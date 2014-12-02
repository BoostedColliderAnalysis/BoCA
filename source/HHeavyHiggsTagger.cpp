# include "HHeavyHiggsTagger.hh"

hdelphes::HHeavyHiggsTagger::HHeavyHiggsTagger(hdelphes::HBottomTagger *NewBottomTagger, hdelphes::HLeptonicTopTagger *NewTopTagger)
{
//     DebugLevel = hanalysis::HObject::HDebug;

    Print(HNotification, "Constructor");

    BottomTagger = NewBottomTagger;
    TopTagger = NewTopTagger;

    TaggerName = "HeavyHiggs";
    SignalNames = {"HeavyHiggs"};
    BackgroundNames = {"NotHeavyHiggs"};
    CandidateBranchName = "HeavyHiggs";

    Branch = new HMvaHeavyHiggsBranch();
    JetTag = new hanalysis::HJetTag();

    DefineVariables();
}

hdelphes::HHeavyHiggsTagger::~HHeavyHiggsTagger()
{
    Print(HNotification, "Destructor");
    delete Branch;
    delete JetTag;
    delete BottomTagger;
    delete TopTagger;

}


std::vector< HMvaHeavyHiggsBranch * > hdelphes::HHeavyHiggsTagger::GetBranches(hanalysis::HEvent *const Event, const hanalysis::HObject::HState State)
{

    Print(HInformation, "Get Higgs Tags");

    JetTag->HeavyParticles= {HeavyHiggsId};
    HJets Jets = Event->GetJets()->GetStructuredTaggedJets(JetTag);

    HJets HeavyHiggsJets;
    HJets OtherJets;
    for (auto & Jet : Jets) {

        Print(HInformation, "Dominant Fraction", GetParticleName(Jet.user_info<hanalysis::HJetInfo>().GetMaximalId()));

        hanalysis::HJetInfo *JetInfo = new hanalysis::HJetInfo;
        if (Jet.user_info<hanalysis::HJetInfo>().GetMaximalId() == HeavyHiggsId) {
            JetInfo->SetTag(1);
        } else {
            JetInfo->SetTag(0);
        }

//         const float Bdt = BottomTagger->GetBdt(Jet,Reader->Reader);
        BottomTagger->FillBranch(Jet);
        const float Bdt = BottomReader->GetBdt();
        JetInfo->SetBdt(Bdt);
        Jet.set_user_info(JetInfo);
        Print(HInformation, "Top Bdt", Bdt);

        if (JetInfo->GetTag()) {
            HeavyHiggsJets.push_back(Jet);
        } else {
            OtherJets.push_back(Jet);
        }
    }

//     Print(HInformation, "Higgsness", Jets[0].user_info<hanalysis::HJetInfo>().GetFraction(CpvHiggsId), Jets[1].user_info<hanalysis::HJetInfo>().GetFraction(CpvHiggsId));


    HJets Leptons = Event->GetLeptons()->GetTaggedJets(JetTag);
    HJets HeavyHiggsLeptons;
    HJets OtherLeptons;
    for (auto & Lepton : Leptons) {

//     hanalysis::HJetInfo *JetInfo = new hanalysis::HJetInfo;
        if (Lepton.user_info<hanalysis::HJetInfo>().GetMaximalId() == HeavyHiggsId) {
            HeavyHiggsLeptons.push_back(Lepton);
        } else {
            OtherLeptons.push_back(Lepton);
        }

    }




    std::vector<hanalysis::HJetLeptonPair> JetPairs;
    if (State == hanalysis::HObject::HSignal) {
        Print(HInformation, "Higgs Jets", HeavyHiggsJets.size());
        for (auto & Jet : HeavyHiggsJets) {
            for (const auto & Lepton : HeavyHiggsLeptons) {
                hanalysis::HJetLeptonPair JetPair(Jet, Lepton);
                JetPair.SetBdt(Jet.user_info<hanalysis::HJetInfo>().GetBdt());
                JetPair.SetTag(1);
                JetPairs.push_back(JetPair);
            }
        }
    } else if (State == hanalysis::HObject::HBackground) {
        for (const auto & Jet : OtherJets) {
            for (const auto & Lepton : HeavyHiggsLeptons) {
                hanalysis::HJetLeptonPair JetPair(Jet, Lepton);
                JetPair.SetBdt(Jet.user_info<hanalysis::HJetInfo>().GetBdt());
                JetPair.SetTag(0);
                JetPairs.push_back(JetPair);
            }
        }
        for (const auto & Jet : HeavyHiggsJets) {
            for (const auto & Lepton : OtherLeptons) {
                hanalysis::HJetLeptonPair JetPair(Jet, Lepton);
                JetPair.SetBdt(Jet.user_info<hanalysis::HJetInfo>().GetBdt());
                JetPair.SetTag(0);
                JetPairs.push_back(JetPair);
            }
        }
        for (const auto & Jet : OtherJets) {
            for (const auto & Lepton : OtherLeptons) {
                hanalysis::HJetLeptonPair JetPair(Jet, Lepton);
                JetPair.SetBdt(Jet.user_info<hanalysis::HJetInfo>().GetBdt());
                JetPair.SetTag(0);
                JetPairs.push_back(JetPair);
            }
        }
    }

    for (auto & JetPair : JetPairs) {
        TopTagger->FillBranch(JetPair);
        JetPair.SetBdt(TopReader->GetBdt());
    }

    std::vector<hanalysis::HPairPair> HeavyHiggses;
    for (const auto & Pair1 : JetPairs) {
        for (const auto & Pair2 : JetPairs) {
            hanalysis::HPairPair HeavyHiggsTagger(Pair1, Pair2);
            HeavyHiggses.push_back(HeavyHiggsTagger);
        }
    }


    Print(HInformation, "Number of Heavy Higgses", HeavyHiggses.size());

    std::vector<HMvaHeavyHiggsBranch *> HeavyHiggsBranches;
    for (const auto & HeavyHiggsTagger : HeavyHiggses) {
        HMvaHeavyHiggsBranch *HeavyHiggsBranch = new HMvaHeavyHiggsBranch();
        FillBranch(HeavyHiggsBranch,HeavyHiggsTagger);
        HeavyHiggsBranches.push_back(HeavyHiggsBranch);
    }


    return HeavyHiggsBranches;

}

void hdelphes::HHeavyHiggsTagger::FillBranch(const hanalysis::HPairPair &PairPair)
{
    Print(HInformation, "FillPairTagger", PairPair.GetBdt());

    FillBranch(Branch, PairPair);

}

void hdelphes::HHeavyHiggsTagger::FillBranch(HMvaHeavyHiggsBranch *HeavyHiggsBranch, const hanalysis::HPairPair &PairPair)
{
    Print(HInformation, "FillPairTagger", PairPair.GetBdt());

    HeavyHiggsBranch->Mass = PairPair.GetInvariantMass();
    HeavyHiggsBranch->Pt = PairPair.GetPtSum();
    HeavyHiggsBranch->DeltaR = PairPair.GetDeltaR();
    HeavyHiggsBranch->DeltaRap = PairPair.GetDeltaRap();
    HeavyHiggsBranch->DeltaPhi = PairPair.GetDeltaPhi();
    HeavyHiggsBranch->TopBdt = PairPair.GetBdt();
    if (PairPair.GetTag() == 1) {
        HeavyHiggsBranch->HeavyHiggsTag = 1;
    } else {
        HeavyHiggsBranch->HeavyHiggsTag = 0;
    }


}

void hdelphes::HHeavyHiggsTagger::DefineVariables()
{

    Print(HNotification , "Define Variables");

    Observables.push_back(NewObservable(&Branch->Mass, "Mass"));
    Observables.push_back(NewObservable(&Branch->Pt, "Pt"));
    Observables.push_back(NewObservable(&Branch->DeltaPhi, "DeltaPhi"));
    Observables.push_back(NewObservable(&Branch->DeltaRap, "DeltaRap"));
    Observables.push_back(NewObservable(&Branch->DeltaR, "DeltaR"));
//     Observables.push_back(NewObservable(&HeavyHiggs->Pull1, "Pull1"));
//     Observables.push_back(NewObservable(&HeavyHiggs->Pull2, "Pull2"));
//     Observables.push_back(NewObservable(&HeavyHiggs->Pull, "Pull"));
    Observables.push_back(NewObservable(&Branch->TopBdt, "TopTag"));

    Spectators.push_back(NewObservable(&Branch->HeavyHiggsTag, "HeavyHiggsTag"));

    Print(HNotification, "Variables defined");

}

