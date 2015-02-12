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

bool hanalysis::hdelphes::HJet::GetJets(const hanalysis::HFourVector::HJetDetails JetDetails)
{
    Print(HInformation, "Get Jets", ClonesArrays->JetSum());
    for (const int JetNumber : HRange(ClonesArrays->JetSum())) {
        Print(HDetailed, "Jet Number", JetNumber);
        delphes::Jet *JetClone = (delphes::Jet *)ClonesArrays->Jet(JetNumber);

        switch (JetDetails) {
        case Plain: {
            fastjet::PseudoJet Jet = PseudoJet(JetClone->P4());
            Jet.set_user_info(new HJetInfo(JetClone->BTag));
            JetsM.push_back(Jet);
        }
        break;
        case Tagging: {
            fastjet::PseudoJet Jet = PseudoJet(JetClone->P4());
            HJetInfo *JetInfo = new HJetInfo(GetJetId(JetClone));
            JetInfo->SetBTag(JetClone->BTag);
            Jet.set_user_info(JetInfo);
            JetsM.push_back(Jet);
        }
        break;
        case Structure:
            JetsM.push_back(StructuredJet(JetClone, JetDetails));
            break;
        case TaggingStructure: {
            JetsM.push_back(StructuredJet(JetClone, JetDetails));
        }
        break;
        default:
            Print(HError, "unhandeled case");
        }
        DelphesTags(JetClone);
    }
    PrintTruthLevel(HDebug);
    return 1;
}

void hanalysis::hdelphes::HJet::DelphesTags(const delphes::Jet *const JetClone)
{
    Print(HInformation, "Get taggs");
    if (JetClone->TauTag == 1) {
        Print(HDetailed, "Has Tau Tag");
        TauTag(JetClone);
    } else if (JetClone->BTag > 0) {
        Print(HDetailed, "Has B Tag");
        BottomLorentzVectors.push_back(const_cast<delphes::Jet *>(JetClone)->P4());
        BottomJets.push_back(PseudoJet(const_cast<delphes::Jet *>(JetClone)->P4()));
    } else {
        Print(HDetailed, "No Delphes Tag");
        JetLorentzVectors.push_back(const_cast<delphes::Jet *>(JetClone)->P4());
    }
}

void hanalysis::hdelphes::HJet::TauTag(const delphes::Jet *const JetClone)
{
    Print(HInformation, "TauTagCalculations");
    if (JetClone->Charge == - 1) {
        TauLorentzVectors.push_back(const_cast<delphes::Jet *>(JetClone)->P4());
        Print(HDebug, "Tau Jet");
    } else if (JetClone->Charge == 1) {
        AntiTauLorentzVectors.push_back(const_cast<delphes::Jet *>(JetClone)->P4());
        Print(HDebug, "Anti Tau Jet");
    } else Print(HError, "Jet Charge: ", JetClone->Charge);
}

fastjet::PseudoJet hanalysis::hdelphes::HJet::StructuredJet(const delphes::Jet *const JetClone, const hanalysis::HJet::HJetDetails JetDetails)
{
    Print(HInformation, "Get Constituents");
    HJets ConstituentJets;
    std::vector<HConstituent> Constituents;
    hanalysis::HJetInfo *JetInfo = new hanalysis::HJetInfo(JetClone->BTag);

    for (const int ConstituentNumber : HRange(JetClone->Constituents.GetEntriesFast())) {

        TObject *Object = JetClone->Constituents.At(ConstituentNumber);
        if (Object == 0) continue;
        fastjet::PseudoJet Constituent = GetConstituents(Object, JetDetails);
        JetInfo->AddConstituents(Constituent.user_info<hanalysis::HJetInfo>().Constituents());
        ConstituentJets.push_back(Constituent);
    }

    fastjet::PseudoJet Jet = fastjet::join(ConstituentJets);
    Jet.set_user_info(JetInfo);
    return Jet;
}

