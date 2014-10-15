# include "HJetDelphes.hh"

HJetDelphes::HJetDelphes()
{

    Print(1, "Constructor");

//     DebugLevel = 4;

}

HJetDelphes::~HJetDelphes()
{

    Print(1, "Destructor");

}

bool HJetDelphes::GetJets(HJetDetails JetDetails)
{

    Print(2, "Get Jets", ClonesArrays->JetSum());

    for (int JetNumber = 0; JetNumber < ClonesArrays->JetSum(); ++JetNumber) {

        Print(4, "Jet Number", JetNumber);
        const Jet *const JetClone = (Jet *)ClonesArrays->JetClonesArray->At(JetNumber);

        if (Structure) {

            Jets.push_back(GetConstituents(JetClone));

        } else {

            Jets.push_back(GetPseudoJet(const_cast<Jet *>(JetClone)->P4()));

        }

        if (Tagging) {

            Jets.back().set_user_info(new HJetInfo(GetJetId(JetClone)));
            Jets.back().set_user_index(Jets.back().user_info<HJetInfo>().GetMaximalId());


        }

        GetDelphesTags(JetClone);

//         Jets[JetNumber].user_info<HJetInfo>().PrintAllInfos();
        Print(0, "Tag", Jets[JetNumber].user_info<HJetInfo>().GetMaximalId(), Jets[JetNumber].user_info<HJetInfo>().GetMaximalFraction());

    }
    Print(0, "Loop finished");
    return 1;

}

void HJetDelphes::GetDelphesTags(const Jet *const JetClone)
{
    Print(2, "Get taggs");

    if (JetClone->TauTag == 1) {

        Print(4, "Has Tau Tag");

        GetTau(JetClone);

    } else if (JetClone->BTag > 0) {

        Print(4, "Has B Tag");

        BottomLorentzVectors.push_back(const_cast<Jet *>(JetClone)->P4());
        BottomJets.push_back(GetPseudoJet(const_cast<Jet *>(JetClone)->P4()));

    } else {

        JetLorentzVectors.push_back(const_cast<Jet *>(JetClone)->P4());

    }

}


void HJetDelphes::GetTau(const Jet *const JetClone)
{

    Print(2, "TauTagCalculations");

    if (JetClone->Charge == - 1) {

        TauLorentzVectors.push_back(const_cast<Jet *>(JetClone)->P4());
        Print(3, "Tau Jet");

    } else if (JetClone->Charge == 1) {

        AntiTauLorentzVectors.push_back(const_cast<Jet *>(JetClone)->P4());
        Print(3, "Anti Tau Jet");

    } else Print(0, "Jet Charge: ", JetClone->Charge);

}

int HJetDelphes::GetMotherId(const TObject *const Object)
{


    Print(2, "Get Mother Id", ClonesArrays->ParticleSum());

    if (Object->IsA() != GenParticle::Class()) {

        Print(0, "Object is", Object->ClassName());
        return 0;

    }

    GenParticle *ParticleClone = (GenParticle *) Object;


    int MotherId = EmptyId;
//     int *ThisBranch = &MotherId;
//     Print(0,"This",*ThisBranch);

    MotherId = GetMotherId(ParticleClone, MotherId, 1/*, ThisBranch*/);
        
//     int *ThisBranch = &MotherId;
//     Print(0,"This",*ThisBranch);
    

//     for (int i = 0; i < ClonesArrays->ParticleSum(); ++i) {
//         Print(0, "Pointer", i, *(Particles.at(i)), MotherId);
//     }


    Print(3, "Mother Id", MotherId);

    return MotherId;

}




