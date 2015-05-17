# include "HLeptonDelphes.hh"
# include "Predicate.hh"

analysis::hdelphes::HLepton::HLepton()
{
    Print(kNotification, "Constructor");
}

bool analysis::hdelphes::HLepton::GetElectrons()
{
  Print(kInformation, "Get Electrons", clones_arrays().ElectronSum());
    return GetElectrons(Plain);
}

bool analysis::hdelphes::HLepton::GetElectrons(analysis::HFourVector::HJetDetails JetDetails)
{
    Print(kInformation, "Get Electrons", clones_arrays().ElectronSum());
    for (int ElectronNumber : Range(clones_arrays().ElectronSum())) {
        delphes::Electron &electron = static_cast<delphes::Electron &>(clones_arrays().Electron(ElectronNumber));
        const int ElectronCharge = electron.Charge;
        if (ElectronCharge == -1) {
            ElectronLorentzVectors.emplace_back(electron.P4());
            ElectronJets.emplace_back(PseudoJet(electron.P4()));
            if (JetDetails == analysis::HFourVector::Tagging) {
                Constituent constituent(electron.P4(), GetBranchFamily(*electron.Particle.GetObject()));
                ElectronJets.back().set_user_info(new JetInfo(constituent));
            }
            Print(kDebug, "Electron");
        } else if (ElectronCharge == 1) {
            AntiElectronLorentzVectors.emplace_back(electron.P4());
            AntiElectronJets.emplace_back(PseudoJet(electron.P4()));
            if (JetDetails == analysis::HFourVector::Tagging) {

                Constituent constituent(electron.P4(), GetBranchFamily(*electron.Particle.GetObject()));
                AntiElectronJets.back().set_user_info(new JetInfo(constituent));
            }
            Print(kDebug, "Anti Electron");
        } else
            Print(kNotification, "Electron Charge", ElectronCharge);
    }
    PrintTruthLevel(kDebug);
    return 1;
}

bool analysis::hdelphes::HLepton::GetMuons()
{
    Print(kInformation, "Get Muons", clones_arrays().MuonSum());
    return GetMuons(Plain);
}

bool analysis::hdelphes::HLepton::GetMuons(HJetDetails JetDetails)
{
    Print(kInformation, "Get Muons", clones_arrays().MuonSum());
    for (int MuonNumber : Range(clones_arrays().MuonSum())) {
        delphes::Muon &muon = static_cast<delphes::Muon &>(clones_arrays().Muon(MuonNumber));
        const int MuonCharge = muon.Charge;
        if (MuonCharge == -1) {
            MuonLorentzVectors.emplace_back(muon.P4());
            MuonJets.emplace_back(PseudoJet(muon.P4()));
            if (JetDetails == analysis::HFourVector::Tagging) {
                Constituent constituent(muon.P4(), GetBranchFamily(*muon.Particle.GetObject()));
                MuonJets.back().set_user_info(new JetInfo(constituent));
            }
            Print(kDebug, "Muon");
        } else if (MuonCharge == 1) {
            AntiMuonLorentzVectors.emplace_back(muon.P4());
            AntiMuonJets.emplace_back(PseudoJet(muon.P4()));
            if (JetDetails == analysis::HFourVector::Tagging) {
                Constituent constituent(muon.P4(), GetBranchFamily(*muon.Particle.GetObject()));
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

