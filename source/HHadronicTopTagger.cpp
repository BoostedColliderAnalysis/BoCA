# include "HHadronicTopTagger.hh"

hdelphes::HHadronicTopTagger::HHadronicTopTagger(HBottomTagger *NewBottomTagger, HHadronicWTagger *NewHadronicWTagger)
{
//     DebugLevel = hanalysis::HObject::HDebug;

    Print(HNotification, "Constructor");

    BottomTagger = NewBottomTagger;
    BottomReader = new hmva::HReader(BottomTagger);

    HadronicWTagger = NewHadronicWTagger(BottomTagger);
    HadronicWReader = new hmva::HReader(HadronicWTagger);

    TaggerName = "HadronicTop";
    SignalNames = {"HadronicTop"};
    BackgroundNames = {"NotHadronicTop"};
    CandidateBranchName = "HadronicTop";

    Branch = new HLeptonicTopBranch();
    JetTag = new hanalysis::HJetTag();

    DefineVariables();

}

hdelphes::HHadronicTopTagger::~HHadronicTopTagger()
{
    Print(HNotification, "Destructor");
    delete Branch;
    delete JetTag;
    delete BottomReader;
    delete HadronicWReader;
}

void hdelphes::HHadronicTopTagger::DefineVariables()
{

    Print(HNotification , "Define Variables");

    Observables.push_back(NewObservable(&Branch->Mass, "Mass"));
    Observables.push_back(NewObservable(&Branch->JetPt, "JetPt"));
    Observables.push_back(NewObservable(&Branch->LeptonPt, "LeptonPt"));
    Observables.push_back(NewObservable(&Branch->DeltaPhi, "DeltaPhi"));
    Observables.push_back(NewObservable(&Branch->DeltaRap, "DeltaRap"));
    Observables.push_back(NewObservable(&Branch->DeltaR, "DeltaR"));
    Observables.push_back(NewObservable(&Branch->BottomTag, "BottomTag"));

    Spectators.push_back(NewObservable(&Branch->TopTag, "TopTag"));

    Print(HNotification, "Variables defined");

}


std::vector<HLeptonicTopBranch *> hdelphes::HHadronicTopTagger::GetBranches(hanalysis::HEvent *const Event, const hanalysis::HObject::HState State)
{

    Print(HInformation, "Get Top Tags");

    JetTag->HeavyParticles = {TopId};
    HJets Jets = Event->GetJets()->GetStructuredTaggedJets(JetTag);
    Print(HInformation, "Jet Number", Jets.size());


    if (State == HSignal) {
        for (HJets::iterator Jet = Jets.begin(); Jet != Jets.end();) {
            Print(HInformation, "Truth Level", GetParticleName((*Jet).user_info<hanalysis::HJetInfo>().GetMaximalId()));
            if (std::abs((*Jet).user_info<hanalysis::HJetInfo>().GetMaximalId()) != TopId) {
                Jet = Jets.erase(Jet);
            } else {
                ++Jet;

                hanalysis::HJetInfo *JetInfo = new hanalysis::HJetInfo;
                BottomTagger->FillBranch(Jet);
                JetInfo->SetBdt(BottomReader->GetBdt());
                Jet.set_user_info(JetInfo);
            }
        }
    } else if (State == HBackground) {
        for (HJets::iterator Jet = Jets.begin(); Jet != Jets.end();) {
            if (std::abs((*Jet).user_info<hanalysis::HJetInfo>().GetMaximalId()) == TopId || std::abs((*Jet).user_info<hanalysis::HJetInfo>().GetMaximalId()) == MixedJetId) {
                Jet = Jets.erase(Jet);
            } else {
                ++Jet;

                hanalysis::HJetInfo *JetInfo = new hanalysis::HJetInfo;
                BottomTagger->FillBranch(Jet);
                JetInfo->SetBdt(BottomReader->GetBdt());
                Jet.set_user_info(JetInfo);
            }
        }
    }

    std::vector<hdelphes::HSuperStructure> JetPairs;
    for (HJets::iterator Jet1 = Jets.begin(); Jet1 != Jets.end(); ++Jet1) {
        for (HJets::iterator Jet2 = Jet1 + 1; Jet2 != Jets.end(); ++Jet2) {
            for (HJets::iterator Jet3 = Jet2 + 1; Jet3 != Jets.end(); ++Jet3) {
                hdelphes::HSuperStructure JetPair((*Jet1), (*Jet2));

                HadronicWTagger->FillBranch(JetPairs);
                JetPair->SetBdt(HadronicWReader->GetBdt());
                JetPairs.push_back(JetPair);
            }
        }
    }



    std::vector<hanalysis::HPairJetPair> PairJetPairs;

    for (auto & Jet : Jets) {
        hanalysis::HJetInfo *JetInfo = new hanalysis::HJetInfo;
        BottomTagger->FillBranch(Jet);
        JetInfo->SetBdt(BottomReader->GetBdt());
        Jet.set_user_info(JetInfo);

        for (auto & Lepton : Leptons) {
            Print(HDebug, "Lepton Tagging", GetParticleName(Lepton.user_index()), GetParticleName(Jet.user_index()));
            if ((State == HSignal && Lepton.user_index() == Jet.user_index()) || State == HBackground) {

                hanalysis::HJetLeptonPair JetLeptonPair(Jet, Lepton);
                if (std::abs(Jet.user_index()) == TopId && Jet.user_index() == Lepton.user_index())
                    JetLeptonPair.SetTag(1);
                else if (std::abs(Jet.user_index()) == MixedJetId && Jet.user_index() == Lepton.user_index())
                    JetLeptonPair.SetTag(.5);
                else
                    JetLeptonPair.SetTag(0);
                PairJetPairs.push_back(JetLeptonPair);
            }
        }
    }

    Print(HInformation, "Number JetPairs", PairJetPairs.size());

    std::vector<HLeptonicTopBranch *> LeptonicTopBranches;
    for (const auto & JetLeptonPair : PairJetPairs) {
        HLeptonicTopBranch *LeptonicTopBranch = new HLeptonicTopBranch();
        FillBranch(LeptonicTopBranch, JetLeptonPair);
        LeptonicTopBranches.push_back(LeptonicTopBranch);
    }


    return LeptonicTopBranches;

}

