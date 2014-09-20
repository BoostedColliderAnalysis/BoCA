# include "HLeptonDelphes.hh"

HLeptonDelphes::HLeptonDelphes()
{

    Print(0, "Constructor");

}

HLeptonDelphes::~HLeptonDelphes()
{
    Print(0, "Destructor");


}

void HLeptonDelphes::GetElectrons()
{

    Print(1, "Get Electrons");

    int ElectronSum = ClonesArray->ElectronClonesArray->GetEntriesFast();
    Print(2, "Number of Electrons", ElectronSum);
    for (int ElectronNumber = 0; ElectronNumber < ElectronSum; ElectronNumber++) {

        Electron* ElectronClone = (Electron *)ClonesArray->ElectronClonesArray->At(ElectronNumber);

        int ElectronCharge = ElectronClone->Charge;

        if (ElectronCharge == -1) {

            ElectronVector.push_back(GetLorentzVector(ElectronClone, ElectronMass));
            ElectronJetVector.push_back(GetPseudoJetPt(ElectronClone));
	    
            Print(2, "Electron");

        } else if (ElectronCharge == 1) {

            AntiElectronVector.push_back(GetLorentzVector(ElectronClone, ElectronMass));
            AntiElectronJetVector.push_back(GetPseudoJetPt(ElectronClone));	    
	    
            Print(2, "Anti Electron");

        } else

            Print(0,"Electron Charge", ElectronCharge);

    }

}

void HLeptonDelphes::GetMuons()
{

    Print(1, "Get Muons");

    int MuonSum = ClonesArray->MuonClonesArray->GetEntriesFast();
    Print(2, "Number of Muons", MuonSum);
    for (int MuonNumber = 0; MuonNumber < MuonSum; ++MuonNumber) {

        Muon* MuonClone = (Muon *)ClonesArray->MuonClonesArray->At(MuonNumber);
        int MuonCharge = MuonClone->Charge;

        if (MuonCharge == -1) {

            MuonVector.push_back(GetLorentzVector(MuonClone, MuonMass));
            MuonJetVector.push_back(GetPseudoJetPt(MuonClone));
	    
            Print(2, "Muon");

        } else if (MuonCharge == 1) {

            AntiMuonVector.push_back(GetLorentzVector(MuonClone, MuonMass));
            AntiMuonJetVector.push_back(GetPseudoJetPt(MuonClone));
            Print(2, "Anti Muon");

        } else

            Print(0,"Muon Charge", MuonCharge);

    }

}
