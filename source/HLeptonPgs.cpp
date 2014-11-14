# include "HLeptonPgs.hh"

hpgs::HLepton::HLepton()
{

    Print(HNotification, "Constructor");

}

hpgs::HLepton::~HLepton()
{

    Print(HNotification, "Destructor");


}


bool hpgs::HLepton::GetElectrons()
{

  Print(HInformation, "Get Electrons", ClonesArray->GetElectronSum());
  for (const int ElectronNumber : HRange(ClonesArray->GetElectronSum())) {

        TRootElectron *ElectronClone = (TRootElectron *)ClonesArray->GetElectron(ElectronNumber);

        int ElectronCharge = ElectronClone->Charge;

        if (ElectronCharge == -1) {

            ElectronLorentzVectors.push_back(GetLorentzVector(ElectronClone));
            ElectronJets.push_back(GetPseudoJet(ElectronClone));

            Print(HDebug, "Electron");

        } else if (ElectronCharge == 1) {

            AntiElectronLorentzVectors.push_back(GetLorentzVector(ElectronClone));
            AntiElectronJets.push_back(GetPseudoJet(ElectronClone));

            Print(HDebug, "Anti Electron");

        } else

            Print(HNotification, "Electron Charge", ElectronCharge);

    }

    return 1;

}

bool hpgs::HLepton::GetMuons()
{

    Print(HInformation, "Get Muons", ClonesArray->GetMuonSum());
    for (const int MuonNumber : HRange(ClonesArray->GetMuonSum())) {

        TRootMuon *MuonClone = (TRootMuon *)ClonesArray->GetMuon(MuonNumber);
        int MuonCharge = MuonClone->Charge;

        if (MuonCharge == -1) {

            MuonLorentzVectors.push_back(GetLorentzVector(MuonClone));
            MuonJets.push_back(GetPseudoJet(MuonClone));

	    Print(HDebug, "Muon with Pt");

        } else if (MuonCharge == 1) {

            AntiMuonLorentzVectors.push_back( GetLorentzVector(MuonClone));
            AntiMuonJets.push_back(GetPseudoJet(MuonClone));

	    Print(HDebug, "Anti Muon with Pt");

        } else

            Print(HNotification, "Muon Charge", MuonCharge);

    }

    return 1;

}