fastjet::PseudoJet hanalysis::hdelphes::HJet::GetConstituents(TObject *Object, hanalysis::HJet::HJetDetails JetDetails,HConstituent::HDetector Detector)
{

    Print(HDebug, "GetConstituent", Object->ClassName());
    fastjet::PseudoJet Jet;
    HJetInfo *JetInfo = new HJetInfo();

    if (Object->IsA() == delphes::GenParticle::Class()) {
        // TODO should we take the GenParticle information into account or not?
        delphes::GenParticle *ParticleClone = const_cast<delphes::GenParticle *>((delphes::GenParticle *) Object);
        TLorentzVector Position(ParticleClone->X, ParticleClone->Y, ParticleClone->Z, ParticleClone->T);
        HConstituent Constituent(ParticleClone->P4(), Position, HConstituent::HGenParticle);
        if (JetDetails == TaggingStructure) Constituent.SetFamily(GetBranchFamily(Object));
        Jet = PseudoJet(ParticleClone->P4());
        JetInfo->AddConstituent(Constituent);
    } else if (Object->IsA() == delphes::Track::Class()) {
        delphes::Track *TrackClone = const_cast<delphes::Track *>((delphes::Track *) Object);
        TLorentzVector Position(TrackClone->X, TrackClone->Y, TrackClone->Z, TrackClone->T);
        HConstituent Constituent(TrackClone->P4(), Position, HConstituent::HTrack);
        if (JetDetails == TaggingStructure) Constituent.SetFamily(GetBranchFamily(TrackClone->Particle.GetObject()));
        Jet = PseudoJet(TrackClone->P4());
        JetInfo->AddConstituent(Constituent);
    } else if (Object->IsA() == delphes::Tower::Class()) {
        delphes::Tower *TowerClone = (delphes::Tower *) Object;
        std::vector<HConstituent> Constituents;
        Constituents.push_back(HConstituent(TowerClone->P4()));
        if (JetDetails == TaggingStructure) Constituents = GetJetId(TowerClone).Constituents();
//         if(Detector == HConstituent::HPhoton)
        for (auto & Constituent : Constituents) Constituent.SetDetector(Detector);
        Jet = PseudoJet(TowerClone->P4());
        JetInfo->AddConstituents(Constituents);
    } else if (Object->IsA() == delphes::Muon::Class()) {
        delphes::Muon *MuonClone = const_cast<delphes::Muon *>((delphes::Muon *) Object);
        HConstituent Constituent(MuonClone->P4(), HConstituent::HMuon);
        if (JetDetails == TaggingStructure) Constituent.SetFamily(GetBranchFamily(MuonClone->Particle.GetObject()));
        Jet = PseudoJet(MuonClone->P4());
        JetInfo->AddConstituent(Constituent);
    } else {
        Print(HError, "Unkonw Jet Constituent", Object->ClassName());
    }

    Jet.set_user_info(JetInfo);

    return Jet;

}

bool hanalysis::hdelphes::HJet::GetEFlow(const HJetDetails JetDetails)
{
    Print(HDebug, "Get EFlow", ClonesArrays->GetEFlowTrackSum());

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
    Print(HDebug, "Get Track EFlow", ClonesArrays->GetEFlowTrackSum());

    if (ClonesArrays->GetElectronSum() > 0) Print(HDetailed, "Number of Electons", ClonesArrays->GetElectronSum());
    if (ClonesArrays->GetMuonSum() > 0) Print(HDetailed, "Number of Muons", ClonesArrays->GetMuonSum());

    for (const int EFlowTrackNumber : HRange(ClonesArrays->GetEFlowTrackSum())) {

        if (JetDetails == TaggingStructure || JetDetails == Structure) {
            EFlowJets.push_back(GetConstituents(ClonesArrays->GetEFlowTrack(EFlowTrackNumber), JetDetails,HConstituent::HTrack));
            continue;
        }

        delphes::Track *const EFlowTrackClone = (delphes::Track *) ClonesArrays->GetEFlowTrack(EFlowTrackNumber);

        if (JetDetails == Isolation || JetDetails ==  TaggingIsolation) {

            bool Isolated = GetIsolation<delphes::Electron>(EFlowTrackClone, ClonesArrays->GetElectronClonesArray());
            if (Isolated) Isolated = GetIsolation<delphes::Muon>(EFlowTrackClone, ClonesArrays->GetMuonClonesArray());
            if (!Isolated) continue;

        }

        EFlowJets.push_back(PseudoJet(const_cast<delphes::Track *>(EFlowTrackClone)->P4()));

        if (JetDetails == Tagging || JetDetails ==  TaggingIsolation) {

            HConstituent Constituent(EFlowTrackClone->P4(), GetBranchFamily(EFlowTrackClone->Particle.GetObject()));
            EFlowJets.back().set_user_info(new HJetInfo(Constituent));
            Print(HDetailed, "Track EFlow Id", EFlowJets.back().user_index());

        }
    }


}

