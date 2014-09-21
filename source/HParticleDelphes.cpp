# include "HParticleDelphes.hh"

HParticleDelphes::HParticleDelphes()
{

    Print(2, "Constructor");

}

HParticleDelphes::~HParticleDelphes()
{

    Print(2, "Destructor");

}

bool HParticleDelphes::GetParticles()
{

    Print(1, "Get Particles");

    int ParticleSum = ClonesArrays->ParticleClonesArray->GetEntriesFast();

    Print(2, "Number of Particles", ParticleSum);

    for (int ParticleNumber = 0; ParticleNumber < ParticleSum; ++ParticleNumber) {

        GenParticle *GenParticleClone = (GenParticle *) ClonesArrays->ParticleClonesArray->At(ParticleNumber);

        int ParticleStatus = GenParticleClone->Status;
        Print(3, "Particles Status", ParticleStatus);

        int ParticleID = GenParticleClone->PID;
        Print(3, "Particles ID", ParticleID);

        if (ParticleStatus == 1) {

            if (abs(ParticleID) == 11) {

                TLorentzVector ElectronParticle = GetLorentzVector(GenParticleClone);

                if (ParticleID > 0) {

                    ElectronVector.push_back(ElectronParticle);
                    Print(2, "Electron");

                } else if (ParticleID < 0) {

                    AntiElectronVector.push_back(ElectronParticle);
                    Print(2, "Anti Electron");

                }

            } // Electrons

            if (abs(ParticleID) == 13) {

                TLorentzVector MuonParticle = GetLorentzVector(GenParticleClone);

                if (ParticleID > 0) {

                    MuonVector.push_back(MuonParticle);
                    Print(2, "Muon");

                } else if (ParticleID < 0) {

                    AntiMuonVector.push_back(MuonParticle);
                    Print(2, "Anti Muon");

                }

            } // Muons

        }



        if (ParticleStatus == 2) {

            if (abs(ParticleID) == 4) {

                PseudoJet CharmJet = GetPseudoJetPt(GenParticleClone);

                CharmJetVector.push_back(CharmJet);
                Print(2, "Charm");

            } // charms

            if (abs(ParticleID) == 5000000) {

                PseudoJet HiggsParticle = GetPseudoJetPt(GenParticleClone);

                HiggsJetVector.push_back(HiggsParticle);
                Print(2, "CPV Higgs");

            } // cp Higgs

        }



        if (ParticleStatus == 3) {

            if (abs(ParticleID) == TopId) {

                TLorentzVector TopQuark = GetLorentzVector(GenParticleClone);
                PseudoJet TopJet = GetPseudoJetPt(GenParticleClone);
                TopJet.set_user_index(TopId);

                TopJetVector.push_back(TopJet);
                ParticleJetVector.push_back(TopJet);

                if (ParticleID > 0) {

                    TopVector.push_back(TopQuark);
                    Print(2, "Top");

                } else if (ParticleID < 0) {

                    AntiTopVector.push_back(TopQuark);
                    Print(2, "Anti Top");

                }


            } // top

            if (abs(ParticleID) == BottomId) {

                PseudoJet BottomJet = GetPseudoJetPt(GenParticleClone);
                BottomJet.set_user_index(BottomId);

                BottomJetVector.push_back(BottomJet);
                ParticleJetVector.push_back(BottomJet);

                Print(2, "Bottom");


            } // bottoms

            if (abs(ParticleID) == 0) {

                PseudoJet HiggsParticle = GetPseudoJetPt(GenParticleClone);

                HiggsJetVector.push_back(HiggsParticle);
                Print(2, "Heavy CPV Higgs");

            } // heavy higgs

        }

    }

    return 1;

}

struct HDistance {

    int Position = -1;

    int ParticleId = 0;

    float Distance = 999999;

    float SecondDistance = 999999;

};

