# include "HJetDelphes.hh"
# include "fastjet/ClusterSequence.hh"



hanalysis::hdelphes::HJet::HJet(): DetectorGeometry()
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
    Print(HInformation, "Get Jets", clones_arrays_->JetSum());
    for (const int JetNumber : Range(clones_arrays_->JetSum())) {
        Print(HDetailed, "Jet Number", JetNumber);
        delphes::Jet &JetClone = static_cast<delphes::Jet &>(*clones_arrays_->Jet(JetNumber));

        switch (JetDetails) {
        case Plain: {
            fastjet::PseudoJet Jet = PseudoJet(JetClone.P4());
            Jet.set_user_info(new HJetInfo(JetClone.BTag));
            JetsM.push_back(Jet);
        }
        break;
        case Tagging: {
            fastjet::PseudoJet Jet = PseudoJet(JetClone.P4());
            HJetInfo *JetInfo = new HJetInfo(GetJetId(JetClone));
            JetInfo->SetBTag(JetClone.BTag);
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

void hanalysis::hdelphes::HJet::DelphesTags(const delphes::Jet &JetClone)
{
    Print(HInformation, "Get taggs");
    if (JetClone.TauTag == 1) {
        Print(HDetailed, "Has Tau Tag");
        TauTag(JetClone);
    } else if (JetClone.BTag > 0) {
        Print(HDetailed, "Has B Tag");
        BottomLorentzVectors.push_back(const_cast<delphes::Jet &>(JetClone).P4());
        BottomJets.push_back(PseudoJet(const_cast<delphes::Jet &>(JetClone).P4()));
    } else {
        Print(HDetailed, "No Delphes Tag");
        JetLorentzVectors.push_back(const_cast<delphes::Jet &>(JetClone).P4());
    }

    Print(HDebug, "Btag", JetClone.BTag);
}

void hanalysis::hdelphes::HJet::TauTag(const delphes::Jet &JetClone)
{
    Print(HInformation, "TauTagCalculations");
    if (JetClone.Charge == - 1) {
        TauLorentzVectors.push_back(const_cast<delphes::Jet &>(JetClone).P4());
        Print(HDebug, "Tau Jet");
    } else if (JetClone.Charge == 1) {
        AntiTauLorentzVectors.push_back(const_cast<delphes::Jet &>(JetClone).P4());
        Print(HDebug, "Anti Tau Jet");
    } else Print(HError, "Jet Charge: ", JetClone.Charge);
}

fastjet::PseudoJet hanalysis::hdelphes::HJet::StructuredJet(const delphes::Jet &JetClone, const hanalysis::HJet::HJetDetails JetDetails)
{
    Print(HInformation, "Get Constituents");
    HJets ConstituentJets;
    std::vector<HConstituent> Constituents;
    hanalysis::HJetInfo *JetInfo = new hanalysis::HJetInfo(JetClone.BTag);

    for (const int ConstituentNumber : Range(JetClone.Constituents.GetEntriesFast())) {
        if (!JetClone.Constituents.At(ConstituentNumber)) continue;
        fastjet::PseudoJet Constituent = GetConstituents(*JetClone.Constituents.At(ConstituentNumber), JetDetails);
        JetInfo->AddConstituents(Constituent.user_info<hanalysis::HJetInfo>().Constituents());
        ConstituentJets.push_back(Constituent);
    }

    fastjet::PseudoJet Jet = fastjet::join(ConstituentJets);
    Jet.set_user_info(JetInfo);
    return Jet;
}

fastjet::PseudoJet hanalysis::hdelphes::HJet::GetConstituents(const TObject &Object, const hanalysis::HJet::HJetDetails JetDetails, const HConstituent::SubDetector Detector)
{

    Print(HDebug, "GetConstituent", Object.ClassName());
    fastjet::PseudoJet Jet;
    HJetInfo *JetInfo = new HJetInfo();

    if (Object.IsA() == delphes::GenParticle::Class()) {
        // TODO should we take the GenParticle information into account or not?
        const delphes::GenParticle &ParticleClone = static_cast<const delphes::GenParticle &>(Object);
        TLorentzVector Position(ParticleClone.X, ParticleClone.Y, ParticleClone.Z, ParticleClone.T);
        HConstituent Constituent(const_cast<delphes::GenParticle &>(ParticleClone).P4(), Position, HConstituent::HGenParticle);
        if (JetDetails == TaggingStructure) Constituent.SetFamily(GetBranchFamily(Object));
        Jet = PseudoJet(const_cast<delphes::GenParticle &>(ParticleClone).P4());
        JetInfo->AddConstituent(Constituent);
    } else if (Object.IsA() == delphes::Track::Class()) {
        const delphes::Track &TrackClone = static_cast<const delphes::Track &>(Object);
        TLorentzVector Position(TrackClone.X, TrackClone.Y, TrackClone.Z, TrackClone.T);
        HConstituent Constituent(const_cast<delphes::Track &>(TrackClone).P4(), Position, HConstituent::HTrack);
        if (JetDetails == TaggingStructure) Constituent.SetFamily(GetBranchFamily(*TrackClone.Particle.GetObject()));
        Jet = PseudoJet(const_cast<delphes::Track &>(TrackClone).P4());
        JetInfo->AddConstituent(Constituent);
    } else if (Object.IsA() == delphes::Tower::Class()) {
        const delphes::Tower &TowerClone = static_cast<const delphes::Tower &>(Object);
        std::vector<HConstituent> Constituents;
        Constituents.push_back(HConstituent(const_cast<delphes::Tower &>(TowerClone).P4()));
        if (JetDetails == TaggingStructure) Constituents = GetJetId(TowerClone).Constituents();
//         if(Detector == HConstituent::HPhoton)
        for (auto & Constituent : Constituents) Constituent.SetDetector(Detector);
        Jet = PseudoJet(const_cast<delphes::Tower &>(TowerClone).P4());
        JetInfo->AddConstituents(Constituents);
    } else if (Object.IsA() == delphes::Muon::Class()) {
        const delphes::Muon &MuonClone = static_cast<const delphes::Muon &>(Object);
        HConstituent Constituent(const_cast<delphes::Muon &>(MuonClone).P4(), HConstituent::HMuon);
        if (JetDetails == TaggingStructure) Constituent.SetFamily(GetBranchFamily(*MuonClone.Particle.GetObject()));
        Jet = PseudoJet(const_cast<delphes::Muon &>(MuonClone).P4());
        JetInfo->AddConstituent(Constituent);
    } else {
        Print(HError, "Unkonw Jet Constituent", Object.ClassName());
    }

    Jet.set_user_info(JetInfo);

    return Jet;

}

bool hanalysis::hdelphes::HJet::GetEFlow(const HJetDetails JetDetails)
{
    Print(HDebug, "Get EFlow", clones_arrays_->GetEFlowTrackSum());

    if (clones_arrays_->GetEFlowTrackClonesArray()) GetTrackEFlow(JetDetails);
    if (clones_arrays_->GetEFlowPhotonClonesArray()) GetPhotonEFlow(JetDetails);
    if (clones_arrays_->GetEFlowNeutralHadronClonesArray()) GetHadronEFlow(JetDetails);
    if (clones_arrays_->GetEFlowMuonClonesArray()) GetMuonEFlow(JetDetails);

    Print(HDebug, "Number of EFlow Jet", EFlowJets.size());

    PrintTruthLevel(HDetailed);

    return 1;

}

void hanalysis::hdelphes::HJet::GetTrackEFlow(const HJetDetails JetDetails)
{
    Print(HDebug, "Get Track EFlow", clones_arrays_->GetEFlowTrackSum());

    if (clones_arrays_->GetElectronSum() > 0) Print(HDetailed, "Number of Electons", clones_arrays_->GetElectronSum());
    if (clones_arrays_->GetMuonSum() > 0) Print(HDetailed, "Number of Muons", clones_arrays_->GetMuonSum());

    for (const int EFlowTrackNumber : Range(clones_arrays_->GetEFlowTrackSum())) {

        if (JetDetails == TaggingStructure || JetDetails == Structure) {
            if (!clones_arrays_->GetEFlowTrack(EFlowTrackNumber)) continue;
            EFlowJets.push_back(GetConstituents(*clones_arrays_->GetEFlowTrack(EFlowTrackNumber), JetDetails, HConstituent::HTrack));
            continue;
        }

        delphes::Track &EFlowTrackClone = static_cast<delphes::Track &>(* clones_arrays_->GetEFlowTrack(EFlowTrackNumber));

        if (JetDetails == Isolation || JetDetails ==  TaggingIsolation) {

            bool Isolated = GetIsolation<delphes::Electron>(EFlowTrackClone, *clones_arrays_->GetElectronClonesArray());
            if (Isolated) Isolated = GetIsolation<delphes::Muon>(EFlowTrackClone, *clones_arrays_->GetMuonClonesArray());
            if (!Isolated) continue;

        }

        EFlowJets.push_back(PseudoJet(EFlowTrackClone.P4()));

        if (JetDetails == Tagging || JetDetails ==  TaggingIsolation) {

            HConstituent Constituent(EFlowTrackClone.P4(), GetBranchFamily(*EFlowTrackClone.Particle.GetObject()));
            EFlowJets.back().set_user_info(new HJetInfo(Constituent));
            Print(HDetailed, "Track EFlow Id", EFlowJets.back().user_index());

        }
    }

}

void hanalysis::hdelphes::HJet::GetPhotonEFlow(const HJetDetails JetDetails)
{
    Print(HDebug, "Get Photon EFlow", clones_arrays_->GetEFlowPhotonSum());

    if (clones_arrays_->GetPhotonSum() > 0) Print(HDebug, "Number of Photons", clones_arrays_->GetPhotonSum());
    for (const int EFlowPhotonNumber : Range(clones_arrays_->GetEFlowPhotonSum())) {

        if (JetDetails == TaggingStructure || JetDetails == Structure) {
            if (!clones_arrays_->GetEFlowPhoton(EFlowPhotonNumber)) continue;
            EFlowJets.push_back(GetConstituents(*clones_arrays_->GetEFlowPhoton(EFlowPhotonNumber), JetDetails, HConstituent::HPhoton));
            continue;
        }

        delphes::Tower &EFlowPhotonClone = static_cast<delphes::Tower &>(* clones_arrays_->GetEFlowPhoton(EFlowPhotonNumber));

        if (JetDetails == Isolation || JetDetails == TaggingIsolation) {

            bool Isolated = GetIsolation<delphes::Photon>(EFlowPhotonClone, *clones_arrays_->GetPhotonClonesArray());
            if (!Isolated) continue;

        }

        EFlowJets.push_back(PseudoJet(EFlowPhotonClone.P4()));

        if (JetDetails == Tagging || JetDetails ==  TaggingIsolation) {

            EFlowJets.back().set_user_info(new hanalysis::HJetInfo(GetJetId(EFlowPhotonClone)));
            Print(HDetailed, "Photon EFlow Id", EFlowJets.back().user_index());

        }


    }

}

void hanalysis::hdelphes::HJet::GetHadronEFlow(const HJetDetails JetDetails)
{

    Print(HDebug, "Get Hadron EFlow", clones_arrays_->GetEFlowNeutralHadronSum());

    for (const int HadronNumber : Range(clones_arrays_->GetEFlowNeutralHadronSum())) {

        if (JetDetails == TaggingStructure || JetDetails == Structure) {
            if (!clones_arrays_->GetEFlowNeutralHadron(HadronNumber)) continue;
            EFlowJets.push_back(GetConstituents(*clones_arrays_->GetEFlowNeutralHadron(HadronNumber), JetDetails, HConstituent::HTower));
            continue;
        }

        delphes::Tower &HadronClone = static_cast<delphes::Tower &>(*clones_arrays_->GetEFlowNeutralHadron(HadronNumber));

        EFlowJets.push_back(PseudoJet(HadronClone.P4()));
        if (JetDetails == Tagging || JetDetails ==  TaggingIsolation) {

            EFlowJets.back().set_user_info(new hanalysis::HJetInfo(GetJetId(HadronClone)));
            Print(HDetailed, "Hadron EFlow Id", EFlowJets.back().user_index());

        }

    }

}

void hanalysis::hdelphes::HJet::GetMuonEFlow(const HJetDetails JetDetails)
{

    Print(HDebug, "Get Muon EFlow", clones_arrays_->GetEFlowMuonSum());

    for (const int MuonNumber : Range(clones_arrays_->GetEFlowMuonSum())) {

        if (JetDetails == TaggingStructure || JetDetails == Structure) {
            if (!clones_arrays_->GetEFlowMuon(MuonNumber)) continue;
            EFlowJets.push_back(GetConstituents(*clones_arrays_->GetEFlowMuon(MuonNumber), JetDetails, HConstituent::HMuon));
            continue;
        }

        delphes::Muon &EFlowMuonClone = static_cast<delphes::Muon &>(*clones_arrays_->GetEFlowMuon(MuonNumber));

        if (JetDetails == Isolation || JetDetails ==  TaggingIsolation) {

            bool Isolated = GetIsolation<delphes::Muon>(EFlowMuonClone, *clones_arrays_->GetMuonClonesArray());
            if (!Isolated) continue;

        }

        EFlowJets.push_back(PseudoJet(EFlowMuonClone.P4()));
        if (JetDetails == Tagging || JetDetails ==  TaggingIsolation) {

            HConstituent Constituent(EFlowMuonClone.P4(), GetBranchFamily(*EFlowMuonClone.Particle.GetObject()));
            EFlowJets.back().set_user_info(new HJetInfo(Constituent));
            Print(HDetailed, "Muon EFlow Id", EFlowJets.back().user_index());

        }

    }

}

void hanalysis::hdelphes::HJet::GetGenJet()
{
    Print(HInformation, "GetGenJet", clones_arrays_->GetGenJetSum());
    for (const int GenJetNumber : Range(clones_arrays_->GetGenJetSum())) GenJets.push_back(PseudoJet(static_cast<delphes::Jet &>(*clones_arrays_->GetGenJet(GenJetNumber)).P4()));
}

float hanalysis::hdelphes::HJet::GetScalarHt()
{
    Print(HInformation, "GetScalerHt");
    return static_cast<delphes::ScalarHT &>(*clones_arrays_->GetScalarHt()).HT;
}

fastjet::PseudoJet hanalysis::hdelphes::HJet::GetMissingEt()
{
    Print(HInformation, "Get Missing ET");
    return PseudoJet(static_cast<delphes::MissingET &>(*clones_arrays_->GetMissingEt()).P4());
}




HJets hanalysis::hdelphes::HJet::GranulatedJets(const HJets &NewEFlowJets)
{
    // start of granularization of the hadronic calorimeter to redefine hadrons
    const float CellDeltaRap = DetectorGeometry.MinCellResolution;
    const float CellDeltaPhi = DetectorGeometry.MinCellResolution;
    const float PtCutOff = DetectorGeometry.MinCellPt;


    HJets EFlowJets = sorted_by_pt(NewEFlowJets);
    HJets NewGranulatedJets;
    NewGranulatedJets.push_back(EFlowJets[0]);

    for (const auto & EFlowJet : EFlowJets) {
        int NewJet = 0;

        for (size_t j = 0; j < NewGranulatedJets.size(); ++j) {

            const float CellDiffRap = std::abs(EFlowJet.pseudorapidity() - NewGranulatedJets[j].pseudorapidity()) / CellDeltaRap;
            float CellDiffPhi = std::abs(EFlowJet.phi() - NewGranulatedJets[j].phi());
            if (CellDiffPhi > Pi) CellDiffPhi = TwoPi - CellDiffPhi;
            CellDiffPhi = CellDiffPhi / CellDeltaPhi;

            if (CellDiffRap < 1 && CellDiffPhi < 1) {

                NewJet = 1;

                const float TotalEnergy  = EFlowJet.e() + NewGranulatedJets[j].e();
                const float RescaleFactor = std::sqrt(std::pow(EFlowJet.px() + NewGranulatedJets[j].px(), 2) + std::pow(EFlowJet.py() + NewGranulatedJets[j].py(), 2) + pow(EFlowJet.pz() + NewGranulatedJets[j].pz(), 2));
                const float RescaledPx = TotalEnergy * (EFlowJet.px() + NewGranulatedJets[j].px()) / RescaleFactor;
                const float RescaledPy = TotalEnergy * (EFlowJet.py() + NewGranulatedJets[j].py()) / RescaleFactor;
                const float RescaledPz = TotalEnergy * (EFlowJet.pz() + NewGranulatedJets[j].pz()) / RescaleFactor;

                fastjet::PseudoJet CombinedJet(RescaledPx, RescaledPy, RescaledPz, TotalEnergy);


                std::vector<HConstituent> Constituents;
                std::vector<HConstituent> NewConstituents = EFlowJet.user_info<hanalysis::HJetInfo>().Constituents();
                Constituents.insert(Constituents.end(), NewConstituents.begin(), NewConstituents.end());
                NewConstituents = NewGranulatedJets[j].user_info<hanalysis::HJetInfo>().Constituents();
                Constituents.insert(Constituents.end(), NewConstituents.begin(), NewConstituents.end());

                CombinedJet.set_user_info(new HJetInfo(Constituents));

                NewGranulatedJets.erase(NewGranulatedJets.begin() + j);
                NewGranulatedJets.push_back(CombinedJet);
                break;

            }
        }

        if (NewJet != 1) {
            NewGranulatedJets.push_back(EFlowJet);
            NewGranulatedJets = sorted_by_pt(NewGranulatedJets);
        }
    }


    for (size_t ii = 0; ii < NewGranulatedJets.size(); ++ii) {

        if ((NewGranulatedJets[ii].perp() < PtCutOff)) {
            NewGranulatedJets.erase(NewGranulatedJets.begin() + ii);
            --ii;
        }
    }

    return NewGranulatedJets;

}


HJets hanalysis::hdelphes::HJet::GetJets()
{
    fastjet::ClusterSequence *ClusterSequence = new fastjet::ClusterSequence(GranulatedJets(GetStructuredEFlowJets()), DetectorGeometry.JetDefinition);
    HJets Jets = fastjet::sorted_by_pt(ClusterSequence->inclusive_jets(DetectorGeometry.JetMinPt));
    if (Jets.empty()) {
        delete ClusterSequence;
        return Jets;
    }
    ClusterSequence->delete_self_when_unused();
    for (auto & Jet : Jets) {
        std::vector<HConstituent> Constituents;
        for (const auto & Constituent : Jet.constituents()) {
            std::vector<HConstituent> NewConstituents = Constituent.user_info<HJetInfo>().Constituents();
            Constituents.insert(Constituents.end(), NewConstituents.begin(), NewConstituents.end());
        }
        Jet.set_user_info(new HJetInfo(Constituents));
    }
    return Jets;
}

HJets hanalysis::hdelphes::HJet::GetSubJets(const fastjet::PseudoJet &Jet, const int SubJetNumber)
{
    Print(HInformation, "Get Sub Jets");
    HJets Pieces;
    if (!Jet.has_constituents()) {
        Print(HError, "Pieceless jet");
        return Pieces;
    }
    if (!Jet.has_user_info<HJetInfo>()) {
        Print(HError, "Get Sub Jets", "No Jet Info");
        return Pieces;
    }
    //     fastjet::ClusterSequence *ClusterSequence = new fastjet::ClusterSequence(Jet.constituents(), fastjet::JetDefinition(fastjet::kt_algorithm, DetectorGeometry.JetConeSize));
    fastjet::ClusterSequence *ClusterSequence = new fastjet::ClusterSequence(Jet.constituents(), DetectorGeometry.SubJetDefinition);
    HJets NewPieces = ClusterSequence->exclusive_jets_up_to(SubJetNumber);
    ClusterSequence->delete_self_when_unused();

    for (auto & Piece : NewPieces) {
        std::vector<HConstituent> Constituents;
        for (const auto & PieceConstituent : Piece.constituents()) {
            if (!PieceConstituent.has_user_info<HJetInfo>()) {
                Print(HError, "Get Sub Jets", "No Piece Constituent Info");
                continue;
            }
            std::vector<HConstituent> NewConstituents = PieceConstituent.user_info<HJetInfo>().Constituents();
            Constituents.insert(Constituents.end(), NewConstituents.begin(), NewConstituents.end());
        }
        Piece.set_user_info(new HJetInfo(Constituents, Jet.user_info<HJetInfo>().BTag()));
        Pieces.push_back(Piece);
    }
    return Pieces;
}


// fastjet::PseudoJet hanalysis::hdelphes::HJet::GetMissingEt()
// {
//     HJets granulated_jets = GranulatedJets(GetStructuredEFlowJets());
//     fastjet::PseudoJet jet_sum = std::accumulate(granulated_jets.begin(), granulated_jets.end(), fastjet::PseudoJet());
//     return fastjet::PseudoJet(-jet_sum.px(), -jet_sum.py(), -jet_sum.pz(), jet_sum.e());
// }

