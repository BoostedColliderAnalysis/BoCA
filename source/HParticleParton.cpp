# include "HParticleParton.hh"

hparton::HParticle::HParticle()
{

    Print(HNotification, "Constructor");

//     Debug =5;

}

hparton::HParticle::~HParticle()
{

    Print(HNotification, "Destructor");

}

bool hparton::HParticle::GetParticles()
{

    Print(HInformation, "Get Particles", ClonesArrays->GetParticleSum());

    for (const int ParticleNumber : HRange(ClonesArrays->GetParticleSum())) {

        TRootLHEFParticle *ParticleClone = (TRootLHEFParticle *) ClonesArrays->GetParticle(ParticleNumber);

        int ParticleStatus = ParticleClone->Status;
        Print(HDetailed, "Particles Status", ParticleStatus);

        int ParticleID = ParticleClone->PID;
        Print(HDetailed, "Particles ID", ParticleID);

        if (ParticleStatus == StableParticle) {

            if (std::abs(ParticleID) == ElectronId) {

                TLorentzVector ElectronVector = GetLorentzVector(ParticleClone);

                if (ParticleID > 0) {

                    ElectronVectors.push_back(ElectronVector);
                    Print(HDebug, "Electron");

                } else if (ParticleID < 0) {

                    AntiElectronVectors.push_back(ElectronVector);
                    Print(HDebug, "Anti Electron");

                }

            } // Electrons

            if (std::abs(ParticleID) == MuonId) {

                TLorentzVector MuonVector = GetLorentzVector(ParticleClone);

                if (ParticleID > 0) {

                    MuonVectors.push_back(MuonVector);
                    Print(HDebug, "Muon");

                } else if (ParticleID < 0) {

                    AntiMuonVectors.push_back(MuonVector);
                    Print(HDebug, "Anti Muon");

                }

            } // Muons

            if (std::abs(ParticleID) == BottomId) {

                fastjet::PseudoJet BottomJet = GetPseudoJet(ParticleClone);

                BottomJets.push_back(BottomJet);
                Print(HDebug, "Bottom");

            } // bottoms

            if (std::abs(ParticleID) == TopId) {

                TLorentzVector TopVector = GetLorentzVector(ParticleClone);
                fastjet::PseudoJet TopJet = GetPseudoJet(ParticleClone);
                TopJets.push_back(TopJet);

                if (ParticleID > 0) {

                    TopVectors.push_back(TopVector);
                    Print(HDebug, "Top");

                } else if (ParticleID < 0) {

                    AntiTopVector.push_back(TopVector);
                    Print(HDebug, "Anti Top");

                }


            } // top

        }



        if (ParticleStatus == UnstableParticle) {

            if (std::abs(ParticleID) == CharmId) {

                fastjet::PseudoJet CharmJet = GetPseudoJet(ParticleClone);

                CharmJets.push_back(CharmJet);
                Print(HDebug, "Charm");

            } // charms

//             if (std::abs(ParticleID) == 5) {
//
//                 fastjet::PseudoJet JetCandidate = GetPseudoJetPt(ParticleClone);
//
//                 BottomJetVector.push_back(JetCandidate);
//                 Print(HDebug,"Bottom");
//
//             } // bottoms

            if (std::abs(ParticleID) == CpvHiggsId) {

                fastjet::PseudoJet HiggsJet = GetPseudoJet(ParticleClone);

                HiggsJets.push_back(HiggsJet);
                Print(HDebug, "CPV Higgs");

            } // cp Higgs

        }



        if (ParticleStatus == GeneratorParticle) {



            if (std::abs(ParticleID) == HeavyHiggsId) {

                fastjet::PseudoJet HiggsJet = GetPseudoJet(ParticleClone);

                HiggsJets.push_back(HiggsJet);
                Print(HDebug, "Heavy CPV Higgs");

            } // heavy higgs

        }

    }

    return 1;

}
