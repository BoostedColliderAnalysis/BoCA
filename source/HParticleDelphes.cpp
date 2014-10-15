# include "HParticleDelphes.hh"

HParticleDelphes::HParticleDelphes()
{

    Print(3, "Constructor");

//     Debug = 5;

}

HParticleDelphes::~HParticleDelphes()
{

    Print(3, "Destructor");

}


bool HParticleDelphes::GetParticles()
{

    Print(2, "Get Particles", ClonesArrays->ParticleSum());

    for (int ParticleNumber = 0; ParticleNumber < ClonesArrays->ParticleSum(); ++ParticleNumber) {

        const GenParticle *const ParticleClone = (GenParticle *) ClonesArrays->ParticleClonesArray->At(ParticleNumber);

        const int ParticleID = ParticleClone->PID;
        Print(4, "Particles ID", ParticleID);

        if (ParticleClone->Status == Stable) {
            Print(4, "Particles Status", "stable");

            if (abs(ParticleID) == ElectronId) {

                TLorentzVector ElectronLorentzVector = const_cast<GenParticle *>(ParticleClone)->P4();

                if (ParticleID > 0) {

                    ElectronLorentzVectors.push_back(ElectronLorentzVector);
                    Print(3, "Electron");

                } else if (ParticleID < 0) {

                    AntiElectronLorentzVectors.push_back(ElectronLorentzVector);
                    Print(3, "Anti Electron");

                }

            }

            if (abs(ParticleID) == MuonId) {

                if (ParticleID > 0) {

                    MuonLorentzVectors.push_back(const_cast<GenParticle *>(ParticleClone)->P4());
                    Print(3, "Muon");

                } else if (ParticleID < 0) {

                    AntiMuonLorentzVectors.push_back(const_cast<GenParticle *>(ParticleClone)->P4());
                    Print(3, "Anti Muon");

                }

            }

        }



        if (ParticleClone->Status == Unstable) {
            Print(4, "Particles Status", "unstable");

            if (abs(ParticleID) == CharmId) {

                CharmJetVector.push_back(GetPseudoJet(const_cast<GenParticle *>(ParticleClone)->P4()));
                Print(3, "Charm");

            }

            if (abs(ParticleID) == CpvHiggsId) {

                HiggsJetVector.push_back(GetPseudoJet(const_cast<GenParticle *>(ParticleClone)->P4()));
                Print(3, "CPV Higgs");

            }


            if (abs(ParticleID) == BottomId) {

                BottomJetVector.push_back(GetPseudoJet(const_cast<GenParticle *>(ParticleClone)->P4()));
                ParticleJetVector.push_back(GetPseudoJet(const_cast<GenParticle *>(ParticleClone)->P4()));
                ParticleJetVector.back().set_user_index(BottomId);

                Print(3, "Bottom");

            }


            if (abs(ParticleID) == HeavyHiggsId) {

                PseudoJet HiggsParticle = GetPseudoJet(const_cast<GenParticle *>(ParticleClone)->P4());

                HiggsJetVector.push_back(HiggsParticle);
                Print(3, "Heavy CPV Higgs");

                Print(0, "HeavyHiggs", ParticleClone->Status);
                if (ParticleClone->D1 != -1) Print(0, "Daughter1", ((GenParticle *) ClonesArrays->ParticleClonesArray->At(ParticleClone->D1))->PID);
                if (ParticleClone->D2 != -1) Print(0, "Daughter2", ((GenParticle *) ClonesArrays->ParticleClonesArray->At(ParticleClone->D2))->PID);

            }

        }



        if (ParticleClone->Status == Undefined) {
            Print(4, "Particles Status", "undefined");

            if (abs(ParticleID) == TopId) {

                TLorentzVector TopQuark = const_cast<GenParticle *>(ParticleClone)->P4();
                PseudoJet TopJet = GetPseudoJet(const_cast<GenParticle *>(ParticleClone)->P4());
                TopJet.set_user_index(TopId);

                TopJetVector.push_back(TopJet);
                ParticleJetVector.push_back(TopJet);

                if (ParticleID > 0) {

                    TopVector.push_back(TopQuark);
                    Print(3, "Top");

                } else if (ParticleID < 0) {

                    AntiTopVector.push_back(TopQuark);
                    Print(3, "Anti Top");

                }

            }

        }

    }

    return 1;

}

