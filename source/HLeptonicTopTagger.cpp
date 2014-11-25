# include "HLeptonicTopTagger.hh"

hdelphes::HLeptonicTopTagger::HLeptonicTopTagger()
{
//     DebugLevel = hanalysis::HObject::HDebug;

    Print(HNotification, "Constructor");
    AnalysisName = "HiggsCpv";
    TaggerName = "Top";
    SignalNames = {"Top"};
    BackgroundNames = {"NotTop"};
    TestName = "Test";
    TestTreeNames = {"pp-bbtt-bblvlv-background", "pp-x0tt-bblvlv-even"};
    SignalTreeNames = TestTreeNames;
    BackgroundTreeNames = TestTreeNames;
    CandidateBranchName = "Top";
    LeptonicTopTagger = new HLeptonicTopBranch();
    JetTag = new hanalysis::HJetTag();

    DefineVariables();
}

hdelphes::HLeptonicTopTagger::~HLeptonicTopTagger()
{
    Print(HNotification, "Destructor");
    delete LeptonicTopTagger;
}


std::vector<HLeptonicTopBranch *> hdelphes::HLeptonicTopTagger::GetTopTag(hanalysis::HEvent *const Event, const hanalysis::HObject::HState State, HBottomTagger *BottomTagger)
{

    Print(HInformation, "Get Top Tags");

    JetTag->SetHeavyParticles( {TopId});
    HJets Jets = Event->GetJets()->GetStructuredTaggedJets(JetTag);
    Print(HInformation, "Jet Number", Jets.size());
//     if (Jets.size() < 1) return 0;

    if (State == HSignal) {
        for (HJets::iterator Jet = Jets.begin(); Jet != Jets.end();) {
            Print(HInformation, "Truth Level", GetParticleName((*Jet).user_info<hanalysis::HJetInfo>().GetMaximalId()));
            if (std::abs((*Jet).user_info<hanalysis::HJetInfo>().GetMaximalId()) != TopId
               ) {
                Jet = Jets.erase(Jet);
            } else {
                ++Jet;
            }
        }
    } else if (State == HBackground) {
        for (HJets::iterator Jet = Jets.begin(); Jet != Jets.end();) {
            if (std::abs((*Jet).user_info<hanalysis::HJetInfo>().GetMaximalId()) == TopId) {
                Jet = Jets.erase(Jet);
            } else {
                ++Jet;
            }
        }
    }


    HJets Leptons = Event->GetLeptons()->GetTaggedJets(JetTag);
    Print(HInformation, "Lepton Number", Leptons.size());
//     if (Leptons.size() < 1) return 0;

    std::vector<hdelphes::HSuperStructure> JetPairs;

    for (HJets::iterator Jet = Jets.begin(); Jet != Jets.end(); ++Jet) {
        const float Bdt = BottomTagger->GetBottomBdt((*Jet));
        hanalysis::HJetInfo *JetInfo = new hanalysis::HJetInfo;
        JetInfo->SetBTag(Bdt);
        (*Jet).set_user_info(JetInfo);
        for (HJets::iterator Lepton = Leptons.begin(); Lepton != Leptons.end(); ++Lepton) {
            Print(HDebug, "Lepton Tagging", GetParticleName((*Lepton).user_index()), GetParticleName((*Jet).user_index()));
            if ((State == HSignal && (*Lepton).user_index() == (*Jet).user_index()) || (State == HBackground)) {

                hdelphes::HSuperStructure JetPair((*Jet), (*Lepton));
                JetPair.SetBTag((*Jet).user_info<hanalysis::HJetInfo>().GetBTag());
                if (std::abs((*Jet).user_index()) == TopId) JetPair.Tag = 1;
                JetPairs.push_back(JetPair);
            }
        }
    }

    Print(HInformation, "Number JetPairs", JetPairs.size());
//     if (JetPairs.size() < 1) return 0;

    std::vector<HLeptonicTopBranch *> LeptonicTopBranches;
    for (const auto & JetPair : JetPairs) {
//         HLeptonicTopBranch *TopTagger = static_cast<HLeptonicTopBranch *>(TopBranch->NewEntry());
        HLeptonicTopBranch *LeptonicTopBranch = new HLeptonicTopBranch();
        FillTopBranch(JetPair, LeptonicTopBranch);
        LeptonicTopBranches.push_back(LeptonicTopBranch);
    }


    return LeptonicTopBranches;

}

void hdelphes::HLeptonicTopTagger::FillTopBranch(const hdelphes::HSuperStructure &Pair, HLeptonicTopBranch *TopTagger)
{
    Print(HInformation, "Fill Top Tagger", Pair.GetBTag());

    TopTagger->Mass = Pair.GetInvariantMass();
    TopTagger->Pt = Pair.GetPtSum();
    TopTagger->DeltaR = Pair.GetDeltaR();
    TopTagger->DeltaEta = Pair.GetDeltaEta();
    TopTagger->DeltaPhi = Pair.GetPhiDelta();
    TopTagger->BottomTag = Pair.GetBTag();
    if (Pair.Tag == 1) {
        TopTagger->TopTag = 1;
    } else {
        TopTagger->TopTag = 0;
    }

}

// float hdelphes::HLeptonicTopTagger::GetDeltaR(const fastjet::PseudoJet &Jet)
// {
//
//     Print(HInformation, "Get Delta R");
//
//     float DeltaR;
//     for (const auto & Constituent : Jet.constituents()) {
//         const float TempDeltaR = Jet.delta_R(Constituent);
//         if (TempDeltaR > DeltaR) DeltaR = TempDeltaR;
//     }
//     return DeltaR;
//
// }

float hdelphes::HLeptonicTopTagger::GetTopBdt(const hdelphes::HSuperStructure &Top)
{

    HLeptonicTopBranch *TopTagger = new HLeptonicTopBranch();
    FillTopBranch(Top, TopTagger);
    const float Bdt = GetBdt(TopTagger, Reader->Reader);
    delete TopTagger;

    return Bdt;

}

void hdelphes::HLeptonicTopTagger::DefineVariables()
{

    Print(HNotification , "Define Variables");

    Observables.push_back(NewObservable(&LeptonicTopTagger->Mass, "Mass"));
    Observables.push_back(NewObservable(&LeptonicTopTagger->Pt, "Pt"));
    Observables.push_back(NewObservable(&LeptonicTopTagger->DeltaPhi, "DeltaPhi"));
    Observables.push_back(NewObservable(&LeptonicTopTagger->DeltaEta, "DeltaEta"));
    Observables.push_back(NewObservable(&LeptonicTopTagger->DeltaR, "DeltaR"));
    Observables.push_back(NewObservable(&LeptonicTopTagger->BottomTag, "BottomTag"));

    Spectators.push_back(NewObservable(&LeptonicTopTagger->TopTag, "TopTag"));

    Print(HNotification, "Variables defined");

}

float hdelphes::HLeptonicTopTagger::GetBdt(TObject *Branch, TMVA::Reader *Reader)
{

    Print(HInformation, "Get Bdt", BdtMethodName);

    *LeptonicTopTagger = *static_cast<HLeptonicTopBranch *>(Branch);
    const float BdtEvaluation = Reader->EvaluateMVA(BdtMethodName);
    Print(HInformation, "BTagger Bdt", BdtEvaluation);

    return ((BdtEvaluation + 1) / 2);

}
