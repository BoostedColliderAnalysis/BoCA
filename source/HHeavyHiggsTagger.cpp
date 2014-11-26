# include "HHeavyHiggsTagger.hh"

hdelphes::HHeavyHiggsTagger::HHeavyHiggsTagger()
{
//     DebugLevel = hanalysis::HObject::HDebug;

    Print(HNotification, "Constructor");
    AnalysisName = "HiggsCpv";
    TaggerName = "HeavyHiggs";
    SignalNames = {"HeavyHiggs"};
    BackgroundNames = {"NotHeavyHiggs"};
    TestName = "Test";
    TestTreeNames = {"pp-bbtt-bblvlv-background", "pp-x0tt-bblvlv-even"};
    SignalTreeNames = TestTreeNames;
    BackgroundTreeNames = TestTreeNames;
    CandidateBranchName = "HeavyHiggs";
    HeavyHiggs = new HMvaHeavyHiggsBranch();
    JetTag = new hanalysis::HJetTag();

    DefineVariables();
}

hdelphes::HHeavyHiggsTagger::~HHeavyHiggsTagger()
{
    Print(HNotification, "Destructor");
    delete HeavyHiggs;
}


std::vector< HMvaHeavyHiggsBranch * > hdelphes::HHeavyHiggsTagger::GetHeavyHiggsTag(hanalysis::HEvent *const Event, const hanalysis::HObject::HState State, hdelphes::HBottomTagger *BottomTagger, hdelphes::HLeptonicTopTagger *TopTagger)
{

    Print(HInformation, "Get Higgs Tags");

    JetTag->SetHeavyParticles( {HeavyHiggsId});
    HJets Jets = Event->GetJets()->GetStructuredTaggedJets(JetTag);

    HJets HeavyHiggsJets;
    HJets OtherJets;
    for (auto & Jet : Jets) {

        Print(HInformation, "Dominant Fraction", GetParticleName(Jet.user_info<hanalysis::HJetInfo>().GetMaximalId()));

        hanalysis::HJetInfo *JetInfo = new hanalysis::HJetInfo;
        if (Jet.user_info<hanalysis::HJetInfo>().GetMaximalId() == HeavyHiggsId) {
            JetInfo->SetHiggsTag(1);
        } else {
            JetInfo->SetHiggsTag(0);
        }

        const float Bdt = BottomTagger->GetBottomBdt(Jet);
        JetInfo->SetBTag(Bdt);
        Jet.set_user_info(JetInfo);
        Print(HInformation, "Top Bdt", Bdt);

        if (JetInfo->GetHiggsTag()) {
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




    std::vector<hdelphes::HSuperStructure> JetPairs;
    if (State == hanalysis::HObject::HSignal) {
        Print(HInformation, "Higgs Jets", HeavyHiggsJets.size());
        for ( auto & Jet : HeavyHiggsJets) {
            for (const auto & Lepton : HeavyHiggsLeptons) {
                hdelphes::HSuperStructure JetPair((Jet), (Lepton));
                JetPair.SetBTag((Jet).user_info<hanalysis::HJetInfo>().GetBTag());
                JetPair.Tag = 1;
                JetPairs.push_back(JetPair);
            }
        }
    } else if (State == hanalysis::HObject::HBackground) {
        for (const auto & Jet : OtherJets) {
            for (const auto & Lepton : HeavyHiggsLeptons) {
                hdelphes::HSuperStructure JetPair((Jet), (Lepton));
                JetPair.SetBTag((Jet).user_info<hanalysis::HJetInfo>().GetBTag());
                JetPair.Tag = 0;
                JetPairs.push_back(JetPair);
            }
        }
        for (const auto & Jet : HeavyHiggsJets) {
            for (const auto & Lepton : OtherLeptons) {
                hdelphes::HSuperStructure JetPair((Jet), (Lepton));
                JetPair.SetBTag((Jet).user_info<hanalysis::HJetInfo>().GetBTag());
                JetPair.Tag = 0;
                JetPairs.push_back(JetPair);
            }
        }
        for (const auto & Jet : OtherJets) {
            for (const auto & Lepton : OtherLeptons) {
                hdelphes::HSuperStructure JetPair((Jet), (Lepton));
                JetPair.SetBTag((Jet).user_info<hanalysis::HJetInfo>().GetBTag());
                JetPair.Tag = 0;
                JetPairs.push_back(JetPair);
            }
        }
    }


    for (auto & JetPair : JetPairs) {
        const float Bdt = TopTagger->GetTopBdt(JetPair);
        JetPair.SetHeavyParticleTag(Bdt);
    }

    std::vector<HHeavyHiggs> HeavyHiggses;
    for (const auto & Pair1 : JetPairs) {
        for (const auto & Pair2 : JetPairs) {
            HHeavyHiggs HeavyHiggsTagger((Pair1), (Pair2));
            HeavyHiggses.push_back(HeavyHiggsTagger);
        }
    }


    Print(HInformation, "Number of Heavy Higgses", HeavyHiggses.size());

    std::vector<HMvaHeavyHiggsBranch *> HeavyHiggsBranches;
    for (const auto & HeavyHiggsTagger : HeavyHiggses) {
        HMvaHeavyHiggsBranch *HeavyHiggsBranch = new HMvaHeavyHiggsBranch();
        FillHeavyHiggsBranch(HeavyHiggsTagger, HeavyHiggsBranch);
        HeavyHiggsBranches.push_back(HeavyHiggsBranch);
    }


    return HeavyHiggsBranches;

}

void hdelphes::HHeavyHiggsTagger::FillHeavyHiggsBranch(const HHeavyHiggs &HeavyHiggsTagger, HMvaHeavyHiggsBranch *HeavyHiggsRoot)
{
    Print(HInformation, "FillPairTagger", HeavyHiggsTagger.GetTopTag());

    HeavyHiggsRoot->Mass = HeavyHiggsTagger.GetInvariantMass();
    HeavyHiggsRoot->Pt = HeavyHiggsTagger.GetPtSum();
    HeavyHiggsRoot->DeltaR = HeavyHiggsTagger.GetDeltaR();
    HeavyHiggsRoot->DeltaEta = HeavyHiggsTagger.GetDeltaEta();
    HeavyHiggsRoot->DeltaPhi = HeavyHiggsTagger.GetDeltaPhi();
    HeavyHiggsRoot->TopTag = HeavyHiggsTagger.GetTopTag();
    if (HeavyHiggsTagger.Tag == 1) {
        HeavyHiggsRoot->HeavyHiggsTag = 1;
    } else {
        HeavyHiggsRoot->HeavyHiggsTag = 0;
    }


}

float hdelphes::HHeavyHiggsTagger::GetHeavyHiggsBdt(const HHeavyHiggs &HeavyHiggsTagger)
{

    HMvaHeavyHiggsBranch *HeavyHiggsBranch = new HMvaHeavyHiggsBranch();
    FillHeavyHiggsBranch(HeavyHiggsTagger,HeavyHiggsBranch);
    const float Bdt = GetBdt(HeavyHiggsBranch, Reader->Reader);
    delete HeavyHiggsBranch;
    return Bdt;
}

void hdelphes::HHeavyHiggsTagger::DefineVariables()
{

    Print(HNotification , "Define Variables");

    Observables.push_back(NewObservable(&HeavyHiggs->Mass, "Mass"));
    Observables.push_back(NewObservable(&HeavyHiggs->Pt, "Pt"));
    Observables.push_back(NewObservable(&HeavyHiggs->DeltaPhi, "DeltaPhi"));
    Observables.push_back(NewObservable(&HeavyHiggs->DeltaEta, "DeltaEta"));
    Observables.push_back(NewObservable(&HeavyHiggs->DeltaR, "DeltaR"));
//     Observables.push_back(NewObservable(&HeavyHiggs->Pull1, "Pull1"));
//     Observables.push_back(NewObservable(&HeavyHiggs->Pull2, "Pull2"));
//     Observables.push_back(NewObservable(&HeavyHiggs->Pull, "Pull"));
    Observables.push_back(NewObservable(&HeavyHiggs->TopTag, "TopTag"));

    Spectators.push_back(NewObservable(&HeavyHiggs->HeavyHiggsTag, "HeavyHiggsTag"));

    Print(HNotification, "Variables defined");

}

float hdelphes::HHeavyHiggsTagger::GetBdt(TObject *Branch, TMVA::Reader *Reader2)
{

    Print(HInformation, "Get Bdt", BdtMethodName);

    *HeavyHiggs = *static_cast<HMvaHeavyHiggsBranch *>(Branch);
    const float BdtEvaluation = Reader2->EvaluateMVA(BdtMethodName);
    Print(HInformation, "BTagger Bdt", BdtEvaluation);

    return ((BdtEvaluation + 1) / 2);

}
