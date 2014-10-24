# include "HJetDelphes.hh"

Analysis::HDelphes::HJet::HJet()
{

    Print(1, "Constructor");

//     DebugLevel = 4;

}

Analysis::HDelphes::HJet::~HJet()
{

    Print(1, "Destructor");

}

void Analysis::HDelphes::HJet::NewEvent(const Analysis::HClonesArray *const NewClonesArrays)
{

    Print(2, "New Event");

    HJet::NewEvent(NewClonesArrays);

    Topology.assign(ClonesArrays->ParticleSum(), EmptyId); // FIXME why is this not working at this stage

    Print(2, "Topology", Topology.size());

}

bool Analysis::HDelphes::HJet::GetJets(HJetDetails JetDetails)
{

    Print(2, "Get Jets", ClonesArrays->JetSum());

    for (int JetNumber : HRange(ClonesArrays->JetSum())) {

        Print(4, "Jet Number", JetNumber);
        const Jet *const JetClone = (Jet *)ClonesArrays->JetClonesArray->At(JetNumber);

        if (JetDetails == Structure) {

            Jets.push_back(GetConstituents(JetClone));

        } else {

            Jets.push_back(GetPseudoJet(const_cast<Jet *>(JetClone)->P4()));

        }

        if (JetDetails == Tagging) {

            Jets.back().set_user_info(new Analysis::HJetInfo(GetJetId(JetClone)));
            Jets.back().set_user_index(Jets.back().user_info<Analysis::HJetInfo>().GetMaximalId());


        }

        GetDelphesTags(JetClone);

//         Jets.at(JetNumber).user_info<HJetInfo>().PrintAllInfos();
        Print(0, "Tag", Jets.at(JetNumber).user_info<Analysis::HJetInfo>().GetMaximalId(), Jets.at(JetNumber).user_info<Analysis::HJetInfo>().GetMaximalFraction());

    }

    return 1;

}

void Analysis::HDelphes::HJet::GetDelphesTags(const Jet *const JetClone)
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


void Analysis::HDelphes::HJet::GetTau(const Jet *const JetClone)
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

int Analysis::HDelphes::HJet::GetMotherId(const TObject *const Object)
{

    Print(3, "Get Mother Id", ClonesArrays->ParticleSum());

    if (abs(Topology.size()) != ClonesArrays->ParticleSum()) {
        Print(1, "Resize", Topology.size(), ClonesArrays->ParticleSum()); // FIXME why is this necessary
        Topology.assign(ClonesArrays->ParticleSum(), EmptyId);
    }

    if (Object->IsA() != GenParticle::Class() || Object == 0) {

        Print(0, "Object is", Object->ClassName());
        return 0;

    }

    int MotherId = EmptyId;
    const int Position = ClonesArrays->ParticleClonesArray->IndexOf(Object);
    GenParticle *const ParticleClone = (GenParticle *) Object;

    MotherId = GetMotherId(ParticleClone, MotherId, Position);

    Print(3, "Mother Id", MotherId);
    std::replace(Topology.begin(), Topology.end(), 100, MotherId);

    if(MotherId == EmptyId) Print(0,"No Mother Id",ParticleClone->PID);

    return MotherId;

}

int Analysis::HDelphes::HJet::GetMotherId(GenParticle *ParticleClone, int BranchId, int Position)
{
//     DebugLevel = 4;

    Print(3, "Get Mother Id", ParticleClone->PID);
    const int EmptyPosition = -1;
    const int TemporaryId = 100;

    while (Position != EmptyPosition) {

        ParticleClone = (GenParticle *) ClonesArrays->ParticleClonesArray->At(Position);

        BranchId = JetTag->GetBranchId(ParticleClone->PID, BranchId);
        Topology.at(Position) = TemporaryId;

        if (JetTag->HeavyParticles.find(abs(BranchId)) != end(JetTag->HeavyParticles)) break;

        if (ParticleClone->M2 != EmptyPosition) {

            Position = ParticleClone->M2;
//             DebugLevel = 4;
            Print(3, "Mother 2 Position", Position);
//             Print(3, "Pre Branch Id", BranchId);
            BranchId = GetMotherId((GenParticle *) ClonesArrays->ParticleClonesArray->At(Position), BranchId, Position);
//             Print(3, "\n");
//             DebugLevel = 1;

        }

//         if (Topology.at(Position) != EmptyId && Topology.at(Position) != TemporaryId) {
//             BranchId = Topology.at(Position);
//             break;
//         }

        Position = ParticleClone->M1;
        Print(3, "Mother 1 Position", Position);

    }

    Print(3, "Branch Id", BranchId);

//     DebugLevel = 1;
    return BranchId;

}

