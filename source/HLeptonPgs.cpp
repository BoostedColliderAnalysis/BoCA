# include "HLeptonPgs.hh"

HLeptonPgs::HLeptonPgs()
{

    Print(1, "Constructor");

}

HLeptonPgs::~HLeptonPgs()
{

    Print(1, "Destructor");

    
}


void HLeptonPgs::GetElectrons()
{

    Print(2, "Get Electrons");

    int ElectronSum = ClonesArray->ElectronClonesArray->GetEntriesFast();
    Print(3, "Number of Electrons", ElectronSum);
    for (int ElectronNumber = 0; ElectronNumber < ElectronSum; ElectronNumber++) {

        TRootElectron *ElectronClone = (TRootElectron *)ClonesArray->ElectronClonesArray->At(ElectronNumber);

        int ElectronCharge = ElectronClone->Charge;   

        if (ElectronCharge == -1) {
            
            ElectronLorentzVectors.push_back(GetLorentzVector(ElectronClone));
            ElectronJets.push_back(GetPseudoJet(ElectronClone));
	    
            Print(3, "Electron");

        } else if (ElectronCharge == 1) {

            AntiElectronLorentzVectors.push_back(GetLorentzVector(ElectronClone));
            AntiElectronJets.push_back(GetPseudoJet(ElectronClone));
	    
            Print(3, "Anti Electron");

        } else 
            
            Print(1, "Electron Charge", ElectronCharge);

    }

}

void HLeptonPgs::GetMuons()
{

    Print(2, "Get Muons");

    int MuonSum = ClonesArray->MuonClonesArray->GetEntriesFast();
    Print(3, "Number of Muons", MuonSum);
    for (int MuonNumber = 0; MuonNumber < MuonSum; ++MuonNumber) {

        TRootMuon *MuonClone = (TRootMuon *)ClonesArray->MuonClonesArray->At(MuonNumber);
        int MuonCharge = MuonClone->Charge;

        if (MuonCharge == -1) {

            MuonLorentzVectors.push_back(GetLorentzVector(MuonClone));
            MuonJets.push_back(GetPseudoJet(MuonClone));
            
	    Print(3, "Muon with Pt");

        } else if (MuonCharge == 1) {

            AntiMuonLorentzVectors.push_back( GetLorentzVector(MuonClone));
            AntiMuonJets.push_back(GetPseudoJet(MuonClone));
            
	    Print(3, "Anti Muon with Pt");

        } else 
            
            Print(1, "Muon Charge", MuonCharge);

    }

}
