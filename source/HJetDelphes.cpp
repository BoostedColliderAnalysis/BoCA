# include "HJetDelphes.hh"

HJetDelphes::HJetDelphes()
{

    Print(0, "Constructor");

//     Debug =4;

}

HJetDelphes::~HJetDelphes()
{

    Print(0, "Destructor");

}

bool HJetDelphes::GetJets()
{

    return GetJets(0,0);

}

bool HJetDelphes::GetTaggedJets()
{

    return GetJets(1,0);

}

bool HJetDelphes::GetStructuredJets()
{

    return GetJets(0,1);

}

bool HJetDelphes::GetJets(bool Tagging,bool Structure)
{

    Print(1, "Get Jets", ClonesArrays->JetSum());

    Jet *JetClone;

    for (int JetNumber = 0; JetNumber < ClonesArrays->JetSum(); ++JetNumber) {

        Print(3, "Jet Number", JetNumber);
        JetClone = (Jet *)ClonesArrays->JetClonesArray->At(JetNumber);

        if(Structure) {

            JetVector.push_back(GetConstituents(JetClone));

        } else {

            JetVector.push_back(GetPseudoJet(JetClone->P4()));

        }

        if(Tagging)JetVector.back().set_user_info(new HJetInfo(GetJetId(JetClone)));

        GetDelphesTags(JetClone);

    }

    return 1;

}

void HJetDelphes::GetDelphesTags(Jet *JetClone)
{
    Print(1, "Get taggs");

    if (JetClone->TauTag == 1) {

        Print(3, "Has Tau Tag");

        GetTau(JetClone);

    } else if (JetClone->BTag > 0) {

        Print(3, "Has B Tag");

        BottomLorentzVectorVector.push_back(JetClone->P4());
        BottomJetVector.push_back(GetPseudoJet(JetClone->P4()));


    } else {

        JetLorentzVectorVector.push_back(JetClone->P4());

    }

}


void HJetDelphes::GetTau(Jet *JetClone)
{

    Print(1, "TauTagCalculations");

    if (JetClone->Charge == - 1) {

        TauLorentzVectorVector.push_back(JetClone->P4());
        Print(2, "Tau Jet");

    } else if (JetClone->Charge == 1) {

        AntiTauLorentzVectorVector.push_back(JetClone->P4());
        Print(2, "Anti Tau Jet");

    } else Print(-1,"Jet Charge: ",JetClone->Charge);

}

int HJetDelphes::GetMotherId(TObject *Object)
{

    Print(1, "Get Mother Id", ClonesArrays->ParticleSum());

    GenParticle *ParticleClone;
    int MotherId = EmptyId;
    int MotherPosition, ParticleId;

    if (Object->IsA() == GenParticle::Class()) {

        ParticleClone = (GenParticle *) Object;

    } else {

        Print(-1, "it is", Object->ClassName());
        return 0;
    }

    ParticleId = ParticleClone->PID;
    MotherPosition = ParticleClone->M1;
    Print(3, "Particle M1", MotherPosition);

    while (MotherPosition != -1
//         ParticleId != ProtonId
//         && abs(MotherId) != HeavyHiggsId && abs(MotherId) != CpvHiggsId
          ) {

        if (abs(ParticleId) == BottomId
                && (abs(MotherId) != TopId || abs(MotherId) != CpvHiggsId)) {
            MotherId = ParticleId;
        } else if (abs(ParticleId) == TopId && abs(MotherId) != HeavyHiggsId) {
            MotherId = ParticleId;
        } else if (abs(ParticleId) == HeavyHiggsId || abs(ParticleId) == CpvHiggsId) {
            MotherId = ParticleId;
        }
        Print(3, "Mother Id", MotherId);

        if (ClonesArrays->ParticleSum() < MotherPosition) {

            Print(-1, "Faulty event");
            continue;

        }
        ParticleClone = (GenParticle *) ClonesArrays->ParticleClonesArray->At(MotherPosition);
        ParticleId = ParticleClone->PID;
        MotherPosition = ParticleClone->M1;

        Print(3, "Particle Id", ParticleClone->PID);

    }

    Print(3, "Mother Id", MotherId);

    return MotherId;

}


