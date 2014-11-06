# include "HJetDelphes.hh"

hanalysis::hdelphes::HJet::HJet()
{

    Print(1, "Constructor");

//     DebugLevel =5;

}

hanalysis::hdelphes::HJet::~HJet()
{

    Print(1, "Destructor");

}

void hanalysis::hdelphes::HJet::NewEvent(const hanalysis::HClonesArray *const NewClonesArrays)
{

    Print(2, "New Event", "delphes case");

    hanalysis::HJet::NewEvent(NewClonesArrays);

    Topology.assign(ClonesArrays->GetParticleSum(), EmptyId);

    Print(2, "Topology", Topology.size());

}

bool hanalysis::hdelphes::HJet::GetJets(hanalysis::HJet::HJetDetails JetDetails)
{

    Print(2, "Get Jets", ClonesArrays->GetJetSum());

    for (const int JetNumber : HRange(ClonesArrays->GetJetSum())) {

        Print(4, "Jet Number", JetNumber);
        const Jet *const JetClone = (Jet *)ClonesArrays->GetJet(JetNumber);

        if (JetDetails == Structure) {

            Jets.push_back(GetConstituents(JetClone));

        } else {

            Jets.push_back(GetPseudoJet(const_cast<Jet *>(JetClone)->P4()));

        }

        if (JetDetails == Tagging) {

            Jets.back().set_user_info(new HJetInfo(GetJetId(JetClone)));
            Jets.back().set_user_index(Jets.back().user_info<HJetInfo>().GetMaximalId());


        }

        GetDelphesTags(JetClone);

//         Jets.at(JetNumber).user_info<HJetInfo>().PrintAllInfos();
//         Print(0, "Tag", Jets.at(JetNumber).user_info<HJetInfo>().GetMaximalId(), Jets.at(JetNumber).user_info<HJetInfo>().GetMaximalFraction());

    }

    return 1;

}

void hanalysis::hdelphes::HJet::GetDelphesTags(const Jet *const JetClone)
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

        Print(4, "No Delphes Tag");
        JetLorentzVectors.push_back(const_cast<Jet *>(JetClone)->P4());

    }

}


void hanalysis::hdelphes::HJet::GetTau(const Jet *const JetClone)
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

int hanalysis::hdelphes::HJet::GetMotherId(const TObject *const Object)
{

    Print(3, "Get Mother Id", ClonesArrays->GetParticleSum());

    if (Object->IsA() != GenParticle::Class() || Object == 0) {

        Print(0, "Object is", Object->ClassName());
        return EmptyId;

    }

    const int Position = ClonesArrays->GetParticleClonesArray()->IndexOf(Object);
    int MotherId = Topology.at(Position);

    MotherId = GetMotherId(MotherId, Position);

    Print(3, "Mother Id", GetParticleName(MotherId));
    if (MotherId == EmptyId) Print(0, "No Mother Id", Position, Topology.at(Position));

    int Marker = MarkerId;
    std::replace(Topology.begin(), Topology.end(), Marker, MotherId);

    return MotherId;

}

int hanalysis::hdelphes::HJet::GetMotherId(int BranchId, int Position)
{

    Print(3, "Get Mother Id", GetParticleName(BranchId), Position);

    while (Position != EmptyPosition && JetTag->HeavyParticles.find(abs(BranchId)) == end(JetTag->HeavyParticles)) {

        if (Topology.at(Position) != EmptyId && Topology.at(Position) != MarkerId) {

            Print(3, "Topology", GetParticleName(BranchId), GetParticleName(Topology.at(Position)));
            BranchId = JetTag->GetBranchId(BranchId, Topology.at(Position));

        }

        Topology.at(Position) = MarkerId;

        const GenParticle *const ParticleClone = (GenParticle *) ClonesArrays->GetParticle(Position);

        BranchId = JetTag->GetBranchId(ParticleClone->PID, BranchId);
        Print(3, "Branch Id", GetParticleName(ParticleClone->PID), GetParticleName(BranchId));

        Position = ParticleClone->M2;
        if (Position != EmptyPosition) {

            Print(3, "Mother 2 Position", GetParticleName(BranchId), Position);
            BranchId = GetMotherId(BranchId, Position);

        }

        Position = ParticleClone->M1;
        Print(3, "Mother 1 Position", Position);
    }

    Print(3, "Branch Id Result", GetParticleName(BranchId));

    return BranchId;

}

