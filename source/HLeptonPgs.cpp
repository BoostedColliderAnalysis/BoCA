# include "HLeptonPgs.hh"

hanalysis::hpgs::HLepton::HLepton()
{

    Print(1, "Constructor");

}

hanalysis::hpgs::HLepton::~HLepton()
{

    Print(1, "Destructor");


}


bool hanalysis::hpgs::HLepton::GetElectrons()
{

  Print(2, "Get Electrons", ClonesArray->GetElectronSum());
  for (const int ElectronNumber : HRange(ClonesArray->GetElectronSum())) {

        TRootElectron *ElectronClone = (TRootElectron *)ClonesArray->GetElectron(ElectronNumber);

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

    return 1;

}

bool hanalysis::hpgs::HLepton::GetMuons()
{

    Print(2, "Get Muons", ClonesArray->GetMuonSum());
    for (const int MuonNumber : HRange(ClonesArray->GetMuonSum())) {

        TRootMuon *MuonClone = (TRootMuon *)ClonesArray->GetMuon(MuonNumber);
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

    return 1;

}
