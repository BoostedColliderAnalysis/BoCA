# include "HLeptonPgs.hh"

hanalysis::hpgs::HLepton::HLepton()
{

    Print(kNotification, "Constructor");

}

hanalysis::hpgs::HLepton::~HLepton()
{

    Print(kNotification, "Destructor");


}


bool hanalysis::hpgs::HLepton::GetElectrons(hanalysis::HFourVector::HJetDetails JetDetails)
{

    Print(kInformation, "Get Electrons", JetDetails);
    for (const int ElectronNumber : Range(clones_arrays_->GetElectronSum())) {

      TRootElectron *ElectronClone = (TRootElectron *)clones_arrays_->GetElectron(ElectronNumber);

        int ElectronCharge = ElectronClone->Charge;

        if (ElectronCharge == -1) {

            ElectronLorentzVectors.emplace_back(GetLorentzVector(*ElectronClone));
            ElectronJets.emplace_back(GetPseudoJet(*ElectronClone));

            Print(kDebug, "Electron");

        } else if (ElectronCharge == 1) {

            AntiElectronLorentzVectors.emplace_back(GetLorentzVector(*ElectronClone));
            AntiElectronJets.emplace_back(GetPseudoJet(*ElectronClone));

            Print(kDebug, "Anti Electron");

        } else

            Print(kNotification, "Electron Charge", ElectronCharge);

    }

    return 1;

}

bool hanalysis::hpgs::HLepton::GetMuons(hanalysis::HFourVector::HJetDetails JetDetails)
{

    Print(kInformation, "Get Muons", JetDetails);
    for (const int MuonNumber : Range(clones_arrays_->GetMuonSum())) {

      TRootMuon *MuonClone = (TRootMuon *)clones_arrays_->GetMuon(MuonNumber);
        int MuonCharge = MuonClone->Charge;

        if (MuonCharge == -1) {

            MuonLorentzVectors.emplace_back(GetLorentzVector(*MuonClone));
            MuonJets.emplace_back(GetPseudoJet(*MuonClone));

	    Print(kDebug, "Muon with Pt");

        } else if (MuonCharge == 1) {

            AntiMuonLorentzVectors.emplace_back( GetLorentzVector(*MuonClone));
            AntiMuonJets.emplace_back(GetPseudoJet(*MuonClone));

	    Print(kDebug, "Anti Muon with Pt");

        } else

            Print(kNotification, "Muon Charge", MuonCharge);

    }

    return 1;

}
