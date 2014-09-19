# include "HLeptonPgs.hh"

HLeptonPgs::HLeptonPgs()
{

    Print(0, "Constructor");

}

HLeptonPgs::~HLeptonPgs()
{

    Print(0, "Destructor");

    
}


void HLeptonPgs::GetElectrons()
{

    Print(1, "Get Electrons");

    int ElectronSum = ClonesArray->ElectronClonesArray->GetEntriesFast();
    Print(2, "Number of Electrons", ElectronSum);
    for (int ElectronNumber = 0; ElectronNumber < ElectronSum; ElectronNumber++) {

        TRootElectron *ElectronClone = (TRootElectron *)ClonesArray->ElectronClonesArray->At(ElectronNumber);

        int ElectronCharge = ElectronClone->Charge;   

        if (ElectronCharge == -1) {
            
            TLorentzVector ElectronLorentzVector = GetLorentzVector(ElectronClone, ElectronMass);
            ElectronLorentzVectorVector.push_back(ElectronLorentzVector);
            Print(2, "Electron");

        } else if (ElectronCharge == 1) {

            TLorentzVector AntiElectronLorentzVector = GetLorentzVector(ElectronClone, ElectronMass);
            AntiElectronLorentzVectorVector.push_back(AntiElectronLorentzVector);
            Print(2, "Anti Electron");

        } else 
            
            Print(0, "Electron Charge", ElectronCharge);

    }

}

void HLeptonPgs::GetMuons()
{

    Print(1, "Get Muons");

    int MuonSum = ClonesArray->MuonClonesArray->GetEntriesFast();
    Print(2, "Number of Muons", MuonSum);
    for (int MuonNumber = 0; MuonNumber < MuonSum; ++MuonNumber) {

        TRootMuon *MuonClone = (TRootMuon *)ClonesArray->MuonClonesArray->At(MuonNumber);
        int MuonCharge = MuonClone->Charge;

        if (MuonCharge == -1) {

            TLorentzVector MuonLorentzVector = GetLorentzVector(MuonClone, MuonMass);
            MuonLorentzVectorVector.push_back(MuonLorentzVector);
            Print(2, "Muon with Pt");

        } else if (MuonCharge == 1) {

            TLorentzVector AntiMuonLorentzVector = GetLorentzVector(MuonClone, MuonMass);
            AntiMuonLorentzVectorVector.push_back(AntiMuonLorentzVector);
            Print(2, "Anti Muon with Pt");

        } else 
            
            Print(0, "Muon Charge", MuonCharge);

    }

}
