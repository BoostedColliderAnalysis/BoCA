# include "HJetDelphes.hh"
# include "fastjet/ClusterSequence.hh"



hanalysis::hdelphes::HJet::HJet(): detector_geometry_()
{
//     DebugLevel = hanalysis::HObject::kDebug;
    Print(kNotification, "Constructor");
}

bool hanalysis::hdelphes::HJet::GetJets(const hanalysis::HFourVector::HJetDetails JetDetails)
{
    Print(kInformation, "Get Jets", clones_arrays_->JetSum());
    for (const int JetNumber : Range(clones_arrays_->JetSum())) {
        Print(kDetailed, "Jet Number", JetNumber);
        delphes::Jet &jet = static_cast<delphes::Jet &>(*clones_arrays_->Jet(JetNumber));

        switch (JetDetails) {
        case Plain: {
            fastjet::PseudoJet Jet = PseudoJet(jet.P4());
            Jet.set_user_info(new JetInfo(/*jet.BTag*/));
            jets_.emplace_back(Jet);
        }
        break;
        case Tagging: {
            fastjet::PseudoJet Jet = PseudoJet(jet.P4());
            JetInfo *jet_info = new JetInfo(GetJetId(jet));
//             jet_info->SetBTag(jet.BTag);
            Jet.set_user_info(jet_info);
            jets_.emplace_back(Jet);
        }
        break;
        case Structure:
            jets_.emplace_back(StructuredJet(jet, JetDetails));
            break;
        case TaggingStructure: {
            jets_.emplace_back(StructuredJet(jet, JetDetails));
        }
        break;
        default:
            Print(kError, "unhandeled case");
        }
        DelphesTags(jet);
    }
    PrintTruthLevel(kDebug);
    return 1;
}

void hanalysis::hdelphes::HJet::DelphesTags(const delphes::Jet &jet)
{
    Print(kInformation, "Get taggs");
    if (jet.TauTag == 1) {
        Print(kDetailed, "Has Tau Tag");
        TauTag(jet);
    } else if (jet.BTag > 0) {
        Print(kDetailed, "Has B Tag");
        BottomLorentzVectors.emplace_back(const_cast<delphes::Jet &>(jet).P4());
        BottomJets.emplace_back(PseudoJet(const_cast<delphes::Jet &>(jet).P4()));
    } else {
        Print(kDetailed, "No Delphes Tag");
        JetLorentzVectors.emplace_back(const_cast<delphes::Jet &>(jet).P4());
    }

    Print(kDebug, "Btag", jet.BTag);
}

void hanalysis::hdelphes::HJet::TauTag(const delphes::Jet &jet)
{
    Print(kInformation, "TauTagCalculations");
    if (jet.Charge == - 1) {
        TauLorentzVectors.emplace_back(const_cast<delphes::Jet &>(jet).P4());
        Print(kDebug, "Tau Jet");
    } else if (jet.Charge == 1) {
        AntiTauLorentzVectors.emplace_back(const_cast<delphes::Jet &>(jet).P4());
        Print(kDebug, "Anti Tau Jet");
    } else Print(kError, "Jet Charge: ", jet.Charge);
}

fastjet::PseudoJet hanalysis::hdelphes::HJet::StructuredJet(const delphes::Jet &jet, const hanalysis::HJet::HJetDetails JetDetails)
{
    Print(kInformation, "Get constituents");
    Jets constituentJets;
    std::vector<Constituent> constituents;
    hanalysis::JetInfo *jet_info = new hanalysis::JetInfo(/*jet.BTag*/);

    for (const int constituentNumber : Range(jet.Constituents.GetEntriesFast())) {
      if (!jet.Constituents.At(constituentNumber)) continue;
        fastjet::PseudoJet constituent = Getconstituents(*jet.Constituents.At(constituentNumber), JetDetails);
        jet_info->Addconstituents(constituent.user_info<hanalysis::JetInfo>().constituents());
        constituentJets.emplace_back(constituent);
    }

    fastjet::PseudoJet Jet = fastjet::join(constituentJets);
    Jet.set_user_info(jet_info);
    return Jet;
}

