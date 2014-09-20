# include "HLepton.hh"

HLepton::HLepton()
{

    Print(0,"Constructor");

}

HLepton::~HLepton()
{

    Print(0,"Destructor");

}

void HLepton::NewEvent(HClonesArray *NewClonesArray)
{

    Print(1,"New Event");

    ClonesArray = NewClonesArray;

    ElectronVector.clear();

    AntiElectronVector.clear();

    MuonVector.clear();

    AntiMuonVector.clear();

    TauVector.clear();

    AntiTauVector.clear();

    LeptonVector.clear();

    AntiLeptonVector.clear();

    LeptonJetVector.clear();

    AntiLeptonJetVector.clear();

}

vector<TLorentzVector> HLepton::GetLeptonVector()
{

    Print(1,"Get Leptons");

    LeptonVector = ElectronVector;
    LeptonVector.insert(LeptonVector.end(), MuonVector.begin(), MuonVector.end());
//     LeptonVector.insert(LeptonVector.end(), TauVector.begin(), TauVector.end());
    sort(LeptonVector.begin(), LeptonVector.end(), SortByPt());
    
    Print(2,"Number of Leptons",LeptonVector.size());

    AntiLeptonVector = AntiElectronVector;
    AntiLeptonVector.insert(AntiLeptonVector.end(), AntiMuonVector.begin(), AntiMuonVector.end());
//     AntiLeptonVector.insert(AntiLeptonVector.end(), AntiTauVector.begin(), AntiTauVector.end());
    sort(AntiLeptonVector.begin(), AntiLeptonVector.end(), SortByPt());


    Print(2,"Number of Anti Leptons",AntiLeptonVector.size());

    vector<TLorentzVector> CompleteVector = LeptonVector;
    CompleteVector.insert(CompleteVector.end(), AntiLeptonVector.begin(), AntiLeptonVector.end());
    sort(CompleteVector.begin(), CompleteVector.end(), SortByPt());
        
    return CompleteVector;
    
}



vector<PseudoJet> HLepton::GetLeptonJetVector()
{

    Print(1,"Get Lepton Jets");

    LeptonJetVector = ElectronJetVector;
    LeptonJetVector.insert(LeptonJetVector.end(), MuonJetVector.begin(), MuonJetVector.end());
//     LeptonJetVector.insert(LeptonJetVector.end(), TauJetVector.begin(), TauJetVector.end());
    sort(LeptonJetVector.begin(), LeptonJetVector.end(), SortJetByPt());

    Print(2,"Number of Leptons",LeptonJetVector.size());

    AntiLeptonJetVector = AntiElectronJetVector;
    AntiLeptonJetVector.insert(AntiLeptonJetVector.end(), AntiMuonJetVector.begin(), AntiMuonJetVector.end());
//     AntiLeptonJetVector.insert(AntiLeptonJetVector.end(), AntiTauJetVector.begin(), AntiTauJetVector.end());
    sort(AntiLeptonJetVector.begin(), AntiLeptonJetVector.end(), SortJetByPt());
    Print(2,"Number of Anti Leptons",AntiLeptonJetVector.size());

    vector<PseudoJet> CompleteJetVector = LeptonJetVector;
    CompleteJetVector.insert(CompleteJetVector.end(), AntiLeptonJetVector.begin(), AntiLeptonJetVector.end());
    sort(CompleteJetVector.begin(), CompleteJetVector.end(), SortJetByPt());
        
    return CompleteJetVector;
    
}


// void  leptons::FindLargestLorentzVector()
// {
//
//     TLorentzVector Lepton;
//
//     float ElectronPT = Electron.Pt();
//     float MuonPT = Muon.Pt();
//     float TauPT = Tau.Pt();
//
//     if (ElectronPT > MuonPT && ElectronPT > TauPT) {
//         Lepton =  Electron;
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
