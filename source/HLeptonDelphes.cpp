# include "HLeptonDelphes.hh"

HLeptonDelphes::HLeptonDelphes()
{

    Print(1, "Constructor");

}

HLeptonDelphes::~HLeptonDelphes()
{
    Print(1, "Destructor");


}

void HLeptonDelphes::GetElectrons()
{

    Print(2, "Get Electrons", ClonesArray->ElectronSum());

    for (int ElectronNumber = 0; ElectronNumber < ClonesArray->ElectronSum(); ElectronNumber++) {

        const Electron* const ElectronClone = (Electron *)ClonesArray->ElectronClonesArray->At(ElectronNumber);

        const int ElectronCharge = ElectronClone->Charge;

        if (ElectronCharge == -1) {

            ElectronVector.push_back(const_cast<Electron*>(ElectronClone)->P4());
            ElectronJetVector.push_back(GetPseudoJet(const_cast<Electron*>(ElectronClone)->P4()));
	    
            Print(3, "Electron");

        } else if (ElectronCharge == 1) {

            AntiElectronVector.push_back(const_cast<Electron*>(ElectronClone)->P4());
            AntiElectronJetVector.push_back(GetPseudoJet(const_cast<Electron*>(ElectronClone)->P4()));
            
            Print(3, "Anti Electron");

        } else

            Print(1,"Electron Charge", ElectronCharge);

    }

}

void HLeptonDelphes::GetMuons()
{

    Print(2, "Get Muons", ClonesArray->MuonSum());
        
    for (int MuonNumber = 0; MuonNumber < ClonesArray->MuonSum(); ++MuonNumber) {

        const Muon * const MuonClone = (Muon *)ClonesArray->MuonClonesArray->At(MuonNumber);
        const int MuonCharge = MuonClone->Charge;

        if (MuonCharge == -1) {

            MuonVector.push_back(const_cast<Muon*>(MuonClone)->P4());
            MuonJetVector.push_back(GetPseudoJet(const_cast<Muon*>(MuonClone)->P4()));
	    
            Print(3, "Muon");

        } else if (MuonCharge == 1) {

            AntiMuonVector.push_back(const_cast<Muon*>(MuonClone)->P4());
            AntiMuonJetVector.push_back(GetPseudoJet(const_cast<Muon*>(MuonClone)->P4()));
            Print(3, "Anti Muon");

        } else

            Print(1,"Muon Charge", MuonCharge);

    }

}
