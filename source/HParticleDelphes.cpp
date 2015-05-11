# include "HParticleDelphes.hh"

hanalysis::hdelphes::HParticle ::HParticle()
{
    Print(kDebug, "Constructor");
//     DebugLevel = hanalysis::HObject::kDebug;
}

bool hanalysis::hdelphes::HParticle ::GetParticles()
{

  Print(kInformation, "Get Particles", clones_arrays_->GetParticleSum());

  for (const int ParticleNumber : Range(clones_arrays_->GetParticleSum())) {

    const delphes::GenParticle *const ParticleClone = (delphes::GenParticle *) clones_arrays_->GetParticle(ParticleNumber);

        const int ParticleId = ParticleClone->PID;
        Print(kDetailed, "Particles ID", ParticleId);

        int MotherId = EmptyId;
        int MotherStatus = EmptyId;
        int Mother2Id = EmptyId;
        int Mother2Status = EmptyId;
        if (ParticleClone->M1 != EmptyPosition) {
          const delphes::GenParticle *const MotherParticle = (delphes::GenParticle *) clones_arrays_->GetParticle(ParticleClone->M1);

            MotherId = MotherParticle->PID;
            MotherStatus = MotherParticle->Status;
        }
        if (ParticleClone->M2 != EmptyPosition) {
          const delphes::GenParticle *const MotherParticle = (delphes::GenParticle *) clones_arrays_->GetParticle(ParticleClone->M2);

            Mother2Id = MotherParticle->PID;
            Mother2Status = MotherParticle->Status;
        }

        if (ParticleClone->Status == StableParticle) {
            Print(kDetailed, "Particles Status", "stable");

            if (std::abs(ParticleId) == ElectronId) {

                const TLorentzVector ElectronVector = const_cast<delphes::GenParticle *>(ParticleClone)->P4();
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

                const TLorentzVector MuonVector = const_cast<delphes::GenParticle *>(ParticleClone)->P4();
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



        if (ParticleClone->Status == UnstableParticle) {
            Print(kDetailed, "Particles Status", "unstable");

            if (std::abs(ParticleId) == CharmId) {

                CharmJets.emplace_back(PseudoJet(const_cast<delphes::GenParticle *>(ParticleClone)->P4()));
                Print(kDebug, "Charm");

            }

            if (std::abs(ParticleId) == CpvHiggsId) {

                HiggsJets.emplace_back(PseudoJet(const_cast<delphes::GenParticle *>(ParticleClone)->P4()));
                Print(kDebug, "CPV Higgs");

            }


            if (std::abs(ParticleId) == BottomId) {

                BottomJets.emplace_back(PseudoJet(const_cast<delphes::GenParticle *>(ParticleClone)->P4()));
                ParticleJets.emplace_back(PseudoJet(const_cast<delphes::GenParticle *>(ParticleClone)->P4()));
                ParticleJets.back().set_user_index(ParticleId);

                Print(kDebug, "Bottom");

            }


            if (std::abs(ParticleId) == HeavyHiggsId) {

                const fastjet::PseudoJet HiggsParticle = PseudoJet(const_cast<delphes::GenParticle *>(ParticleClone)->P4());

                HiggsJets.emplace_back(HiggsParticle);
                Print(kDebug, "Heavy CPV Higgs");

                Print(kDebug, "HeavyHiggs", ParticleClone->Status);
                if (ParticleClone->D1 != -1) Print(kDebug, "Daughter1", ((delphes::GenParticle *) clones_arrays_->GetParticle(ParticleClone->D1))->PID);
                if (ParticleClone->D2 != -1) Print(kDebug, "Daughter2", ((delphes::GenParticle *) clones_arrays_->GetParticle(ParticleClone->D2))->PID);

            }

        }



        if (ParticleClone->Status == GeneratorParticle) {
            Print(kInformation, "Particles Status", "Generator");

            HFamily Family(ParticleId, MotherId, Mother2Id);
            Constituent constituent(const_cast<delphes::GenParticle *>(ParticleClone)->P4(), Family);
            fastjet::PseudoJet GeneratorJet = PseudoJet(constituent.Momentum());
            GeneratorJet.set_user_info(new JetInfo(constituent));
            GeneratorJets.emplace_back(GeneratorJet);




            if (std::abs(ParticleId) == ElectronNeutrinoId || std::abs(ParticleId) == MuonNeutrinoId) {
                // const TLorentzVector TopVector = const_cast<delphes::GenParticle *>(ParticleClone)->P4();
                fastjet::PseudoJet NeutrinoJet = PseudoJet(const_cast<delphes::GenParticle *>(ParticleClone)->P4());
                NeutrinoJet.set_user_index(ParticleId);
                Print(kInformation, "Neutrino", NeutrinoJet);
                NeutrinoJets.emplace_back(NeutrinoJet);
            }

            if (std::abs(ParticleId) == TopId) {

                const TLorentzVector TopVector = const_cast<delphes::GenParticle *>(ParticleClone)->P4();
                fastjet::PseudoJet TopJet = PseudoJet(const_cast<delphes::GenParticle *>(ParticleClone)->P4());
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
                fastjet::PseudoJet BottomJet = PseudoJet(const_cast<delphes::GenParticle *>(ParticleClone)->P4());
//                 BottomJet.set_user_index(ParticleId);
                Print(kInformation, "Bottom", MotherId, Mother2Id);
            }

            if (std::abs(ParticleId) == ElectronId || std::abs(ParticleId) == MuonId) {
                fastjet::PseudoJet LeptonJet = PseudoJet(const_cast<delphes::GenParticle *>(ParticleClone)->P4());
                //                 BottomJet.set_user_index(ParticleId);
                Print(kInformation, "Lepton", LeptonJet);
            }

            if (std::abs(ParticleId) == WId) {
                fastjet::PseudoJet WJet = PseudoJet(const_cast<delphes::GenParticle *>(ParticleClone)->P4());
                //                 BottomJet.set_user_index(ParticleId);
                Print(kInformation, "W", WJet);
            }
        }


//         if (MotherStatus == GeneratorParticle) {
//           if (ParticleClone->M1 < ParticleNumber) {
//
//
//             Print(kError, "Daughter 0",static_cast<JetInfo *>(GeneratorJets.at(ParticleClone->M1).user_info_shared_ptr().get())->constituents().front().Family().ParticleId,static_cast<JetInfo *>(GeneratorJets.at(ParticleClone->M1).user_info_shared_ptr().get())->constituents().front().Family().Mother1Id);
//
//                 Print(kError, "Daughter",
//                       ParticleNumber, ParticleId, ParticleClone->M1, MotherId);
//
//                 static_cast<JetInfo *>(GeneratorJets.at(ParticleClone->M1).user_info_shared_ptr().get())->AddDaughter(ParticleId);
//
//                 Print(kError, "Daughter 2",
//                       static_cast<JetInfo *>(GeneratorJets.at(ParticleClone->M1).user_info_shared_ptr().get())->constituents().front().Family().Daughters.size());
//             }
//         }
    }

    fastjet::PseudoJet Met;
    Print(kInformation, "MPt", std::accumulate(NeutrinoJets.begin(), NeutrinoJets.end(), Met));

    return 1;

}

