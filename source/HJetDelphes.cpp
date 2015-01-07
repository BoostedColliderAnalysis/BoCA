# include "HJetDelphes.hh"

hanalysis::hdelphes::HJet::HJet()
{
//     DebugLevel = hanalysis::HObject::HDebug;
    Print(HNotification, "Constructor");
}

hanalysis::hdelphes::HJet::~HJet()
{
    Print(HNotification, "Destructor");
}
/*
void hdelphes::HJet::NewEvent(const hanalysis::HClonesArray *const NewClonesArrays)
{

    Print(HInformation, "New Event", "delphes case");

    hanalysis::HJet::NewEvent(NewClonesArrays);

    Topology.assign(ClonesArrays->GetParticleSum(), EmptyId);
    Print(HInformation, "Topology", Topology.size());

}*/

bool hanalysis::hdelphes::HJet::GetJets(const hanalysis::HFourVector::HJetDetails JetDetails)
{

    Print(HInformation, "Get Jets", ClonesArrays->GetJetSum());

    for (const int JetNumber : HRange(ClonesArrays->GetJetSum())) {

        Print(HDetailed, "Jet Number", JetNumber);
        const Jet *const JetClone = (Jet *)ClonesArrays->GetJet(JetNumber);

        if (JetDetails == Structure || JetDetails == TaggingStructure) {

            Jets.push_back(GetConstituents(JetClone, JetDetails));

        } else {

            Jets.push_back(GetPseudoJet(const_cast<Jet *>(JetClone)->P4()));

        }

        if (JetDetails == Tagging || JetDetails == TaggingStructure) {

            hanalysis::HJetInfo *JetInfo = new hanalysis::HJetInfo(GetJetId(JetClone));

            if (JetDetails == TaggingStructure && Jets.back().has_user_info<hanalysis::HJetInfo>())
                JetInfo->SetVertices(Jets.back().user_info<hanalysis::HJetInfo>().GetVertices());

            Jets.back().set_user_info(JetInfo);
            Jets.back().set_user_index(Jets.back().user_info<hanalysis::HJetInfo>().GetMaximalId());


            Jets.at(JetNumber).user_info<hanalysis::HJetInfo>().PrintAllInfos(HDetailed);
            Print(HDebug, "Tag", Jets.at(JetNumber).user_info<hanalysis::HJetInfo>().GetMaximalId(), Jets.at(JetNumber).user_info<hanalysis::HJetInfo>().GetMaximalFraction());

        }

        GetDelphesTags(JetClone);

    }

    PrintTruthLevel(HDebug);

    return 1;

}

void hanalysis::hdelphes::HJet::GetDelphesTags(const Jet *const JetClone)
{
    Print(HInformation, "Get taggs");

    if (JetClone->TauTag == 1) {

        Print(HDetailed, "Has Tau Tag");

        GetTau(JetClone);

    } else if (JetClone->BTag > 0) {

        Print(HDetailed, "Has B Tag");

        BottomLorentzVectors.push_back(const_cast<Jet *>(JetClone)->P4());
        BottomJets.push_back(GetPseudoJet(const_cast<Jet *>(JetClone)->P4()));

    } else {

        Print(HDetailed, "No Delphes Tag");
        JetLorentzVectors.push_back(const_cast<Jet *>(JetClone)->P4());

    }

}


void hanalysis::hdelphes::HJet::GetTau(const Jet *const JetClone)
{

    Print(HInformation, "TauTagCalculations");

    if (JetClone->Charge == - 1) {

        TauLorentzVectors.push_back(const_cast<Jet *>(JetClone)->P4());
        Print(HDebug, "Tau Jet");

    } else if (JetClone->Charge == 1) {

        AntiTauLorentzVectors.push_back(const_cast<Jet *>(JetClone)->P4());
        Print(HDebug, "Anti Tau Jet");

    } else Print(HError, "Jet Charge: ", JetClone->Charge);

}