fastjet::PseudoJet hanalysis::hdelphes::HJet::Getconstituents(const TObject &Object, const hanalysis::HJet::HJetDetails JetDetails, const Constituent::SubDetector Detector)
{

    Print(kDebug, "Getconstituent", Object.ClassName());
    fastjet::PseudoJet Jet;
    JetInfo *jet_info = new JetInfo();

    if (Object.IsA() == delphes::GenParticle::Class()) {
        // TODO should we take the GenParticle information into account or not?
        const delphes::GenParticle &ParticleClone = static_cast<const delphes::GenParticle &>(Object);
        TLorentzVector Position(ParticleClone.X, ParticleClone.Y, ParticleClone.Z, ParticleClone.T);
        Constituent constituent(const_cast<delphes::GenParticle &>(ParticleClone).P4(), Position, Constituent::HGenParticle);
        if (JetDetails == TaggingStructure) constituent.SetFamily(GetBranchFamily(Object));
        Jet = PseudoJet(const_cast<delphes::GenParticle &>(ParticleClone).P4());
        jet_info->Addconstituent(constituent);
    } else if (Object.IsA() == delphes::Track::Class()) {
        const delphes::Track &TrackClone = static_cast<const delphes::Track &>(Object);
        TLorentzVector Position(TrackClone.X, TrackClone.Y, TrackClone.Z, TrackClone.T);
        Constituent constituent(const_cast<delphes::Track &>(TrackClone).P4(), Position, Constituent::HTrack);
        if (JetDetails == TaggingStructure) constituent.SetFamily(GetBranchFamily(*TrackClone.Particle.GetObject()));
        Jet = PseudoJet(const_cast<delphes::Track &>(TrackClone).P4());
        jet_info->Addconstituent(constituent);
    } else if (Object.IsA() == delphes::Tower::Class()) {
        const delphes::Tower &TowerClone = static_cast<const delphes::Tower &>(Object);
        std::vector<Constituent> constituents;
        constituents.emplace_back(Constituent(const_cast<delphes::Tower &>(TowerClone).P4()));
        if (JetDetails == TaggingStructure) constituents = GetJetId(TowerClone).constituents();
//         if(Detector == Constituent::HPhoton)
        for (auto & constituent : constituents) constituent.SetDetector(Detector);
        Jet = PseudoJet(const_cast<delphes::Tower &>(TowerClone).P4());
        jet_info->Addconstituents(constituents);
    } else if (Object.IsA() == delphes::Muon::Class()) {
        const delphes::Muon &MuonClone = static_cast<const delphes::Muon &>(Object);
        Constituent constituent(const_cast<delphes::Muon &>(MuonClone).P4(), Constituent::HMuon);
        if (JetDetails == TaggingStructure) constituent.SetFamily(GetBranchFamily(*MuonClone.Particle.GetObject()));
        Jet = PseudoJet(const_cast<delphes::Muon &>(MuonClone).P4());
        jet_info->Addconstituent(constituent);
    } else {
        Print(kError, "Unkonw Jet constituent", Object.ClassName());
    }

    Jet.set_user_info(jet_info);
    Print(kInformation,"Jet info",Jet.has_user_info<JetInfo>());

    return Jet;

}

bool hanalysis::hdelphes::HJet::GetEFlow(const HJetDetails JetDetails)
{
    Print(kDebug, "Get EFlow", clones_arrays_->GetEFlowTrackSum(), JetDetails);

    if (clones_arrays_->GetEFlowTrackClonesArray()) GetTrackEFlow(JetDetails);
    if (clones_arrays_->GetEFlowPhotonClonesArray()) GetPhotonEFlow(JetDetails);
    if (clones_arrays_->GetEFlowNeutralHadronClonesArray()) GetHadronEFlow(JetDetails);
    if (clones_arrays_->GetEFlowMuonClonesArray()) GetMuonEFlow(JetDetails);

    Print(kDebug, "Number of EFlow Jet", EFlowJets.size());

    PrintTruthLevel(kDetailed);

    return 1;

}

