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
    
    AntiMuonLorentzVectors.clear();
    
    BottomJetVector.clear();
    
    TopJetVector.clear();
    
    HiggsJetVector.clear();
    
    CharmJetVector.clear();
    
    ParticleJetVector.clear();
    
}

vector<TLorentzVector> HParticle::LeptonVector()
{
    
    Print(2,"LeptonVector");
    
    vector<TLorentzVector> TotalVector;

    TotalVector = ElectronLorentzVectors;
    TotalVector.insert(TotalVector.end(), MuonLorentzVectors.begin(), MuonLorentzVectors.end());

    sort(TotalVector.begin(), TotalVector.end(), SortByPt());
    
    int TotalVectorSum = TotalVector.size();
    Print(2,"Lepton Particle",TotalVectorSum);

    return (TotalVector);


}

vector<TLorentzVector> HParticle::AntiLeptonVector()
{
    
    Print(2,"AntiLeptonVector");
    
    vector<TLorentzVector> TotalVector;

    TotalVector = AntiElectronLorentzVectors;
    TotalVector.insert(TotalVector.end(), AntiMuonLorentzVectors.begin(), AntiMuonLorentzVectors.end());

    sort(TotalVector.begin(), TotalVector.end(), SortByPt());
    
    int TotalVectorSum = TotalVector.size();
    Print(2,"Anti Lepton Particle",TotalVectorSum);
    
    return (TotalVector);


}
