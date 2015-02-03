# include "HLeptonDelphes.hh"

hanalysis::hdelphes::HLepton::HLepton()
{

    Print(HNotification, "Constructor");

}

hanalysis::hdelphes::HLepton::~HLepton()
{
    Print(HNotification, "Destructor");


}

bool hanalysis::hdelphes::HLepton::GetElectrons()
{

    Print(HInformation, "Get Electrons", ClonesArrays->GetElectronSum());

    return GetElectrons(Plain);

}

bool hanalysis::hdelphes::HLepton::GetElectrons(hanalysis::HFourVector::HJetDetails JetDetails)
{

    Print(HInformation, "Get Electrons", ClonesArrays->GetElectronSum());

    for (int ElectronNumber : HRange(ClonesArrays->GetElectronSum())) {

        delphes::Electron *ElectronClone = (delphes::Electron *)ClonesArrays->GetElectron(ElectronNumber);

        const int ElectronCharge = ElectronClone->Charge;

        if (ElectronCharge == -1) {

            ElectronLorentzVectors.push_back(const_cast<delphes::Electron *>(ElectronClone)->P4());
            ElectronJets.push_back(PseudoJet(const_cast<delphes::Electron *>(ElectronClone)->P4()));

            if (JetDetails == hanalysis::HFourVector::Tagging) {

                HConstituent Constituent(ElectronClone->P4(), GetBranchFamily(ElectronClone->Particle.GetObject()));
                ElectronJets.back().set_user_info(new HJetInfo(Constituent));
            }

            Print(HDebug, "Electron");

        } else if (ElectronCharge == 1) {

            AntiElectronLorentzVectors.push_back(const_cast<delphes::Electron *>(ElectronClone)->P4());
            AntiElectronJets.push_back(PseudoJet(const_cast<delphes::Electron *>(ElectronClone)->P4()));

            if (JetDetails == hanalysis::HFourVector::Tagging) {

              HConstituent Constituent(ElectronClone->P4(), GetBranchFamily(ElectronClone->Particle.GetObject()));
              AntiElectronJets.back().set_user_info(new HJetInfo(Constituent));
            }

            Print(HDebug, "Anti Electron");

        } else

            Print(HNotification, "Electron Charge", ElectronCharge);

    }

    PrintTruthLevel(HDebug);
    return 1;

}

bool hanalysis::hdelphes::HLepton::GetMuons()
{

    Print(HInformation, "Get Muons", ClonesArrays->GetMuonSum());

    return GetMuons(Plain);

}

bool hanalysis::hdelphes::HLepton::GetMuons(HJetDetails JetDetails)
{

    Print(HInformation, "Get Muons", ClonesArrays->GetMuonSum());

    for (int MuonNumber : HRange(ClonesArrays->GetMuonSum())) {

        delphes::Muon *const MuonClone = (delphes::Muon *)ClonesArrays->GetMuon(MuonNumber);
        const int MuonCharge = MuonClone->Charge;

        if (MuonCharge == -1) {

            MuonLorentzVectors.push_back(const_cast<delphes::Muon *>(MuonClone)->P4());
            MuonJets.push_back(PseudoJet(const_cast<delphes::Muon *>(MuonClone)->P4()));

            if (JetDetails == hanalysis::HFourVector::Tagging) {

              HConstituent Constituent(MuonClone->P4(), GetBranchFamily(MuonClone->Particle.GetObject()));
              MuonJets.back().set_user_info(new HJetInfo(Constituent));
            }

            Print(HDebug, "Muon");

        } else if (MuonCharge == 1) {

            AntiMuonLorentzVectors.push_back(const_cast<delphes::Muon *>(MuonClone)->P4());
            AntiMuonJets.push_back(PseudoJet(const_cast<delphes::Muon *>(MuonClone)->P4()));
            if (JetDetails == hanalysis::HFourVector::Tagging) {
              HConstituent Constituent(MuonClone->P4(), GetBranchFamily(MuonClone->Particle.GetObject()));
              AntiMuonJets.back().set_user_info(new HJetInfo(Constituent));
            }
            Print(HDebug, "Anti Muon");

        } else {

            Print(HNotification, "Muon Charge", MuonCharge);
        }

    }

    return 1;

}

// HJets hdelphes::HLepton::GetLeptons(HJetDetails JetDetails)
// {
//
//     Print(HInformation, "Get Tagged Lepton Jets");
//
//     Print(HInformation,"Get Lepton Jets");
//
//     if(!GotElectrons) GotElectrons = GetElectrons(JetDetails);
//     if(!GotMuons) GotMuons = GetMuons(JetDetails);
//
//     LeptonJets = ElectronJets;
//     LeptonJets.insert(LeptonJets.end(), MuonJets.begin(), MuonJets.end());
//     //     LeptonJetVector.insert(LeptonJetVector.end(), TauJetVector.begin(), TauJetVector.end());
//     //     sort(LeptonJetVector.begin(), LeptonJetVector.end(), SortJetByPt());
//
//     Print(HDebug,"Number of Lepton Jets",LeptonJets.size());
//
//     AntiLeptonJets = AntiElectronJets;
//     AntiLeptonJets.insert(AntiLeptonJets.end(), AntiMuonJets.begin(), AntiMuonJets.end());
//     //     AntiLeptonJetVector.insert(AntiLeptonJetVector.end(), AntiTauJetVector.begin(), AntiTauJetVector.end());
//     //     sort(AntiLeptonJetVector.begin(), AntiLeptonJetVector.end(), SortJetByPt());
//     Print(HDebug,"Number of Anti Lepton Jets",AntiLeptonJets.size());
//
//     HJets AllJets = LeptonJets;
//     AllJets.insert(AllJets.end(), AntiLeptonJets.begin(), AntiLeptonJets.end());
//     //     sort(CompleteJetVector.begin(), CompleteJetVector.end(), SortJetByPt());
//
//     return AllJets;
//
// }

