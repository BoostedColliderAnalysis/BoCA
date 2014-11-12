# include "HParticleParton.hh"

hparton::HParticle::HParticle()
{

    Print(1, "Constructor");

//     Debug =5;

}

hparton::HParticle::~HParticle()
{

    Print(1, "Destructor");

}

bool hparton::HParticle::GetParticles()
{

    Print(2, "Get Particles", ClonesArrays->GetParticleSum());

    for (const int ParticleNumber : HRange(ClonesArrays->GetParticleSum())) {

        TRootLHEFParticle *ParticleClone = (TRootLHEFParticle *) ClonesArrays->GetParticle(ParticleNumber);

        int ParticleStatus = ParticleClone->Status;
        Print(4, "Particles Status", ParticleStatus);

        int ParticleID = ParticleClone->PID;
        Print(4, "Particles ID", ParticleID);

        if (ParticleStatus == Stable) {

            if (std::abs(ParticleID) == ElectronId) {

                TLorentzVector ElectronParticle = GetLorentzVector(ParticleClone);

                if (ParticleID > 0) {

                    ElectronLorentzVectors.push_back(ElectronParticle);
                    Print(3, "Electron");

                } else if (ParticleID < 0) {

                    AntiElectronLorentzVectors.push_back(ElectronParticle);
                    Print(3, "Anti Electron");

                }

            } // Electrons

            if (std::abs(ParticleID) == MuonId) {

                TLorentzVector MuonParticle = GetLorentzVector(ParticleClone);

                if (ParticleID > 0) {

                    MuonLorentzVectors.push_back(MuonParticle);
                    Print(3, "Muon");

                } else if (ParticleID < 0) {

                    AntiMuonLorentzVectors.push_back(MuonParticle);
                    Print(3, "Anti Muon");

                }

            } // Muons

            if (std::abs(ParticleID) == BottomId) {

                PseudoJet JetCandidate = GetPseudoJet(ParticleClone);

                BottomJetVector.push_back(JetCandidate);
                Print(3, "Bottom");

            } // bottoms

            if (std::abs(ParticleID) == TopId) {

                TLorentzVector TopQuark = GetLorentzVector(ParticleClone);
                PseudoJet TopJet = GetPseudoJet(ParticleClone);
                TopJetVector.push_back(TopJet);

                if (ParticleID > 0) {

                    TopVector.push_back(TopQuark);
                    Print(3, "Top");

                } else if (ParticleID < 0) {

                    AntiTopVector.push_back(TopQuark);
                    Print(3, "Anti Top");

                }


            } // top

        }



        if (ParticleStatus == Unstable) {

            if (std::abs(ParticleID) == CharmId) {

                PseudoJet JetCandidate = GetPseudoJet(ParticleClone);

                CharmJetVector.push_back(JetCandidate);
                Print(3, "Charm");

            } // charms

//             if (std::abs(ParticleID) == 5) {
//
//                 PseudoJet JetCandidate = GetPseudoJetPt(ParticleClone);
//
//                 BottomJetVector.push_back(JetCandidate);
//                 Print(3,"Bottom");
//
//             } // bottoms

            if (std::abs(ParticleID) == CpvHiggsId) {

                PseudoJet HiggsParticle = GetPseudoJet(ParticleClone);

                HiggsJetVector.push_back(HiggsParticle);
                Print(3, "CPV Higgs");

            } // cp Higgs

        }



        if (ParticleStatus == Undefined) {



            if (std::abs(ParticleID) == HeavyHiggsId) {

                PseudoJet HiggsParticle = GetPseudoJet(ParticleClone);

                HiggsJetVector.push_back(HiggsParticle);
                Print(3, "Heavy CPV Higgs");

            } // heavy higgs

        }

    }

    return 1;

}