int HJetDelphes::GetMotherId(GenParticle *ParticleClone, int BranchId, int WhichMother/*, int *ThisBranch*/)
{

    Print(2, "Get Mother Id", ParticleClone->PID);
    const int EmptyPosition = -1;

    while (ParticleClone->M1 != EmptyPosition) {

        if (ParticleClone->M2 != EmptyPosition) {

            Print(3, "Mother 2", ParticleClone->M2);
//             Print(0,"This",*ThisBranch);
//             Particles[ParticleClone->M2] = ThisBranch;
            BranchId = GetMotherId((GenParticle *) ClonesArrays->ParticleClonesArray->At(ParticleClone->M2), BranchId, 2/*, ThisBranch*/);

        }
//         if (BranchId == - ParticleClone->PID) DebugLevel = 4;

        BranchId = JetTag->GetBranchId(ParticleClone->PID, BranchId, WhichMother);
        
        Print(3, "Mother 1", ParticleClone->M1);
//         Print(0,"This",*ThisBranch);
//         Particles[ParticleClone->M1] = ThisBranch;
        ParticleClone = (GenParticle *) ClonesArrays->ParticleClonesArray->At(ParticleClone->M1);

        WhichMother = 1;
    }

    Print(3, "Branch Id", BranchId);

    return BranchId;

}



//         BranchId = GetBranchId(ParticleClone->PID, BranchId);
//         if (ParticleClone->PID == -6) DebugLevel = 4;
//         if (ParticleClone->PID == HeavyHiggsId) {
//
//             Print(0, "PID", ParticleClone->PID);
//
//             if (ParticleClone->D1 != -1) {
//
//                 GenParticle *Daughter1 = (GenParticle *) ClonesArrays->ParticleClonesArray->At(ParticleClone->D1);
//                 Print(0, "D1", Daughter1->PID);
//
//             }
//             if (ParticleClone->D2 != -1) {
//                 GenParticle *Daughter2 = (GenParticle *) ClonesArrays->ParticleClonesArray->At(ParticleClone->D2);
//
//                 Print(0, "D2", Daughter2->PID);
//             }
//
//
//         }


PseudoJet HJetDelphes::GetConstituents(const Jet *const JetClone) const
{

    Print(2, "Get Constituents");

    vector<PseudoJet> Constituents;

    for (int ConstituentNumber = 0; ConstituentNumber < JetClone->Constituents.GetEntriesFast(); ++ConstituentNumber) {

        const TObject *const Object = JetClone->Constituents.At(ConstituentNumber);

        if (Object == 0) continue;

        Constituents.push_back(GetConstituentJet(Object));

    }

    return fastjet::join(Constituents);

}

bool HJetDelphes::GetEFlow(const HJetDetails JetDetails)
{
    Print(2, "Get EFlow");


//     int Empty = EmptyId;
//     Particles.assign(ClonesArrays->ParticleSum(), &Empty);

    if (ClonesArrays->EFlowTrackClonesArray) GetTrackEFlow(JetDetails);
    if (ClonesArrays->EFlowPhotonClonesArray) GetPhotonEFlow(JetDetails);
    if (ClonesArrays->EFlowNeutralHadronClonesArray) GetHadronEFlow(JetDetails);
    if (ClonesArrays->EFlowMuonClonesArray) GetMuonEFlow(JetDetails);

    Print(3, "Number of EFlow Jet", EFlowJets.size());

    return 1;

}


void HJetDelphes::GetTrackEFlow(const HJetDetails JetDetails)
{
    Print(2, "Get Track EFlow", ClonesArrays->EFlowTrackSum());

    if (ClonesArrays->ElectronSum() > 0) Print(4, "Number of Electons", ClonesArrays->ElectronSum());
    if (ClonesArrays->MuonSum() > 0) Print(4, "Number of Muons", ClonesArrays->MuonSum());

    for (int EFlowTrackNumber = 0; EFlowTrackNumber < ClonesArrays->EFlowTrackSum() ; ++EFlowTrackNumber) {

        const Track *const EFlowTrackClone = (Track *) ClonesArrays->EFlowTrackClonesArray->At(EFlowTrackNumber);

        if (Isolation || TaggingIsolation) {

            bool Isolated = GetIsolation<Electron>(EFlowTrackClone, ClonesArrays->ElectronClonesArray);
            if (Isolated) Isolated = GetIsolation<Muon>(EFlowTrackClone, ClonesArrays->MuonClonesArray);
            if (!Isolated) continue;

        }

        EFlowJets.push_back(GetPseudoJet(const_cast<Track *>(EFlowTrackClone)->P4()));

        if (Tagging || TaggingIsolation) {

            EFlowJets.back().set_user_index(GetMotherId(EFlowTrackClone->Particle.GetObject()));
            Print(4, "Track EFlow Id", EFlowJets.back().user_index());

        }

    }


}

