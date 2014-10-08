# include "HJetDelphes.hh"

HJetDelphes::HJetDelphes()
{

    Print(1, "Constructor");

//     Debug =4;

}

HJetDelphes::~HJetDelphes()
{

    Print(1, "Destructor");

}

bool HJetDelphes::GetJets()
{

    return GetJets(0, 0);

}

bool HJetDelphes::GetTaggedJets()
{

    return GetJets(1, 0);

}

bool HJetDelphes::GetStructuredJets()
{

    return GetJets(0, 1);

}

bool HJetDelphes::GetJets(bool Tagging, bool Structure)
{

    Print(2, "Get Jets", ClonesArrays->JetSum());

    for (int JetNumber = 0; JetNumber < ClonesArrays->JetSum(); ++JetNumber) {

        Print(4, "Jet Number", JetNumber);
        const Jet* JetClone = (Jet *)ClonesArrays->JetClonesArray->At(JetNumber);

        if (Structure) {

            JetVector.push_back(GetConstituents(*JetClone));

        } else {

            JetVector.push_back(GetPseudoJet(const_cast<Jet*>(JetClone)->P4()));

        }

        if (Tagging) {
            
            JetVector.back().set_user_info(new HJetInfo(GetJetId(JetClone)));
            JetVector.back().set_user_index(JetVector.back().user_info<HJetInfo>().GetMaximalId());
            
            
        }

        GetDelphesTags(*JetClone);

//         JetVector[JetNumber].user_info<HJetInfo>().PrintAllInfos();
        Print(0, "Tag", JetVector[JetNumber].user_info<HJetInfo>().GetMaximalId(), JetVector[JetNumber].user_info<HJetInfo>().GetMaximalFraction());
    
    }
    Print(0, "Loop finished");
    return 1;

}

void HJetDelphes::GetDelphesTags(const Jet& JetClone)
{
    Print(2, "Get taggs");

    if (JetClone.TauTag == 1) {

        Print(4, "Has Tau Tag");

        GetTau(JetClone);

    } else if (JetClone.BTag > 0) {

        Print(4, "Has B Tag");

        BottomLorentzVectorVector.push_back(const_cast<Jet*>(&JetClone)->P4());
        BottomJetVector.push_back(GetPseudoJet(const_cast<Jet*>(&JetClone)->P4()));

    } else {

        JetLorentzVectorVector.push_back(const_cast<Jet*>(&JetClone)->P4());

    }

}


void HJetDelphes::GetTau(const Jet& JetClone)
{

    Print(2, "TauTagCalculations");

    if (JetClone.Charge == - 1) {

        TauLorentzVectorVector.push_back(const_cast<Jet*>(&JetClone)->P4());
        Print(3, "Tau Jet");

    } else if (JetClone.Charge == 1) {

        AntiTauLorentzVectorVector.push_back(const_cast<Jet*>(&JetClone)->P4());
        Print(3, "Anti Tau Jet");

    } else Print(0, "Jet Charge: ", JetClone.Charge);

}

int HJetDelphes::GetMotherId(const TObject& Object) const
{

    Print(2, "Get Mother Id", ClonesArrays->ParticleSum());


    if (Object.IsA() != GenParticle::Class()) {

        Print(0, "it is", Object.ClassName());
        return 0;

    }

    GenParticle *ParticleClone = (GenParticle *) &Object;

    int MotherId = EmptyId;
    int ParticleId = ParticleClone->PID;
    int MotherPosition = ParticleClone->M1;
    Print(4, "Particle M1", MotherPosition);

    while (MotherPosition != -1) {

        if (
            (abs(ParticleId) == GluonId || abs(ParticleId) == UpId || abs(ParticleId) == DownId || abs(ParticleId) == StrangeId || abs(ParticleId) == CharmId || abs(ParticleId) == UpDown0Id || abs(ParticleId) == UpDown1Id || abs(ParticleId) == UpUp1Id || abs(ParticleId) == DownDown1Id)
            && (abs(MotherId) != TopId && abs(MotherId) != CpvHiggsId && abs(MotherId) != HeavyHiggsId && abs(MotherId) != BottomId)) {
            MotherId = IsrId;
        } else if (abs(ParticleId) == BottomId
                   && (abs(MotherId) != TopId && abs(MotherId) != CpvHiggsId)) {
            MotherId = ParticleId;
        } else if (abs(ParticleId) == TopId && abs(MotherId) != HeavyHiggsId) {
            MotherId = ParticleId;
        } else if (abs(ParticleId) == HeavyHiggsId || abs(ParticleId) == CpvHiggsId) {
            MotherId = ParticleId;
        }

        Print(4, "Mother Id", MotherId);

        if (MotherPosition > ClonesArrays->ParticleSum()) {

          Print(0, "Faulty eMotherPositionvent");
            continue;

        }
        ParticleClone = (GenParticle *) ClonesArrays->ParticleClonesArray->At(MotherPosition);
        ParticleId = ParticleClone->PID;
        MotherPosition = ParticleClone->M1;

        Print(4, "Particle Id", ParticleClone->PID);

    }

    if (MotherId == EmptyId)
        Print(0, "Mother Id", MotherId);

    return MotherId;

}


