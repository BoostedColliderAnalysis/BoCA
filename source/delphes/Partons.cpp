# include "delphes/Partons.hh"
# include "Predicate.hh"

analysis::delphes::Partons::Partons()
{
//     DebugLevel = analysis::Object::kDebug;
    Print(kDebug, "Constructor");
}

bool analysis::delphes::Partons::GetParticles()
{
    Print(kInformation, "Particles", clones_arrays().ParticleSum());
    for (const int ParticleNumber : Range(clones_arrays().ParticleSum())) {
        ::delphes::GenParticle &particle = static_cast<::delphes::GenParticle &>(clones_arrays().Particle(ParticleNumber));
        const int particle_id = particle.PID;
        Print(kDetailed, "Particles ID", particle_id);
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
        if (particle.Status == kStable) {
            Print(kDetailed, "Particles Status", "stable");
            if (std::abs(particle_id) == ElectronId) {
                const TLorentzVector ElectronVector = particle.P4();
                const fastjet::PseudoJet ElectronJet = analysis::PseudoJet(ElectronVector);
                if (particle_id > 0) {
                    ElectronVectors.emplace_back(ElectronVector);
                    ElectronJets.emplace_back(ElectronJet);
                    Print(kDebug, "Electron");
                } else if (particle_id < 0) {
                    AntiElectronVectors.emplace_back(ElectronVector);
                    AntiElectronJets.emplace_back(ElectronJet);
                    Print(kDebug, "Anti Electron");
                }
            }
            if (std::abs(particle_id) == MuonId) {
                const TLorentzVector MuonVector = particle.P4();
                const fastjet::PseudoJet MuonJet = analysis::PseudoJet(MuonVector);
                if (particle_id > 0) {
                    MuonVectors.emplace_back(MuonVector);
                    MuonJets.emplace_back(MuonJet);
                    Print(kDebug, "Muon");
                } else if (particle_id < 0) {
                    AntiMuonVectors.emplace_back(MuonVector);
                    AntiMuonJets.emplace_back(MuonJet);
                    Print(kDebug, "Anti Muon");
                }
            }
        }
        if (particle.Status == kUnstable) {
            Print(kDetailed, "Particles Status", "unstable");
            if (std::abs(particle_id) == CharmId) {
              CharmJets.emplace_back(analysis::PseudoJet(particle.P4()));
                Print(kDebug, "Charm");
            }
            if (std::abs(particle_id) == CpvHiggsId) {
              HiggsJets.emplace_back(analysis::PseudoJet(particle.P4()));
                Print(kDebug, "CPV Higgs");
            }
            if (std::abs(particle_id) == BottomId) {
              BottomJets.emplace_back(analysis::PseudoJet(particle.P4()));
              ParticleJets.emplace_back(analysis::PseudoJet(particle.P4()));
                ParticleJets.back().set_user_index(particle_id);
                Print(kDebug, "Bottom");
            }
            if (std::abs(particle_id) == HeavyHiggsId) {
              const fastjet::PseudoJet HiggsParticle = analysis::PseudoJet(particle.P4());
                HiggsJets.emplace_back(HiggsParticle);
                Print(kDebug, "Heavy CPV Higgs");
                Print(kDebug, "HeavyHiggs", particle.Status);
                if (particle.D1 != -1) {
                    Print(kDebug, "Daughter1", static_cast<::delphes::GenParticle &>(clones_arrays().Particle(particle.D1)).PID);
                }
                if (particle.D2 != -1) {
                    Print(kDebug, "Daughter2", static_cast<::delphes::GenParticle &>(clones_arrays().Particle(particle.D2)).PID);
                }
            }
        }
        if (particle.Status == kGenerator) {
            Print(kInformation, "Particles Status", "Generator");
            Family family(particle_id, MotherId, Mother2Id);
            Constituent constituent(particle.P4(), family);
            fastjet::PseudoJet GeneratorJet = analysis::PseudoJet(constituent.Momentum());
            GeneratorJet.set_user_info(new JetInfo(constituent));
            GeneratorJets.emplace_back(GeneratorJet);
            if (std::abs(particle_id) == ElectronNeutrinoId || std::abs(particle_id) == MuonNeutrinoId) {
              fastjet::PseudoJet NeutrinoJet = analysis::PseudoJet(particle.P4());
                NeutrinoJet.set_user_index(particle_id);
                Print(kInformation, "Neutrino", NeutrinoJet);
                NeutrinoJets.emplace_back(NeutrinoJet);
            }
            if (std::abs(particle_id) == TopId) {
                const TLorentzVector TopVector = particle.P4();
                fastjet::PseudoJet TopJet = analysis::PseudoJet(particle.P4());
                TopJet.set_user_index(particle_id);
                Print(kInformation, "Top", TopJet);
                TopJets.emplace_back(TopJet);
                ParticleJets.emplace_back(TopJet);
                if (particle_id > 0) {
                    TopVectors.emplace_back(TopVector);
                    Print(kDebug, "Top");
                } else if (particle_id < 0) {
                    AntiTopVector.emplace_back(TopVector);
                    Print(kDebug, "Anti Top");
                }
            }
            if (std::abs(particle_id) == BottomId) {
              fastjet::PseudoJet BottomJet = analysis::PseudoJet(particle.P4());
//                 BottomJet.set_user_index(particle_id);
                Print(kInformation, "Bottom", MotherId, Mother2Id);
            }
            if (std::abs(particle_id) == ElectronId || std::abs(particle_id) == MuonId) {
              fastjet::PseudoJet LeptonJet = analysis::PseudoJet(particle.P4());
                //                 BottomJet.set_user_index(particle_id);
                Print(kInformation, "Lepton", LeptonJet);
            }
            if (std::abs(particle_id) == WId) {
              fastjet::PseudoJet WJet = analysis::PseudoJet(particle.P4());
                //                 BottomJet.set_user_index(particle_id);
                Print(kInformation, "W", WJet);
            }
        }
    }
    fastjet::PseudoJet Met;
    Print(kInformation, "MPt", std::accumulate(NeutrinoJets.begin(), NeutrinoJets.end(), Met));
    return 1;
}