vector< PseudoJet > HParticleDelphes::TagJets(vector<PseudoJet> JetVector)
{
    Print(2, "Tag Jets");

    if (JetVector.size() == 0) return JetVector;

    RemoveBottoms();

//     vector<vector<HDistance> DistanceMatrix;

    vector<HDistance> DistanceVector;
    vector<HDistance> SecondDistanceVector;
    vector<HDistance> ThirdDistanceVector;

    Print(2, "Heavy Quraks", ParticleJetVector.size());

    for (unsigned ParticleNumber = 0; ParticleNumber < ParticleJetVector.size(); ++ParticleNumber) {

        HDistance JetDistance;
        DistanceVector.push_back(JetDistance);

        HDistance SecondJetDistance;
        SecondDistanceVector.push_back(SecondJetDistance);

        HDistance ThirdJetDistance;
        ThirdDistanceVector.push_back(ThirdJetDistance);

        Print(2, "Particle ID", ParticleJetVector[ParticleNumber].user_index());

        for (unsigned JetNumber = 0; JetNumber < JetVector.size(); ++JetNumber) {

            float Distance = JetVector[JetNumber].delta_R(ParticleJetVector[ParticleNumber]);

            Print(2, "Distance", Distance);

            if (Distance < DistanceVector[ParticleNumber].Distance) {

                ThirdDistanceVector[ParticleNumber] = SecondDistanceVector[ParticleNumber];
                SecondDistanceVector[ParticleNumber] = DistanceVector[ParticleNumber];

                DistanceVector[ParticleNumber].Distance = Distance;
                DistanceVector[ParticleNumber].Position = JetNumber;
                DistanceVector[ParticleNumber].ParticleId = ParticleJetVector[ParticleNumber].user_index();

            } else if (Distance < SecondDistanceVector[ParticleNumber].Distance) {

                ThirdDistanceVector[ParticleNumber] = SecondDistanceVector[ParticleNumber];

                SecondDistanceVector[ParticleNumber].Distance = Distance;
                SecondDistanceVector[ParticleNumber].Position = JetNumber;
                SecondDistanceVector[ParticleNumber].ParticleId = ParticleJetVector[ParticleNumber].user_index();


            } else if (Distance < ThirdDistanceVector[ParticleNumber].Distance) {


                ThirdDistanceVector[ParticleNumber].Distance = Distance;
                ThirdDistanceVector[ParticleNumber].Position = JetNumber;
                ThirdDistanceVector[ParticleNumber].ParticleId = ParticleJetVector[ParticleNumber].user_index();

            }

        }

    }

    for (unsigned ParticleNumber = 0; ParticleNumber < ParticleJetVector.size(); ++ParticleNumber) {

        Print(2, "Particle", DistanceVector[ParticleNumber].ParticleId);

        for (unsigned ParticleNumber2 = 0; ParticleNumber2 < ParticleNumber; ++ParticleNumber2) {

            if (DistanceVector[ParticleNumber].Position == DistanceVector[ParticleNumber2].Position) {

                if (DistanceVector[ParticleNumber].Distance < DistanceVector[ParticleNumber2].Distance) {

                    if (DistanceVector[ParticleNumber2].Position != SecondDistanceVector[ParticleNumber2].Position) {
                        
                        DistanceVector[ParticleNumber2] = SecondDistanceVector[ParticleNumber2];

                    } else {

                        DistanceVector[ParticleNumber2] = ThirdDistanceVector[ParticleNumber2];

                    }

                } else if (DistanceVector[ParticleNumber2].Distance < DistanceVector[ParticleNumber].Distance) {

                    if (DistanceVector[ParticleNumber].Position != SecondDistanceVector[ParticleNumber].Position) {
                        
                        DistanceVector[ParticleNumber] = SecondDistanceVector[ParticleNumber];
                        
                    } else {
                        
                        DistanceVector[ParticleNumber] = ThirdDistanceVector[ParticleNumber];
                        
                    }

                } else Print(2, "What is going on here");

            }

        }

        Print(2, "JetPosition", DistanceVector[ParticleNumber].Position, DistanceVector[ParticleNumber].Distance);
        JetVector[DistanceVector[ParticleNumber].Position].set_user_index(DistanceVector[ParticleNumber].ParticleId);

    }


    return JetVector;

}

void HParticleDelphes::RemoveBottoms()
{
    Print(1, "Remove Bottoms");

    vector<HDistance> DistanceVector;

    Print(2, "ParticleSum", ParticleJetVector.size());

    for (unsigned ParticleNumber = 0; ParticleNumber < ParticleJetVector.size(); ++ParticleNumber) {

        HDistance ParticleDistance;
        ParticleDistance.ParticleId = ParticleJetVector[ParticleNumber].user_index();

        Print(3, "Particle ID", ParticleDistance.ParticleId);

        DistanceVector.push_back(ParticleDistance);

        for (unsigned ParticleNumber2 = 0; ParticleNumber2 < ParticleNumber; ++ParticleNumber2) {

            float Distance = ParticleJetVector[ParticleNumber].delta_R(ParticleJetVector[ParticleNumber2]);

            Print(3, "Distance", ParticleJetVector[ParticleNumber2].user_index(), Distance);

            if (ParticleJetVector[ParticleNumber].user_index() != ParticleJetVector[ParticleNumber2].user_index()) {

                if (Distance < DistanceVector[ParticleNumber].Distance) {

                    DistanceVector[ParticleNumber].Distance = Distance;
                    DistanceVector[ParticleNumber].Position = ParticleNumber2;

                }

                if (Distance < DistanceVector[ParticleNumber2].Distance) {

                    DistanceVector[ParticleNumber2].Distance = Distance;
                    DistanceVector[ParticleNumber2].Position = ParticleNumber;

                }

            }

        }

    }

    for (unsigned ParticleNumber = 0; ParticleNumber < DistanceVector.size(); ++ParticleNumber) {

        if (DistanceVector[ParticleNumber].ParticleId == TopId) {

            Print(3, "Final Particle Distance", ParticleJetVector[DistanceVector[ParticleNumber].Position].user_index(), DistanceVector[ParticleNumber].Distance);

            ParticleJetVector.erase(ParticleJetVector.begin() + DistanceVector[ParticleNumber].Position);

        }

    }

}