PseudoJet HJetDelphes::GetConstituents(const Jet &JetClone) const
{

    Print(2, "Get Constituents");

    vector<PseudoJet> ConstituentsVector;

    for (int ConstituentNumber = 0; ConstituentNumber < JetClone.Constituents.GetEntriesFast(); ++ConstituentNumber) {

        const TObject *Object = JetClone.Constituents.At(ConstituentNumber);

        if (Object == 0) continue;
        
        ConstituentsVector.push_back(GetConstituentJet(*Object));

    }

    return fastjet::join(ConstituentsVector);

}

bool HJetDelphes::GetEFlow()
{

    return GetEFlow(0, 1);

}

bool HJetDelphes::GetTaggedEFlow()
{

    return GetEFlow(1, 1);

}


bool HJetDelphes::GetEFlow(bool Tagging, bool Isolation)
{
    Print(2, "Get EFlow");

    if (ClonesArrays->EFlowTrackClonesArray) GetTrackEFlow(Tagging,Isolation);
    if (ClonesArrays->EFlowPhotonClonesArray) GetPhotonEFlow(Tagging,Isolation);
    if (ClonesArrays->EFlowNeutralHadronClonesArray) GetHadronEFlow(Tagging,Isolation);
    if (ClonesArrays->EFlowMuonClonesArray) GetMuonEFlow(Tagging,Isolation);

    Print(3, "Number of EFlow Jet", EFlowJetVector.size());

    return 1;

}


void HJetDelphes::GetTrackEFlow(bool Tagging, bool Isolation)
{

    if (ClonesArrays->ElectronSum() > 0) Print(4, "Number of Electons", ClonesArrays->ElectronSum());
    if (ClonesArrays->MuonSum() > 0) Print(4, "Number of Muons", ClonesArrays->MuonSum());
    if (ClonesArrays->EFlowTrackSum() > 0) Print(3, "Number of E Flow Tracks", ClonesArrays->EFlowTrackSum());
    for (int EFlowTrackNumber = 0; EFlowTrackNumber < ClonesArrays->EFlowTrackSum() ; ++EFlowTrackNumber) {

        const Track *EFlowTrackClone = (Track *) ClonesArrays->EFlowTrackClonesArray->At(EFlowTrackNumber);

        if (Isolation) {

            bool Isolated = GetIsolation<Electron>(*EFlowTrackClone, *ClonesArrays->ElectronClonesArray);
            if (Isolated) Isolated = GetIsolation<Muon>(*EFlowTrackClone, *ClonesArrays->MuonClonesArray);
            if (!Isolated) continue;

        }

        EFlowJetVector.push_back(GetPseudoJet(const_cast<Track*>(EFlowTrackClone)->P4()));
        const TObject *Object = EFlowTrackClone->Particle.GetObject();

        if (Tagging) {

            EFlowJetVector.back().set_user_index(GetMotherId(*Object));
            Print(4, "EFlow Id", EFlowJetVector.back().user_index());

        }

    }


}

void HJetDelphes::GetPhotonEFlow(bool Tagging, bool Isolation)
{

    if (ClonesArrays->EFlowPhotonSum() > 0) Print(3, "Number of E Flow Photons", ClonesArrays->EFlowPhotonSum());
    if (ClonesArrays->PhotonSum() > 0) Print(3, "Number of Photons", ClonesArrays->PhotonSum());
    for (int EFlowPhotonNumber = 0; EFlowPhotonNumber < ClonesArrays->EFlowPhotonSum() ; ++EFlowPhotonNumber) {

        const Tower *EFlowPhotonClone = (Tower *) ClonesArrays->EFlowPhotonClonesArray->At(EFlowPhotonNumber);

        if (Isolation) {

            bool Isolated = GetIsolation<Photon>(*EFlowPhotonClone, *ClonesArrays->PhotonClonesArray);
            if (!Isolated) continue;

        }

        EFlowJetVector.push_back(GetPseudoJet(const_cast<Tower*>(EFlowPhotonClone)->P4()));

        if (Tagging) {

            EFlowJetVector.back().set_user_info(new HJetInfo(GetJetId(EFlowPhotonClone)));
            EFlowJetVector.back().set_user_index(EFlowJetVector.back().user_info<HJetInfo>().GetMaximalId());
            Print(4, "EFlow Id", EFlowJetVector.back().user_index());

        }

    }

}

