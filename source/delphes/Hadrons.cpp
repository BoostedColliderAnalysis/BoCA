# include "delphes/Hadrons.hh"
# include "fastjet/ClusterSequence.hh"
# include "TClass.h"
# include "Predicate.hh"

namespace analysis
{

namespace delphes
{

Hadrons::Hadrons()
{
//     DebugLevel = Object::kDebug;
    Print(kNotification, "Constructor");
}

Jets Hadrons::DelphesJets(const FourVector::JetDetail jet_detail)
{
    Print(kInformation, "Jets", clones_arrays().JetSum());
    analysis::Jets jets;
    for (const int JetNumber : Range(clones_arrays().JetSum())) {
        Print(kDetailed, "Jet Number", JetNumber);
        ::delphes::Jet &jet = static_cast<::delphes::Jet &>(clones_arrays().Jet(JetNumber));
        switch (jet_detail) {
        case kPlain: {
            fastjet::PseudoJet Jet = analysis::PseudoJet(jet.P4());
            Jet.set_user_info(new JetInfo(jet));
            jets.emplace_back(Jet);
        }
        break;
        case kTagging: {
            fastjet::PseudoJet Jet = analysis::PseudoJet(jet.P4());
            Jet.set_user_info(new JetInfo(JetId(jet)));
            jets.emplace_back(Jet);
        }
        break;
        case kStructure:
            jets.emplace_back(StructuredJet(jet, jet_detail));
            break;
        case kTaggingStructure: {
            jets.emplace_back(StructuredJet(jet, jet_detail));
        }
        break;
        default:
            Print(kError, "Delphes Jets", "unhandeled case");
        }
    }
    PrintTruthLevel(kDebug);
    return jets;
}

fastjet::PseudoJet Hadrons::StructuredJet(const ::delphes::Jet &jet, const Hadrons::JetDetail jet_detail)
{
    Print(kInformation, "constituents");
    analysis::Jets constituentJets;
    std::vector<Constituent> constituents;
    JetInfo *jet_info = new JetInfo(bool(jet.BTag), jet.Charge);
    for (const int constituentNumber : Range(jet.Constituents.GetEntriesFast())) {
        if (!jet.Constituents.At(constituentNumber)) continue;
        fastjet::PseudoJet constituent = ConstituentJet(*jet.Constituents.At(constituentNumber), jet_detail);
        jet_info->Addconstituents(constituent.user_info<JetInfo>().constituents());
        constituentJets.emplace_back(constituent);
    }
    fastjet::PseudoJet Jet = fastjet::join(constituentJets);
    Jet.set_user_info(jet_info);
    return Jet;
}

fastjet::PseudoJet Hadrons::ConstituentJet(const TObject &Object, const Hadrons::JetDetail jet_detail, const Constituent::SubDetector Detector)
{
    Print(kDebug, "constituent", Object.ClassName());
    fastjet::PseudoJet jet;
    JetInfo *jet_info = new JetInfo();
    if (Object.IsA() == ::delphes::GenParticle::Class()) {
        // TODO should we take the GenParticle information into account or not?
        const ::delphes::GenParticle &particle = static_cast<const ::delphes::GenParticle &>(Object);
        TLorentzVector Position(particle.X, particle.Y, particle.Z, particle.T);
        Constituent constituent(const_cast<::delphes::GenParticle &>(particle).P4(), Position, Constituent::kGenParticle, particle.Charge);
        if (jet_detail == kTaggingStructure) constituent.SetFamily(BranchFamily(Object));
        jet = analysis::PseudoJet(const_cast<::delphes::GenParticle &>(particle).P4());
        jet_info->Addconstituent(constituent);
    } else if (Object.IsA() == ::delphes::Track::Class()) {
        const ::delphes::Track &track = static_cast<const ::delphes::Track &>(Object);
        TLorentzVector Position(track.X, track.Y, track.Z, track.T);
        Constituent constituent(const_cast<::delphes::Track &>(track).P4(), Position, Constituent::kTrack, track.Charge);
        if (jet_detail == kTaggingStructure) constituent.SetFamily(BranchFamily(*track.Particle.GetObject()));
        jet = analysis::PseudoJet(const_cast<::delphes::Track &>(track).P4());
        jet_info->Addconstituent(constituent);
    } else if (Object.IsA() == ::delphes::Tower::Class()) {
        const ::delphes::Tower &tower = static_cast<const ::delphes::Tower &>(Object);
        std::vector<Constituent> constituents;
        constituents.emplace_back(Constituent(const_cast<::delphes::Tower &>(tower).P4()));
        if (jet_detail == kTaggingStructure) constituents = JetId(tower).constituents();
//         if(Detector == Constituent::HPhoton)
        for (auto & constituent : constituents) constituent.SetDetector(Detector);
        jet = analysis::PseudoJet(const_cast<::delphes::Tower &>(tower).P4());
        jet_info->Addconstituents(constituents);
    } else if (Object.IsA() == ::delphes::Muon::Class()) {
        const ::delphes::Muon &muon = static_cast<const ::delphes::Muon &>(Object);
        Constituent constituent(const_cast<::delphes::Muon &>(muon).P4(), Constituent::kMuon, muon.Charge);
        if (jet_detail == kTaggingStructure) constituent.SetFamily(BranchFamily(*muon.Particle.GetObject()));
        jet = analysis::PseudoJet(const_cast<::delphes::Muon &>(muon).P4());
        jet_info->Addconstituent(constituent);
    } else {
        Print(kError, "Unkonw Jet constituent", Object.ClassName());
    }
    jet.set_user_info(jet_info);
    Print(kInformation, "Jet info", jet.has_user_info<JetInfo>());
    return jet;
}

Jets Hadrons::EFlowJets(const JetDetail jet_detail)
{
    analysis::Jets e_flow_jets;
    Print(kDebug, "EFlow", clones_arrays().EFlowTrackSum(), jet_detail);
    if (FindInVector(clones_arrays().Branches(), ClonesArrays::Branch::kEFlowTrack)) Join(e_flow_jets, EFlowTrack(jet_detail));
    if (FindInVector(clones_arrays().Branches(), ClonesArrays::Branch::kEflowPhoton)) Join(e_flow_jets, EFlowPhoton(jet_detail));
    if (FindInVector(clones_arrays().Branches(), ClonesArrays::Branch::kEFlowNeutralHadron)) Join(e_flow_jets, EFlowHadron(jet_detail));
    if (FindInVector(clones_arrays().Branches(), ClonesArrays::Branch::kEFlowMuon)) Join(e_flow_jets, EFlowMuon(jet_detail));
    Print(kDebug, "Number of EFlow Jet", e_flow_jets.size());
    PrintTruthLevel(kDetailed);
    return e_flow_jets;
}

Jets Hadrons::EFlowTrack(const JetDetail jet_detail)
{
    analysis::Jets e_flow_jets;
    Print(kDebug, "Track EFlow", clones_arrays().EFlowTrackSum());
    if (clones_arrays().ElectronSum() > 0) Print(kDetailed, "Number of Electons", clones_arrays().ElectronSum());
    if (clones_arrays().MuonSum() > 0) Print(kDetailed, "Number of Muons", clones_arrays().MuonSum());
    for (const int EFlowTrackNumber : Range(clones_arrays().EFlowTrackSum())) {
        if (jet_detail == kTaggingStructure || jet_detail == kStructure) {
//             if (!clones_arrays().GetEFlowTrack(EFlowTrackNumber)) continue;
            e_flow_jets.emplace_back(ConstituentJet(clones_arrays().EFlowTrack(EFlowTrackNumber), jet_detail, Constituent::kTrack));
            continue;
        }
        ::delphes::Track &e_flow_track = static_cast<::delphes::Track &>(clones_arrays().EFlowTrack(EFlowTrackNumber));
        if (jet_detail == kIsolation || jet_detail ==  kTaggingIsolation) {
            bool Isolated = GetIsolation<::delphes::Electron>(e_flow_track, clones_arrays().ElectronClonesArray());
            if (Isolated) Isolated = GetIsolation<::delphes::Muon>(e_flow_track, clones_arrays().MuonClonesArray());
            if (!Isolated) continue;
        }
        e_flow_jets.emplace_back(analysis::PseudoJet(e_flow_track.P4()));
        if (jet_detail == kTagging || jet_detail ==  kTaggingIsolation) {
            Constituent constituent(e_flow_track.P4(), BranchFamily(*e_flow_track.Particle.GetObject()));
            e_flow_jets.back().set_user_info(new JetInfo(constituent));
            Print(kDetailed, "Track EFlow Id", e_flow_jets.back().user_index());
        }
    }
    return e_flow_jets;
}

Jets Hadrons::EFlowPhoton(const JetDetail jet_detail)
{
    Print(kDebug, "Photon EFlow", clones_arrays().EFlowPhotonSum());
    analysis::Jets e_flow_jets;
    if (clones_arrays().PhotonSum() > 0) Print(kDebug, "Number of Photons", clones_arrays().PhotonSum());
    for (const int e_flow_photon_number : Range(clones_arrays().EFlowPhotonSum())) {
        if (jet_detail == kTaggingStructure || jet_detail == kStructure) {
//             if (!clones_arrays().GetEFlowPhoton(e_flow_photon_number)) continue;
            e_flow_jets.emplace_back(ConstituentJet(clones_arrays().EFlowPhoton(e_flow_photon_number), jet_detail, Constituent::kPhoton));
            continue;
        }
        ::delphes::Tower &e_flow_photon = static_cast<::delphes::Tower &>(clones_arrays().EFlowPhoton(e_flow_photon_number));
        if (jet_detail == kIsolation || jet_detail == kTaggingIsolation) {
            bool Isolated = GetIsolation<::delphes::Photon>(e_flow_photon, clones_arrays().PhotonClonesArray());
            if (!Isolated) continue;
        }
        e_flow_jets.emplace_back(analysis::PseudoJet(e_flow_photon.P4()));
        if (jet_detail == kTagging || jet_detail ==  kTaggingIsolation) {
            e_flow_jets.back().set_user_info(new JetInfo(JetId(e_flow_photon)));
            Print(kDetailed, "Photon EFlow Id", e_flow_jets.back().user_index());
        }
    }
    return e_flow_jets;
}

Jets Hadrons::EFlowHadron(const JetDetail jet_detail)
{
    Print(kDebug, "Hadron EFlow", clones_arrays().EFlowNeutralHadronSum());
    analysis::Jets e_flow_jets;
    for (const int HadronNumber : Range(clones_arrays().EFlowNeutralHadronSum())) {
        if (jet_detail == kTaggingStructure || jet_detail == kStructure) {
            e_flow_jets.emplace_back(ConstituentJet(clones_arrays().EFlowNeutralHadron(HadronNumber), jet_detail, Constituent::kTower));
            continue;
        }
        ::delphes::Tower &e_flow_hadron = static_cast<::delphes::Tower &>(clones_arrays().EFlowNeutralHadron(HadronNumber));
        e_flow_jets.emplace_back(analysis::PseudoJet(e_flow_hadron.P4()));
        if (jet_detail == kTagging || jet_detail ==  kTaggingIsolation) {
            e_flow_jets.back().set_user_info(new JetInfo(JetId(e_flow_hadron)));
            Print(kDetailed, "Hadron EFlow Id", e_flow_jets.back().user_index());
        }
    }
    return e_flow_jets;
}

Jets Hadrons::EFlowMuon(const JetDetail jet_detail)
{
    Print(kDebug, "Muon EFlow", clones_arrays().EFlowMuonSum());
    analysis::Jets e_flow_jets;
    for (const int muon_number : Range(clones_arrays().EFlowMuonSum())) {
        if (jet_detail == kTaggingStructure || jet_detail == kStructure) {
//             if (!clones_arrays().GetEFlowMuon(muon_number)) continue;
            e_flow_jets.emplace_back(ConstituentJet(clones_arrays().EFlowMuon(muon_number), jet_detail, Constituent::kMuon));
            continue;
        }
        ::delphes::Muon &e_flow_muon = static_cast<::delphes::Muon &>(clones_arrays().EFlowMuon(muon_number));
        if (jet_detail == kIsolation || jet_detail ==  kTaggingIsolation) {
            bool Isolated = GetIsolation<::delphes::Muon>(e_flow_muon, clones_arrays().MuonClonesArray());
            if (!Isolated) continue;
        }
        e_flow_jets.emplace_back(analysis::PseudoJet(e_flow_muon.P4()));
        if (jet_detail == kTagging || jet_detail ==  kTaggingIsolation) {
            Constituent constituent(e_flow_muon.P4(), BranchFamily(*e_flow_muon.Particle.GetObject()));
            e_flow_jets.back().set_user_info(new JetInfo(constituent));
            Print(kDetailed, "Muon EFlow Id", e_flow_jets.back().user_index());
        }
    }
    return e_flow_jets;
}

Jets Hadrons::GenJets()
{
    Print(kInformation, "GenJet", clones_arrays().GenJetSum());
    analysis::Jets gen_jets;
    for (const int GenJetNumber : Range(clones_arrays().GenJetSum())) gen_jets.emplace_back(analysis::PseudoJet(static_cast<::delphes::Jet &>(clones_arrays().GenJet(GenJetNumber)).P4()));
    return gen_jets;
}

float Hadrons::ScalarHt()
{
    Print(kInformation, "ScalerHt");
    return static_cast<::delphes::ScalarHT &>(clones_arrays().ScalarHt()).HT;
}

fastjet::PseudoJet Hadrons::MissingEt()
{
    Print(kInformation, "Missing ET");
    return analysis::PseudoJet(static_cast<::delphes::MissingET &>(clones_arrays().MissingEt()).P4());
}

Jets Hadrons::GranulatedJets(const analysis::Jets &e_flow_jets)
{
    // start of granularization of the hadronic calorimeter to redefine hadrons
    DetectorGeometry detector_geometry;
    const float cell_delta_rap = detector_geometry.MinCellResolution;
    const float cell_delta_phi = detector_geometry.MinCellResolution;
    const float pt_cut_off = detector_geometry.MinCellPt;
    analysis::Jets sorted_jets = sorted_by_pt(e_flow_jets);
    analysis::Jets jets;
    jets.emplace_back(sorted_jets.front());
    for (const auto & e_flow_jet : sorted_jets) {
        bool is_new_jet = false;
        for (std::size_t j = 0; j < jets.size(); ++j) {
            const float cell_diff_rap = std::abs(e_flow_jet.pseudorapidity() - jets[j].pseudorapidity()) / cell_delta_rap;
            float cell_diff_phi = std::abs(e_flow_jet.phi() - jets[j].phi());
            if (cell_diff_phi > M_PI) cell_diff_phi = 2 * M_PI - cell_diff_phi;
            cell_diff_phi /= cell_delta_phi;
            if (cell_diff_rap < 1 && cell_diff_phi < 1) {
                is_new_jet = true;
                const float total_energy  = e_flow_jet.e() + jets[j].e();
                const float rescale_factor = std::sqrt(std::pow(e_flow_jet.px() + jets[j].px(), 2) + std::pow(e_flow_jet.py() + jets[j].py(), 2) + pow(e_flow_jet.pz() + jets[j].pz(), 2));
                const float RescaledPx = total_energy * (e_flow_jet.px() + jets[j].px()) / rescale_factor;
                const float RescaledPy = total_energy * (e_flow_jet.py() + jets[j].py()) / rescale_factor;
                const float RescaledPz = total_energy * (e_flow_jet.pz() + jets[j].pz()) / rescale_factor;
                fastjet::PseudoJet combined_jet(RescaledPx, RescaledPy, RescaledPz, total_energy);
                std::vector<Constituent> combined_constituents;
                std::vector<Constituent> constituents = e_flow_jet.user_info<JetInfo>().constituents();
                combined_constituents.insert(combined_constituents.end(), constituents.begin(), constituents.end());
                constituents = jets[j].user_info<JetInfo>().constituents();
                combined_constituents.insert(combined_constituents.end(), constituents.begin(), constituents.end());
                combined_jet.set_user_info(new JetInfo(combined_constituents));
                jets.erase(jets.begin() + j);
                jets.emplace_back(combined_jet);
                break;
            }
        }
        if (!is_new_jet) {
            jets.emplace_back(e_flow_jet);
            jets = sorted_by_pt(jets);
        }
    }
    jets = RemoveIfSoft(jets, pt_cut_off);
    return jets;
}

Jets Hadrons::ClusteredJets()
{
    DetectorGeometry detector_geometry;
    fastjet::ClusterSequence *cluster_sequence = new fastjet::ClusterSequence(GranulatedJets(EFlowJets(kStructure)), detector_geometry.JetDefinition);
    analysis::Jets jets = fastjet::sorted_by_pt(cluster_sequence->inclusive_jets(detector_geometry.JetMinPt));
    if (jets.empty()) {
        delete cluster_sequence;
        return jets;
    }
    cluster_sequence->delete_self_when_unused();
    for (auto & jet : jets)  {
        std::vector<Constituent> constituents;
        for (const auto & constituent : jet.constituents()) {
            std::vector<Constituent> Newconstituents = constituent.user_info<JetInfo>().constituents();
            constituents.insert(constituents.end(), Newconstituents.begin(), Newconstituents.end());
        }
        jet.set_user_info(new JetInfo(constituents));
    }
    return jets;
}

void Hadrons::DoubleCounting()
{

}

}

}