PseudoJet HJetDelphes::GetConstituents(Jet *JetClone)
{

    Print(1, "Get Constituents");

    TObject *Object;
    vector<PseudoJet> ConstituentsVector;

    for (int ConstituentNumber = 0; ConstituentNumber < JetClone->Constituents.GetEntriesFast(); ++ConstituentNumber) {

        Object = JetClone->Constituents.At(ConstituentNumber);

        if (Object == 0) continue;

        if (Object->IsA() == GenParticle::Class()) {

            ConstituentsVector.push_back(GetPseudoJet(((GenParticle *) Object)->P4()));

        } else if (Object->IsA() == Track::Class()) {

            ConstituentsVector.push_back(GetPseudoJet(((Track *) Object)->P4()));

        } else if (Object->IsA() == Tower::Class()) {

            ConstituentsVector.push_back(GetPseudoJet(((Tower *) Object)->P4()));

        } else if (Object->IsA() == Muon::Class()) {

            ConstituentsVector.push_back(GetPseudoJet(((Muon *) Object)->P4()));

        } else {

            Print(-1, "something else", Object->ClassName());

        }
    }

    fastjet::JetDefinition jetDefinition(fastjet::antikt_algorithm, .7);
    fastjet::ClusterSequence JetClusterSequence(ConstituentsVector, jetDefinition);

    vector<PseudoJet> Jet = JetClusterSequence.inclusive_jets(20);

    if (Jet.size() != 1)Print(-1, "Jet Sum", Jet.size());

    return Jet.front();


}

bool HJetDelphes::GetEFlow()
{

    return GetEFlow(0, 0);

}

bool HJetDelphes::GetTaggedEFlow()
{

    return GetEFlow(1, 0);

}