void HJetDelphes::GetHadronEFlow(bool Tagging, bool Isolation)
{

    if (ClonesArrays->EFlowNeutralHadronSum() > 0) Print(3, "Number of EF Neut Had", ClonesArrays->EFlowNeutralHadronSum());
    for (int HadronNumber = 0; HadronNumber < ClonesArrays->EFlowNeutralHadronSum(); ++HadronNumber) {

        const Tower *HadronClone = (Tower *) ClonesArrays->EFlowNeutralHadronClonesArray->At(HadronNumber);

        EFlowJetVector.push_back(GetPseudoJet(const_cast<Tower*>(HadronClone)->P4()));
        if (Tagging) {

            EFlowJetVector.back().set_user_info(new HJetInfo(GetJetId(HadronClone)));
            EFlowJetVector.back().set_user_index(EFlowJetVector.back().user_info<HJetInfo>().GetMaximalId());
            Print(4, "EFlow Id", EFlowJetVector.back().user_index());

        }

    }

}

void HJetDelphes::GetMuonEFlow(bool Tagging, bool Isolation)
{

    Print(3, "Number of EF Muon", ClonesArrays->EFlowMuonSum());

    for (int MuonNumber = 0; MuonNumber < ClonesArrays->EFlowMuonSum(); ++MuonNumber) {

        const Muon *EFlowMuonClone = (Muon *) ClonesArrays->EFlowMuonClonesArray->At(MuonNumber);

        if (Isolation) {

            bool Isolated = GetIsolation<Muon>(*EFlowMuonClone, *ClonesArrays->MuonClonesArray);
            if (!Isolated) continue;

        }

        EFlowJetVector.push_back(GetPseudoJet(const_cast<Muon*>(EFlowMuonClone)->P4()));
        const TObject* Object = EFlowMuonClone->Particle.GetObject();
        if (Tagging) {
            EFlowJetVector.back().set_user_index(GetMotherId(*Object));
            Print(4, "EFlow Id", EFlowJetVector.back().user_index());
        }

    }

}