std::vector<HTopTriple> hdelphes::HHadronicTopTagger::FillTriple(const fastjet::PseudoJet &Jet1,const fastjet::PseudoJet &Jet2,const fastjet::PseudoJet &Jet3)
{
    Print(HInformation, "Fill Triples");
        
    std::vector<HTopTriple>  TopTriples;
    
    hdelphes::HSuperStructure JetPair12(Jet1,Jet2);
    HadronicWTagger->FillBranch(JetPair12);
    JetPair12->SetBdt(HadronicWReader->GetBdt());
    HTopTriple TopTriple1(JetPair12,Jet3);
    TopTriples.push_back(TopTriple1);
    
    hdelphes::HSuperStructure JetPair23(Jet2,Jet3);
    HadronicWTagger->FillBranch(JetPair23);
    JetPair23->SetBdt(HadronicWReader->GetBdt());
    HTopTriple TopTriple2(JetPair23,Jet1);
    TopTriples.push_back(TopTriple2);
    
    hdelphes::HSuperStructure JetPair13(Jet1,Jet3);
    HadronicWTagger->FillBranch(JetPair13);
    JetPair13->SetBdt(HadronicWReader->GetBdt());
    HTopTriple TopTriple3(JetPair13,Jet2);
    TopTriples.push_back(TopTriple3);
    
    return TopTriples;
    
}


void hdelphes::HHadronicTopTagger::FillBranch(const hanalysis::HJetLeptonPair &JetLeptonPair)
{
    Print(HInformation, "Fill Top Tagger", JetLeptonPair.GetBdt());

    FillBranch(Branch, JetLeptonPair);

}


void hdelphes::HHadronicTopTagger::FillBranch(HLeptonicTopBranch *LeptonicTopBranch, const hanalysis::HJetLeptonPair &JetLeptonPair)
{
    Print(HInformation, "Fill Top Tagger", JetLeptonPair.GetBdt());

    LeptonicTopBranch->Mass = JetLeptonPair.GetInvariantMass();
    LeptonicTopBranch->JetPt = JetLeptonPair.GetJetPt();
    LeptonicTopBranch->LeptonPt = JetLeptonPair.GetLeptonPt();
    LeptonicTopBranch->DeltaR = JetLeptonPair.GetDeltaR();
    LeptonicTopBranch->DeltaRap = JetLeptonPair.GetDeltaRap();
    LeptonicTopBranch->DeltaPhi = JetLeptonPair.GetPhiDelta();
    LeptonicTopBranch->BottomTag = JetLeptonPair.GetBdt();
    LeptonicTopBranch->TopTag = JetLeptonPair.GetTag();

}
