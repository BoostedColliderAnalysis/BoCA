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
    for (const int ElectronNumber : Range(clones_arrays_->ElectronSum())) {

      TRootElectron &electron = static_cast<TRootElectron &>(clones_arrays().Electron(ElectronNumber));

        int ElectronCharge = electron.Charge;

        if (ElectronCharge == -1) {

            ElectronLorentzVectors.emplace_back(GetLorentzVector(electron));
            ElectronJets.emplace_back(GetPseudoJet(electron));

            Print(kDebug, "Electron");

        } else if (ElectronCharge == 1) {

            AntiElectronLorentzVectors.emplace_back(GetLorentzVector(electron));
            AntiElectronJets.emplace_back(GetPseudoJet(electron));

            Print(kDebug, "Anti Electron");

        } else

            Print(kNotification, "Electron Charge", ElectronCharge);

    }

    return 1;

}

bool hanalysis::hpgs::HLepton::GetMuons(hanalysis::HFourVector::HJetDetails JetDetails)
{

    Print(kInformation, "Get Muons", JetDetails);
    for (const int MuonNumber : Range(clones_arrays_->MuonSum())) {

      TRootMuon &muon = static_cast<TRootMuon &>(clones_arrays().Muon(MuonNumber));
        int MuonCharge = muon.Charge;

        if (MuonCharge == -1) {

            MuonLorentzVectors.emplace_back(GetLorentzVector(muon));
            MuonJets.emplace_back(GetPseudoJet(muon));

	    Print(kDebug, "Muon with Pt");

        } else if (MuonCharge == 1) {

            AntiMuonLorentzVectors.emplace_back( GetLorentzVector(muon));
            AntiMuonJets.emplace_back(GetPseudoJet(muon));

	    Print(kDebug, "Anti Muon with Pt");

        } else

            Print(kNotification, "Muon Charge", MuonCharge);

    }

    return 1;

}