PseudoJet hanalysis::hdelphes::HJet::GetConstituents(const Jet *const JetClone) const
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

bool hanalysis::hdelphes::HJet::GetEFlow(const HJetDetails JetDetails)
{
    Print(2, "Get EFlow");

    if (ClonesArrays->GetEFlowTrackClonesArray()) GetTrackEFlow(JetDetails);
    if (ClonesArrays->GetEFlowPhotonClonesArray()) GetPhotonEFlow(JetDetails);
    if (ClonesArrays->GetEFlowNeutralHadronClonesArray()) GetHadronEFlow(JetDetails);
    if (ClonesArrays->GetEFlowMuonClonesArray()) GetMuonEFlow(JetDetails);

    Print(3, "Number of EFlow Jet", EFlowJets.size());

    PrintTruthLevel(4);

    return 1;

}

void hanalysis::hdelphes::HJet::PrintTruthLevel(int const Severity) const
{
    if (Severity <= DebugLevel) {

        for (const int Position : HRange(ClonesArrays->GetParticleSum())) {
            //     for (const int Position : HRange(100)) {

            const GenParticle *Particle = (GenParticle *)ClonesArrays->GetParticle(Position);

            PrintCell(Position);
            PrintCell(GetParticleName(Topology.at(Position)));
            PrintCell(Particle->Status);
            PrintCell(GetParticleName(Particle->PID));
            PrintCell(Particle->M1);
            PrintCell(PrintParticle(Particle->M1));
            PrintCell(Particle->M2);
            PrintCell(PrintParticle(Particle->M2));
            PrintCell(Particle->D1);
            PrintCell(PrintParticle(Particle->D1));
            PrintCell(Particle->D2);
            PrintCell(PrintParticle(Particle->D2));
            std::cout << std::endl;

        }

        Print(1, "");

    }

}

string hanalysis::hdelphes::HJet::PrintParticle(const int Position) const
{

    if (Position != -1) {
        return GetParticleName(((GenParticle *)ClonesArrays->GetParticle(Position))->PID);
    } else {
        return " ";
    };

}


void hanalysis::hdelphes::HJet::GetTrackEFlow(const HJetDetails JetDetails)
{
    Print(2, "Get Track EFlow", ClonesArrays->GetEFlowTrackSum());

    if (ClonesArrays->GetElectronSum() > 0) Print(4, "Number of Electons", ClonesArrays->GetElectronSum());
    if (ClonesArrays->GetMuonSum() > 0) Print(4, "Number of Muons", ClonesArrays->GetMuonSum());

    for (int EFlowTrackNumber : HRange(ClonesArrays->GetEFlowTrackSum())) {

        const Track *const EFlowTrackClone = (Track *) ClonesArrays->GetEFlowTrack(EFlowTrackNumber);

        if (JetDetails == Isolation || JetDetails ==  TaggingIsolation) {

            bool Isolated = GetIsolation<Electron>(EFlowTrackClone, ClonesArrays->GetElectronClonesArray());
            if (Isolated) Isolated = GetIsolation<Muon>(EFlowTrackClone, ClonesArrays->GetMuonClonesArray());
            if (!Isolated) continue;

        }

        EFlowJets.push_back(GetPseudoJet(const_cast<Track *>(EFlowTrackClone)->P4()));

        if (JetDetails == Tagging || JetDetails ==  TaggingIsolation) {

            EFlowJets.back().set_user_index(GetMotherId(EFlowTrackClone->Particle.GetObject()));
            Print(4, "Track EFlow Id", EFlowJets.back().user_index());

        }

    }


}