bool HJetDelphes::GetEFlow(bool Tagging, bool Isolation)
{
    Print(1, "Get EFlow");

    // Tracks

    Track *EFlowTrackClone;
    Tower *EFlowPhotonClone;
    Tower *HadronClone;
    Muon *EFlowMuonClone;

//     PseudoJet JetCandidate;
    TObject *Object;
    bool Isolated;

    if (ClonesArrays->ElectronSum() > 0) Print(3, "Number of Electons", ClonesArrays->ElectronSum());
    if (ClonesArrays->MuonSum() > 0) Print(3, "Number of Muons", ClonesArrays->MuonSum());
    if (ClonesArrays->EFlowTrackSum() > 0) Print(2, "Number of E Flow Tracks", ClonesArrays->EFlowTrackSum());

    for (int EFlowTrackNumber = 0; EFlowTrackNumber < ClonesArrays->EFlowTrackSum() ; ++EFlowTrackNumber) {

        EFlowTrackClone = (Track *) ClonesArrays->EFlowTrackClonesArray->At(EFlowTrackNumber);
//         JetCandidate = GetPseudoJet(EFlowTrackClone->P4());

        // Make sure this is not an electron
        if (Isolation) {
//             Isolated = true;

//             for (int ElectronNumber = 0; ElectronNumber < ClonesArrays->ElectronSum(); ++ElectronNumber) {
//
//                 ElectronClone = (Electron *) ClonesArrays->ElectronClonesArray->At(ElectronNumber);
//                 Isolated = CheckIsolation(EFlowTrackClone, ElectronClone);
//
//             }

            Isolated = GetIsolation<Electron>(EFlowTrackClone,
// 					       ElectronClone,
                                              ClonesArrays->ElectronClonesArray);
            if(Isolated) Isolated = GetIsolation<Muon>(EFlowTrackClone,
// 	      MuonClone,
                                        ClonesArrays->MuonClonesArray);

            // make sure this is not a muon
//             for (int MuonNumber = 0; MuonNumber < ClonesArrays->MuonSum(); ++MuonNumber) {
//
//                 MuonClone = (Muon *) ClonesArrays->MuonClonesArray->At(MuonNumber);
//                 Isolated = CheckIsolation(EFlowTrackClone, MuonClone);
//
//             }

            if (!Isolated) continue;

        }


        EFlowJetVector.push_back(GetPseudoJet(EFlowTrackClone->P4()));
        Object = EFlowTrackClone->Particle.GetObject();
        if (Tagging) {

            EFlowJetVector.back().set_user_index(GetMotherId(Object));
            Print(3, "EFlow Id", EFlowJetVector.back().user_index());

        }

    }


    // Photons
    if (ClonesArrays->EFlowPhotonSum() > 0) Print(2, "Number of E Flow Photons", ClonesArrays->EFlowPhotonSum());
    if (ClonesArrays->PhotonSum() > 0) Print(2, "Number of Photons", ClonesArrays->PhotonSum());
    for (int EFlowPhotonNumber = 0; EFlowPhotonNumber < ClonesArrays->EFlowPhotonSum() ; ++EFlowPhotonNumber) {

        EFlowPhotonClone = (Tower *) ClonesArrays->EFlowPhotonClonesArray->At(EFlowPhotonNumber);
//         JetCandidate = GetPseudoJet(EFlowPhotonClone->P4());

        // Make sure this is not a photon
        if (Isolation) {
//             Isolated = true;

            Isolated = GetIsolation<Photon>(EFlowPhotonClone,
// 				     PhotonClone,
                                            ClonesArrays->PhotonClonesArray);
//             for (int PhotonNumber = 0; PhotonNumber < ClonesArrays->PhotonSum(); ++PhotonNumber) {
//
//                 PhotonClone = (Photon *) ClonesArrays->PhotonClonesArray->At(PhotonNumber);
//
//                 Isolated = CheckIsolation(EFlowPhotonClone, PhotonClone);
//
//             }

            if (!Isolated) continue;

        }


        EFlowJetVector.push_back(GetPseudoJet(EFlowPhotonClone->P4()));
        if (Tagging) {

            EFlowJetVector.back().set_user_info(new HJetInfo(GetJetId(EFlowPhotonClone)));
            EFlowJetVector.back().set_user_index(EFlowJetVector.back().user_info<HJetInfo>().GetMaximalId());
            Print(3, "EFlow Id", EFlowJetVector.back().user_index());

        }

    }

    // Neutral Hadrons
    if (ClonesArrays->EFlowNeutralHadronSum() > 0) Print(2, "Number of EF Neut Had", ClonesArrays->EFlowNeutralHadronSum());
    for (int HadronNumber = 0; HadronNumber < ClonesArrays->EFlowNeutralHadronSum(); ++HadronNumber) {

        HadronClone = (Tower *) ClonesArrays->EFlowNeutralHadronClonesArray->At(HadronNumber);

        EFlowJetVector.push_back(GetPseudoJet(HadronClone->P4()));
        if (Tagging) {

            EFlowJetVector.back().set_user_info(new HJetInfo(GetJetId(HadronClone)));
            EFlowJetVector.back().set_user_index(EFlowJetVector.back().user_info<HJetInfo>().GetMaximalId());
            Print(3, "EFlow Id", EFlowJetVector.back().user_index());

        }

    }

    // Muon
    if (ClonesArrays->EFlowMuonClonesArray) {

        Print(2, "Number of EF Muon", ClonesArrays->EFlowMuonSum());

        for (int MuonNumber = 0; MuonNumber < ClonesArrays->EFlowMuonSum(); ++MuonNumber) {

            EFlowMuonClone = (Muon *) ClonesArrays->EFlowMuonClonesArray->At(MuonNumber);

            if (Isolation) {
                // make sure this is not a muon
//                 Isolated = true;
                Isolated = GetIsolation<Muon>(EFlowMuonClone,
// 						MuonClone,
                                              ClonesArrays->MuonClonesArray);
//                 for (int MuonNumber = 0; MuonNumber < ClonesArrays->MuonSum(); ++MuonNumber) {
//
//                     MuonClone = (Muon *) ClonesArrays->MuonClonesArray->At(MuonNumber);
//                     Isolated = CheckIsolation(EFlowMuonClone, MuonClone);
//
//                 }
                if (!Isolated) continue;

            }

            EFlowJetVector.push_back(GetPseudoJet(EFlowMuonClone->P4()));
            Object = EFlowMuonClone->Particle.GetObject();
            if (Tagging) {
                EFlowJetVector.back().set_user_index(GetMotherId(Object));
                Print(3, "EFlow Id", EFlowJetVector.back().user_index());
            }

        }

    }

    Print(2, "Number of EFlow Jet", EFlowJetVector.size());

    return 1;

}


