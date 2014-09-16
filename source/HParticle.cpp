# include "HParticle.hh"

HParticle::HParticle()
{
    
    Print(0,"Constructor");

}

HParticle::~HParticle()
{
    
    Print(0,"Destructor");

}

void HParticle::NewEvent(){
    
    Print(1,"New Event");
    
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


bool HParticle::GetParticles(HClonesArrayBase *ImportClonesArrays)
{
    
    Print(1,"Get Particles");

    ClonesArrays = ImportClonesArrays;
    int ParticleSum = ClonesArrays->ParticleClonesArray->GetEntriesFast();
    
    Print(2,"Number of Particles",ParticleSum);
    
    for (int ParticleNumber = 0; ParticleNumber < ParticleSum; ParticleNumber++) {

        CParticle *GenParticleClone = (CParticle *) ClonesArrays->ParticleClonesArray->At(ParticleNumber);

        int ParticleStatus = GenParticleClone->Status;
        Print(3,"Particles Status",ParticleStatus);

        int ParticleID = GenParticleClone->PID;
        Print(3,"Particles ID",ParticleID);

        if (ParticleStatus == 1) {

            if (abs(ParticleID) == 11) {

                TLorentzVector ElectronParticle = GetLorentzVector(GenParticleClone);

                if (ParticleID > 0) {

                    ElectronVector.push_back(ElectronParticle);
                    Print(2,"Electron");

                } else if (ParticleID < 0) {

                    AntiElectronVector.push_back(ElectronParticle);
                    Print(2,"Anti Electron");

                }

            } // Electrons

            if (abs(ParticleID) == 13) {

                TLorentzVector MuonParticle = GetLorentzVector(GenParticleClone);

                if (ParticleID > 0) {

                    MuonVector.push_back(MuonParticle);
                    Print(2,"Muon");

                } else if (ParticleID < 0) {

                    AntiMuonVector.push_back(MuonParticle);
                    Print(2,"Anti Muon");

                }

            } // Muons

        }



        if (ParticleStatus == 2) {

            if (abs(ParticleID) == 4) {

                PseudoJet JetCandidate = GetPseudoJet(GenParticleClone);

                CharmJetVector.push_back(JetCandidate);
                Print(2,"Charm");

            } // charms

            if (abs(ParticleID) == 5) {

                PseudoJet JetCandidate = GetPseudoJet(GenParticleClone);

                BottomJetVector.push_back(JetCandidate);
                Print(2,"Bottom");

            } // bottoms
            
            if (abs(ParticleID)==5000000){
             
                PseudoJet HiggsParticle = GetPseudoJet(GenParticleClone);
                
                HiggsJetVector.push_back(HiggsParticle);
                Print(2,"CPV Higgs");
                
            } // cp Higgs

        }



        if (ParticleStatus == 3) {

            if (abs(ParticleID) == 6) {

                TLorentzVector TopQuark = GetLorentzVector(GenParticleClone);
                PseudoJet TopJet = GetPseudoJet(GenParticleClone);
                TopJetVector.push_back(TopJet);
                
                if (ParticleID > 0) {

                    TopVector.push_back(TopQuark);
                Print(2,"Top");

                } else if (ParticleID < 0) {

                    AntiTopVector.push_back(TopQuark);
                    Print(2,"Anti Top");

                }


            } // top
            
            if (abs(ParticleID)==0){
                
                PseudoJet HiggsParticle = GetPseudoJet(GenParticleClone);
                
                HiggsJetVector.push_back(HiggsParticle);
                Print(2,"Heavy CPV Higgs");
                
            } // heavy higgs

        }

    }

    return 1;
    
}


TLorentzVector HParticle::GetLorentzVector(CParticle *ParticleClone)
{
    
    Print(2,"Get Lorentz Vector");
    
    float ParticlePt = ParticleClone->PT;
    float ParticleEta = ParticleClone->Eta;
    float ParticlePhi = ParticleClone->Phi;
    float ParticleE = ParticleClone->E;
    TLorentzVector LorentzVector;
    LorentzVector.SetPtEtaPhiE(ParticlePt, ParticleEta, ParticlePhi, ParticleE);

    return (LorentzVector);

}

PseudoJet HParticle::GetPseudoJet(CParticle *ParticleClone)
{
    
    Print(2,"Get Pseudo Jet");

    float ParticlePt = ParticleClone->PT;
    float ParticleEta = ParticleClone->Eta;
    float ParticlePhi = ParticleClone->Phi;

    PseudoJet Jet = PseudoJet(ParticlePt * cos(ParticlePhi), ParticlePt * sin(ParticlePhi), ParticlePt * sinh(ParticleEta), ParticlePt * cosh(ParticleEta));

    return (Jet);

}

vector<TLorentzVector> HParticle::LeptonVector()
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

vector<TLorentzVector> HParticle::AntiLeptonVector()
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

