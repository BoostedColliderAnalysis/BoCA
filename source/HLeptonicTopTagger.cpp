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
    Observables.push_back(NewObservable(&Branch->DeltaEta, "DeltaEta"));
    Observables.push_back(NewObservable(&Branch->DeltaR, "DeltaR"));
    Observables.push_back(NewObservable(&Branch->BottomTag, "BottomTag"));

    Spectators.push_back(NewObservable(&Branch->TopTag, "TopTag"));

    Print(HNotification, "Variables defined");

}


std::vector<HLeptonicTopBranch *> hdelphes::HLeptonicTopTagger::GetBranches(hanalysis::HEvent *const Event, const hanalysis::HObject::HState State)
{

    Print(HInformation, "Get Top Tags");

    JetTag->SetHeavyParticles( {TopId});
    HJets Jets = Event->GetJets()->GetStructuredTaggedJets(JetTag);
    Print(HInformation, "Jet Number", Jets.size());


    if (State == HSignal) {
        for (HJets::iterator Jet = Jets.begin(); Jet != Jets.end();) {
            Print(HInformation, "Truth Level", GetParticleName((*Jet).user_info<hanalysis::HJetInfo>().GetMaximalId()));
            if (std::abs((*Jet).user_info<hanalysis::HJetInfo>().GetMaximalId()) != TopId) {
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

//     HJets TopJets;
//     HJets OtherJets;
//     for (const auto & Jet : Jets) {
//         if (std::abs(Jet.user_info<hanalysis::HJetInfo>().GetMaximalId()) == TopId) {
//             TopJets.push_back(Jet);
//         } else {
//             OtherJets.push_back(Jet);
//         }
//     }
//
//
    HJets Leptons = Event->GetLeptons()->GetTaggedJets(JetTag);
    Print(HInformation, "Lepton Number", Leptons.size());
//
//     HJets TopLeptons;
//     HJets OtherLeptons;
//     for (const auto & Lepton : Leptons) {
//         if (std::abs(Lepton.user_info<hanalysis::HJetInfo>().GetMaximalId()) == TopId) {
//             TopLeptons.push_back(Lepton);
//         } else {
//             OtherLeptons.push_back(Lepton);
//         }
//     }


    std::vector<hanalysis::HJetLeptonPair> JetLeptonPairs;

    for (HJets::iterator Jet = Jets.begin(); Jet != Jets.end(); ++Jet) {
        hanalysis::HJetInfo *JetInfo = new hanalysis::HJetInfo;
        BottomTagger->FillBranch(*Jet);
        JetInfo->SetBdt(BottomReader->GetBdt());
        (*Jet).set_user_info(JetInfo);

        for (HJets::iterator Lepton = Leptons.begin(); Lepton != Leptons.end(); ++Lepton) {
            Print(HDebug, "Lepton Tagging", GetParticleName((*Lepton).user_index()), GetParticleName((*Jet).user_index()));
            if ((State == HSignal && (*Lepton).user_index() == (*Jet).user_index()) || (State == HBackground)) {

                hanalysis::HJetLeptonPair JetLeptonPair((*Jet), (*Lepton));
                JetLeptonPair.SetBdt((*Jet).user_info<hanalysis::HJetInfo>().GetBdt());
                if (std::abs((*Jet).user_index()) == TopId) JetLeptonPair.SetTag(1);
                JetLeptonPairs.push_back(JetLeptonPair);
            }
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
    LeptonicTopBranch->DeltaEta = JetLeptonPair.GetDeltaEta();
    LeptonicTopBranch->DeltaPhi = JetLeptonPair.GetPhiDelta();
    LeptonicTopBranch->BottomTag = JetLeptonPair.GetBdt();
    if (JetLeptonPair.GetTag() == 1) {
        LeptonicTopBranch->TopTag = 1;
    } else {
        LeptonicTopBranch->TopTag = 0;
    }

}
