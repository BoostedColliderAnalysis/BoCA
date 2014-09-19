# include "HLeptonBase.hh"

HLeptonBase::HLeptonBase()
{
       
    Print(0,"Constructor");
    

}

HLeptonBase::~HLeptonBase()
{
    Print(0,"Destructor");
    
    
}

void HLeptonBase::NewEvent(HClonesArrayBase *ClonesArrayImport)
{
    
    Print(1,"New Event");
    
    ClonesArray = ClonesArrayImport;

    ElectronLorentzVectorVector.clear();
    
    AntiElectronLorentzVectorVector.clear();
    
    MuonLorentzVectorVector.clear();
    
    AntiMuonLorentzVectorVector.clear();
    
    TauLorentzVectorVector.clear();
    
    AntiTauLorentzVectorVector.clear();
    
    LeptonLorentzVectorVector.clear();
    
    AntiLeptonLorentzVectorVector.clear();
    
    LeptonJetVector.clear();
    
    AntiLeptonJetVector.clear();
    
    
    
}


void HLeptonBase::GetLeptonLorentzVectorVector()
{
    
    Print(1,"Get Leptons");

    LeptonLorentzVectorVector = ElectronLorentzVectorVector;
    LeptonLorentzVectorVector.insert(LeptonLorentzVectorVector.end(), MuonLorentzVectorVector.begin(), MuonLorentzVectorVector.end());
//     LeptonLorentzVectorVector.insert(LeptonLorentzVectorVector.end(), TauLorentzVectorVector.begin(), TauLorentzVectorVector.end());
    sort(LeptonLorentzVectorVector.begin(), LeptonLorentzVectorVector.end(), SortByPt());

    AntiLeptonLorentzVectorVector = AntiElectronLorentzVectorVector;
    AntiLeptonLorentzVectorVector.insert(AntiLeptonLorentzVectorVector.end(), AntiMuonLorentzVectorVector.begin(), AntiMuonLorentzVectorVector.end());
//     AntiLeptonLorentzVectorVector.insert(AntiLeptonLorentzVectorVector.end(), AntiTauLorentzVectorVector.begin(), AntiTauLorentzVectorVector.end());
    sort(AntiLeptonLorentzVectorVector.begin(), AntiLeptonLorentzVectorVector.end(), SortByPt());
    
    int LeptonSum = LeptonLorentzVectorVector.size();
    for (int LeptonNumber =0;LeptonNumber<LeptonSum;++LeptonNumber){
        
        TLorentzVector Lepton = LeptonLorentzVectorVector[LeptonNumber];
        
        PseudoJet LeptonJet(Lepton.Px(),Lepton.Py(),Lepton.Pz(),Lepton.E());
        
        LeptonJetVector.push_back(LeptonJet);
        
    }
    
    LeptonSum = AntiLeptonLorentzVectorVector.size();
    for (int LeptonNumber =0;LeptonNumber<LeptonSum;++LeptonNumber){
        
        TLorentzVector Lepton = AntiLeptonLorentzVectorVector[LeptonNumber];
        
        PseudoJet LeptonJet(Lepton.Px(),Lepton.Py(),Lepton.Pz(),Lepton.E());
        
        AntiLeptonJetVector.push_back(LeptonJet);
        
    }
    
    Print(2,"Number of Leptons:",LeptonLorentzVectorVector.size());
    Print(2,"Number of Anti Leptons:",AntiLeptonLorentzVectorVector.size());

}


// void  leptons::FindLargestLorentzVector()
// {
//
//     TLorentzVector LeptonLorentzVector;
//
//     float ElectronPT = ElectronLorentzVector.Pt();
//     float MuonPT = MuonLorentzVector.Pt();
//     float TauPT = TauLorentzVector.Pt();
//
//     if (ElectronPT > MuonPT && ElectronPT > TauPT) {
//         LeptonLorentzVector =  ElectronLorentzVector;
//     } else if (MuonPT > ElectronPT && MuonPT > TauPT) {
//         LeptonLorentzVector = MuonLorentzVector;
//     } else if (TauPT > ElectronPT && TauPT > MuonPT) {
//         LeptonLorentzVector = TauLorentzVector;
//     }
//
//     return (LeptonLorentzVector);
//
// }                                                           // FindLargestLorentzVector

/*

void leptons::LeptonsAndMissingEt()
{

    const float LeptonLowerPtCut = 25.0;
    const float LeptonUpperEtaCut = 2.5;

    int MuonCounter = 0, ElectronCounter = 0;                       //initial the varibles Important

    float MissingPx, MissingPy, MissingEt, MissingPhi;
    MissingPx = 0;
    MissingPy = 0;
    MissingEt = 0;
    MissingPhi = 0;

    int ElectronSum = ClonesArrayClass->ElectronClonesArray->GetEntriesFast();

    for (int ElectronNumber = 0; ElectronNumber < ElectronSum; ElectronNumber++) {

        Electron *electron = (Electron *) ClonesArrayClass->ElectronClonesArray->At(ElectronNumber);
        float ElectronPt = electron->PT;
        float ElectronEta = electron->Eta;
        float ElectronPhi = electron->Phi;

        if (ElectronPt > LeptonLowerPtCut && Abs(ElectronEta) < LeptonUpperEtaCut) {

            ElectronCounter++;
            PseudoJet lepton = PseudoJet(ElectronPt * Cos(ElectronPhi), ElectronPt * Sin(ElectronPhi), ElectronPt * SinH(ElectronEta), ElectronPt * CosH(ElectronEta));

        }

    }

    int MuonSum = ClonesArrayClass->MuonClonesArray->GetEntriesFast();

    for (int MuonNumber = 0; MuonNumber < MuonSum; MuonNumber++) {

        Muon *muon = (Muon *) ClonesArrayClass->MuonClonesArray->At(MuonNumber);
        float MuonPt = muon->PT;
        float MuonEta = muon->Eta;
        float MuonPhi = muon->Phi;

        if (MuonPt > LeptonLowerPtCut && Abs(MuonEta) < LeptonUpperEtaCut) {

            MuonCounter++;
            PseudoJet lepton = PseudoJet(MuonPt * Cos(MuonPhi), MuonPt * Sin(MuonPhi), MuonPt * SinH(MuonEta), MuonPt * CosH(MuonEta));

        }

    }

    int MissingEtSum = ClonesArrayClass->MissingEtClonesArray->GetEntriesFast();

    if (MissingEtSum > 0) {

        MissingET *met = (MissingET *) ClonesArrayClass->MissingEtClonesArray->At(0);

        MissingEt = met->MET;
        MissingPhi = met->Phi;

        MissingPx = MissingEt * cos(MissingPhi);
        MissingPy = MissingEt * sin(MissingPhi);

    }


}*/