void HJetDelphes::GetGenJet()
{
    Print(2, "GetGenJet");

    Print(3, "Number of GenJets",  ClonesArrays->GenJetSum());
    for (int GenJetNumber = 0; GenJetNumber <  ClonesArrays->GenJetSum(); ++GenJetNumber) {

        const Jet *GenJetClone = (Jet *) ClonesArrays->GenJetClonesArray->At(GenJetNumber);

        GenJetVector.push_back(GetPseudoJet(const_cast<Jet*>(GenJetClone)->P4()));

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
//     Print(3, "Tag Jets");
//
//     vector<HDistance> DistanceVector;
//
//     Print(3, "Heavy Quarks", BottomJetVector.size());
//
//     for (unsigned ParticleNumber = 0; ParticleNumber < BottomJetVector.size(); ++ParticleNumber) {
//
//         HDistance JetDistance;
//         DistanceVector.push_back(JetDistance);
//
//         Print(3, "Particle ID", BottomJetVector[ParticleNumber].user_index());
//
//         for (unsigned JetNumber = 0; JetNumber < JetVector.size(); ++JetNumber) {
//
//             float Distance = JetVector[JetNumber].delta_R(BottomJetVector[ParticleNumber]);
//
//             Print(3, "Distance", Distance);
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
//         Print(3, "Particle", DistanceVector[ParticleNumber].ParticleId);
//
//         if (JetVector[DistanceVector[ParticleNumber].Position].user_index() < 0) {
//
//             JetVector[DistanceVector[ParticleNumber].Position].set_user_index(DistanceVector[ParticleNumber].ParticleId);
//             Print(3, "JetPosition", DistanceVector[ParticleNumber].Position, DistanceVector[ParticleNumber].Distance);
//
//         } else {
//
//             Print(1, "Double tagging", DistanceVector[ParticleNumber].Position, DistanceVector[ParticleNumber].Distance);
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
//     Print(3, "Tag Jets");
//
//     vector<HDistance> DistanceVector;
//
//     Print(3, "Heavy Quarks", TopJetVector.size());
//
//     for (unsigned ParticleNumber = 0; ParticleNumber < TopJetVector.size(); ++ParticleNumber) {
//
//         HDistance JetDistance;
//         DistanceVector.push_back(JetDistance);
//
//         Print(3, "Particle ID", TopJetVector[ParticleNumber].user_index());
//
//         for (unsigned JetNumber = 0; JetNumber < JetVector.size(); ++JetNumber) {
//
//             if (JetVector[JetNumber].user_index() == BottomId) {
//
//                 float Distance = JetVector[JetNumber].delta_R(TopJetVector[ParticleNumber]);
//
//                 Print(3, "Distance", Distance);
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
//         Print(3, "Particle", DistanceVector[ParticleNumber].ParticleId);
//
//         if (JetVector[DistanceVector[ParticleNumber].Position].user_index() == BottomId) {
//
//         Print(3, "JetPosition", DistanceVector[ParticleNumber].Position, DistanceVector[ParticleNumber].Distance);
//
//             JetVector[DistanceVector[ParticleNumber].Position].set_user_index(DistanceVector[ParticleNumber].ParticleId);
//
//         } else  {
//
// //             Print(1,"Not a Bottom",JetVector[DistanceVector[ParticleNumber].Position].user_index() );
//
//             Print(1, "Double tagging", DistanceVector[ParticleNumber].Position, DistanceVector[ParticleNumber].Distance);
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
    Print(3, "Tag Jets");

    vector<HDistance> DistanceVector;

    Print(3, "Heavy Quarks", ParticleVector.size());

    for (unsigned ParticleNumber = 0; ParticleNumber < ParticleVector.size(); ++ParticleNumber) {

        HDistance JetDistance;
        DistanceVector.push_back(JetDistance);

        Print(3, "Particle ID", ParticleVector[ParticleNumber].user_index());

        for (unsigned JetNumber = 0; JetNumber < JetVector.size(); ++JetNumber) {

            if (JetVector[JetNumber].user_index() == Prerequisit) {

                float Distance = JetVector[JetNumber].delta_R(ParticleVector[ParticleNumber]);

                Print(3, "Distance", Distance);

                if (Distance < DistanceVector[ParticleNumber].Distance) {

                    DistanceVector[ParticleNumber].Distance = Distance;
                    DistanceVector[ParticleNumber].Position = JetNumber;
                    DistanceVector[ParticleNumber].ParticleId = ParticleVector[ParticleNumber].user_index();

                }

            }

        }

    }

    for (unsigned ParticleNumber = 0; ParticleNumber < ParticleVector.size(); ++ParticleNumber) {

        Print(3, "Particle", DistanceVector[ParticleNumber].ParticleId);

        if (JetVector[DistanceVector[ParticleNumber].Position].user_index() == Prerequisit) {

            Print(3, "JetPosition", DistanceVector[ParticleNumber].Position, DistanceVector[ParticleNumber].Distance);

            JetVector[DistanceVector[ParticleNumber].Position].set_user_index(DistanceVector[ParticleNumber].ParticleId);

        } else  {

            Print(3, "Double tagging", DistanceVector[ParticleNumber].Position, DistanceVector[ParticleNumber].Distance);

        }


    }


    return JetVector;

}


// vector< PseudoJet > HJetDelphes::TagJets(vector<PseudoJet> JetVector)
// {
//     Print(3, "Tag Jets");
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
//     Print(3, "Heavy Quraks", ParticleJetVector.size());
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
//         Print(3, "Particle ID", ParticleJetVector[ParticleNumber].user_index());
//
//         for (unsigned JetNumber = 0; JetNumber < JetVector.size(); ++JetNumber) {
//
//             float Distance = JetVector[JetNumber].delta_R(ParticleJetVector[ParticleNumber]);
//
//             Print(3, "Distance", Distance);
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
//         Print(3, "Particle", DistanceVector[ParticleNumber].ParticleId);
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
//                 } else Print(3, "What is going on here");
//
//             }
//
//         }
//
//
//         if (JetVector.size() > ParticleNumber) {
//             Print(3, "JetPosition", DistanceVector[ParticleNumber].Position, DistanceVector[ParticleNumber].Distance);
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
//     Print(2, "Remove Bottoms");
//
//     vector<HDistance> DistanceVector;
//
//     Print(3, "ParticleSum", ParticleJetVector.size());
//
//     for (unsigned ParticleNumber = 0; ParticleNumber < ParticleJetVector.size(); ++ParticleNumber) {
//
//         HDistance ParticleDistance;
//         ParticleDistance.ParticleId = ParticleJetVector[ParticleNumber].user_index();
//
//         Print(4, "Particle ID", ParticleDistance.ParticleId);
//
//         DistanceVector.push_back(ParticleDistance);
//
//         for (unsigned ParticleNumber2 = 0; ParticleNumber2 < ParticleNumber; ++ParticleNumber2) {
//
//             float Distance = ParticleJetVector[ParticleNumber].delta_R(ParticleJetVector[ParticleNumber2]);
//
//             Print(4, "Distance", ParticleJetVector[ParticleNumber2].user_index(), Distance);
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
//             Print(4, "Final Particle Distance", ParticleJetVector[DistanceVector[ParticleNumber].Position].user_index(), DistanceVector[ParticleNumber].Distance);
//
//             ParticleJetVector.erase(ParticleJetVector.begin() + DistanceVector[ParticleNumber].Position);
//
//         }
//
//     }
//
// }