void hanalysis::hdelphes::HJet::GetTrackEFlow(const HJetDetails JetDetails)
{
    Print(kDebug, "Get Track EFlow", clones_arrays_->GetEFlowTrackSum());

    if (clones_arrays_->GetElectronSum() > 0) Print(kDetailed, "Number of Electons", clones_arrays_->GetElectronSum());
    if (clones_arrays_->GetMuonSum() > 0) Print(kDetailed, "Number of Muons", clones_arrays_->GetMuonSum());

    for (const int EFlowTrackNumber : Range(clones_arrays_->GetEFlowTrackSum())) {

        if (JetDetails == TaggingStructure || JetDetails == Structure) {
            if (!clones_arrays_->GetEFlowTrack(EFlowTrackNumber)) continue;
            EFlowJets.emplace_back(Getconstituents(*clones_arrays_->GetEFlowTrack(EFlowTrackNumber), JetDetails, Constituent::HTrack));
            continue;
        }

        delphes::Track &EFlowTrackClone = static_cast<delphes::Track &>(* clones_arrays_->GetEFlowTrack(EFlowTrackNumber));

        if (JetDetails == Isolation || JetDetails ==  TaggingIsolation) {

            bool Isolated = GetIsolation<delphes::Electron>(EFlowTrackClone, *clones_arrays_->GetElectronClonesArray());
            if (Isolated) Isolated = GetIsolation<delphes::Muon>(EFlowTrackClone, *clones_arrays_->GetMuonClonesArray());
            if (!Isolated) continue;

        }

        EFlowJets.emplace_back(PseudoJet(EFlowTrackClone.P4()));

        if (JetDetails == Tagging || JetDetails ==  TaggingIsolation) {

            Constituent constituent(EFlowTrackClone.P4(), GetBranchFamily(*EFlowTrackClone.Particle.GetObject()));
            EFlowJets.back().set_user_info(new JetInfo(constituent));
            Print(kDetailed, "Track EFlow Id", EFlowJets.back().user_index());

        }
    }

}

void hanalysis::hdelphes::HJet::GetPhotonEFlow(const HJetDetails JetDetails)
{
    Print(kDebug, "Get Photon EFlow", clones_arrays_->GetEFlowPhotonSum());

    if (clones_arrays_->GetPhotonSum() > 0) Print(kDebug, "Number of Photons", clones_arrays_->GetPhotonSum());
    for (const int EFlowPhotonNumber : Range(clones_arrays_->GetEFlowPhotonSum())) {

        if (JetDetails == TaggingStructure || JetDetails == Structure) {
            if (!clones_arrays_->GetEFlowPhoton(EFlowPhotonNumber)) continue;
            EFlowJets.emplace_back(Getconstituents(*clones_arrays_->GetEFlowPhoton(EFlowPhotonNumber), JetDetails, Constituent::HPhoton));
            continue;
        }

        delphes::Tower &EFlowPhotonClone = static_cast<delphes::Tower &>(* clones_arrays_->GetEFlowPhoton(EFlowPhotonNumber));

        if (JetDetails == Isolation || JetDetails == TaggingIsolation) {

            bool Isolated = GetIsolation<delphes::Photon>(EFlowPhotonClone, *clones_arrays_->GetPhotonClonesArray());
            if (!Isolated) continue;

        }

        EFlowJets.emplace_back(PseudoJet(EFlowPhotonClone.P4()));

        if (JetDetails == Tagging || JetDetails ==  TaggingIsolation) {

            EFlowJets.back().set_user_info(new hanalysis::JetInfo(GetJetId(EFlowPhotonClone)));
            Print(kDetailed, "Photon EFlow Id", EFlowJets.back().user_index());

        }


    }

}

