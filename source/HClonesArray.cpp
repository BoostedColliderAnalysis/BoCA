# include "HClonesArray.hh"

Analysis::HClonesArray::HClonesArray()
{

    Print(1, "Constructor");

}

Analysis::HClonesArray::~HClonesArray()
{

    Print(1, "Destructor");

    delete ParticleClonesArray;
    delete PhotonClonesArray;
    delete ElectronClonesArray;
    delete MuonClonesArray;
    delete JetClonesArray;
    delete MissingEtClonesArray;
    delete TauClonesArray;
    delete TrackClonesArray;
    delete TowerClonesArray;
    delete EFlowTrackClonesArray;
    delete EFlowPhotonClonesArray;
    delete EFlowNeutralHadronClonesArray;
    delete EFlowMuonClonesArray;
    delete GenJetClonesArray;
    delete ScalarHtClonesArray;

}

void Analysis::HClonesArray::ResetBranches()
{

    Print(1, "Reset Branches");

    ParticleClonesArray = NULL;
    PhotonClonesArray = NULL;
    ElectronClonesArray = NULL;
    MuonClonesArray = NULL;
    JetClonesArray = NULL;
    MissingEtClonesArray = NULL;
    TauClonesArray = NULL;
    TrackClonesArray = NULL;
    TowerClonesArray = NULL;
    EFlowTrackClonesArray = NULL;
    EFlowPhotonClonesArray = NULL;
    EFlowNeutralHadronClonesArray = NULL;
    EFlowMuonClonesArray = NULL;
    GenJetClonesArray = NULL;
    ScalarHtClonesArray = NULL;

    Print(1,"Branches reset");
}

void Analysis::HDelphes::HClonesArray::GetBranches(const ExRootTreeReader * const TreeReader)
{

    Print(1, "Get Branches");

    ParticleClonesArray = const_cast<ExRootTreeReader*>(TreeReader)->UseBranch("Particle");
    PhotonClonesArray = const_cast<ExRootTreeReader*>(TreeReader)->UseBranch("Photon");
    ElectronClonesArray = const_cast<ExRootTreeReader*>(TreeReader)->UseBranch("Electron");
    MuonClonesArray = const_cast<ExRootTreeReader*>(TreeReader)->UseBranch("Muon");
    JetClonesArray = const_cast<ExRootTreeReader*>(TreeReader)->UseBranch("Jet");
    MissingEtClonesArray = const_cast<ExRootTreeReader*>(TreeReader)->UseBranch("MissingET");
    TrackClonesArray = const_cast<ExRootTreeReader*>(TreeReader)->UseBranch("Track");
    TowerClonesArray = const_cast<ExRootTreeReader*>(TreeReader)->UseBranch("Tower");
    EFlowTrackClonesArray = const_cast<ExRootTreeReader*>(TreeReader)->UseBranch("EFlowTrack");
    EFlowPhotonClonesArray = const_cast<ExRootTreeReader*>(TreeReader)->UseBranch("EFlowPhoton");
    EFlowNeutralHadronClonesArray = const_cast<ExRootTreeReader*>(TreeReader)->UseBranch("EFlowNeutralHadron");
//     EFlowMuonClonesArray = const_cast<ExRootTreeReader*>(TreeReader)->UseBranch("EFlowMuon");
    GenJetClonesArray = const_cast<ExRootTreeReader*>(TreeReader)->UseBranch("GenJet");
    ScalarHtClonesArray = const_cast<ExRootTreeReader*>(TreeReader)->UseBranch("ScalarHT");

}

void Analysis::HDelphes::HClonesArraySnowmass::GetBranches(const ExRootTreeReader *const TreeReader)
{

    Print(1, "Get Branches");

    ParticleClonesArray = const_cast<ExRootTreeReader*>(TreeReader)->UseBranch("Particle");
    PhotonClonesArray = const_cast<ExRootTreeReader*>(TreeReader)->UseBranch("Photon");
    ElectronClonesArray = const_cast<ExRootTreeReader*>(TreeReader)->UseBranch("Electron");
    MuonClonesArray = const_cast<ExRootTreeReader*>(TreeReader)->UseBranch("Muon");
    JetClonesArray = const_cast<ExRootTreeReader*>(TreeReader)->UseBranch("Jet");
    MissingEtClonesArray = const_cast<ExRootTreeReader*>(TreeReader)->UseBranch("MissingET");
    EFlowTrackClonesArray = const_cast<ExRootTreeReader*>(TreeReader)->UseBranch("EFlowTrack");
    EFlowPhotonClonesArray = const_cast<ExRootTreeReader*>(TreeReader)->UseBranch("EFlowPhoton");
    EFlowNeutralHadronClonesArray = const_cast<ExRootTreeReader*>(TreeReader)->UseBranch("EFlowNeutralHadron");
    Print(2,"We have EFlow Branches");
    EFlowMuonClonesArray = const_cast<ExRootTreeReader*>(TreeReader)->UseBranch("EFlowMuon");
    GenJetClonesArray = const_cast<ExRootTreeReader*>(TreeReader)->UseBranch("GenJet");
    ScalarHtClonesArray = const_cast<ExRootTreeReader*>(TreeReader)->UseBranch("ScalarHT");

}

void Analysis::HPgs::HClonesArray::GetBranches(const ExRootTreeReader * const TreeReader)
{

    Print(1, "Get Branches");

    PhotonClonesArray = const_cast<ExRootTreeReader*>(TreeReader)->UseBranch("Photon");
    ElectronClonesArray = const_cast<ExRootTreeReader*>(TreeReader)->UseBranch("Electron");
    MuonClonesArray = const_cast<ExRootTreeReader*>(TreeReader)->UseBranch("Muon");
    JetClonesArray = const_cast<ExRootTreeReader*>(TreeReader)->UseBranch("Jet");
    MissingEtClonesArray = const_cast<ExRootTreeReader*>(TreeReader)->UseBranch("MissingET");
    TauClonesArray = const_cast<ExRootTreeReader*>(TreeReader)->UseBranch("Tau");

}

void Analysis::HParton::HClonesArray::GetBranches(const ExRootTreeReader * const TreeReader)
{

    Print(1, "Get Branches");

    ParticleClonesArray = const_cast<ExRootTreeReader*>(TreeReader)->UseBranch("Particle");

}
