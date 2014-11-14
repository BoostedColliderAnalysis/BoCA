# include "HLeptonDelphes.hh"

hdelphes::HLepton::HLepton()
{

    Print(HNotification, "Constructor");

}

hdelphes::HLepton::~HLepton()
{
    Print(HNotification, "Destructor");


}

bool hdelphes::HLepton::GetElectrons()
{

    Print(HInformation, "Get Electrons", ClonesArray->GetElectronSum());

    for (int ElectronNumber : HRange(ClonesArray->GetElectronSum())) {

        const Electron* const ElectronClone = (Electron *)ClonesArray->GetElectron(ElectronNumber);

        const int ElectronCharge = ElectronClone->Charge;

        if (ElectronCharge == -1) {

            ElectronLorentzVectors.push_back(const_cast<Electron*>(ElectronClone)->P4());
            ElectronJets.push_back(GetPseudoJet(const_cast<Electron*>(ElectronClone)->P4()));

            Print(HDebug, "Electron");

        } else if (ElectronCharge == 1) {

            AntiElectronLorentzVectors.push_back(const_cast<Electron*>(ElectronClone)->P4());
            AntiElectronJets.push_back(GetPseudoJet(const_cast<Electron*>(ElectronClone)->P4()));

            Print(HDebug, "Anti Electron");

        } else

            Print(HNotification,"Electron Charge", ElectronCharge);

    }

    return 1;

}

bool hdelphes::HLepton::GetMuons()
{

    Print(HInformation, "Get Muons", ClonesArray->GetMuonSum());

    for (int MuonNumber : HRange(ClonesArray->GetMuonSum())) {

        const Muon * const MuonClone = (Muon *)ClonesArray->GetMuon(MuonNumber);
        const int MuonCharge = MuonClone->Charge;

        if (MuonCharge == -1) {

            MuonLorentzVectors.push_back(const_cast<Muon*>(MuonClone)->P4());
            MuonJets.push_back(GetPseudoJet(const_cast<Muon*>(MuonClone)->P4()));

            Print(HDebug, "Muon");

        } else if (MuonCharge == 1) {

            AntiMuonLorentzVectors.push_back(const_cast<Muon*>(MuonClone)->P4());
            AntiMuonJets.push_back(GetPseudoJet(const_cast<Muon*>(MuonClone)->P4()));
            Print(HDebug, "Anti Muon");

        } else

            Print(HNotification,"Muon Charge", MuonCharge);

    }

    return 1;

}