void hanalysis::hdelphes::HJet::GetHadronEFlow(const HJetDetails JetDetails)
{

    Print(kDebug, "Get Hadron EFlow", clones_arrays_->GetEFlowNeutralHadronSum());

    for (const int HadronNumber : Range(clones_arrays_->GetEFlowNeutralHadronSum())) {

        if (JetDetails == TaggingStructure || JetDetails == Structure) {
            if (!clones_arrays_->GetEFlowNeutralHadron(HadronNumber)) continue;
            EFlowJets.emplace_back(Getconstituents(*clones_arrays_->GetEFlowNeutralHadron(HadronNumber), JetDetails, Constituent::HTower));
            continue;
        }

        delphes::Tower &HadronClone = static_cast<delphes::Tower &>(*clones_arrays_->GetEFlowNeutralHadron(HadronNumber));

        EFlowJets.emplace_back(PseudoJet(HadronClone.P4()));
        if (JetDetails == Tagging || JetDetails ==  TaggingIsolation) {

            EFlowJets.back().set_user_info(new hanalysis::JetInfo(GetJetId(HadronClone)));
            Print(kDetailed, "Hadron EFlow Id", EFlowJets.back().user_index());

        }

    }

}

void hanalysis::hdelphes::HJet::GetMuonEFlow(const HJetDetails JetDetails)
{

    Print(kDebug, "Get Muon EFlow", clones_arrays_->GetEFlowMuonSum());

    for (const int MuonNumber : Range(clones_arrays_->GetEFlowMuonSum())) {

        if (JetDetails == TaggingStructure || JetDetails == Structure) {
            if (!clones_arrays_->GetEFlowMuon(MuonNumber)) continue;
            EFlowJets.emplace_back(Getconstituents(*clones_arrays_->GetEFlowMuon(MuonNumber), JetDetails, Constituent::HMuon));
            continue;
        }

        delphes::Muon &EFlowMuonClone = static_cast<delphes::Muon &>(*clones_arrays_->GetEFlowMuon(MuonNumber));

        if (JetDetails == Isolation || JetDetails ==  TaggingIsolation) {

            bool Isolated = GetIsolation<delphes::Muon>(EFlowMuonClone, *clones_arrays_->GetMuonClonesArray());
            if (!Isolated) continue;

        }

        EFlowJets.emplace_back(PseudoJet(EFlowMuonClone.P4()));
        if (JetDetails == Tagging || JetDetails ==  TaggingIsolation) {

            Constituent constituent(EFlowMuonClone.P4(), GetBranchFamily(*EFlowMuonClone.Particle.GetObject()));
            EFlowJets.back().set_user_info(new JetInfo(constituent));
            Print(kDetailed, "Muon EFlow Id", EFlowJets.back().user_index());

        }

    }

}

void hanalysis::hdelphes::HJet::GetGenJet()
{
    Print(kInformation, "GetGenJet", clones_arrays_->GetGenJetSum());
    for (const int GenJetNumber : Range(clones_arrays_->GetGenJetSum())) GenJets.emplace_back(PseudoJet(static_cast<delphes::Jet &>(*clones_arrays_->GetGenJet(GenJetNumber)).P4()));
}

float hanalysis::hdelphes::HJet::GetScalarHt()
{
    Print(kInformation, "GetScalerHt");
    return static_cast<delphes::ScalarHT &>(*clones_arrays_->GetScalarHt()).HT;
}

fastjet::PseudoJet hanalysis::hdelphes::HJet::GetMissingEt()
{
    Print(kInformation, "Get Missing ET");
    return PseudoJet(static_cast<delphes::MissingET &>(*clones_arrays_->GetMissingEt()).P4());
}




