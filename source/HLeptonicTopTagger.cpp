# include "HLeptonicTopTagger.hh"

hdelphes::HLeptonicTopTagger::HLeptonicTopTagger(hdelphes::HBottomTagger *NewBottomTagger)
{
//     DebugLevel = hanalysis::HObject::HDebug;

    Print(HNotification, "Constructor");

    BottomTagger = NewBottomTagger;
    BottomReader = new hmva::HReader(BottomTagger);

    TaggerName = "Top";
    SignalNames = {"Top"};
    BackgroundNames = {"NotTop"};
    CandidateBranchName = "Top";

    Branch = new HLeptonicTopBranch();
    JetTag = new hanalysis::HJetTag();

    DefineVariables();

}

hdelphes::HLeptonicTopTagger::~HLeptonicTopTagger()
{
    Print(HNotification, "Destructor");
    delete Branch;
    delete JetTag;
    delete BottomReader;
}

void hdelphes::HLeptonicTopTagger::DefineVariables()
{

    Print(HNotification , "Define Variables");

    Observables.push_back(NewObservable(&Branch->Mass, "Mass"));
    Observables.push_back(NewObservable(&Branch->JetPt, "JetPt"));
    Observables.push_back(NewObservable(&Branch->LeptonPt, "LeptonPt"));
    Observables.push_back(NewObservable(&Branch->DeltaPhi, "DeltaPhi"));
    Observables.push_back(NewObservable(&Branch->DeltaRap, "DeltaRap"));
    Observables.push_back(NewObservable(&Branch->DeltaR, "DeltaR"));
    Observables.push_back(NewObservable(&Branch->BottomBdt, "BottomBdt"));

    Spectators.push_back(NewObservable(&Branch->TopTag, "TopTag"));

    Print(HNotification, "Variables defined");

}


std::vector<HLeptonicTopBranch *> hdelphes::HLeptonicTopTagger::GetBranches(hanalysis::HEvent *const Event, const hanalysis::HObject::HState State)
{

    Print(HInformation, "Get Top Tags");

    JetTag->HeavyParticles = {TopId, HiggsId, CpvHiggsId, HeavyHiggsId};
    HJets Jets = Event->GetJets()->GetStructuredTaggedJets(JetTag);
    Print(HInformation, "Jet Number", Jets.size());


//     if (State == HSignal) {
//         for (HJets::iterator Jet = Jets.begin(); Jet != Jets.end();) {
//             Print(HInformation, "Truth Level", GetParticleName((*Jet).user_info<hanalysis::HJetInfo>().GetMaximalId()));
//             if (std::abs((*Jet).user_info<hanalysis::HJetInfo>().GetMaximalId()) != TopId) {
//                 Jet = Jets.erase(Jet);
//             } else {
//                 ++Jet;
//             }
//         }
//     } else if (State == HBackground) {
//         for (HJets::iterator Jet = Jets.begin(); Jet != Jets.end();) {
//             if (std::abs((*Jet).user_info<hanalysis::HJetInfo>().GetMaximalId()) == TopId || std::abs((*Jet).user_info<hanalysis::HJetInfo>().GetMaximalId()) == MixedJetId) {
//                 Jet = Jets.erase(Jet);
//             } else {
//                 ++Jet;
//             }
//         }
//     }

    for (HJets::iterator Jet = Jets.begin(); Jet != Jets.end();) {
        if (std::abs((*Jet).user_index()) == MixedJetId) {
            Jet = Jets.erase(Jet);
        } else {
            hanalysis::HJetInfo *JetInfo = new hanalysis::HJetInfo;
            BottomTagger->FillBranch(*Jet);
            JetInfo->SetBdt(BottomReader->GetBdt());
            (*Jet).set_user_info(JetInfo);
            ++Jet;
        }
    }

//     for (auto & Jet : Jets) {
//         hanalysis::HJetInfo *JetInfo = new hanalysis::HJetInfo;
//         BottomTagger->FillBranch(Jet);
//         JetInfo->SetBdt(BottomReader->GetBdt());
// //         JetInfo->SetTag(Jet.user_index());
//         Jet.set_user_info(JetInfo);
//     }

    HJets Leptons = Event->GetLeptons()->GetTaggedJets(JetTag);
    Print(HInformation, "Lepton Number", Leptons.size());

    for (HJets::iterator Lepton = Leptons.begin(); Lepton != Leptons.end();) {
        if (std::abs((*Lepton).user_index()) == MixedJetId) {
            Lepton = Leptons.erase(Lepton);
        } else {
            hanalysis::HJetInfo *JetInfo = new hanalysis::HJetInfo;
            BottomTagger->FillBranch(*Lepton);
            JetInfo->SetBdt(BottomReader->GetBdt());
            (*Lepton).set_user_info(JetInfo);
            ++Lepton;
        }
    }


    std::vector<hanalysis::HJetLeptonPair> JetLeptonPairs;

    for (auto & Lepton : Leptons) {
        if (State == HSignal && std::abs(Lepton.user_index() != TopId)) continue;

        for (auto & Jet : Jets) {
            Print(HDebug, "Lepton Tagging", GetParticleName(Lepton.user_index()), GetParticleName(Jet.user_index()));

            if (State == HSignal && std::abs(Jet.user_index() != TopId)) continue;
            if (State == HSignal && Lepton.user_index() != Jet.user_index()) continue;

            if (State == HBackground && (Lepton.user_index() == Jet.user_index() && Jet.user_index() == TopId)) continue;

            hanalysis::HJetLeptonPair JetLeptonPair(Jet, Lepton);
            if (std::abs(Jet.user_index()) == TopId && Jet.user_index() == Lepton.user_index())
                JetLeptonPair.SetTag(1);
            else
                JetLeptonPair.SetTag(0);
            JetLeptonPairs.push_back(JetLeptonPair);

        }
    }

    Print(HInformation, "Number JetPairs", JetLeptonPairs.size());

    std::vector<HLeptonicTopBranch *> LeptonicTopBranches;
    for (const auto & JetLeptonPair : JetLeptonPairs) {
        HLeptonicTopBranch *LeptonicTopBranch = new HLeptonicTopBranch();
        FillBranch(LeptonicTopBranch, JetLeptonPair);
        LeptonicTopBranches.push_back(LeptonicTopBranch);
    }


    return LeptonicTopBranches;

}

void hdelphes::HLeptonicTopTagger::FillBranch(const hanalysis::HJetLeptonPair &JetLeptonPair)
{
    Print(HInformation, "Fill Top Tagger", JetLeptonPair.GetBdt());

    FillBranch(Branch, JetLeptonPair);

}


void hdelphes::HLeptonicTopTagger::FillBranch(HLeptonicTopBranch *LeptonicTopBranch, const hanalysis::HJetLeptonPair &JetLeptonPair)
{
    Print(HInformation, "Fill Top Tagger", JetLeptonPair.GetBdt());

    LeptonicTopBranch->Mass = JetLeptonPair.GetInvariantMass();
    LeptonicTopBranch->JetPt = JetLeptonPair.GetJetPt();
    LeptonicTopBranch->LeptonPt = JetLeptonPair.GetLeptonPt();
    LeptonicTopBranch->DeltaR = JetLeptonPair.GetDeltaR();
    LeptonicTopBranch->DeltaRap = JetLeptonPair.GetDeltaRap();
    LeptonicTopBranch->DeltaPhi = JetLeptonPair.GetPhiDelta();
    LeptonicTopBranch->BottomBdt = JetLeptonPair.GetBdt();
    LeptonicTopBranch->TopTag = JetLeptonPair.GetTag();

}
