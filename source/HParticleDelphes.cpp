# include "HParticleDelphes.hh"

hdelphes::HParticle ::HParticle()
{

    Print(HDebug, "Constructor");

//     Debug = 5;

}

hdelphes::HParticle ::~HParticle()
{

    Print(HDebug, "Destructor");

}


bool hdelphes::HParticle ::GetParticles()
{

    Print(HInformation, "Get Particles", ClonesArrays->GetParticleSum());

    for (const int ParticleNumber : HRange(ClonesArrays->GetParticleSum())) {

        const GenParticle *const ParticleClone = (GenParticle *) ClonesArrays->GetParticle(ParticleNumber);

        const int ParticleID = ParticleClone->PID;
        Print(HDetailed, "Particles ID", ParticleID);

        if (ParticleClone->Status == StableParticle) {
            Print(HDetailed, "Particles Status", "stable");

            if (std::abs(ParticleID) == ElectronId) {

                const TLorentzVector ElectronVector = const_cast<GenParticle *>(ParticleClone)->P4();
                const fastjet::PseudoJet ElectronJet = GetPseudoJet(ElectronVector);

                if (ParticleID > 0) {

                    ElectronVectors.push_back(ElectronVector);
                    ElectronJets.push_back(ElectronJet);
                    Print(HDebug, "Electron");

                } else if (ParticleID < 0) {

                    AntiElectronVectors.push_back(ElectronVector);
                    AntiElectronJets.push_back(ElectronJet);
                    Print(HDebug, "Anti Electron");

                }

            }

            if (std::abs(ParticleID) == MuonId) {

                const TLorentzVector MuonVector = const_cast<GenParticle *>(ParticleClone)->P4();
                const fastjet::PseudoJet MuonJet = GetPseudoJet(MuonVector);

                if (ParticleID > 0) {

                    MuonVectors.push_back(MuonVector);
                    MuonJets.push_back(MuonJet);
                    Print(HDebug, "Muon");

                } else if (ParticleID < 0) {

                    AntiMuonVectors.push_back(MuonVector);
                    AntiMuonJets.push_back(MuonJet);
                    Print(HDebug, "Anti Muon");

                }

            }

        }



        if (ParticleClone->Status == UnstableParticle) {
            Print(HDetailed, "Particles Status", "unstable");

            if (std::abs(ParticleID) == CharmId) {

                CharmJets.push_back(GetPseudoJet(const_cast<GenParticle *>(ParticleClone)->P4()));
                Print(HDebug, "Charm");

            }

            if (std::abs(ParticleID) == CpvHiggsId) {

                HiggsJets.push_back(GetPseudoJet(const_cast<GenParticle *>(ParticleClone)->P4()));
                Print(HDebug, "CPV Higgs");

            }


            if (std::abs(ParticleID) == BottomId) {

                BottomJets.push_back(GetPseudoJet(const_cast<GenParticle *>(ParticleClone)->P4()));
                ParticleJets.push_back(GetPseudoJet(const_cast<GenParticle *>(ParticleClone)->P4()));
                ParticleJets.back().set_user_index(BottomId);

                Print(HDebug, "Bottom");

            }


            if (std::abs(ParticleID) == HeavyHiggsId) {

                const fastjet::PseudoJet HiggsParticle = GetPseudoJet(const_cast<GenParticle *>(ParticleClone)->P4());

                HiggsJets.push_back(HiggsParticle);
                Print(HDebug, "Heavy CPV Higgs");

                Print(HError, "HeavyHiggs", ParticleClone->Status);
                if (ParticleClone->D1 != -1) Print(HError, "Daughter1", ((GenParticle *) ClonesArrays->GetParticle(ParticleClone->D1))->PID);
                if (ParticleClone->D2 != -1) Print(HError, "Daughter2", ((GenParticle *) ClonesArrays->GetParticle(ParticleClone->D2))->PID);

            }

        }



        if (ParticleClone->Status == GeneratorParticle) {
            Print(HDetailed, "Particles Status", "Generator");

            if (std::abs(ParticleID) == TopId) {

                const TLorentzVector TopVector = const_cast<GenParticle *>(ParticleClone)->P4();
                fastjet::PseudoJet TopJet = GetPseudoJet(const_cast<GenParticle *>(ParticleClone)->P4());
                TopJet.set_user_index(TopId);

                TopJets.push_back(TopJet);
                ParticleJets.push_back(TopJet);

                if (ParticleID > 0) {

                    TopVectors.push_back(TopVector);
                    Print(HDebug, "Top");

                } else if (ParticleID < 0) {

                    AntiTopVector.push_back(TopVector);
                    Print(HDebug, "Anti Top");

                }

            }

        }

    }

    return 1;

}

