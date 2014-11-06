# include "HLeptonDelphes.hh"

hanalysis::hdelphes::HLepton::HLepton()
{

    Print(1, "Constructor");

}

hanalysis::hdelphes::HLepton::~HLepton()
{
    Print(1, "Destructor");


}

bool hanalysis::hdelphes::HLepton::GetElectrons()
{

    Print(2, "Get Electrons", ClonesArray->GetElectronSum());

    for (int ElectronNumber : HRange(ClonesArray->GetElectronSum())) {

        const Electron* const ElectronClone = (Electron *)ClonesArray->GetElectron(ElectronNumber);

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

    return 1;

}

bool hanalysis::hdelphes::HLepton::GetMuons()
{

    Print(2, "Get Muons", ClonesArray->GetMuonSum());

    for (int MuonNumber : HRange(ClonesArray->GetMuonSum())) {

        const Muon * const MuonClone = (Muon *)ClonesArray->GetMuon(MuonNumber);
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

    return 1;

}