void HJetDelphes::GetGenJet()
{
    Print(1, "GetGenJet");
    Jet *GenJetClone;

    Print(2, "Number of GenJets",  ClonesArrays->GenJetSum());
    for (int GenJetNumber = 0; GenJetNumber <  ClonesArrays->GenJetSum(); ++GenJetNumber) {

        GenJetClone = (Jet *) ClonesArrays->GenJetClonesArray->At(GenJetNumber);

        GenJetVector.push_back(GetPseudoJet(GenJetClone->P4()));

    }

}












//  poor mans jet identification





struct HDistance {

    int Position = -1;

    int ParticleId = 0;

    float Distance = 999999;

};

// vector< PseudoJet > HJetDelphes::TagBottom(vector<PseudoJet> JetVector)
// {
//     Print(2, "Tag Jets");
//
//     vector<HDistance> DistanceVector;
//
//     Print(2, "Heavy Quarks", BottomJetVector.size());
//
//     for (unsigned ParticleNumber = 0; ParticleNumber < BottomJetVector.size(); ++ParticleNumber) {
//
//         HDistance JetDistance;
//         DistanceVector.push_back(JetDistance);
//
//         Print(2, "Particle ID", BottomJetVector[ParticleNumber].user_index());
//
//         for (unsigned JetNumber = 0; JetNumber < JetVector.size(); ++JetNumber) {
//
//             float Distance = JetVector[JetNumber].delta_R(BottomJetVector[ParticleNumber]);
//
//             Print(2, "Distance", Distance);
//
//             if (Distance < DistanceVector[ParticleNumber].Distance) {
//
//                 DistanceVector[ParticleNumber].Distance = Distance;
//                 DistanceVector[ParticleNumber].Position = JetNumber;
//                 DistanceVector[ParticleNumber].ParticleId = BottomJetVector[ParticleNumber].user_index();
//
//             }
//
//         }
//
//     }
//
//     for (unsigned ParticleNumber = 0; ParticleNumber < BottomJetVector.size(); ++ParticleNumber) {
//
//         Print(2, "Particle", DistanceVector[ParticleNumber].ParticleId);
//
//         if (JetVector[DistanceVector[ParticleNumber].Position].user_index() < 0) {
//
//             JetVector[DistanceVector[ParticleNumber].Position].set_user_index(DistanceVector[ParticleNumber].ParticleId);
//             Print(2, "JetPosition", DistanceVector[ParticleNumber].Position, DistanceVector[ParticleNumber].Distance);
//
//         } else {
//
//             Print(0, "Double tagging", DistanceVector[ParticleNumber].Position, DistanceVector[ParticleNumber].Distance);
//
//         }
//
//
//     }
//
//     return JetVector;
//
// };
//
// vector< PseudoJet > HJetDelphes::TagTop(vector<PseudoJet> JetVector)
// {
//     Print(2, "Tag Jets");
//
//     vector<HDistance> DistanceVector;
//
//     Print(2, "Heavy Quarks", TopJetVector.size());
//
//     for (unsigned ParticleNumber = 0; ParticleNumber < TopJetVector.size(); ++ParticleNumber) {
//
//         HDistance JetDistance;
//         DistanceVector.push_back(JetDistance);
//
//         Print(2, "Particle ID", TopJetVector[ParticleNumber].user_index());
//
//         for (unsigned JetNumber = 0; JetNumber < JetVector.size(); ++JetNumber) {
//
//             if (JetVector[JetNumber].user_index() == BottomId) {
//
//                 float Distance = JetVector[JetNumber].delta_R(TopJetVector[ParticleNumber]);
//
//                 Print(2, "Distance", Distance);
//
//                 if (Distance < DistanceVector[ParticleNumber].Distance) {
//
//                     DistanceVector[ParticleNumber].Distance = Distance;
//                     DistanceVector[ParticleNumber].Position = JetNumber;
//                     DistanceVector[ParticleNumber].ParticleId = TopJetVector[ParticleNumber].user_index();
//
//                 }
//
//             }
//
//         }
//
//     }
//
//     for (unsigned ParticleNumber = 0; ParticleNumber < TopJetVector.size(); ++ParticleNumber) {
//
//         Print(2, "Particle", DistanceVector[ParticleNumber].ParticleId);
//
//         if (JetVector[DistanceVector[ParticleNumber].Position].user_index() == BottomId) {
//
//         Print(2, "JetPosition", DistanceVector[ParticleNumber].Position, DistanceVector[ParticleNumber].Distance);
//
//             JetVector[DistanceVector[ParticleNumber].Position].set_user_index(DistanceVector[ParticleNumber].ParticleId);
//
//         } else  {
//
// //             Print(0,"Not a Bottom",JetVector[DistanceVector[ParticleNumber].Position].user_index() );
//
//             Print(0, "Double tagging", DistanceVector[ParticleNumber].Position, DistanceVector[ParticleNumber].Distance);
//
//         }
//
//
//     }
//
//
//     return JetVector;
//
// };



