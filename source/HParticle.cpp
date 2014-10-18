# include "HParticle.hh"

HParticle::HParticle()
{
    
    Print(1,"Constructor");

//     Debug =5;
    
}

HParticle::~HParticle()
{
    
    Print(1,"Destructor");

}

void HParticle::NewEvent(const HClonesArray * const NewClonesArrays){
    
    Print(2,"New Event");
    
    ClonesArrays = NewClonesArrays;
    
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

vector<TLorentzVector> HParticle::GetLeptonLorentzVectors()
{
    
    Print(2,"LeptonVector");
    
    vector<TLorentzVector> TotalVector;

    TotalVector = ElectronLorentzVectors;
    TotalVector.insert(TotalVector.end(), MuonLorentzVectors.begin(), MuonLorentzVectors.end());

    sort(TotalVector.begin(), TotalVector.end(), SortByPt());
    
    Print(2,"Lepton Particle",TotalVector.size());

    return (TotalVector);


}

vector<TLorentzVector> HParticle::GetAntiLeptonLorentzVectors()
{
    
    Print(2,"AntiLeptonVector");
    
    vector<TLorentzVector> TotalVector;

    TotalVector = AntiElectronLorentzVectors;
    TotalVector.insert(TotalVector.end(), AntiMuonLorentzVectors.begin(), AntiMuonLorentzVectors.end());

    sort(TotalVector.begin(), TotalVector.end(), SortByPt());
    
    Print(2,"Anti Lepton Particle",TotalVector.size());
    
    return (TotalVector);


}

vector<PseudoJet> HParticle::GetLeptonJets()
{
    
    Print(2,"LeptonVector");
    
    vector<PseudoJet> TotalVector;
    
    TotalVector = ElectronJets;
    TotalVector.insert(TotalVector.end(), MuonJets.begin(), MuonJets.end());
    
    sort(TotalVector.begin(), TotalVector.end(), SortJetByPt());
    
    Print(2,"Lepton Particle",TotalVector.size());
    
    return (TotalVector);
    
    
}

vector<PseudoJet> HParticle::GetAntiLeptonJets()
{
    
    Print(2,"AntiLeptonVector");
    
    vector<PseudoJet> TotalVector;
    
    TotalVector = AntiElectronJets;
    TotalVector.insert(TotalVector.end(), AntiMuonJets.begin(), AntiMuonJets.end());
    
    sort(TotalVector.begin(), TotalVector.end(), SortJetByPt());
    
    Print(2,"Anti Lepton Particle",TotalVector.size());
    
    return (TotalVector);
    
    
}
