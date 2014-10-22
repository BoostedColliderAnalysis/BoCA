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

    for (int ElectronNumber : HRange(ClonesArray->ElectronSum())) {

        const Electron* const ElectronClone = (Electron *)ClonesArray->ElectronClonesArray->At(ElectronNumber);

        const int ElectronCharge = ElectronClone->Charge;

        if (ElectronCharge == -1) {

            ElectronLorentzVectors.push_back(const_cast<Electron*>(ElectronClone)->P4());
            ElectronJets.push_back(GetPseudoJet(const_cast<Electron*>(ElectronClone)->P4()));
	    
            Print(3, "Electron");

        } else if (ElectronCharge == 1) {

            AntiElectronLorentzVectors.push_back(const_cast<Electron*>(ElectronClone)->P4());
            AntiElectronJets.push_back(GetPseudoJet(const_cast<Electron*>(ElectronClone)->P4()));
            
            Print(3, "Anti Electron");

        } else

            Print(1,"Electron Charge", ElectronCharge);

    }

}

void HLeptonDelphes::GetMuons()
{

    Print(2, "Get Muons", ClonesArray->MuonSum());
        
    for (int MuonNumber : HRange(ClonesArray->MuonSum())) {

        const Muon * const MuonClone = (Muon *)ClonesArray->MuonClonesArray->At(MuonNumber);
        const int MuonCharge = MuonClone->Charge;

        if (MuonCharge == -1) {

            MuonLorentzVectors.push_back(const_cast<Muon*>(MuonClone)->P4());
            MuonJets.push_back(GetPseudoJet(const_cast<Muon*>(MuonClone)->P4()));
	    
            Print(3, "Muon");

        } else if (MuonCharge == 1) {

            AntiMuonLorentzVectors.push_back(const_cast<Muon*>(MuonClone)->P4());
            AntiMuonJets.push_back(GetPseudoJet(const_cast<Muon*>(MuonClone)->P4()));
            Print(3, "Anti Muon");

        } else

            Print(1,"Muon Charge", MuonCharge);

    }

}