vector< PseudoJet > HJetDelphes::TagJets(vector<PseudoJet> JetVector)
{

    if (JetVector.size() == 0) return JetVector;

    JetVector = JetTagger(JetVector, BottomJetVector);
//     JetVector = JetTagger(JetVector, TopJetVector, BottomId); // FIXME do it right

    return JetVector;


}

vector< PseudoJet > HJetDelphes::JetTagger(vector<PseudoJet> JetVector, vector<PseudoJet> ParticleVector)
{

    JetVector = JetTagger(JetVector, ParticleVector, EmptyId);


    return JetVector;

}


vector< PseudoJet > HJetDelphes::JetTagger(vector<PseudoJet> JetVector, vector<PseudoJet> ParticleVector, int Prerequisit)
{
    Print(2, "Tag Jets");

    vector<HDistance> DistanceVector;

    Print(2, "Heavy Quarks", ParticleVector.size());

    for (unsigned ParticleNumber = 0; ParticleNumber < ParticleVector.size(); ++ParticleNumber) {

        HDistance JetDistance;
        DistanceVector.push_back(JetDistance);

        Print(2, "Particle ID", ParticleVector[ParticleNumber].user_index());

        for (unsigned JetNumber = 0; JetNumber < JetVector.size(); ++JetNumber) {

            if (JetVector[JetNumber].user_index() == Prerequisit) {

                float Distance = JetVector[JetNumber].delta_R(ParticleVector[ParticleNumber]);

                Print(2, "Distance", Distance);

                if (Distance < DistanceVector[ParticleNumber].Distance) {

                    DistanceVector[ParticleNumber].Distance = Distance;
                    DistanceVector[ParticleNumber].Position = JetNumber;
                    DistanceVector[ParticleNumber].ParticleId = ParticleVector[ParticleNumber].user_index();

                }

            }

        }

    }

    for (unsigned ParticleNumber = 0; ParticleNumber < ParticleVector.size(); ++ParticleNumber) {

        Print(2, "Particle", DistanceVector[ParticleNumber].ParticleId);

        if (JetVector[DistanceVector[ParticleNumber].Position].user_index() == Prerequisit) {

            Print(2, "JetPosition", DistanceVector[ParticleNumber].Position, DistanceVector[ParticleNumber].Distance);

            JetVector[DistanceVector[ParticleNumber].Position].set_user_index(DistanceVector[ParticleNumber].ParticleId);

        } else  {

            Print(2, "Double tagging", DistanceVector[ParticleNumber].Position, DistanceVector[ParticleNumber].Distance);

        }


    }


    return JetVector;

}


