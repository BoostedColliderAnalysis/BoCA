# include "HLeptonDelphes.hh"

hanalysis::hdelphes::HLepton::HLepton()
{
    Print(kNotification, "Constructor");
}

bool hanalysis::hdelphes::HLepton::GetElectrons()
{
  Print(kInformation, "Get Electrons", clones_arrays_->GetElectronSum());
    return GetElectrons(Plain);
}

bool hanalysis::hdelphes::HLepton::GetElectrons(hanalysis::HFourVector::HJetDetails JetDetails)
{
    Print(kInformation, "Get Electrons", clones_arrays_->GetElectronSum());
    for (int ElectronNumber : Range(clones_arrays_->GetElectronSum())) {
        delphes::Electron &ElectronClone = static_cast<delphes::Electron &>(*clones_arrays_->GetElectron(ElectronNumber));
        const int ElectronCharge = ElectronClone.Charge;
        if (ElectronCharge == -1) {
            ElectronLorentzVectors.emplace_back(ElectronClone.P4());
            ElectronJets.emplace_back(PseudoJet(ElectronClone.P4()));
            if (JetDetails == hanalysis::HFourVector::Tagging) {
                Constituent constituent(ElectronClone.P4(), GetBranchFamily(*ElectronClone.Particle.GetObject()));
                ElectronJets.back().set_user_info(new JetInfo(constituent));
            }
            Print(kDebug, "Electron");
        } else if (ElectronCharge == 1) {
            AntiElectronLorentzVectors.emplace_back(ElectronClone.P4());
            AntiElectronJets.emplace_back(PseudoJet(ElectronClone.P4()));
            if (JetDetails == hanalysis::HFourVector::Tagging) {

                Constituent constituent(ElectronClone.P4(), GetBranchFamily(*ElectronClone.Particle.GetObject()));
                AntiElectronJets.back().set_user_info(new JetInfo(constituent));
            }
            Print(kDebug, "Anti Electron");
        } else
            Print(kNotification, "Electron Charge", ElectronCharge);
    }
    PrintTruthLevel(kDebug);
    return 1;
}

bool hanalysis::hdelphes::HLepton::GetMuons()
{
    Print(kInformation, "Get Muons", clones_arrays_->GetMuonSum());
    return GetMuons(Plain);
}

bool hanalysis::hdelphes::HLepton::GetMuons(HJetDetails JetDetails)
{
    Print(kInformation, "Get Muons", clones_arrays_->GetMuonSum());
    for (int MuonNumber : Range(clones_arrays_->GetMuonSum())) {
        delphes::Muon &MuonClone = static_cast<delphes::Muon &>(*clones_arrays_->GetMuon(MuonNumber));
        const int MuonCharge = MuonClone.Charge;
        if (MuonCharge == -1) {
            MuonLorentzVectors.emplace_back(MuonClone.P4());
            MuonJets.emplace_back(PseudoJet(MuonClone.P4()));
            if (JetDetails == hanalysis::HFourVector::Tagging) {
                Constituent constituent(MuonClone.P4(), GetBranchFamily(*MuonClone.Particle.GetObject()));
                MuonJets.back().set_user_info(new JetInfo(constituent));
            }
            Print(kDebug, "Muon");
        } else if (MuonCharge == 1) {
            AntiMuonLorentzVectors.emplace_back(MuonClone.P4());
            AntiMuonJets.emplace_back(PseudoJet(MuonClone.P4()));
            if (JetDetails == hanalysis::HFourVector::Tagging) {
                Constituent constituent(MuonClone.P4(), GetBranchFamily(*MuonClone.Particle.GetObject()));
                AntiMuonJets.back().set_user_info(new JetInfo(constituent));
            }
            Print(kDebug, "Anti Muon");
        } else {
            Print(kNotification, "Muon Charge", MuonCharge);
        }
    }
    return 1;
}

// Jets hdelphes::HLepton::GetLeptons(HJetDetails JetDetails)
// {
//
//     Print(kInformation, "Get Tagged Lepton Jets");
//
//     Print(kInformation,"Get Lepton Jets");
//
//     if(!GotElectrons) GotElectrons = GetElectrons(JetDetails);
//     if(!GotMuons) GotMuons = GetMuons(JetDetails);
//
//     LeptonJets = ElectronJets;
//     LeptonJets.insert(LeptonJets.end(), MuonJets.begin(), MuonJets.end());
//     //     LeptonJetVector.insert(LeptonJetVector.end(), TauJetVector.begin(), TauJetVector.end());
//     //     sort(LeptonJetVector.begin(), LeptonJetVector.end(), SortJetByPt());
//
//     Print(kDebug,"Number of Lepton Jets",LeptonJets.size());
//
//     AntiLeptonJets = AntiElectronJets;
//     AntiLeptonJets.insert(AntiLeptonJets.end(), AntiMuonJets.begin(), AntiMuonJets.end());
//     //     AntiLeptonJetVector.insert(AntiLeptonJetVector.end(), AntiTauJetVector.begin(), AntiTauJetVector.end());
//     //     sort(AntiLeptonJetVector.begin(), AntiLeptonJetVector.end(), SortJetByPt());
//     Print(kDebug,"Number of Anti Lepton Jets",AntiLeptonJets.size());
//
//     Jets AllJets = LeptonJets;
//     AllJets.insert(AllJets.end(), AntiLeptonJets.begin(), AntiLeptonJets.end());
//     //     sort(CompleteJetVector.begin(), CompleteJetVector.end(), SortJetByPt());
//
//     return AllJets;
//
// }

