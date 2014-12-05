# include "HParticle.hh"

hanalysis::HParticle::HParticle()
{

    Print(HNotification,"Constructor");

//     Debug =5;

}

hanalysis::HParticle::~HParticle()
{

    Print(HNotification,"Destructor");

}

void hanalysis::HParticle::NewEvent(const HClonesArray * const NewClonesArrays){

    Print(HInformation,"New Event");

//     ClonesArrays = NewClonesArrays;
    hanalysis::HFourVector::NewEvent(NewClonesArrays);

    GotParticles = 0;

    TopVectors.clear();

    AntiTopVector.clear();

    ElectronVectors.clear();

    MuonVectors.clear();

    AntiElectronVectors.clear();

    AntiMuonJets.clear();

    ElectronJets.clear();

    MuonJets.clear();

    AntiElectronJets.clear();

    AntiMuonJets.clear();

    BottomJets.clear();

    TopJets.clear();

    HiggsJets.clear();

    CharmJets.clear();

    ParticleJets.clear();
    
    NeutrinoJets.clear();

}

HVectors hanalysis::HParticle::GetLeptonLorentzVectors()
{

  Print(HInformation,"LeptonVector");

  GotParticles = GetParticles();

    HVectors LeptonVectors;

    LeptonVectors = ElectronVectors;
    LeptonVectors.insert(LeptonVectors.end(), MuonVectors.begin(), MuonVectors.end());

    std::sort(LeptonVectors.begin(), LeptonVectors.end(), SortByPt());

    Print(HInformation,"Lepton Particle",LeptonVectors.size());

    return LeptonVectors;


}

HVectors hanalysis::HParticle::GetAntiLeptonVectors()
{

  Print(HInformation,"AntiLeptonVector");

  GotParticles = GetParticles();

    HVectors AntiLeptonVectors;

    AntiLeptonVectors = AntiElectronVectors;
    AntiLeptonVectors.insert(AntiLeptonVectors.end(), AntiMuonVectors.begin(), AntiMuonVectors.end());

    std::sort(AntiLeptonVectors.begin(), AntiLeptonVectors.end(), SortByPt());

    Print(HInformation,"Anti Lepton Particle",AntiLeptonVectors.size());

    return AntiLeptonVectors;


}

HJets hanalysis::HParticle::GetLeptonJets()
{

  Print(HInformation,"LeptonVector");

  GotParticles = GetParticles();

    HJets LeptonJets;

    LeptonJets = ElectronJets;
    LeptonJets.insert(LeptonJets.end(), MuonJets.begin(), MuonJets.end());

    std::sort(LeptonJets.begin(), LeptonJets.end(), SortJetByPt());

    Print(HInformation,"Lepton Particle",LeptonJets.size());

    return LeptonJets;


}

HJets hanalysis::HParticle::GetAntiLeptonJets()
{

  Print(HInformation,"AntiLeptonVector");

  GotParticles = GetParticles();

    HJets AntiLeptonJets;

    AntiLeptonJets = AntiElectronJets;
    AntiLeptonJets.insert(AntiLeptonJets.end(), AntiMuonJets.begin(), AntiMuonJets.end());

    std::sort(AntiLeptonJets.begin(), AntiLeptonJets.end(), SortJetByPt());

    Print(HInformation,"Anti Lepton Particle",AntiLeptonJets.size());

    return AntiLeptonJets;


}
