# include "HClonesArray.hh"

hanalysis::HClonesArray::HClonesArray()
{

    Print(HNotification, "Constructor");

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

}

hanalysis::hdelphes::HClonesArray::HClonesArray()
{

    Print(HNotification, "Constructor");

}

hanalysis::hdelphes::HClonesArraySnowmass::HClonesArraySnowmass()
{

    Print(HNotification, "Constructor");

}

hanalysis::hpgs::HClonesArray::HClonesArray()
{

    Print(HNotification, "Constructor");

}

hanalysis::hparton::HClonesArray::HClonesArray()
{

    Print(HNotification, "Constructor");

}

hanalysis::HClonesArray::~HClonesArray()
{

    Print(HNotification, "Destructor");

//     delete ParticleClonesArray;
//     delete PhotonClonesArray;
//     delete ElectronClonesArray;
//     delete MuonClonesArray;
//     delete JetClonesArray;
//     delete MissingEtClonesArray;
//     delete TauClonesArray;
//     delete TrackClonesArray;
//     delete TowerClonesArray;
//     delete EFlowTrackClonesArray;
//     delete EFlowPhotonClonesArray;
//     delete EFlowNeutralHadronClonesArray;
//     delete EFlowMuonClonesArray;
//     delete GenJetClonesArray;
//     delete ScalarHtClonesArray;

}


void hanalysis::hdelphes::HClonesArray::GetBranches(const ExRootTreeReader *const TreeReader)
{

    Print(HNotification, "Get Branches");

    ParticleClonesArray = const_cast<ExRootTreeReader *>(TreeReader)->UseBranch("Particle");
    PhotonClonesArray = const_cast<ExRootTreeReader *>(TreeReader)->UseBranch("Photon");
    ElectronClonesArray = const_cast<ExRootTreeReader *>(TreeReader)->UseBranch("Electron");
    MuonClonesArray = const_cast<ExRootTreeReader *>(TreeReader)->UseBranch("Muon");
    JetClonesArray = const_cast<ExRootTreeReader *>(TreeReader)->UseBranch("Jet");
    MissingEtClonesArray = const_cast<ExRootTreeReader *>(TreeReader)->UseBranch("MissingET");
    TrackClonesArray = const_cast<ExRootTreeReader *>(TreeReader)->UseBranch("Track");
    TowerClonesArray = const_cast<ExRootTreeReader *>(TreeReader)->UseBranch("Tower");
    EFlowTrackClonesArray = const_cast<ExRootTreeReader *>(TreeReader)->UseBranch("EFlowTrack");
    EFlowPhotonClonesArray = const_cast<ExRootTreeReader *>(TreeReader)->UseBranch("EFlowPhoton");
    EFlowNeutralHadronClonesArray = const_cast<ExRootTreeReader *>(TreeReader)->UseBranch("EFlowNeutralHadron");
//     EFlowMuonClonesArray = const_cast<ExRootTreeReader*>(TreeReader)->UseBranch("EFlowMuon");
    GenJetClonesArray = const_cast<ExRootTreeReader *>(TreeReader)->UseBranch("GenJet");
    ScalarHtClonesArray = const_cast<ExRootTreeReader *>(TreeReader)->UseBranch("ScalarHT");

    Print(HError,"Got all Branches");
}

void hanalysis::hdelphes::HClonesArraySnowmass::GetBranches(const ExRootTreeReader *const TreeReader)
{

    Print(HNotification, "Get Branches");

    ParticleClonesArray = const_cast<ExRootTreeReader *>(TreeReader)->UseBranch("Particle");
    PhotonClonesArray = const_cast<ExRootTreeReader *>(TreeReader)->UseBranch("Photon");
    ElectronClonesArray = const_cast<ExRootTreeReader *>(TreeReader)->UseBranch("Electron");
    MuonClonesArray = const_cast<ExRootTreeReader *>(TreeReader)->UseBranch("Muon");
    JetClonesArray = const_cast<ExRootTreeReader *>(TreeReader)->UseBranch("Jet");
    MissingEtClonesArray = const_cast<ExRootTreeReader *>(TreeReader)->UseBranch("MissingET");
    EFlowTrackClonesArray = const_cast<ExRootTreeReader *>(TreeReader)->UseBranch("EFlowTrack");
    EFlowPhotonClonesArray = const_cast<ExRootTreeReader *>(TreeReader)->UseBranch("EFlowPhoton");
    EFlowNeutralHadronClonesArray = const_cast<ExRootTreeReader *>(TreeReader)->UseBranch("EFlowNeutralHadron");
    Print(HInformation, "We have EFlow Branches");
    EFlowMuonClonesArray = const_cast<ExRootTreeReader *>(TreeReader)->UseBranch("EFlowMuon");
    GenJetClonesArray = const_cast<ExRootTreeReader *>(TreeReader)->UseBranch("GenJet");
    ScalarHtClonesArray = const_cast<ExRootTreeReader *>(TreeReader)->UseBranch("ScalarHT");

}

void hanalysis::hpgs::HClonesArray::GetBranches(const ExRootTreeReader *const TreeReader)
{

    Print(HNotification, "Get Branches");

    PhotonClonesArray = const_cast<ExRootTreeReader *>(TreeReader)->UseBranch("Photon");
    ElectronClonesArray = const_cast<ExRootTreeReader *>(TreeReader)->UseBranch("Electron");
    MuonClonesArray = const_cast<ExRootTreeReader *>(TreeReader)->UseBranch("Muon");
    JetClonesArray = const_cast<ExRootTreeReader *>(TreeReader)->UseBranch("Jet");
    MissingEtClonesArray = const_cast<ExRootTreeReader *>(TreeReader)->UseBranch("MissingET");
    TauClonesArray = const_cast<ExRootTreeReader *>(TreeReader)->UseBranch("Tau");

}

void hanalysis::hparton::HClonesArray::GetBranches(const ExRootTreeReader *const TreeReader)
{

    Print(HNotification, "Get Branches");

    ParticleClonesArray = const_cast<ExRootTreeReader *>(TreeReader)->UseBranch("Particle");

}