fastjet::PseudoJet hanalysis::hdelphes::HJet::GetConstituents(const Jet *const JetClone, const hanalysis::HJet::HJetDetails JetDetails)
{

    Print(HInformation, "Get Constituents");

    HJets Constituents;

    std::vector<HConstituent> Vertices;

    for (const int ConstituentNumber : HRange(JetClone->Constituents.GetEntriesFast())) {

        TObject *Object = JetClone->Constituents.At(ConstituentNumber);

        if (Object == 0) continue;

        Constituents.push_back(GetConstituentJet(Object, JetDetails));

        for (auto & Vertex : Constituents.back().user_info<hanalysis::HJetInfo>().GetVertices()) {

            Vertices.push_back(Vertex);
//         Vertices.insert(Vertices.end(),Constituents.back().user_info<hanalysis::HJetInfo>().GetVertices().begin(),Constituents.back().user_info<hanalysis::HJetInfo>().GetVertices().end());
            Print(HDetailed, "Vertex", Vertex.Position.Vect().Mag());
        }
//         if (Constituents.back().user_info<hanalysis::HJetInfo>().GetVertex().Vect().Mag() > Vertex.Vect().Mag()) {
//             Vertex = Constituents.back().user_info<hanalysis::HJetInfo>().GetVertex();
//             Print(HDetailed, "Vertex", Vertex.Vect().Mag());
//         }

    }

    fastjet::PseudoJet Jet = fastjet::join(Constituents);
    hanalysis::HJetInfo *JetInfo = new hanalysis::HJetInfo;
    JetInfo->SetVertices(Vertices);
    Jet.set_user_info(JetInfo);
//     Print(HDetailed, "Vertex", Jet.user_info<hanalysis::HJetInfo>().GetVertices().front().Position.Vect().Mag());

    return Jet;

}

fastjet::PseudoJet hanalysis::hdelphes::HJet::GetConstituentJet(TObject *Object, hanalysis::HJet::HJetDetails JetDetails)
{

    HConstituent Constituent = GetConstituent(Object, JetDetails);
    Print(HDetailed, "Vertex", Constituent.Position.Vect().Mag());

    fastjet::PseudoJet Jet = GetPseudoJet(Constituent.Momentum);
    if (JetDetails == TaggingStructure) Jet.set_user_index(Constituent.MotherId);

    hanalysis::HJetInfo *JetInfo = new hanalysis::HJetInfo;
    JetInfo->SetVertex(Constituent);
    Jet.set_user_info(JetInfo);

//   Print(HDetailed, "Vertex", Jet.user_info<hanalysis::HJetInfo>().GetVertex().Vect().Mag());


    return Jet;

}

HConstituent hanalysis::hdelphes::HJet::GetConstituent(TObject *Object, hanalysis::HJet::HJetDetails JetDetails)
{

    Print(HDebug, "GetConstituent", Object->ClassName());

    HConstituent Constituent;

    if (Object->IsA() == GenParticle::Class()) {

        GenParticle *ParticleClone = const_cast<GenParticle *>((GenParticle *) Object);
        Constituent.Momentum = ParticleClone->P4();
        if (JetDetails == TaggingStructure) Constituent.MotherId = GetMotherId(Object);
        Constituent.Position.SetXYZT(ParticleClone->X, ParticleClone->Y, ParticleClone->Z, ParticleClone->T);
        Print(HDebug, "Gen Vertex", ParticleClone->X, ParticleClone->Y, ParticleClone->Z);
        // TODO should we take the GenParticle information into account or not?

    } else if (Object->IsA() == Track::Class()) {

        Track *TrackClone = const_cast<Track *>((Track *) Object);
        Constituent.Momentum = TrackClone->P4();
        if (JetDetails == TaggingStructure) Constituent.MotherId = GetMotherId(TrackClone->Particle.GetObject());
        TVector3 Vector(TrackClone->X, TrackClone->Y, TrackClone->Z);
        Print(HDebug, "Track Vertex", TrackClone->X, TrackClone->Y, TrackClone->Z);
        Constituent.Position.SetVect(Vector);

    } else if (Object->IsA() == Tower::Class()) {

        Tower *TowerClone = const_cast<Tower *>((Tower *) Object);
        Constituent.Momentum = TowerClone->P4();
        if (JetDetails == TaggingStructure) {
            Constituent.MotherId = GetJetId(TowerClone).GetMaximalId();
            GetJetId(TowerClone).PrintAllInfos(HDetailed);
        }

    } else if (Object->IsA() == Muon::Class()) {

        Muon *MuonClone = const_cast<Muon *>((Muon *) Object);
        Constituent.Momentum = MuonClone->P4();
        if (JetDetails == TaggingStructure) Constituent.MotherId = GetMotherId(MuonClone->Particle.GetObject());

    } else {

        Print(HError, "Unkonw Jet Constituent", Object->ClassName());

    }

    if (Constituent.Position.Vect().Mag() > 0) Print(HDebug, "Vertex", Constituent.Position.Vect().Mag());

    return Constituent;

}

bool hanalysis::hdelphes::HJet::GetEFlow(const HJetDetails JetDetails)
{
    Print(HInformation, "Get EFlow");

    if (ClonesArrays->GetEFlowTrackClonesArray()) GetTrackEFlow(JetDetails);
    if (ClonesArrays->GetEFlowPhotonClonesArray()) GetPhotonEFlow(JetDetails);
    if (ClonesArrays->GetEFlowNeutralHadronClonesArray()) GetHadronEFlow(JetDetails);
    if (ClonesArrays->GetEFlowMuonClonesArray()) GetMuonEFlow(JetDetails);

    Print(HDebug, "Number of EFlow Jet", EFlowJets.size());

    PrintTruthLevel(HDetailed);

    return 1;

}

