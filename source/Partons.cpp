# include "Partons.hh"
# include "Predicate.hh"

analysis::Partons::Partons()
{
    Print(kNotification,"Constructor");
}

void analysis::Partons::NewEvent(const ClonesArrays &clones_arrays) {
    Print(kInformation,"New event");
    analysis::FourVector::NewEvent(clones_arrays);
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
    GeneratorJets.clear();
}

Vectors analysis::Partons::GetLeptonLorentzVectors()
{
    Print(kInformation,"LeptonVector");
    GotParticles = GetParticles();
    Vectors LeptonVectors;
    LeptonVectors = ElectronVectors;
    LeptonVectors.insert(LeptonVectors.end(), MuonVectors.begin(), MuonVectors.end());
    std::sort(LeptonVectors.begin(), LeptonVectors.end(), SortByPt());
    Print(kInformation,"Lepton Particle",LeptonVectors.size());
    return LeptonVectors;
}

Vectors analysis::Partons::GetAntiLeptonVectors()
{
    Print(kInformation,"AntiLeptonVector");
    GotParticles = GetParticles();
    Vectors AntiLeptonVectors;
    AntiLeptonVectors = AntiElectronVectors;
    AntiLeptonVectors.insert(AntiLeptonVectors.end(), AntiMuonVectors.begin(), AntiMuonVectors.end());
    std::sort(AntiLeptonVectors.begin(), AntiLeptonVectors.end(), SortByPt());
    Print(kInformation,"Anti Lepton Particle",AntiLeptonVectors.size());
    return AntiLeptonVectors;
}

Jets analysis::Partons::GetLeptonJets()
{
    Print(kInformation,"LeptonVector");
    GotParticles = GetParticles();
    Jets LeptonJets;
    LeptonJets = ElectronJets;
    LeptonJets.insert(LeptonJets.end(), MuonJets.begin(), MuonJets.end());
    std::sort(LeptonJets.begin(), LeptonJets.end(), SortJetByPt());
    Print(kInformation,"Lepton Particle",LeptonJets.size());
    return LeptonJets;
}

Jets analysis::Partons::GetAntiLeptonJets()
{
    Print(kInformation,"AntiLeptonVector");
    GotParticles = GetParticles();
    Jets AntiLeptonJets;
    AntiLeptonJets = AntiElectronJets;
    AntiLeptonJets.insert(AntiLeptonJets.end(), AntiMuonJets.begin(), AntiMuonJets.end());
    std::sort(AntiLeptonJets.begin(), AntiLeptonJets.end(), SortJetByPt());
    Print(kInformation,"Anti Lepton Particle",AntiLeptonJets.size());
    return AntiLeptonJets;
}
