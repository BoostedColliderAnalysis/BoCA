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
    
    ElectronVector.clear();
    
    MuonVector.clear();
    
    AntiElectronVector.clear();
    
    AntiMuonVector.clear();
    
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

    TotalVector = ElectronVector;
    TotalVector.insert(TotalVector.end(), MuonVector.begin(), MuonVector.end());

    sort(TotalVector.begin(), TotalVector.end(), SortByPt());
    
    int TotalVectorSum = TotalVector.size();
    Print(2,"Lepton Particle",TotalVectorSum);

    return (TotalVector);


}

vector<TLorentzVector> HParticle::AntiLeptonVector()
{
    
    Print(2,"AntiLeptonVector");
    
    vector<TLorentzVector> TotalVector;

    TotalVector = AntiElectronVector;
    TotalVector.insert(TotalVector.end(), AntiMuonVector.begin(), AntiMuonVector.end());

    sort(TotalVector.begin(), TotalVector.end(), SortByPt());
    
    int TotalVectorSum = TotalVector.size();
    Print(2,"Anti Lepton Particle",TotalVectorSum);
    
    return (TotalVector);


}