void HJetDelphes::GetPhotonEFlow(const HJetDetails JetDetails)
{
    Print(2, "Get Photon EFlow", ClonesArrays->EFlowPhotonSum());

    if (ClonesArrays->PhotonSum() > 0) Print(3, "Number of Photons", ClonesArrays->PhotonSum());
    for (int EFlowPhotonNumber = 0; EFlowPhotonNumber < ClonesArrays->EFlowPhotonSum() ; ++EFlowPhotonNumber) {

        const Tower *const EFlowPhotonClone = (Tower *) ClonesArrays->EFlowPhotonClonesArray->At(EFlowPhotonNumber);

        if (Isolation || TaggingIsolation) {

            bool Isolated = GetIsolation<Photon>(EFlowPhotonClone, ClonesArrays->PhotonClonesArray);
            if (!Isolated) continue;

        }

        EFlowJets.push_back(GetPseudoJet(const_cast<Tower *>(EFlowPhotonClone)->P4()));

        if (Tagging || TaggingIsolation) {

            EFlowJets.back().set_user_info(new HJetInfo(GetJetId(EFlowPhotonClone)));
            EFlowJets.back().set_user_index(EFlowJets.back().user_info<HJetInfo>().GetMaximalId());
            Print(4, "Photon EFlow Id", EFlowJets.back().user_index());

        }

    }

}

void HJetDelphes::GetHadronEFlow(const HJetDetails JetDetails)
{

    Print(2, "Get Hadron EFlow", ClonesArrays->EFlowNeutralHadronSum());

    for (int HadronNumber = 0; HadronNumber < ClonesArrays->EFlowNeutralHadronSum(); ++HadronNumber) {

        const Tower *const HadronClone = (Tower *) ClonesArrays->EFlowNeutralHadronClonesArray->At(HadronNumber);

        EFlowJets.push_back(GetPseudoJet(const_cast<Tower *>(HadronClone)->P4()));
        if (Tagging || TaggingIsolation) {

            EFlowJets.back().set_user_info(new HJetInfo(GetJetId(HadronClone)));
            EFlowJets.back().set_user_index(EFlowJets.back().user_info<HJetInfo>().GetMaximalId());
            Print(4, "Hadron EFlow Id", EFlowJets.back().user_index());

        }

    }

}

void HJetDelphes::GetMuonEFlow(const HJetDetails JetDetails)
{

    Print(2, "Get Muon EFlow", ClonesArrays->EFlowMuonSum());

    for (int MuonNumber = 0; MuonNumber < ClonesArrays->EFlowMuonSum(); ++MuonNumber) {

        const Muon *const EFlowMuonClone = (Muon *) ClonesArrays->EFlowMuonClonesArray->At(MuonNumber);

        if (Isolation || TaggingIsolation) {

            bool Isolated = GetIsolation<Muon>(EFlowMuonClone, ClonesArrays->MuonClonesArray);
            if (!Isolated) continue;

        }

        EFlowJets.push_back(GetPseudoJet(const_cast<Muon *>(EFlowMuonClone)->P4()));

        if (Tagging || TaggingIsolation) {
            EFlowJets.back().set_user_index(GetMotherId(EFlowMuonClone->Particle.GetObject()));
            Print(4, "Muon EFlow Id", EFlowJets.back().user_index());
        }

    }

}



void HJetDelphes::GetGenJet()
{

    Print(2, "GetGenJet", ClonesArrays->GenJetSum());

    for (int GenJetNumber = 0; GenJetNumber <  ClonesArrays->GenJetSum(); ++GenJetNumber) {

        const Jet *const GenJetClone = (Jet *) ClonesArrays->GenJetClonesArray->At(GenJetNumber);

        GenJets.push_back(GetPseudoJet(const_cast<Jet *>(GenJetClone)->P4()));

    }

}