PseudoJet Analysis::HDelphes::HJet::GetConstituents(const Jet *const JetClone) const
{

    Print(2, "Get Constituents");

    vector<PseudoJet> Constituents;

    for (int ConstituentNumber : HRange(JetClone->Constituents.GetEntriesFast())) {

        const TObject *const Object = JetClone->Constituents.At(ConstituentNumber);

        if (Object == 0) continue;

        Constituents.push_back(GetConstituentJet(Object));

    }

    return fastjet::join(Constituents);

}

bool Analysis::HDelphes::HJet::ReadEFlow(const HJetDetails JetDetails)
{
    Print(2, "Get EFlow");


//     int Empty = EmptyId;
//     Particles.assign(ClonesArrays->ParticleSum(), &Empty);

    if (ClonesArrays->EFlowTrackClonesArray) GetTrackEFlow(JetDetails);
    if (ClonesArrays->EFlowPhotonClonesArray) GetPhotonEFlow(JetDetails);
    if (ClonesArrays->EFlowNeutralHadronClonesArray) GetHadronEFlow(JetDetails);
    if (ClonesArrays->EFlowMuonClonesArray) GetMuonEFlow(JetDetails);

//     for (int Position : HRange(100)) {
    for (int Position : HRange(ClonesArrays->ParticleSum())) {
        GenParticle *Particle = (GenParticle *)ClonesArrays->ParticleClonesArray->At(Position);
        std::cout << std::left << std::setw(10) << std::setfill(' ') << Position
                  << std::left << std::setw(10) << std::setfill(' ') << Topology.at(Position)
                  << std::left << std::setw(10) << std::setfill(' ') << Particle->Status
                  << std::left << std::setw(10) << std::setfill(' ') << GetStringFromEnum(Particle->PID)
                  << std::left << std::setw(10) << std::setfill(' ') << Particle->M1
                  << std::left << std::setw(10) << std::setfill(' ') << Particle->M2
                  << std::left << std::setw(10) << std::setfill(' ') << Particle->D1
                  << std::left << std::setw(10) << std::setfill(' ') << Particle->D2
                  << std::endl;
    }
    Print(1, "");

    Print(3, "Number of EFlow Jet", EFlowJets.size());

    return 1;

}


void Analysis::HDelphes::HJet::GetTrackEFlow(const HJetDetails JetDetails)
{
    Print(2, "Get Track EFlow", ClonesArrays->EFlowTrackSum());

    if (ClonesArrays->ElectronSum() > 0) Print(4, "Number of Electons", ClonesArrays->ElectronSum());
    if (ClonesArrays->MuonSum() > 0) Print(4, "Number of Muons", ClonesArrays->MuonSum());

    for (int EFlowTrackNumber : HRange(ClonesArrays->EFlowTrackSum())) {

        const Track *const EFlowTrackClone = (Track *) ClonesArrays->EFlowTrackClonesArray->At(EFlowTrackNumber);

        if (JetDetails == Isolation || JetDetails ==  TaggingIsolation) {

            bool Isolated = GetIsolation<Electron>(EFlowTrackClone, ClonesArrays->ElectronClonesArray);
            if (Isolated) Isolated = GetIsolation<Muon>(EFlowTrackClone, ClonesArrays->MuonClonesArray);
            if (!Isolated) continue;

        }

        EFlowJets.push_back(GetPseudoJet(const_cast<Track *>(EFlowTrackClone)->P4()));

        if (JetDetails == Tagging || JetDetails ==  TaggingIsolation) {

            EFlowJets.back().set_user_index(GetMotherId(EFlowTrackClone->Particle.GetObject()));
            Print(4, "Track EFlow Id", EFlowJets.back().user_index());

        }

    }


}

