# include "HParticleParton.hh"

HParticleParton::HParticleParton()
{
    
    Print(1,"Constructor");

//     Debug =5;
    
}

HParticleParton::~HParticleParton()
{
    
    Print(1,"Destructor");

}

bool HParticleParton::GetParticles()
{
    
    Print(2,"Get Particles");

    int ParticleSum = ClonesArrays->ParticleClonesArray->GetEntriesFast();
    
    Print(3,"Number of Particles",ParticleSum);
    
    for (int ParticleNumber = 0; ParticleNumber < ParticleSum; ++ParticleNumber) {

        TRootLHEFParticle *ParticleClone = (TRootLHEFParticle *) ClonesArrays->ParticleClonesArray->At(ParticleNumber);

        int ParticleStatus = ParticleClone->Status;
        Print(4,"Particles Status",ParticleStatus);

        int ParticleID = ParticleClone->PID;
        Print(4,"Particles ID",ParticleID);

        if (ParticleStatus == 1) {

            if (abs(ParticleID) == 11) {

                TLorentzVector ElectronParticle = GetLorentzVector(ParticleClone);

                if (ParticleID > 0) {

                    ElectronLorentzVectors.push_back(ElectronParticle);
                    Print(3,"Electron");

                } else if (ParticleID < 0) {

                    AntiElectronLorentzVectors.push_back(ElectronParticle);
                    Print(3,"Anti Electron");

                }

            } // Electrons

            if (abs(ParticleID) == 13) {

                TLorentzVector MuonParticle = GetLorentzVector(ParticleClone);

                if (ParticleID > 0) {

                    MuonLorentzVectors.push_back(MuonParticle);
                    Print(3,"Muon");

                } else if (ParticleID < 0) {

                    AntiMuonLorentzVectors.push_back(MuonParticle);
                    Print(3,"Anti Muon");

                }

            } // Muons
            
            if (abs(ParticleID) == 5) {
                
                PseudoJet JetCandidate = GetPseudoJet(ParticleClone);
                
                BottomJetVector.push_back(JetCandidate);
                Print(3,"Bottom");
                
            } // bottoms
            
            if (abs(ParticleID) == 6) {
                
                TLorentzVector TopQuark = GetLorentzVector(ParticleClone);
                PseudoJet TopJet = GetPseudoJet(ParticleClone);
                TopJetVector.push_back(TopJet);
                
                if (ParticleID > 0) {
                    
                    TopVector.push_back(TopQuark);
                    Print(3,"Top");
                    
                } else if (ParticleID < 0) {
                    
                    AntiTopVector.push_back(TopQuark);
                    Print(3,"Anti Top");
                    
                }
                
                
            } // top

        }



        if (ParticleStatus == 2) {

            if (abs(ParticleID) == 4) {

                PseudoJet JetCandidate = GetPseudoJet(ParticleClone);

                CharmJetVector.push_back(JetCandidate);
                Print(3,"Charm");

            } // charms

//             if (abs(ParticleID) == 5) {
// 
//                 PseudoJet JetCandidate = GetPseudoJetPt(ParticleClone);
// 
//                 BottomJetVector.push_back(JetCandidate);
//                 Print(3,"Bottom");
// 
//             } // bottoms
            
            if (abs(ParticleID)==5000000){
             
                PseudoJet HiggsParticle = GetPseudoJet(ParticleClone);
                
                HiggsJetVector.push_back(HiggsParticle);
                Print(3,"CPV Higgs");
                
            } // cp Higgs

        }



        if (ParticleStatus == 3) {


            
            if (abs(ParticleID)==0){
                
                PseudoJet HiggsParticle = GetPseudoJet(ParticleClone);
                
                HiggsJetVector.push_back(HiggsParticle);
                Print(3,"Heavy CPV Higgs");
                
            } // heavy higgs

        }

    }

    return 1;
    
}
