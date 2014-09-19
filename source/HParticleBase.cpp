# include "HParticleBase.hh"

HParticleBase::HParticleBase()
{
    
    Print(0,"Constructor");

//     Debug =5;
    
}

HParticleBase::~HParticleBase()
{
    
    Print(0,"Destructor");

}

void HParticleBase::NewEvent(HClonesArrayBase *ImportClonesArrays){
    
    Print(1,"New Event");
    
    ClonesArrays = ImportClonesArrays;
    
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
    
}

vector<TLorentzVector> HParticleBase::LeptonVector()
{
    
    Print(1,"LeptonVector");
    
    vector<TLorentzVector> TotalVector;

    TotalVector = ElectronVector;
    TotalVector.insert(TotalVector.end(), MuonVector.begin(), MuonVector.end());

    sort(TotalVector.begin(), TotalVector.end(), SortByPt());
    
    int TotalVectorSum = TotalVector.size();
    Print(1,"Lepton Particle",TotalVectorSum);

    return (TotalVector);


}

vector<TLorentzVector> HParticleBase::AntiLeptonVector()
{
    
    Print(1,"AntiLeptonVector");
    
    vector<TLorentzVector> TotalVector;

    TotalVector = AntiElectronVector;
    TotalVector.insert(TotalVector.end(), AntiMuonVector.begin(), AntiMuonVector.end());

    sort(TotalVector.begin(), TotalVector.end(), SortByPt());
    
    int TotalVectorSum = TotalVector.size();
    Print(1,"Anti Lepton Particle",TotalVectorSum);
    
    return (TotalVector);


}

// vector<PseudoJet> HParticle::GetTops()
// {
//     
//     vector<TLorentzVector> TotalVector;
//     
//     TotalVector = TopVector;
//     TotalVector.insert(TotalVector.end(), AntiMuonVector.begin(), AntiMuonVector.end());
//     
//     sort(TotalVector.begin(), TotalVector.end(), SortByPt());
//     
//     
//     
//     if (Debug > 1) cout << TotalVector.size() << " truth level anti leptons" << endl;
//     return (TotalVector);
//     
//     return (Jet);
//     
// }