// vector< PseudoJet > HJetDelphes::TagJets(vector<PseudoJet> JetVector)
// {
//     Print(2, "Tag Jets");
//
//     if (JetVector.size() == 0) return JetVector;
//
//     RemoveBottoms();
//
// //     vector<vector<HDistance> DistanceMatrix;
//
//     vector<HDistance> DistanceVector;
//     vector<HDistance> SecondDistanceVector;
//     vector<HDistance> ThirdDistanceVector;
//
//     Print(2, "Heavy Quraks", ParticleJetVector.size());
//
//     for (unsigned ParticleNumber = 0; ParticleNumber < ParticleJetVector.size(); ++ParticleNumber) {
//
//         HDistance JetDistance;
//         DistanceVector.push_back(JetDistance);
//
//         HDistance SecondJetDistance;
//         SecondDistanceVector.push_back(SecondJetDistance);
//
//         HDistance ThirdJetDistance;
//         ThirdDistanceVector.push_back(ThirdJetDistance);
//
//         Print(2, "Particle ID", ParticleJetVector[ParticleNumber].user_index());
//
//         for (unsigned JetNumber = 0; JetNumber < JetVector.size(); ++JetNumber) {
//
//             float Distance = JetVector[JetNumber].delta_R(ParticleJetVector[ParticleNumber]);
//
//             Print(2, "Distance", Distance);
//
//             if (Distance < DistanceVector[ParticleNumber].Distance) {
//
//                 ThirdDistanceVector[ParticleNumber] = SecondDistanceVector[ParticleNumber];
//                 SecondDistanceVector[ParticleNumber] = DistanceVector[ParticleNumber];
//
//                 DistanceVector[ParticleNumber].Distance = Distance;
//                 DistanceVector[ParticleNumber].Position = JetNumber;
//                 DistanceVector[ParticleNumber].ParticleId = ParticleJetVector[ParticleNumber].user_index();
//
//             } else if (Distance < SecondDistanceVector[ParticleNumber].Distance) {
//
//                 ThirdDistanceVector[ParticleNumber] = SecondDistanceVector[ParticleNumber];
//
//                 SecondDistanceVector[ParticleNumber].Distance = Distance;
//                 SecondDistanceVector[ParticleNumber].Position = JetNumber;
//                 SecondDistanceVector[ParticleNumber].ParticleId = ParticleJetVector[ParticleNumber].user_index();
//
//
//             } else if (Distance < ThirdDistanceVector[ParticleNumber].Distance) {
//
//
//                 ThirdDistanceVector[ParticleNumber].Distance = Distance;
//                 ThirdDistanceVector[ParticleNumber].Position = JetNumber;
//                 ThirdDistanceVector[ParticleNumber].ParticleId = ParticleJetVector[ParticleNumber].user_index();
//
//             }
//
//         }
//
//     }
//
//     for (unsigned ParticleNumber = 0; ParticleNumber < ParticleJetVector.size(); ++ParticleNumber) {
//
//         Print(2, "Particle", DistanceVector[ParticleNumber].ParticleId);
//
//         for (unsigned ParticleNumber2 = 0; ParticleNumber2 < ParticleNumber; ++ParticleNumber2) {
//
//             if (DistanceVector[ParticleNumber].Position == DistanceVector[ParticleNumber2].Position) {
//
//                 if (DistanceVector[ParticleNumber].Distance < DistanceVector[ParticleNumber2].Distance) {
//
//                     if (DistanceVector[ParticleNumber2].Position != SecondDistanceVector[ParticleNumber2].Position) {
//
//                         DistanceVector[ParticleNumber2] = SecondDistanceVector[ParticleNumber2];
//
//                     } else {
//
//                         DistanceVector[ParticleNumber2] = ThirdDistanceVector[ParticleNumber2];
//
//                     }
//
//                 } else if (DistanceVector[ParticleNumber2].Distance < DistanceVector[ParticleNumber].Distance) {
//
//                     if (DistanceVector[ParticleNumber].Position != SecondDistanceVector[ParticleNumber].Position) {
//
//                         DistanceVector[ParticleNumber] = SecondDistanceVector[ParticleNumber];
//
//                     } else {
//
//                         DistanceVector[ParticleNumber] = ThirdDistanceVector[ParticleNumber];
//
//                     }
//
//                 } else Print(2, "What is going on here");
//
//             }
//
//         }
//
//
//         if (JetVector.size() > ParticleNumber) {
//             Print(2, "JetPosition", DistanceVector[ParticleNumber].Position, DistanceVector[ParticleNumber].Distance);
//             JetVector[DistanceVector[ParticleNumber].Position].set_user_index(DistanceVector[ParticleNumber].ParticleId);
//         }
//
//
//     }
//
//
//     return JetVector;
//
// }
//
// void HJetDelphes::RemoveBottoms()
// {
//     Print(1, "Remove Bottoms");
//
//     vector<HDistance> DistanceVector;
//
//     Print(2, "ParticleSum", ParticleJetVector.size());
//
//     for (unsigned ParticleNumber = 0; ParticleNumber < ParticleJetVector.size(); ++ParticleNumber) {
//
//         HDistance ParticleDistance;
//         ParticleDistance.ParticleId = ParticleJetVector[ParticleNumber].user_index();
//
//         Print(3, "Particle ID", ParticleDistance.ParticleId);
//
//         DistanceVector.push_back(ParticleDistance);
//
//         for (unsigned ParticleNumber2 = 0; ParticleNumber2 < ParticleNumber; ++ParticleNumber2) {
//
//             float Distance = ParticleJetVector[ParticleNumber].delta_R(ParticleJetVector[ParticleNumber2]);
//
//             Print(3, "Distance", ParticleJetVector[ParticleNumber2].user_index(), Distance);
//
//             if (ParticleJetVector[ParticleNumber].user_index() != ParticleJetVector[ParticleNumber2].user_index()) {
//
//                 if (Distance < DistanceVector[ParticleNumber].Distance) {
//
//                     DistanceVector[ParticleNumber].Distance = Distance;
//                     DistanceVector[ParticleNumber].Position = ParticleNumber2;
//
//                 }
//
//                 if (Distance < DistanceVector[ParticleNumber2].Distance) {
//
//                     DistanceVector[ParticleNumber2].Distance = Distance;
//                     DistanceVector[ParticleNumber2].Position = ParticleNumber;
//
//                 }
//
//             }
//
//         }
//
//     }
//
//     for (unsigned ParticleNumber = 0; ParticleNumber < DistanceVector.size(); ++ParticleNumber) {
//
//         if (DistanceVector[ParticleNumber].ParticleId == TopId) {
//
//             Print(3, "Final Particle Distance", ParticleJetVector[DistanceVector[ParticleNumber].Position].user_index(), DistanceVector[ParticleNumber].Distance);
//
//             ParticleJetVector.erase(ParticleJetVector.begin() + DistanceVector[ParticleNumber].Position);
//
//         }
//
//     }
//
// }