void hanalysis::hdelphes::HJet::GetTrackEFlow(const HJetDetails JetDetails)
{
    Print(HInformation, "Get Track EFlow", ClonesArrays->GetEFlowTrackSum());

    if (ClonesArrays->GetElectronSum() > 0) Print(HDetailed, "Number of Electons", ClonesArrays->GetElectronSum());
    if (ClonesArrays->GetMuonSum() > 0) Print(HDetailed, "Number of Muons", ClonesArrays->GetMuonSum());

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
            Print(HDetailed, "Track EFlow Id", EFlowJets.back().user_index());

        }

    }


}

void hanalysis::hdelphes::HJet::GetPhotonEFlow(const HJetDetails JetDetails)
{
    Print(HInformation, "Get Photon EFlow", ClonesArrays->GetEFlowPhotonSum());

    if (ClonesArrays->GetPhotonSum() > 0) Print(HDebug, "Number of Photons", ClonesArrays->GetPhotonSum());
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
            Print(HDetailed, "Photon EFlow Id", EFlowJets.back().user_index());

        }

    }

}

void hanalysis::hdelphes::HJet::GetHadronEFlow(const HJetDetails JetDetails)
{

    Print(HInformation, "Get Hadron EFlow", ClonesArrays->GetEFlowNeutralHadronSum());

    for (int HadronNumber : HRange(ClonesArrays->GetEFlowNeutralHadronSum())) {

        const Tower *const HadronClone = (Tower *) ClonesArrays->GetEFlowNeutralHadron(HadronNumber);

        EFlowJets.push_back(GetPseudoJet(const_cast<Tower *>(HadronClone)->P4()));
        if (JetDetails == Tagging || JetDetails ==  TaggingIsolation) {

            EFlowJets.back().set_user_info(new hanalysis::HJetInfo(GetJetId(HadronClone)));
            EFlowJets.back().set_user_index(EFlowJets.back().user_info<hanalysis::HJetInfo>().GetMaximalId());
            Print(HDetailed, "Hadron EFlow Id", EFlowJets.back().user_index());

        }

    }

}

void hanalysis::hdelphes::HJet::GetMuonEFlow(const HJetDetails JetDetails)
{

    Print(HInformation, "Get Muon EFlow", ClonesArrays->GetEFlowMuonSum());

    for (int MuonNumber : HRange(ClonesArrays->GetEFlowMuonSum())) {

        const Muon *const EFlowMuonClone = (Muon *) ClonesArrays->GetEFlowMuon(MuonNumber);

        if (JetDetails == Isolation || JetDetails ==  TaggingIsolation) {

            bool Isolated = GetIsolation<Muon>(EFlowMuonClone, ClonesArrays->GetMuonClonesArray());
            if (!Isolated) continue;

        }

        EFlowJets.push_back(GetPseudoJet(const_cast<Muon *>(EFlowMuonClone)->P4()));
        if (JetDetails == Tagging || JetDetails ==  TaggingIsolation) {

            EFlowJets.back().set_user_index(GetMotherId(EFlowMuonClone->Particle.GetObject()));
            Print(HDetailed, "Muon EFlow Id", EFlowJets.back().user_index());

        }

    }

}




void hanalysis::hdelphes::HJet::GetGenJet()
{

    Print(HInformation, "GetGenJet", ClonesArrays->GetGenJetSum());

    for (int GenJetNumber : HRange(ClonesArrays->GetGenJetSum())) {

        const Jet *const GenJetClone = (Jet *) ClonesArrays->GetGenJet(GenJetNumber);

        GenJets.push_back(GetPseudoJet(const_cast<Jet *>(GenJetClone)->P4()));

    }

}


float hanalysis::hdelphes::HJet::GetScalarHt()
{

    Print(HInformation, "GetScalerHt");

    const ScalarHT *const ScalarHtClone = (ScalarHT *) ClonesArrays->GetScalarHt();

    return ScalarHtClone->HT;

}


fastjet::PseudoJet hanalysis::hdelphes::HJet::GetMissingEt()
{

    Print(HInformation, "Get Missing ET");

    const MissingET *const MissingEtClone = (MissingET *) ClonesArrays->GetMissingEt();

    fastjet::PseudoJet Met= GetPseudoJet(const_cast<MissingET *>(MissingEtClone)->P4());
    Print(HDebug, "Met", Met);
    return Met;

}