void hanalysis::hdelphes::HJet::GetPhotonEFlow(const HJetDetails JetDetails)
{
    Print(2, "Get Photon EFlow", ClonesArrays->GetEFlowPhotonSum());

    if (ClonesArrays->GetPhotonSum() > 0) Print(3, "Number of Photons", ClonesArrays->GetPhotonSum());
    for (int EFlowPhotonNumber : HRange(ClonesArrays->GetEFlowPhotonSum())) {

        const Tower *const EFlowPhotonClone = (Tower *) ClonesArrays->GetEFlowPhoton(EFlowPhotonNumber);

        if (JetDetails == Isolation || JetDetails == TaggingIsolation) {

            bool Isolated = GetIsolation<Photon>(EFlowPhotonClone, ClonesArrays->GetPhotonClonesArray());
            if (!Isolated) continue;

        }

        EFlowJets.push_back(GetPseudoJet(const_cast<Tower *>(EFlowPhotonClone)->P4()));

        if (JetDetails == Tagging || JetDetails ==  TaggingIsolation) {

            EFlowJets.back().set_user_info(new hanalysis::HJetInfo(GetJetId(EFlowPhotonClone)));
            EFlowJets.back().set_user_index(EFlowJets.back().user_info<hanalysis::HJetInfo>().GetMaximalId());
            Print(4, "Photon EFlow Id", EFlowJets.back().user_index());

        }

    }

}

void hanalysis::hdelphes::HJet::GetHadronEFlow(const HJetDetails JetDetails)
{

    Print(2, "Get Hadron EFlow", ClonesArrays->GetEFlowNeutralHadronSum());

    for (int HadronNumber : HRange(ClonesArrays->GetEFlowNeutralHadronSum())) {

        const Tower *const HadronClone = (Tower *) ClonesArrays->GetEFlowNeutralHadron(HadronNumber);

        EFlowJets.push_back(GetPseudoJet(const_cast<Tower *>(HadronClone)->P4()));
        if (JetDetails == Tagging || JetDetails ==  TaggingIsolation) {

            EFlowJets.back().set_user_info(new hanalysis::HJetInfo(GetJetId(HadronClone)));
            EFlowJets.back().set_user_index(EFlowJets.back().user_info<hanalysis::HJetInfo>().GetMaximalId());
            Print(4, "Hadron EFlow Id", EFlowJets.back().user_index());

        }

    }

}

void hanalysis::hdelphes::HJet::GetMuonEFlow(const HJetDetails JetDetails)
{

    Print(2, "Get Muon EFlow", ClonesArrays->GetEFlowMuonSum());

    for (int MuonNumber : HRange(ClonesArrays->GetEFlowMuonSum())) {

        const Muon *const EFlowMuonClone = (Muon *) ClonesArrays->GetEFlowMuon(MuonNumber);

        if (JetDetails == Isolation || JetDetails ==  TaggingIsolation) {

            bool Isolated = GetIsolation<Muon>(EFlowMuonClone, ClonesArrays->GetMuonClonesArray());
            if (!Isolated) continue;

        }

        EFlowJets.push_back(GetPseudoJet(const_cast<Muon *>(EFlowMuonClone)->P4()));
        if (JetDetails == Tagging || JetDetails ==  TaggingIsolation) {

            EFlowJets.back().set_user_index(GetMotherId(EFlowMuonClone->Particle.GetObject()));
            Print(4, "Muon EFlow Id", EFlowJets.back().user_index());

        }

    }

}


void hanalysis::hdelphes::HJet::GetGenJet()
{

    Print(2, "GetGenJet", ClonesArrays->GetGenJetSum());

    for (int GenJetNumber : HRange(ClonesArrays->GetGenJetSum())) {

        const Jet *const GenJetClone = (Jet *) ClonesArrays->GetGenJet(GenJetNumber);

        GenJets.push_back(GetPseudoJet(const_cast<Jet *>(GenJetClone)->P4()));

    }

}


float hanalysis::hdelphes::HJet::GetScalarHt()
{

    Print(2, "GetScalerHt");

    const ScalarHT *const ScalarHtClone = (ScalarHT *) ClonesArrays->GetScalarHt();

    return ScalarHtClone->HT;

}