Jets hanalysis::hdelphes::HJet::GranulatedJets(const Jets &NewEFlowJets)
{
    // start of granularization of the hadronic calorimeter to redefine hadrons
    const float CellDeltaRap = detector_geometry().MinCellResolution;
    const float CellDeltaPhi = detector_geometry().MinCellResolution;
    const float PtCutOff = detector_geometry().MinCellPt;


    Jets EFlowJets = sorted_by_pt(NewEFlowJets);
    Jets NewGranulatedJets;
    NewGranulatedJets.emplace_back(EFlowJets[0]);

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


                std::vector<Constituent> constituents;
                std::vector<Constituent> Newconstituents = EFlowJet.user_info<hanalysis::JetInfo>().constituents();
                constituents.insert(constituents.end(), Newconstituents.begin(), Newconstituents.end());
                Newconstituents = NewGranulatedJets[j].user_info<hanalysis::JetInfo>().constituents();
                constituents.insert(constituents.end(), Newconstituents.begin(), Newconstituents.end());

                CombinedJet.set_user_info(new JetInfo(constituents));

                NewGranulatedJets.erase(NewGranulatedJets.begin() + j);
                NewGranulatedJets.emplace_back(CombinedJet);
                break;

            }
        }

        if (NewJet != 1) {
            NewGranulatedJets.emplace_back(EFlowJet);
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


Jets hanalysis::hdelphes::HJet::GetGranJets()
{
    fastjet::ClusterSequence *cluster_sequence = new fastjet::ClusterSequence(GranulatedJets(GetStructuredEFlowJets()), detector_geometry().JetDefinition);
    Jets jets = fastjet::sorted_by_pt(cluster_sequence->inclusive_jets(detector_geometry().JetMinPt));
    if (jets.empty()) {
        delete cluster_sequence;
        return jets;
    }
    cluster_sequence->delete_self_when_unused();
    for (auto & Jet : jets)  {
        std::vector<Constituent> constituents;
        for (const auto & constituent : Jet.constituents()) {
            std::vector<Constituent> Newconstituents = constituent.user_info<JetInfo>().constituents();
            constituents.insert(constituents.end(), Newconstituents.begin(), Newconstituents.end());
        }
        Jet.set_user_info(new JetInfo(constituents));
    }
    return jets;
}

Jets hanalysis::hdelphes::HJet::GetSubJets(const fastjet::PseudoJet &Jet, const int SubJetNumber)
{
    Print(kInformation, "Get Sub Jets");
    Jets Pieces;
    if (!Jet.has_constituents()) {
        Print(kError, "Pieceless jet");
        return Pieces;
    }
    if (!Jet.has_user_info<JetInfo>()) {
        Print(kError, "Get Sub Jets", "No Jet Info");
        return Pieces;
    }
    //     fastjet::ClusterSequence *ClusterSequence = new fastjet::ClusterSequence(Jet.constituents(), fastjet::JetDefinition(fastjet::kt_algorithm, detector_geometry().JetConeSize));
    fastjet::ClusterSequence *ClusterSequence = new fastjet::ClusterSequence(Jet.constituents(), detector_geometry().SubJetDefinition);
    Jets NewPieces = ClusterSequence->exclusive_jets_up_to(SubJetNumber);
    ClusterSequence->delete_self_when_unused();

    for (auto & Piece : NewPieces) {
        std::vector<Constituent> constituents;
        for (const auto & Piececonstituent : Piece.constituents()) {
            if (!Piececonstituent.has_user_info<JetInfo>()) {
                Print(kError, "Get Sub Jets", "No Piece constituent Info");
                continue;
            }
            std::vector<Constituent> Newconstituents = Piececonstituent.user_info<JetInfo>().constituents();
            constituents.insert(constituents.end(), Newconstituents.begin(), Newconstituents.end());
        }
        Piece.set_user_info(new JetInfo(constituents/*, Jet.user_info<JetInfo>().BTag()*/));
        Pieces.emplace_back(Piece);
    }
    return Pieces;
}


// fastjet::PseudoJet hanalysis::hdelphes::HJet::GetMissingEt()
// {
//     Jets granulated_jets = GranulatedJets(GetStructuredEFlowJets());
//     fastjet::PseudoJet jet_sum = std::accumulate(granulated_jets.begin(), granulated_jets.end(), fastjet::PseudoJet());
//     return fastjet::PseudoJet(-jet_sum.px(), -jet_sum.py(), -jet_sum.pz(), jet_sum.e());
// }

