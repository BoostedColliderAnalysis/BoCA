# include "HParticleDelphes.hh"

HParticleDelphes::HParticleDelphes()
{

    Print(0, "Constructor");

}

HParticleDelphes::~HParticleDelphes()
{

    Print(0, "Destructor");

}

bool HParticleDelphes::GetParticles()
{

    Print(1, "Get Particles");

    int ParticleSum = ClonesArrays->ParticleClonesArray->GetEntriesFast();

    Print(2, "Number of Particles", ParticleSum);

    for (int ParticleNumber = 0; ParticleNumber < ParticleSum; ++ParticleNumber) {

        GenParticle *GenParticleClone = (GenParticle *) ClonesArrays->ParticleClonesArray->At(ParticleNumber);

        int ParticleStatus = GenParticleClone->Status;
        Print(3, "Particles Status", ParticleStatus);

        int ParticleID = GenParticleClone->PID;
        Print(3, "Particles ID", ParticleID);

        if (ParticleStatus == 1) {

            if (abs(ParticleID) == 11) {

                TLorentzVector ElectronParticle = GetLorentzVector(GenParticleClone);

                if (ParticleID > 0) {

                    ElectronVector.push_back(ElectronParticle);
                    Print(2, "Electron");

                } else if (ParticleID < 0) {

                    AntiElectronVector.push_back(ElectronParticle);
                    Print(2, "Anti Electron");

                }

            } // Electrons

            if (abs(ParticleID) == 13) {

                TLorentzVector MuonParticle = GetLorentzVector(GenParticleClone);

                if (ParticleID > 0) {

                    MuonVector.push_back(MuonParticle);
                    Print(2, "Muon");

                } else if (ParticleID < 0) {

                    AntiMuonVector.push_back(MuonParticle);
                    Print(2, "Anti Muon");

                }

            } // Muons

        }



        if (ParticleStatus == 2) {

            if (abs(ParticleID) == 4) {

                PseudoJet JetCandidate = GetPseudoJetPt(GenParticleClone);

                CharmJetVector.push_back(JetCandidate);
                Print(2, "Charm");

            } // charms

            if (abs(ParticleID) == 5) {

                PseudoJet JetCandidate = GetPseudoJetPt(GenParticleClone);

                BottomJetVector.push_back(JetCandidate);
                Print(2, "Bottom");

            } // bottoms

            if (abs(ParticleID) == 5000000) {

                PseudoJet HiggsParticle = GetPseudoJetPt(GenParticleClone);

                HiggsJetVector.push_back(HiggsParticle);
                Print(2, "CPV Higgs");

            } // cp Higgs

        }



        if (ParticleStatus == 3) {

            if (abs(ParticleID) == 6) {

                TLorentzVector TopQuark = GetLorentzVector(GenParticleClone);
                PseudoJet TopJet = GetPseudoJetPt(GenParticleClone);
                TopJetVector.push_back(TopJet);

                if (ParticleID > 0) {

                    TopVector.push_back(TopQuark);
                    Print(2, "Top");

                } else if (ParticleID < 0) {

                    AntiTopVector.push_back(TopQuark);
                    Print(2, "Anti Top");

                }


            } // top

            if (abs(ParticleID) == 0) {

                PseudoJet HiggsParticle = GetPseudoJetPt(GenParticleClone);

                HiggsJetVector.push_back(HiggsParticle);
                Print(2, "Heavy CPV Higgs");

            } // heavy higgs

        }

    }

    return 1;

}