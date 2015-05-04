# include "HLeptonPgs.hh"

hanalysis::hpgs::HLepton::HLepton()
{

    Print(HNotification, "Constructor");

}

hanalysis::hpgs::HLepton::~HLepton()
{

    Print(HNotification, "Destructor");


}


bool hanalysis::hpgs::HLepton::GetElectrons(hanalysis::HFourVector::HJetDetails JetDetails)
{

    Print(HInformation, "Get Electrons", JetDetails);
    for (const int ElectronNumber : Range(clones_arrays_->GetElectronSum())) {

      TRootElectron *ElectronClone = (TRootElectron *)clones_arrays_->GetElectron(ElectronNumber);

        int ElectronCharge = ElectronClone->Charge;

        if (ElectronCharge == -1) {

            ElectronLorentzVectors.push_back(GetLorentzVector(*ElectronClone));
            ElectronJets.push_back(GetPseudoJet(*ElectronClone));

            Print(HDebug, "Electron");

        } else if (ElectronCharge == 1) {

            AntiElectronLorentzVectors.push_back(GetLorentzVector(*ElectronClone));
            AntiElectronJets.push_back(GetPseudoJet(*ElectronClone));

            Print(HDebug, "Anti Electron");

        } else

            Print(HNotification, "Electron Charge", ElectronCharge);

    }

    return 1;

}

bool hanalysis::hpgs::HLepton::GetMuons(hanalysis::HFourVector::HJetDetails JetDetails)
{

    Print(HInformation, "Get Muons", JetDetails);
    for (const int MuonNumber : Range(clones_arrays_->GetMuonSum())) {

      TRootMuon *MuonClone = (TRootMuon *)clones_arrays_->GetMuon(MuonNumber);
        int MuonCharge = MuonClone->Charge;

        if (MuonCharge == -1) {

            MuonLorentzVectors.push_back(GetLorentzVector(*MuonClone));
            MuonJets.push_back(GetPseudoJet(*MuonClone));

	    Print(HDebug, "Muon with Pt");

        } else if (MuonCharge == 1) {

            AntiMuonLorentzVectors.push_back( GetLorentzVector(*MuonClone));
            AntiMuonJets.push_back(GetPseudoJet(*MuonClone));

	    Print(HDebug, "Anti Muon with Pt");

        } else

            Print(HNotification, "Muon Charge", MuonCharge);

    }

    return 1;

}