void hanalysis::hdelphes::HJet::GetPhotonEFlow(const HJetDetails JetDetails)
{
    Print(HDebug, "Get Photon EFlow", ClonesArrays->GetEFlowPhotonSum());

    if (ClonesArrays->GetPhotonSum() > 0) Print(HDebug, "Number of Photons", ClonesArrays->GetPhotonSum());
    for (const int EFlowPhotonNumber : HRange(ClonesArrays->GetEFlowPhotonSum())) {

        if (JetDetails == TaggingStructure || JetDetails == Structure) {
          EFlowJets.push_back(GetConstituents(ClonesArrays->GetEFlowPhoton(EFlowPhotonNumber), JetDetails,HConstituent::HPhoton));
            continue;
        }

        delphes::Tower *EFlowPhotonClone = (delphes::Tower *) ClonesArrays->GetEFlowPhoton(EFlowPhotonNumber);

        if (JetDetails == Isolation || JetDetails == TaggingIsolation) {

            bool Isolated = GetIsolation<delphes::Photon>(EFlowPhotonClone, ClonesArrays->GetPhotonClonesArray());
            if (!Isolated) continue;

        }

        EFlowJets.push_back(PseudoJet(const_cast<delphes::Tower *>(EFlowPhotonClone)->P4()));

        if (JetDetails == Tagging || JetDetails ==  TaggingIsolation) {

            EFlowJets.back().set_user_info(new hanalysis::HJetInfo(GetJetId(EFlowPhotonClone)));
            Print(HDetailed, "Photon EFlow Id", EFlowJets.back().user_index());

        }


    }

}

void hanalysis::hdelphes::HJet::GetHadronEFlow(const HJetDetails JetDetails)
{

    Print(HDebug, "Get Hadron EFlow", ClonesArrays->GetEFlowNeutralHadronSum());

    for (const int HadronNumber : HRange(ClonesArrays->GetEFlowNeutralHadronSum())) {

        if (JetDetails == TaggingStructure || JetDetails == Structure) {
          EFlowJets.push_back(GetConstituents(ClonesArrays->GetEFlowNeutralHadron(HadronNumber), JetDetails,HConstituent::HTower));
            continue;
        }

        delphes::Tower *HadronClone = (delphes::Tower *) ClonesArrays->GetEFlowNeutralHadron(HadronNumber);

        EFlowJets.push_back(PseudoJet(const_cast<delphes::Tower *>(HadronClone)->P4()));
        if (JetDetails == Tagging || JetDetails ==  TaggingIsolation) {

            EFlowJets.back().set_user_info(new hanalysis::HJetInfo(GetJetId(HadronClone)));
            Print(HDetailed, "Hadron EFlow Id", EFlowJets.back().user_index());

        }

    }

}

void hanalysis::hdelphes::HJet::GetMuonEFlow(const HJetDetails JetDetails)
{

    Print(HDebug, "Get Muon EFlow", ClonesArrays->GetEFlowMuonSum());

    for (const int MuonNumber : HRange(ClonesArrays->GetEFlowMuonSum())) {

        if (JetDetails == TaggingStructure || JetDetails == Structure) {
          EFlowJets.push_back(GetConstituents(ClonesArrays->GetEFlowMuon(MuonNumber), JetDetails,HConstituent::HMuon));
            continue;
        }

        delphes::Muon *const EFlowMuonClone = (delphes::Muon *) ClonesArrays->GetEFlowMuon(MuonNumber);

        if (JetDetails == Isolation || JetDetails ==  TaggingIsolation) {

            bool Isolated = GetIsolation<delphes::Muon>(EFlowMuonClone, ClonesArrays->GetMuonClonesArray());
            if (!Isolated) continue;

        }

        EFlowJets.push_back(PseudoJet(const_cast<delphes::Muon *>(EFlowMuonClone)->P4()));
        if (JetDetails == Tagging || JetDetails ==  TaggingIsolation) {

            HConstituent Constituent(EFlowMuonClone->P4(), GetBranchFamily(EFlowMuonClone->Particle.GetObject()));
            EFlowJets.back().set_user_info(new HJetInfo(Constituent));
            Print(HDetailed, "Muon EFlow Id", EFlowJets.back().user_index());

        }

    }

}

void hanalysis::hdelphes::HJet::GetGenJet()
{
    Print(HInformation, "GetGenJet", ClonesArrays->GetGenJetSum());
    for (const int GenJetNumber : HRange(ClonesArrays->GetGenJetSum())) {
        const delphes::Jet *const GenJetClone = (delphes::Jet *) ClonesArrays->GetGenJet(GenJetNumber);
        GenJets.push_back(PseudoJet(const_cast<delphes::Jet *>(GenJetClone)->P4()));
    }
}

float hanalysis::hdelphes::HJet::GetScalarHt()
{
    Print(HInformation, "GetScalerHt");
    const delphes::ScalarHT *const ScalarHtClone = (delphes::ScalarHT *) ClonesArrays->GetScalarHt();
    return ScalarHtClone->HT;
}

fastjet::PseudoJet hanalysis::hdelphes::HJet::GetMissingEt()
{
    Print(HInformation, "Get Missing ET");
    const delphes::MissingET *const MissingEtClone = (delphes::MissingET *) ClonesArrays->GetMissingEt();
    fastjet::PseudoJet Met = PseudoJet(const_cast<delphes::MissingET *>(MissingEtClone)->P4());
    Print(HDebug, "Met", Met);
    return Met;
}
