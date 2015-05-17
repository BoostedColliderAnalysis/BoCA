# include "HJetDelphes.hh"
# include "fastjet/ClusterSequence.hh"
# include "TClass.h"
# include "Predicate.hh"

analysis::hdelphes::HJet::HJet(): detector_geometry_()
{
//     DebugLevel = analysis::Object::kDebug;
    Print(kNotification, "Constructor");
}

bool analysis::hdelphes::HJet::GetJets(const analysis::HFourVector::HJetDetails JetDetails)
{
    Print(kInformation, "Get Jets", clones_arrays().JetSum());
    for (const int JetNumber : Range(clones_arrays().JetSum())) {
        Print(kDetailed, "Jet Number", JetNumber);
        delphes::Jet &jet = static_cast<delphes::Jet &>(clones_arrays().Jet(JetNumber));
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

void analysis::hdelphes::HJet::DelphesTags(const delphes::Jet &jet)
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

void analysis::hdelphes::HJet::TauTag(const delphes::Jet &jet)
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

fastjet::PseudoJet analysis::hdelphes::HJet::StructuredJet(const delphes::Jet &jet, const analysis::HJet::HJetDetails JetDetails)
{
    Print(kInformation, "Get constituents");
    Jets constituentJets;
    std::vector<Constituent> constituents;
    analysis::JetInfo *jet_info = new analysis::JetInfo(/*jet.BTag*/);
    for (const int constituentNumber : Range(jet.Constituents.GetEntriesFast())) {
        if (!jet.Constituents.At(constituentNumber)) continue;
        fastjet::PseudoJet constituent = Getconstituents(*jet.Constituents.At(constituentNumber), JetDetails);
        jet_info->Addconstituents(constituent.user_info<analysis::JetInfo>().constituents());
        constituentJets.emplace_back(constituent);
    }
    fastjet::PseudoJet Jet = fastjet::join(constituentJets);
    Jet.set_user_info(jet_info);
    return Jet;
}

fastjet::PseudoJet analysis::hdelphes::HJet::Getconstituents(const TObject &Object, const analysis::HJet::HJetDetails JetDetails, const Constituent::SubDetector Detector)
{
    Print(kDebug, "Getconstituent", Object.ClassName());
    fastjet::PseudoJet Jet;
    JetInfo *jet_info = new JetInfo();
    if (Object.IsA() == delphes::GenParticle::Class()) {
        // TODO should we take the GenParticle information into account or not?
        const delphes::GenParticle &particle = static_cast<const delphes::GenParticle &>(Object);
        TLorentzVector Position(particle.X, particle.Y, particle.Z, particle.T);
        Constituent constituent(const_cast<delphes::GenParticle &>(particle).P4(), Position, Constituent::kGenParticle);
        if (JetDetails == TaggingStructure) constituent.SetFamily(GetBranchFamily(Object));
        Jet = PseudoJet(const_cast<delphes::GenParticle &>(particle).P4());
        jet_info->Addconstituent(constituent);
    } else if (Object.IsA() == delphes::Track::Class()) {
        const delphes::Track &track = static_cast<const delphes::Track &>(Object);
        TLorentzVector Position(track.X, track.Y, track.Z, track.T);
        Constituent constituent(const_cast<delphes::Track &>(track).P4(), Position, Constituent::kTrack);
        if (JetDetails == TaggingStructure) constituent.SetFamily(GetBranchFamily(*track.Particle.GetObject()));
        Jet = PseudoJet(const_cast<delphes::Track &>(track).P4());
        jet_info->Addconstituent(constituent);
    } else if (Object.IsA() == delphes::Tower::Class()) {
        const delphes::Tower &tower = static_cast<const delphes::Tower &>(Object);
        std::vector<Constituent> constituents;
        constituents.emplace_back(Constituent(const_cast<delphes::Tower &>(tower).P4()));
        if (JetDetails == TaggingStructure) constituents = GetJetId(tower).constituents();
//         if(Detector == Constituent::HPhoton)
        for (auto & constituent : constituents) constituent.SetDetector(Detector);
        Jet = PseudoJet(const_cast<delphes::Tower &>(tower).P4());
        jet_info->Addconstituents(constituents);
    } else if (Object.IsA() == delphes::Muon::Class()) {
        const delphes::Muon &muon = static_cast<const delphes::Muon &>(Object);
        Constituent constituent(const_cast<delphes::Muon &>(muon).P4(), Constituent::kMuon);
        if (JetDetails == TaggingStructure) constituent.SetFamily(GetBranchFamily(*muon.Particle.GetObject()));
        Jet = PseudoJet(const_cast<delphes::Muon &>(muon).P4());
        jet_info->Addconstituent(constituent);
    } else {
        Print(kError, "Unkonw Jet constituent", Object.ClassName());
    }
    Jet.set_user_info(jet_info);
    Print(kInformation,"Jet info",Jet.has_user_info<JetInfo>());
    return Jet;
}

bool analysis::hdelphes::HJet::GetEFlow(const HJetDetails JetDetails)
{
    Print(kDebug, "Get EFlow", clones_arrays().EFlowTrackSum(), JetDetails);
//     if (clones_arrays().GetEFlowTrackClonesArray())
      GetTrackEFlow(JetDetails);
//     if (clones_arrays().GetEFlowPhotonClonesArray())
      GetPhotonEFlow(JetDetails);
//     if (clones_arrays().GetEFlowNeutralHadronClonesArray())
      GetHadronEFlow(JetDetails);
      if (FindInVector(clones_arrays().Branches(), ClonesArrays::Branch::kEFlowMuon)) GetMuonEFlow(JetDetails);
    Print(kDebug, "Number of EFlow Jet", EFlowJets.size());
    PrintTruthLevel(kDetailed);
    return 1;
}

void analysis::hdelphes::HJet::GetTrackEFlow(const HJetDetails JetDetails)
{
    Print(kDebug, "Get Track EFlow", clones_arrays().EFlowTrackSum());
    if (clones_arrays().ElectronSum() > 0) Print(kDetailed, "Number of Electons", clones_arrays().ElectronSum());
    if (clones_arrays().MuonSum() > 0) Print(kDetailed, "Number of Muons", clones_arrays().MuonSum());
    for (const int EFlowTrackNumber : Range(clones_arrays().EFlowTrackSum())) {
        if (JetDetails == TaggingStructure || JetDetails == Structure) {
//             if (!clones_arrays().GetEFlowTrack(EFlowTrackNumber)) continue;
            EFlowJets.emplace_back(Getconstituents(clones_arrays().EFlowTrack(EFlowTrackNumber), JetDetails, Constituent::kTrack));
            continue;
        }
        delphes::Track &e_flow_track = static_cast<delphes::Track &>(clones_arrays().EFlowTrack(EFlowTrackNumber));
        if (JetDetails == Isolation || JetDetails ==  TaggingIsolation) {
            bool Isolated = GetIsolation<delphes::Electron>(e_flow_track, clones_arrays().ElectronClonesArray());
            if (Isolated) Isolated = GetIsolation<delphes::Muon>(e_flow_track, clones_arrays().MuonClonesArray());
            if (!Isolated) continue;
        }
        EFlowJets.emplace_back(PseudoJet(e_flow_track.P4()));
        if (JetDetails == Tagging || JetDetails ==  TaggingIsolation) {
            Constituent constituent(e_flow_track.P4(), GetBranchFamily(*e_flow_track.Particle.GetObject()));
            EFlowJets.back().set_user_info(new JetInfo(constituent));
            Print(kDetailed, "Track EFlow Id", EFlowJets.back().user_index());
        }
    }
}

void analysis::hdelphes::HJet::GetPhotonEFlow(const HJetDetails JetDetails)
{
    Print(kDebug, "Get Photon EFlow", clones_arrays().EFlowPhotonSum());
    if (clones_arrays().PhotonSum() > 0) Print(kDebug, "Number of Photons", clones_arrays().PhotonSum());
    for (const int e_flow_photon_number : Range(clones_arrays().EFlowPhotonSum())) {
        if (JetDetails == TaggingStructure || JetDetails == Structure) {
//             if (!clones_arrays().GetEFlowPhoton(e_flow_photon_number)) continue;
            EFlowJets.emplace_back(Getconstituents(clones_arrays().EFlowPhoton(e_flow_photon_number), JetDetails, Constituent::kPhoton));
            continue;
        }
        delphes::Tower &e_flow_photon = static_cast<delphes::Tower &>(clones_arrays().EFlowPhoton(e_flow_photon_number));
        if (JetDetails == Isolation || JetDetails == TaggingIsolation) {
            bool Isolated = GetIsolation<delphes::Photon>(e_flow_photon, clones_arrays().PhotonClonesArray());
            if (!Isolated) continue;
        }
        EFlowJets.emplace_back(PseudoJet(e_flow_photon.P4()));
        if (JetDetails == Tagging || JetDetails ==  TaggingIsolation) {
            EFlowJets.back().set_user_info(new analysis::JetInfo(GetJetId(e_flow_photon)));
            Print(kDetailed, "Photon EFlow Id", EFlowJets.back().user_index());
        }
    }
}

void analysis::hdelphes::HJet::GetHadronEFlow(const HJetDetails JetDetails)
{
    Print(kDebug, "Get Hadron EFlow", clones_arrays().EFlowNeutralHadronSum());
    for (const int HadronNumber : Range(clones_arrays().EFlowNeutralHadronSum())) {
        if (JetDetails == TaggingStructure || JetDetails == Structure) {
//             if (!clones_arrays().GetEFlowNeutralHadron(HadronNumber)) continue;
            EFlowJets.emplace_back(Getconstituents(clones_arrays().EFlowNeutralHadron(HadronNumber), JetDetails, Constituent::kTower));
            continue;
        }
        delphes::Tower &e_flow_hadron = static_cast<delphes::Tower &>(clones_arrays().EFlowNeutralHadron(HadronNumber));
        EFlowJets.emplace_back(PseudoJet(e_flow_hadron.P4()));
        if (JetDetails == Tagging || JetDetails ==  TaggingIsolation) {
            EFlowJets.back().set_user_info(new analysis::JetInfo(GetJetId(e_flow_hadron)));
            Print(kDetailed, "Hadron EFlow Id", EFlowJets.back().user_index());
        }
    }
}

void analysis::hdelphes::HJet::GetMuonEFlow(const HJetDetails JetDetails)
{
    Print(kDebug, "Get Muon EFlow", clones_arrays().EFlowMuonSum());
    for (const int muon_number : Range(clones_arrays().EFlowMuonSum())) {
        if (JetDetails == TaggingStructure || JetDetails == Structure) {
//             if (!clones_arrays().GetEFlowMuon(muon_number)) continue;
            EFlowJets.emplace_back(Getconstituents(clones_arrays().EFlowMuon(muon_number), JetDetails, Constituent::kMuon));
            continue;
        }
        delphes::Muon &e_flow_muon = static_cast<delphes::Muon &>(clones_arrays().EFlowMuon(muon_number));
        if (JetDetails == Isolation || JetDetails ==  TaggingIsolation) {
            bool Isolated = GetIsolation<delphes::Muon>(e_flow_muon, clones_arrays().MuonClonesArray());
            if (!Isolated) continue;
        }
        EFlowJets.emplace_back(PseudoJet(e_flow_muon.P4()));
        if (JetDetails == Tagging || JetDetails ==  TaggingIsolation) {
            Constituent constituent(e_flow_muon.P4(), GetBranchFamily(*e_flow_muon.Particle.GetObject()));
            EFlowJets.back().set_user_info(new JetInfo(constituent));
            Print(kDetailed, "Muon EFlow Id", EFlowJets.back().user_index());
        }
    }
}

void analysis::hdelphes::HJet::GetGenJet()
{
    Print(kInformation, "GetGenJet", clones_arrays().GenJetSum());
    for (const int GenJetNumber : Range(clones_arrays().GenJetSum())) GenJets.emplace_back(PseudoJet(static_cast<delphes::Jet &>(clones_arrays().GenJet(GenJetNumber)).P4()));
}

float analysis::hdelphes::HJet::GetScalarHt()
{
    Print(kInformation, "GetScalerHt");
    return static_cast<delphes::ScalarHT &>(clones_arrays().ScalarHt()).HT;
}

fastjet::PseudoJet analysis::hdelphes::HJet::GetMissingEt()
{
    Print(kInformation, "Get Missing ET");
    return PseudoJet(static_cast<delphes::MissingET &>(clones_arrays().MissingEt()).P4());
}

Jets analysis::hdelphes::HJet::GranulatedJets(const Jets &jets)
{
    // start of granularization of the hadronic calorimeter to redefine hadrons
    const float cell_delta_rap = detector_geometry().MinCellResolution;
    const float cell_delta_phi = detector_geometry().MinCellResolution;
    const float pt_cut_off = detector_geometry().MinCellPt;
    Jets e_flow_jets = sorted_by_pt(jets);
    Jets granulated_jets;
    granulated_jets.emplace_back(e_flow_jets.front());
    for (const auto & e_flow_jet : e_flow_jets) {
        bool is_new_jet = false;
        for (std::size_t j = 0; j < granulated_jets.size(); ++j) {
            const float cell_diff_rap = std::abs(e_flow_jet.pseudorapidity() - granulated_jets[j].pseudorapidity()) / cell_delta_rap;
            float cell_diff_phi = std::abs(e_flow_jet.phi() - granulated_jets[j].phi());
            if (cell_diff_phi > Pi) cell_diff_phi = TwoPi - cell_diff_phi;
            cell_diff_phi /= cell_delta_phi;
            if (cell_diff_rap < 1 && cell_diff_phi < 1) {
              is_new_jet = true;
                const float total_energy  = e_flow_jet.e() + granulated_jets[j].e();
                const float rescale_factor = std::sqrt(std::pow(e_flow_jet.px() + granulated_jets[j].px(), 2) + std::pow(e_flow_jet.py() + granulated_jets[j].py(), 2) + pow(e_flow_jet.pz() + granulated_jets[j].pz(), 2));
                const float RescaledPx = total_energy * (e_flow_jet.px() + granulated_jets[j].px()) / rescale_factor;
                const float RescaledPy = total_energy * (e_flow_jet.py() + granulated_jets[j].py()) / rescale_factor;
                const float RescaledPz = total_energy * (e_flow_jet.pz() + granulated_jets[j].pz()) / rescale_factor;
                fastjet::PseudoJet combined_jet(RescaledPx, RescaledPy, RescaledPz, total_energy);
                std::vector<Constituent> constituents;
                std::vector<Constituent> Newconstituents = e_flow_jet.user_info<analysis::JetInfo>().constituents();
                constituents.insert(constituents.end(), Newconstituents.begin(), Newconstituents.end());
                Newconstituents = granulated_jets[j].user_info<analysis::JetInfo>().constituents();
                constituents.insert(constituents.end(), Newconstituents.begin(), Newconstituents.end());
                combined_jet.set_user_info(new JetInfo(constituents));
                granulated_jets.erase(granulated_jets.begin() + j);
                granulated_jets.emplace_back(combined_jet);
                break;
            }
        }
        if (!is_new_jet) {
            granulated_jets.emplace_back(e_flow_jet);
            granulated_jets = sorted_by_pt(granulated_jets);
        }
    }
    for (std::size_t ii = 0; ii < granulated_jets.size(); ++ii) {
        if ((granulated_jets[ii].perp() < pt_cut_off)) {
            granulated_jets.erase(granulated_jets.begin() + ii);
            --ii;
        }
    }
    return granulated_jets;
}

Jets analysis::hdelphes::HJet::GetGranJets()
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
