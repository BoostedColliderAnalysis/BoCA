# include "exroot/Partons.hh"

analysis::exroot::Partons::Partons()
{
    Print(kNotification, "Constructor");
//     Debug =5;
}

bool analysis::exroot::Partons::GetParticles()
{
    Print(kInformation, "Get Particles", clones_arrays().ParticleSum());
    for (const int ParticleNumber : Range(clones_arrays().ParticleSum())) {
        TRootLHEFParticle &particle = static_cast<TRootLHEFParticle &>(clones_arrays().Particle(ParticleNumber));
        int ParticleStatus = particle.Status;
        Print(kDetailed, "Particles Status", ParticleStatus);
        Print(kDetailed, "Particles ID", particle.PID);
        if (ParticleStatus == kStable) {
            if (std::abs(particle.PID) == ElectronId) {
                TLorentzVector ElectronVector = GetLorentzVector(particle);
                if (particle.PID > 0) {
                    ElectronVectors.emplace_back(ElectronVector);
                    Print(kDebug, "Electron");
                } else if (particle.PID < 0) {
                    AntiElectronVectors.emplace_back(ElectronVector);
                    Print(kDebug, "Anti Electron");
                }
            } // Electrons
            if (std::abs(particle.PID) == MuonId) {
                TLorentzVector MuonVector = GetLorentzVector(particle);
                if (particle.PID > 0) {
                    MuonVectors.emplace_back(MuonVector);
                    Print(kDebug, "Muon");
                } else if (particle.PID < 0) {
                    AntiMuonVectors.emplace_back(MuonVector);
                    Print(kDebug, "Anti Muon");
                }
            } // Muons
            if (std::abs(particle.PID) == BottomId) {
                fastjet::PseudoJet BottomJet = GetPseudoJet(particle);
                BottomJets.emplace_back(BottomJet);
                Print(kDebug, "Bottom");
            } // bottoms
            if (std::abs(particle.PID) == TopId) {
                TLorentzVector TopVector = GetLorentzVector(particle);
                fastjet::PseudoJet TopJet = GetPseudoJet(particle);
                TopJets.emplace_back(TopJet);
                if (particle.PID > 0) {
                    TopVectors.emplace_back(TopVector);
                    Print(kDebug, "Top");
                } else if (particle.PID < 0) {
                    AntiTopVector.emplace_back(TopVector);
                    Print(kDebug, "Anti Top");
                }
            } // top
        }
        if (ParticleStatus == kUnstable) {
            if (std::abs(particle.PID) == CharmId) {
                fastjet::PseudoJet CharmJet = GetPseudoJet(particle);
                CharmJets.emplace_back(CharmJet);
                Print(kDebug, "Charm");
            } // charms
//             if (std::abs(particle.PID) == 5) {
//                 fastjet::PseudoJet JetCandidate = GetPseudoJetPt(ParticleClone);
//                 BottomJetVector.emplace_back(JetCandidate);
//                 Print(kDebug,"Bottom");
//
//             } // bottoms
            if (std::abs(particle.PID) == CpvHiggsId) {
                fastjet::PseudoJet HiggsJet = GetPseudoJet(particle);
                HiggsJets.emplace_back(HiggsJet);
                Print(kDebug, "CPV Higgs");
            } // cp Higgs
        }
        if (ParticleStatus == kGenerator) {
            if (std::abs(particle.PID) == HeavyHiggsId) {
                fastjet::PseudoJet HiggsJet = GetPseudoJet(particle);
                HiggsJets.emplace_back(HiggsJet);
                Print(kDebug, "Heavy CPV Higgs");
            } // heavy higgs
        }
    }
    return 1;
}
