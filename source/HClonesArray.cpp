# include "HClonesArray.hh"

HClonesArray::HClonesArray()
{

    Print(0, "Constructor");
    
}

HClonesArray::~HClonesArray()
{

    Print(0, "Destructor");

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

void HClonesArray::ResetBranches()
{

    Print(0, "Reset Branches");

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

    Print(0,"Branches reset");
}

void HClonesArrayDelphes::UseBranches(ExRootTreeReader *TreeReader)
{
    
    Print(0, "Use Branches");
    
    ParticleClonesArray = TreeReader->UseBranch("Particle");
    PhotonClonesArray = TreeReader->UseBranch("Photon");
    ElectronClonesArray = TreeReader->UseBranch("Electron");
    MuonClonesArray = TreeReader->UseBranch("Muon");
    JetClonesArray = TreeReader->UseBranch("Jet");
    MissingEtClonesArray = TreeReader->UseBranch("MissingET");
    TrackClonesArray = TreeReader->UseBranch("Track");
    TowerClonesArray = TreeReader->UseBranch("Tower");
    EFlowTrackClonesArray = TreeReader->UseBranch("EFlowTrack");
    EFlowPhotonClonesArray = TreeReader->UseBranch("EFlowPhoton");
    EFlowNeutralHadronClonesArray = TreeReader->UseBranch("EFlowNeutralHadron");
//     EFlowMuonClonesArray = TreeReader->UseBranch("EFlowMuon");
    GenJetClonesArray = TreeReader->UseBranch("GenJet");
    ScalarHtClonesArray = TreeReader->UseBranch("ScalarHT");
    
}

void HClonesArraySnowmass::UseBranches(ExRootTreeReader *TreeReader)
{
    
    Print(0, "Use Branches");
    
    ParticleClonesArray = TreeReader->UseBranch("Particle");
    PhotonClonesArray = TreeReader->UseBranch("Photon");
    ElectronClonesArray = TreeReader->UseBranch("Electron");
    MuonClonesArray = TreeReader->UseBranch("Muon");
    JetClonesArray = TreeReader->UseBranch("Jet");
    MissingEtClonesArray = TreeReader->UseBranch("MissingET");
    EFlowTrackClonesArray = TreeReader->UseBranch("EFlowTrack");
    EFlowPhotonClonesArray = TreeReader->UseBranch("EFlowPhoton");
    EFlowNeutralHadronClonesArray = TreeReader->UseBranch("EFlowNeutralHadron");
    Print(1,"We have EFlow Branches");
    EFlowMuonClonesArray = TreeReader->UseBranch("EFlowMuon");
    GenJetClonesArray = TreeReader->UseBranch("GenJet");
    ScalarHtClonesArray = TreeReader->UseBranch("ScalarHT");
    
}

void HClonesArrayPgs::UseBranches(ExRootTreeReader *TreeReader)
{
    
    Print(0, "Use Branches");
        
    PhotonClonesArray = TreeReader->UseBranch("Photon");
    ElectronClonesArray = TreeReader->UseBranch("Electron");
    MuonClonesArray = TreeReader->UseBranch("Muon");
    JetClonesArray = TreeReader->UseBranch("Jet");
    MissingEtClonesArray = TreeReader->UseBranch("MissingET");   
    TauClonesArray = TreeReader->UseBranch("Tau");
    
}

void HClonesArrayParton::UseBranches(ExRootTreeReader *TreeReader)
{
    
    Print(0, "Use Branches");

    ParticleClonesArray = TreeReader->UseBranch("Particle");
    
}