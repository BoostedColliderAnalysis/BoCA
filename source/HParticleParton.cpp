# include "HParticleParton.hh"

hanalysis::hparton::HParticle::HParticle()
{
    Print(kNotification, "Constructor");
//     Debug =5;
}

bool hanalysis::hparton::HParticle::GetParticles()
{
    Print(kInformation, "Get Particles", clones_arrays().ParticleSum());
    for (const int ParticleNumber : Range(clones_arrays().ParticleSum())) {
        TRootLHEFParticle &particle = static_cast<TRootLHEFParticle &>(clones_arrays().Particle(ParticleNumber));
        int ParticleStatus = particle.Status;
        Print(kDetailed, "Particles Status", ParticleStatus);
        int ParticleID = particle.PID;
        Print(kDetailed, "Particles ID", ParticleID);
        if (ParticleStatus == StableParticle) {
            if (std::abs(ParticleID) == ElectronId) {
                TLorentzVector ElectronVector = GetLorentzVector(particle);
                if (ParticleID > 0) {
                    ElectronVectors.emplace_back(ElectronVector);
                    Print(kDebug, "Electron");
                } else if (ParticleID < 0) {
                    AntiElectronVectors.emplace_back(ElectronVector);
                    Print(kDebug, "Anti Electron");
                }
            } // Electrons
            if (std::abs(ParticleID) == MuonId) {
                TLorentzVector MuonVector = GetLorentzVector(particle);
                if (ParticleID > 0) {
                    MuonVectors.emplace_back(MuonVector);
                    Print(kDebug, "Muon");
                } else if (ParticleID < 0) {
                    AntiMuonVectors.emplace_back(MuonVector);
                    Print(kDebug, "Anti Muon");
                }
            } // Muons
            if (std::abs(ParticleID) == BottomId) {
                fastjet::PseudoJet BottomJet = GetPseudoJet(particle);
                BottomJets.emplace_back(BottomJet);
                Print(kDebug, "Bottom");
            } // bottoms
            if (std::abs(ParticleID) == TopId) {
                TLorentzVector TopVector = GetLorentzVector(particle);
                fastjet::PseudoJet TopJet = GetPseudoJet(particle);
                TopJets.emplace_back(TopJet);
                if (ParticleID > 0) {
                    TopVectors.emplace_back(TopVector);
                    Print(kDebug, "Top");
                } else if (ParticleID < 0) {
                    AntiTopVector.emplace_back(TopVector);
                    Print(kDebug, "Anti Top");
                }
            } // top
        }
        if (ParticleStatus == UnstableParticle) {
            if (std::abs(ParticleID) == CharmId) {
                fastjet::PseudoJet CharmJet = GetPseudoJet(particle);
                CharmJets.emplace_back(CharmJet);
                Print(kDebug, "Charm");
            } // charms
//             if (std::abs(ParticleID) == 5) {
//
//                 fastjet::PseudoJet JetCandidate = GetPseudoJetPt(ParticleClone);
//
//                 BottomJetVector.emplace_back(JetCandidate);
//                 Print(kDebug,"Bottom");
//
//             } // bottoms
            if (std::abs(ParticleID) == CpvHiggsId) {
                fastjet::PseudoJet HiggsJet = GetPseudoJet(particle);
                HiggsJets.emplace_back(HiggsJet);
                Print(kDebug, "CPV Higgs");
            } // cp Higgs
        }
        if (ParticleStatus == GeneratorParticle) {
            if (std::abs(ParticleID) == HeavyHiggsId) {
                fastjet::PseudoJet HiggsJet = GetPseudoJet(particle);
                HiggsJets.emplace_back(HiggsJet);
                Print(kDebug, "Heavy CPV Higgs");
            } // heavy higgs
        }
    }
    return 1;
}
