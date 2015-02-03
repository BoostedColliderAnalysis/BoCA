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


void hanalysis::hdelphes::HClonesArray::GetBranches(const std::shared_ptr<ExRootTreeReader> &TreeReader)
{

  Print(HNotification, "Get Branches",TreeReader->GetEntries());

    ParticleClonesArray = std::const_pointer_cast<ExRootTreeReader>(TreeReader)->UseBranch("Particle");
    PhotonClonesArray = std::const_pointer_cast<ExRootTreeReader>(TreeReader)->UseBranch("Photon");
    ElectronClonesArray = std::const_pointer_cast<ExRootTreeReader>(TreeReader)->UseBranch("Electron");
    MuonClonesArray = std::const_pointer_cast<ExRootTreeReader>(TreeReader)->UseBranch("Muon");
    JetClonesArray = std::const_pointer_cast<ExRootTreeReader>(TreeReader)->UseBranch("Jet");
    MissingEtClonesArray = std::const_pointer_cast<ExRootTreeReader>(TreeReader)->UseBranch("MissingET");
    TrackClonesArray = std::const_pointer_cast<ExRootTreeReader>(TreeReader)->UseBranch("Track");
    TowerClonesArray = std::const_pointer_cast<ExRootTreeReader>(TreeReader)->UseBranch("Tower");
    EFlowTrackClonesArray = std::const_pointer_cast<ExRootTreeReader>(TreeReader)->UseBranch("EFlowTrack");
    EFlowPhotonClonesArray = std::const_pointer_cast<ExRootTreeReader>(TreeReader)->UseBranch("EFlowPhoton");
    EFlowNeutralHadronClonesArray = std::const_pointer_cast<ExRootTreeReader>(TreeReader)->UseBranch("EFlowNeutralHadron");
//     EFlowMuonClonesArray = const_cast<ExRootTreeReader*>(&TreeReader)->UseBranch("EFlowMuon");
    GenJetClonesArray = std::const_pointer_cast<ExRootTreeReader>(TreeReader)->UseBranch("GenJet");
    ScalarHtClonesArray = std::const_pointer_cast<ExRootTreeReader>(TreeReader)->UseBranch("ScalarHT");

    Print(HNotification,"Got all Branches");
}

void hanalysis::hdelphes::HClonesArraySnowmass::GetBranches(const std::shared_ptr<ExRootTreeReader> &TreeReader)
{

    Print(HNotification, "Get Branches");

    ParticleClonesArray = std::const_pointer_cast<ExRootTreeReader>(TreeReader)->UseBranch("Particle");
    PhotonClonesArray = std::const_pointer_cast<ExRootTreeReader>(TreeReader)->UseBranch("Photon");
    ElectronClonesArray = std::const_pointer_cast<ExRootTreeReader>(TreeReader)->UseBranch("Electron");
    MuonClonesArray = std::const_pointer_cast<ExRootTreeReader>(TreeReader)->UseBranch("Muon");
    JetClonesArray = std::const_pointer_cast<ExRootTreeReader>(TreeReader)->UseBranch("Jet");
    MissingEtClonesArray = std::const_pointer_cast<ExRootTreeReader>(TreeReader)->UseBranch("MissingET");
    EFlowTrackClonesArray = std::const_pointer_cast<ExRootTreeReader>(TreeReader)->UseBranch("EFlowTrack");
    EFlowPhotonClonesArray = std::const_pointer_cast<ExRootTreeReader>(TreeReader)->UseBranch("EFlowPhoton");
    EFlowNeutralHadronClonesArray = std::const_pointer_cast<ExRootTreeReader>(TreeReader)->UseBranch("EFlowNeutralHadron");
    Print(HInformation, "We have EFlow Branches");
    EFlowMuonClonesArray = std::const_pointer_cast<ExRootTreeReader>(TreeReader)->UseBranch("EFlowMuon");
    GenJetClonesArray = std::const_pointer_cast<ExRootTreeReader>(TreeReader)->UseBranch("GenJet");
    ScalarHtClonesArray = std::const_pointer_cast<ExRootTreeReader>(TreeReader)->UseBranch("ScalarHT");

}

void hanalysis::hpgs::HClonesArray::GetBranches(const std::shared_ptr<ExRootTreeReader> &TreeReader)
{

    Print(HNotification, "Get Branches");

    PhotonClonesArray = std::const_pointer_cast<ExRootTreeReader>(TreeReader)->UseBranch("Photon");
    ElectronClonesArray = std::const_pointer_cast<ExRootTreeReader>(TreeReader)->UseBranch("Electron");
    MuonClonesArray = std::const_pointer_cast<ExRootTreeReader>(TreeReader)->UseBranch("Muon");
    JetClonesArray = std::const_pointer_cast<ExRootTreeReader>(TreeReader)->UseBranch("Jet");
    MissingEtClonesArray = std::const_pointer_cast<ExRootTreeReader>(TreeReader)->UseBranch("MissingET");
    TauClonesArray = std::const_pointer_cast<ExRootTreeReader>(TreeReader)->UseBranch("Tau");

}

void hanalysis::hparton::HClonesArray::GetBranches(const std::shared_ptr<ExRootTreeReader> &TreeReader)
{

    Print(HNotification, "Get Branches");

    ParticleClonesArray = std::const_pointer_cast<ExRootTreeReader>(TreeReader)->UseBranch("Particle");

}
