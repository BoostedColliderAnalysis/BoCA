# include "HParticleDelphes.hh"
# include "Predicate.hh"

analysis::delphes::HParticle ::HParticle()
{
//     DebugLevel = analysis::Object::kDebug;
    Print(kDebug, "Constructor");
}

bool analysis::delphes::HParticle ::GetParticles()
{
    Print(kInformation, "Get Particles", clones_arrays().ParticleSum());
    for (const int ParticleNumber : Range(clones_arrays().ParticleSum())) {

        ::delphes::GenParticle &particle = static_cast<::delphes::GenParticle &>(clones_arrays().Particle(ParticleNumber));

        const int ParticleId = particle.PID;
        Print(kDetailed, "Particles ID", ParticleId);

        int MotherId = EmptyId;
//         int MotherStatus = EmptyId;
        int Mother2Id = EmptyId;
//         int Mother2Status = EmptyId;
        if (particle.M1 != EmptyPosition) {
            ::delphes::GenParticle &mother = static_cast<::delphes::GenParticle &>(clones_arrays().Particle(particle.M1));

            MotherId = mother.PID;
//             MotherStatus = mother.Status;
        }
        if (particle.M2 != EmptyPosition) {
            ::delphes::GenParticle &mother = static_cast<::delphes::GenParticle &>(clones_arrays().Particle(particle.M2));

            Mother2Id = mother.PID;
//             Mother2Status = mother.Status;
        }

        if (particle.Status == StableParticle) {
            Print(kDetailed, "Particles Status", "stable");

            if (std::abs(ParticleId) == ElectronId) {

                const TLorentzVector ElectronVector = particle.P4();
                const fastjet::PseudoJet ElectronJet = PseudoJet(ElectronVector);

                if (ParticleId > 0) {
                    ElectronVectors.emplace_back(ElectronVector);
                    ElectronJets.emplace_back(ElectronJet);
                    Print(kDebug, "Electron");
                } else if (ParticleId < 0) {
                    AntiElectronVectors.emplace_back(ElectronVector);
                    AntiElectronJets.emplace_back(ElectronJet);
                    Print(kDebug, "Anti Electron");
                }
            }

            if (std::abs(ParticleId) == MuonId) {

                const TLorentzVector MuonVector = particle.P4();
                const fastjet::PseudoJet MuonJet = PseudoJet(MuonVector);

                if (ParticleId > 0) {
                    MuonVectors.emplace_back(MuonVector);
                    MuonJets.emplace_back(MuonJet);
                    Print(kDebug, "Muon");
                } else if (ParticleId < 0) {
                    AntiMuonVectors.emplace_back(MuonVector);
                    AntiMuonJets.emplace_back(MuonJet);
                    Print(kDebug, "Anti Muon");
                }
            }
        }

        if (particle.Status == UnstableParticle) {
            Print(kDetailed, "Particles Status", "unstable");

            if (std::abs(ParticleId) == CharmId) {
                CharmJets.emplace_back(PseudoJet(particle.P4()));
                Print(kDebug, "Charm");
            }

            if (std::abs(ParticleId) == CpvHiggsId) {
                HiggsJets.emplace_back(PseudoJet(particle.P4()));
                Print(kDebug, "CPV Higgs");
            }


            if (std::abs(ParticleId) == BottomId) {
                BottomJets.emplace_back(PseudoJet(particle.P4()));
                ParticleJets.emplace_back(PseudoJet(particle.P4()));
                ParticleJets.back().set_user_index(ParticleId);
                Print(kDebug, "Bottom");
            }

            if (std::abs(ParticleId) == HeavyHiggsId) {
                const fastjet::PseudoJet HiggsParticle = PseudoJet(particle.P4());
                HiggsJets.emplace_back(HiggsParticle);
                Print(kDebug, "Heavy CPV Higgs");
                Print(kDebug, "HeavyHiggs", particle.Status);
                if (particle.D1 != -1) Print(kDebug, "Daughter1", static_cast<::delphes::GenParticle &>(clones_arrays().Particle(particle.D1)).PID);
                if (particle.D2 != -1) Print(kDebug, "Daughter2", static_cast<::delphes::GenParticle &>(clones_arrays().Particle(particle.D2)).PID);
            }
        }

        if (particle.Status == GeneratorParticle) {
            Print(kInformation, "Particles Status", "Generator");

            Family family(ParticleId, MotherId, Mother2Id);
            Constituent constituent(particle.P4(), family);
            fastjet::PseudoJet GeneratorJet = PseudoJet(constituent.Momentum());
            GeneratorJet.set_user_info(new JetInfo(constituent));
            GeneratorJets.emplace_back(GeneratorJet);

            if (std::abs(ParticleId) == ElectronNeutrinoId || std::abs(ParticleId) == MuonNeutrinoId) {
                fastjet::PseudoJet NeutrinoJet = PseudoJet(particle.P4());
                NeutrinoJet.set_user_index(ParticleId);
                Print(kInformation, "Neutrino", NeutrinoJet);
                NeutrinoJets.emplace_back(NeutrinoJet);
            }

            if (std::abs(ParticleId) == TopId) {

                const TLorentzVector TopVector = particle.P4();
                fastjet::PseudoJet TopJet = PseudoJet(particle.P4());
                TopJet.set_user_index(ParticleId);
                Print(kInformation, "Top", TopJet);

                TopJets.emplace_back(TopJet);
                ParticleJets.emplace_back(TopJet);

                if (ParticleId > 0) {
                    TopVectors.emplace_back(TopVector);
                    Print(kDebug, "Top");
                } else if (ParticleId < 0) {
                    AntiTopVector.emplace_back(TopVector);
                    Print(kDebug, "Anti Top");
                }
            }

            if (std::abs(ParticleId) == BottomId) {
                fastjet::PseudoJet BottomJet = PseudoJet(particle.P4());
//                 BottomJet.set_user_index(ParticleId);
                Print(kInformation, "Bottom", MotherId, Mother2Id);
            }

            if (std::abs(ParticleId) == ElectronId || std::abs(ParticleId) == MuonId) {
                fastjet::PseudoJet LeptonJet = PseudoJet(particle.P4());
                //                 BottomJet.set_user_index(ParticleId);
                Print(kInformation, "Lepton", LeptonJet);
            }

            if (std::abs(ParticleId) == WId) {
                fastjet::PseudoJet WJet = PseudoJet(particle.P4());
                //                 BottomJet.set_user_index(ParticleId);
                Print(kInformation, "W", WJet);
            }
        }

    }

    fastjet::PseudoJet Met;
    Print(kInformation, "MPt", std::accumulate(NeutrinoJets.begin(), NeutrinoJets.end(), Met));

    return 1;

}

