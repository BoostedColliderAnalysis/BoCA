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

    Print(2, "Get Particles");

    GenParticle *GenParticleClone;
    int ParticleID;

    Print(3, "Number of Particles", ClonesArrays->ParticleSum());
    for (int ParticleNumber = 0; ParticleNumber < ClonesArrays->ParticleSum(); ++ParticleNumber) {

        GenParticleClone = (GenParticle *) ClonesArrays->ParticleClonesArray->At(ParticleNumber);

        ParticleID = GenParticleClone->PID;
        Print(4, "Particles ID", ParticleID);

        if (GenParticleClone->Status == 1) {
        Print(4, "Particles Status", 1);

            if (abs(ParticleID) == 11) {

                TLorentzVector ElectronParticle = GenParticleClone->P4();

                if (ParticleID > 0) {

                    ElectronVector.push_back(ElectronParticle);
                    Print(3, "Electron");

                } else if (ParticleID < 0) {

                    AntiElectronVector.push_back(ElectronParticle);
                    Print(3, "Anti Electron");

                }

            } // Electrons

            if (abs(ParticleID) == 13) {

                if (ParticleID > 0) {

                    MuonVector.push_back(GenParticleClone->P4());
                    Print(3, "Muon");

                } else if (ParticleID < 0) {

                    AntiMuonVector.push_back(GenParticleClone->P4());
                    Print(3, "Anti Muon");

                }

            } // Muons

        }



        if (GenParticleClone->Status == 2) {
            Print(4, "Particles Status", 2);

            if (abs(ParticleID) == 4) {

                CharmJetVector.push_back(GetPseudoJet(GenParticleClone->P4()));
                Print(3, "Charm");

            } // charms

            if (abs(ParticleID) == 5000000) {

                HiggsJetVector.push_back(GetPseudoJet(GenParticleClone->P4()));
                Print(3, "CPV Higgs");

            } // cp Higgs


            if (abs(ParticleID) == BottomId) {

                BottomJetVector.push_back(GetPseudoJet(GenParticleClone->P4()));
                ParticleJetVector.push_back(GetPseudoJet(GenParticleClone->P4()));
                ParticleJetVector.back().set_user_index(BottomId);

                Print(3, "Bottom");

//                 Print(0, "Status 3 ", BottomJet.pt(), BottomJet.eta());

            } // bottoms


        }



        if (GenParticleClone->Status == 3) {
            Print(4, "Particles Status", 3);

//             if (abs(ParticleID) == BottomId) {
//
//                 PseudoJet BottomJet = GetPseudoJet(GenParticleClone->P4());
//                 BottomJet.set_user_index(BottomId);
//
//                 BottomJetVector.push_back(BottomJet);
//                 ParticleJetVector.push_back(BottomJet);
//
//                 Print(3, "Bottom");
//
//                 Print(0, "Status 3 ", BottomJet.pt(), BottomJet.eta());
//
//             } // bottoms

            if (abs(ParticleID) == TopId) {

                TLorentzVector TopQuark = GenParticleClone->P4();
                PseudoJet TopJet = GetPseudoJet(GenParticleClone->P4());
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


            } // top

            if (abs(ParticleID) == 0) {

                PseudoJet HiggsParticle = GetPseudoJet(GenParticleClone->P4());

                HiggsJetVector.push_back(HiggsParticle);
                Print(3, "Heavy CPV Higgs");

            } // heavy higgs

        }

    }

    return 1;

}
