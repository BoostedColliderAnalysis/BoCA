# include "ClonesArrays.hh"


# include "TObjArray.h"
# include "TObject.h"

hanalysis::ClonesArrays::ClonesArrays()
{

    Print(kNotification, "Constructor");

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
    Print(kNotification, "Constructor");
}

hanalysis::hdelphes::HClonesArraySnowmass::HClonesArraySnowmass()
{
    Print(kNotification, "Constructor");
}

hanalysis::hpgs::HClonesArray::HClonesArray()
{
    Print(kNotification, "Constructor");
}

hanalysis::hparton::HClonesArray::HClonesArray()
{
    Print(kNotification, "Constructor");
}

hanalysis::ClonesArrays::~ClonesArrays()
{
    Print(kNotification, "Destructor");

}


void hanalysis::hdelphes::HClonesArray::GetBranches(const std::shared_ptr<ExRootTreeReader> &TreeReader)
{

  Print(kNotification, "Get Branches",TreeReader->GetEntries());
  tree_reader_ = TreeReader.get();

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

    Print(kNotification,"Got all Branches");
}

void hanalysis::hdelphes::HClonesArraySnowmass::GetBranches(const std::shared_ptr<ExRootTreeReader> &TreeReader)
{

  Print(kNotification, "Get Branches");
  tree_reader_ = TreeReader.get();

    ParticleClonesArray = std::const_pointer_cast<ExRootTreeReader>(TreeReader)->UseBranch("Particle");
    PhotonClonesArray = std::const_pointer_cast<ExRootTreeReader>(TreeReader)->UseBranch("Photon");
    ElectronClonesArray = std::const_pointer_cast<ExRootTreeReader>(TreeReader)->UseBranch("Electron");
    MuonClonesArray = std::const_pointer_cast<ExRootTreeReader>(TreeReader)->UseBranch("Muon");
    JetClonesArray = std::const_pointer_cast<ExRootTreeReader>(TreeReader)->UseBranch("Jet");
    MissingEtClonesArray = std::const_pointer_cast<ExRootTreeReader>(TreeReader)->UseBranch("MissingET");
    EFlowTrackClonesArray = std::const_pointer_cast<ExRootTreeReader>(TreeReader)->UseBranch("EFlowTrack");
    EFlowPhotonClonesArray = std::const_pointer_cast<ExRootTreeReader>(TreeReader)->UseBranch("EFlowPhoton");
    EFlowNeutralHadronClonesArray = std::const_pointer_cast<ExRootTreeReader>(TreeReader)->UseBranch("EFlowNeutralHadron");
    Print(kInformation, "We have EFlow Branches");
    EFlowMuonClonesArray = std::const_pointer_cast<ExRootTreeReader>(TreeReader)->UseBranch("EFlowMuon");
    GenJetClonesArray = std::const_pointer_cast<ExRootTreeReader>(TreeReader)->UseBranch("GenJet");
    ScalarHtClonesArray = std::const_pointer_cast<ExRootTreeReader>(TreeReader)->UseBranch("ScalarHT");

}

void hanalysis::hpgs::HClonesArray::GetBranches(const std::shared_ptr<ExRootTreeReader> &TreeReader)
{

  Print(kNotification, "Get Branches");
  tree_reader_ = TreeReader.get();

    PhotonClonesArray = std::const_pointer_cast<ExRootTreeReader>(TreeReader)->UseBranch("Photon");
    ElectronClonesArray = std::const_pointer_cast<ExRootTreeReader>(TreeReader)->UseBranch("Electron");
    MuonClonesArray = std::const_pointer_cast<ExRootTreeReader>(TreeReader)->UseBranch("Muon");
    JetClonesArray = std::const_pointer_cast<ExRootTreeReader>(TreeReader)->UseBranch("Jet");
    MissingEtClonesArray = std::const_pointer_cast<ExRootTreeReader>(TreeReader)->UseBranch("MissingET");
    TauClonesArray = std::const_pointer_cast<ExRootTreeReader>(TreeReader)->UseBranch("Tau");

}

void hanalysis::hparton::HClonesArray::GetBranches(const std::shared_ptr<ExRootTreeReader> &TreeReader)
{

  Print(kNotification, "Get Branches");
  tree_reader_ = TreeReader.get();

    ParticleClonesArray = std::const_pointer_cast<ExRootTreeReader>(TreeReader)->UseBranch("Particle");

}













