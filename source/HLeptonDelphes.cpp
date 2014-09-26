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
    Electron* ElectronClone;
    int ElectronCharge;

    Print(2, "Number of Electrons", ClonesArray->ElectronSum());
    for (int ElectronNumber = 0; ElectronNumber < ClonesArray->ElectronSum(); ElectronNumber++) {

        ElectronClone = (Electron *)ClonesArray->ElectronClonesArray->At(ElectronNumber);

        ElectronCharge = ElectronClone->Charge;

        if (ElectronCharge == -1) {

            ElectronVector.push_back(ElectronClone->P4());
            ElectronJetVector.push_back(GetPseudoJet(ElectronClone->P4()));
	    
            Print(2, "Electron");

        } else if (ElectronCharge == 1) {

            AntiElectronVector.push_back(ElectronClone->P4());
            AntiElectronJetVector.push_back(GetPseudoJet(ElectronClone->P4()));
            
            Print(2, "Anti Electron");

        } else

            Print(0,"Electron Charge", ElectronCharge);

    }

}

void HLeptonDelphes::GetMuons()
{

    Print(1, "Get Muons");
    
    Muon* MuonClone;
    int MuonCharge;
    
    Print(2, "Number of Muons", ClonesArray->MuonSum());
    for (int MuonNumber = 0; MuonNumber < ClonesArray->MuonSum(); ++MuonNumber) {

        MuonClone = (Muon *)ClonesArray->MuonClonesArray->At(MuonNumber);
        MuonCharge = MuonClone->Charge;

        if (MuonCharge == -1) {

            MuonVector.push_back(MuonClone->P4());
            MuonJetVector.push_back(GetPseudoJet(MuonClone->P4()));
	    
            Print(2, "Muon");

        } else if (MuonCharge == 1) {

            AntiMuonVector.push_back(MuonClone->P4());
            AntiMuonJetVector.push_back(GetPseudoJet(MuonClone->P4()));
            Print(2, "Anti Muon");

        } else

            Print(0,"Muon Charge", MuonCharge);

    }

}
