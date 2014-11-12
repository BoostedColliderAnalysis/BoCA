# include "HParticle.hh"

hanalysis::HParticle::HParticle()
{

    Print(1,"Constructor");

//     Debug =5;

}

hanalysis::HParticle::~HParticle()
{

    Print(1,"Destructor");

}

void hanalysis::HParticle::NewEvent(const HClonesArray * const NewClonesArrays){

    Print(2,"New Event");

    ClonesArrays = NewClonesArrays;

    GotParticles = 0;

    TopVector.clear();

    AntiTopVector.clear();

    ElectronLorentzVectors.clear();

    MuonLorentzVectors.clear();

    AntiElectronLorentzVectors.clear();

    AntiMuonJets.clear();

    ElectronJets.clear();

    MuonJets.clear();

    AntiElectronJets.clear();

    AntiMuonJets.clear();

    BottomJetVector.clear();

    TopJetVector.clear();

    HiggsJetVector.clear();

    CharmJetVector.clear();

    ParticleJetVector.clear();

}

HVectors hanalysis::HParticle::GetLeptonLorentzVectors()
{

  Print(2,"LeptonVector");

  GotParticles = GetParticles();

    HVectors TotalVector;

    TotalVector = ElectronLorentzVectors;
    TotalVector.insert(TotalVector.end(), MuonLorentzVectors.begin(), MuonLorentzVectors.end());

    sort(TotalVector.begin(), TotalVector.end(), SortByPt());

    Print(2,"Lepton Particle",TotalVector.size());

    return (TotalVector);


}

HVectors hanalysis::HParticle::GetAntiLeptonLorentzVectors()
{

  Print(2,"AntiLeptonVector");

  GotParticles = GetParticles();

    HVectors TotalVector;

    TotalVector = AntiElectronLorentzVectors;
    TotalVector.insert(TotalVector.end(), AntiMuonLorentzVectors.begin(), AntiMuonLorentzVectors.end());

    sort(TotalVector.begin(), TotalVector.end(), SortByPt());

    Print(2,"Anti Lepton Particle",TotalVector.size());

    return (TotalVector);


}

HJets hanalysis::HParticle::GetLeptonJets()
{

  Print(2,"LeptonVector");

  GotParticles = GetParticles();

    HJets TotalVector;

    TotalVector = ElectronJets;
    TotalVector.insert(TotalVector.end(), MuonJets.begin(), MuonJets.end());

    sort(TotalVector.begin(), TotalVector.end(), SortJetByPt());

    Print(2,"Lepton Particle",TotalVector.size());

    return (TotalVector);


}

HJets hanalysis::HParticle::GetAntiLeptonJets()
{

  Print(2,"AntiLeptonVector");

  GotParticles = GetParticles();

    HJets TotalVector;

    TotalVector = AntiElectronJets;
    TotalVector.insert(TotalVector.end(), AntiMuonJets.begin(), AntiMuonJets.end());

    sort(TotalVector.begin(), TotalVector.end(), SortJetByPt());

    Print(2,"Anti Lepton Particle",TotalVector.size());

    return (TotalVector);


}
