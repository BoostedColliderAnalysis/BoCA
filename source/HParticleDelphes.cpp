# include "HParticleDelphes.hh"

hanalysis::hdelphes::HParticle ::HParticle()
{

    Print(HDebug, "Constructor");

//     DebugLevel = hanalysis::HObject::HInformation;

}

hanalysis::hdelphes::HParticle ::~HParticle()
{

    Print(HDebug, "Destructor");

}


bool hanalysis::hdelphes::HParticle ::GetParticles()
{

    Print(HInformation, "Get Particles", ClonesArrays->GetParticleSum());

    for (const int ParticleNumber : HRange(ClonesArrays->GetParticleSum())) {

        const GenParticle *const ParticleClone = (GenParticle *) ClonesArrays->GetParticle(ParticleNumber);

        const int ParticleId = ParticleClone->PID;
        Print(HDetailed, "Particles ID", ParticleId);

        if (ParticleClone->Status == StableParticle) {
            Print(HDetailed, "Particles Status", "stable");

            if (std::abs(ParticleId) == ElectronId) {

                const TLorentzVector ElectronVector = const_cast<GenParticle *>(ParticleClone)->P4();
                const fastjet::PseudoJet ElectronJet = GetPseudoJet(ElectronVector);

                if (ParticleId > 0) {

                    ElectronVectors.push_back(ElectronVector);
                    ElectronJets.push_back(ElectronJet);
                    Print(HDebug, "Electron");

                } else if (ParticleId < 0) {

                    AntiElectronVectors.push_back(ElectronVector);
                    AntiElectronJets.push_back(ElectronJet);
                    Print(HDebug, "Anti Electron");

                }

            }

            if (std::abs(ParticleId) == MuonId) {

                const TLorentzVector MuonVector = const_cast<GenParticle *>(ParticleClone)->P4();
                const fastjet::PseudoJet MuonJet = GetPseudoJet(MuonVector);

                if (ParticleId > 0) {

                    MuonVectors.push_back(MuonVector);
                    MuonJets.push_back(MuonJet);
                    Print(HDebug, "Muon");

                } else if (ParticleId < 0) {

                    AntiMuonVectors.push_back(MuonVector);
                    AntiMuonJets.push_back(MuonJet);
                    Print(HDebug, "Anti Muon");

                }

            }

        }



        if (ParticleClone->Status == UnstableParticle) {
            Print(HDetailed, "Particles Status", "unstable");

            if (std::abs(ParticleId) == CharmId) {

                CharmJets.push_back(GetPseudoJet(const_cast<GenParticle *>(ParticleClone)->P4()));
                Print(HDebug, "Charm");

            }

            if (std::abs(ParticleId) == CpvHiggsId) {

                HiggsJets.push_back(GetPseudoJet(const_cast<GenParticle *>(ParticleClone)->P4()));
                Print(HDebug, "CPV Higgs");

            }


            if (std::abs(ParticleId) == BottomId) {

                BottomJets.push_back(GetPseudoJet(const_cast<GenParticle *>(ParticleClone)->P4()));
                ParticleJets.push_back(GetPseudoJet(const_cast<GenParticle *>(ParticleClone)->P4()));
                ParticleJets.back().set_user_index(ParticleId);

                Print(HDebug, "Bottom");

            }


            if (std::abs(ParticleId) == HeavyHiggsId) {

                const fastjet::PseudoJet HiggsParticle = GetPseudoJet(const_cast<GenParticle *>(ParticleClone)->P4());

                HiggsJets.push_back(HiggsParticle);
                Print(HDebug, "Heavy CPV Higgs");

                Print(HDebug, "HeavyHiggs", ParticleClone->Status);
                if (ParticleClone->D1 != -1) Print(HDebug, "Daughter1", ((GenParticle *) ClonesArrays->GetParticle(ParticleClone->D1))->PID);
                if (ParticleClone->D2 != -1) Print(HDebug, "Daughter2", ((GenParticle *) ClonesArrays->GetParticle(ParticleClone->D2))->PID);

            }

        }



        if (ParticleClone->Status == GeneratorParticle) {
            Print(HDetailed, "Particles Status", "Generator");

            if (std::abs(ParticleId) == ElectronNeutrinoId || std::abs(ParticleId) == MuonNeutrinoId) {
                // const TLorentzVector TopVector = const_cast<GenParticle *>(ParticleClone)->P4();
                fastjet::PseudoJet NeutrinoJet = GetPseudoJet(const_cast<GenParticle *>(ParticleClone)->P4());
                NeutrinoJet.set_user_index(ParticleId);
                Print(HInformation, "Neutrino", NeutrinoJet);
                NeutrinoJets.push_back(NeutrinoJet);
            }

            if (std::abs(ParticleId) == TopId) {

                const TLorentzVector TopVector = const_cast<GenParticle *>(ParticleClone)->P4();
                fastjet::PseudoJet TopJet = GetPseudoJet(const_cast<GenParticle *>(ParticleClone)->P4());
                TopJet.set_user_index(ParticleId);
                Print(HInformation, "Top", TopJet);

                TopJets.push_back(TopJet);
                ParticleJets.push_back(TopJet);

                if (ParticleId > 0) {

                    TopVectors.push_back(TopVector);
                    Print(HDebug, "Top");

                } else if (ParticleId < 0) {

                    AntiTopVector.push_back(TopVector);
                    Print(HDebug, "Anti Top");

                }

            }

            if (std::abs(ParticleId) == BottomId) {
                fastjet::PseudoJet BottomJet = GetPseudoJet(const_cast<GenParticle *>(ParticleClone)->P4());
//                 BottomJet.set_user_index(ParticleId);
                Print(HInformation, "Bottom", BottomJet);
            }

            if (std::abs(ParticleId) == ElectronId || std::abs(ParticleId) == MuonId) {
                fastjet::PseudoJet LeptonJet = GetPseudoJet(const_cast<GenParticle *>(ParticleClone)->P4());
                //                 BottomJet.set_user_index(ParticleId);
                Print(HInformation, "Lepton", LeptonJet);
            }

            if (std::abs(ParticleId) == WId) {
                fastjet::PseudoJet WJet = GetPseudoJet(const_cast<GenParticle *>(ParticleClone)->P4());
                //                 BottomJet.set_user_index(ParticleId);
                Print(HInformation, "W", WJet);
            }

        }

    }

    fastjet::PseudoJet Met;
    Print(HInformation, "MPt", std::accumulate(NeutrinoJets.begin(), NeutrinoJets.end(), Met));

    return 1;

}