void hanalysis::hdelphes::HClonesArray::GetBranches(ExRootTreeReader &TreeReader)
{

  Print(kNotification, "Get Branches",TreeReader.GetEntries());
  tree_reader_ = &TreeReader;

  ParticleClonesArray = const_cast<ExRootTreeReader&>(TreeReader).UseBranch("Particle");
  PhotonClonesArray = const_cast<ExRootTreeReader&>(TreeReader).UseBranch("Photon");
  ElectronClonesArray = const_cast<ExRootTreeReader&>(TreeReader).UseBranch("Electron");
  MuonClonesArray = const_cast<ExRootTreeReader&>(TreeReader).UseBranch("Muon");
  JetClonesArray = const_cast<ExRootTreeReader&>(TreeReader).UseBranch("Jet");
  MissingEtClonesArray = const_cast<ExRootTreeReader&>(TreeReader).UseBranch("MissingET");
  TrackClonesArray = const_cast<ExRootTreeReader&>(TreeReader).UseBranch("Track");
  TowerClonesArray = const_cast<ExRootTreeReader&>(TreeReader).UseBranch("Tower");
  EFlowTrackClonesArray = const_cast<ExRootTreeReader&>(TreeReader).UseBranch("EFlowTrack");
  EFlowPhotonClonesArray = const_cast<ExRootTreeReader&>(TreeReader).UseBranch("EFlowPhoton");
  EFlowNeutralHadronClonesArray = const_cast<ExRootTreeReader&>(TreeReader).UseBranch("EFlowNeutralHadron");
  //     EFlowMuonClonesArray = const_cast<ExRootTreeReader*>(&TreeReader)->UseBranch("EFlowMuon");
  GenJetClonesArray = const_cast<ExRootTreeReader&>(TreeReader).UseBranch("GenJet");
  ScalarHtClonesArray = const_cast<ExRootTreeReader&>(TreeReader).UseBranch("ScalarHT");

  Print(kNotification,"Got all Branches");
}

void hanalysis::hdelphes::HClonesArraySnowmass::GetBranches(ExRootTreeReader &TreeReader)
{

  Print(kNotification, "Get Branches");
  tree_reader_ = &TreeReader;

  ParticleClonesArray = const_cast<ExRootTreeReader&>(TreeReader).UseBranch("Particle");
  PhotonClonesArray = const_cast<ExRootTreeReader&>(TreeReader).UseBranch("Photon");
  ElectronClonesArray = const_cast<ExRootTreeReader&>(TreeReader).UseBranch("Electron");
  MuonClonesArray = const_cast<ExRootTreeReader&>(TreeReader).UseBranch("Muon");
  JetClonesArray = const_cast<ExRootTreeReader&>(TreeReader).UseBranch("Jet");
  MissingEtClonesArray = const_cast<ExRootTreeReader&>(TreeReader).UseBranch("MissingET");
  EFlowTrackClonesArray = const_cast<ExRootTreeReader&>(TreeReader).UseBranch("EFlowTrack");
  EFlowPhotonClonesArray = const_cast<ExRootTreeReader&>(TreeReader).UseBranch("EFlowPhoton");
  EFlowNeutralHadronClonesArray = const_cast<ExRootTreeReader&>(TreeReader).UseBranch("EFlowNeutralHadron");
  Print(kInformation, "We have EFlow Branches");
  EFlowMuonClonesArray = const_cast<ExRootTreeReader&>(TreeReader).UseBranch("EFlowMuon");
  GenJetClonesArray = const_cast<ExRootTreeReader&>(TreeReader).UseBranch("GenJet");
  ScalarHtClonesArray = const_cast<ExRootTreeReader&>(TreeReader).UseBranch("ScalarHT");

}

void hanalysis::hpgs::HClonesArray::GetBranches(ExRootTreeReader &TreeReader)
{

  Print(kNotification, "Get Branches");
  tree_reader_ = &TreeReader;

  PhotonClonesArray = const_cast<ExRootTreeReader&>(TreeReader).UseBranch("Photon");
  ElectronClonesArray = const_cast<ExRootTreeReader&>(TreeReader).UseBranch("Electron");
  MuonClonesArray = const_cast<ExRootTreeReader&>(TreeReader).UseBranch("Muon");
  JetClonesArray = const_cast<ExRootTreeReader&>(TreeReader).UseBranch("Jet");
  MissingEtClonesArray = const_cast<ExRootTreeReader&>(TreeReader).UseBranch("MissingET");
  TauClonesArray = const_cast<ExRootTreeReader&>(TreeReader).UseBranch("Tau");

}

void hanalysis::hparton::HClonesArray::GetBranches(ExRootTreeReader &TreeReader)
{

  Print(kNotification, "Get Branches");
  tree_reader_ = &TreeReader;

  ParticleClonesArray = const_cast<ExRootTreeReader&>(TreeReader).UseBranch("Particle");

}