void Analysis::HDelphes::HJet::GetPhotonEFlow(const HJetDetails JetDetails)
{
    Print(2, "Get Photon EFlow", ClonesArrays->EFlowPhotonSum());

    if (ClonesArrays->PhotonSum() > 0) Print(3, "Number of Photons", ClonesArrays->PhotonSum());
    for (int EFlowPhotonNumber : HRange(ClonesArrays->EFlowPhotonSum())) {

        const Tower *const EFlowPhotonClone = (Tower *) ClonesArrays->EFlowPhotonClonesArray->At(EFlowPhotonNumber);

        if (JetDetails == Isolation || JetDetails == TaggingIsolation) {

            bool Isolated = GetIsolation<Photon>(EFlowPhotonClone, ClonesArrays->PhotonClonesArray);
            if (!Isolated) continue;

        }

        EFlowJets.push_back(GetPseudoJet(const_cast<Tower *>(EFlowPhotonClone)->P4()));

        if (JetDetails == Tagging || JetDetails ==  TaggingIsolation) {

            EFlowJets.back().set_user_info(new Analysis::HJetInfo(GetJetId(EFlowPhotonClone)));
            EFlowJets.back().set_user_index(EFlowJets.back().user_info<Analysis::HJetInfo>().GetMaximalId());
            Print(4, "Photon EFlow Id", EFlowJets.back().user_index());

        }

    }

}

void Analysis::HDelphes::HJet::GetHadronEFlow(const HJetDetails JetDetails)
{

    Print(2, "Get Hadron EFlow", ClonesArrays->EFlowNeutralHadronSum());

    for (int HadronNumber : HRange(ClonesArrays->EFlowNeutralHadronSum())) {

        const Tower *const HadronClone = (Tower *) ClonesArrays->EFlowNeutralHadronClonesArray->At(HadronNumber);

        EFlowJets.push_back(GetPseudoJet(const_cast<Tower *>(HadronClone)->P4()));
        if (JetDetails == Tagging || JetDetails ==  TaggingIsolation) {

          EFlowJets.back().set_user_info(new Analysis::HJetInfo(GetJetId(HadronClone)));
          EFlowJets.back().set_user_index(EFlowJets.back().user_info<Analysis::HJetInfo>().GetMaximalId());
            Print(4, "Hadron EFlow Id", EFlowJets.back().user_index());

        }

    }

}

void Analysis::HDelphes::HJet::GetMuonEFlow(const HJetDetails JetDetails)
{

    Print(2, "Get Muon EFlow", ClonesArrays->EFlowMuonSum());

    for (int MuonNumber : HRange(ClonesArrays->EFlowMuonSum())) {

        const Muon *const EFlowMuonClone = (Muon *) ClonesArrays->EFlowMuonClonesArray->At(MuonNumber);

        if (JetDetails == Isolation || JetDetails ==  TaggingIsolation) {

            bool Isolated = GetIsolation<Muon>(EFlowMuonClone, ClonesArrays->MuonClonesArray);
            if (!Isolated) continue;

        }

        EFlowJets.push_back(GetPseudoJet(const_cast<Muon *>(EFlowMuonClone)->P4()));
        if (JetDetails == Tagging || JetDetails ==  TaggingIsolation) {

            EFlowJets.back().set_user_index(GetMotherId(EFlowMuonClone->Particle.GetObject()));
            Print(4, "Muon EFlow Id", EFlowJets.back().user_index());

        }

    }

}


void Analysis::HDelphes::HJet::GetGenJet()
{

    Print(2, "GetGenJet", ClonesArrays->GenJetSum());

    for (int GenJetNumber : HRange(ClonesArrays->GenJetSum())) {

        const Jet *const GenJetClone = (Jet *) ClonesArrays->GenJetClonesArray->At(GenJetNumber);

        GenJets.push_back(GetPseudoJet(const_cast<Jet *>(GenJetClone)->P4()));

    }

}


float Analysis::HDelphes::HJet::GetScalarHt()
{

    Print(2, "GetScalerHt");

    const ScalarHT *const ScalarHtClone = (ScalarHT *) ClonesArrays->ScalarHtClonesArray->First();

    return ScalarHtClone->HT;

}

