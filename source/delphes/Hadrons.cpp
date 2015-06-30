#include "delphes/Hadrons.hh"
#include "fastjet/ClusterSequence.hh"

#include "TClass.h"
#include "Predicate.hh"
#include "Debug.hh"

namespace analysis
{

namespace delphes
{

Hadrons::Hadrons()
{
//     debug_level_ = Severity::detailed;
    Note("Constructor");
}

Jets Hadrons::DelphesJets(const JetDetail jet_detail)
{
    Info("Jets", clones_arrays().JetSum());
    analysis::Jets jets;
    for (const int JetNumber : Range(clones_arrays().JetSum())) {
        Detail("Jet Number", JetNumber);
        ::delphes::Jet &jet = static_cast<::delphes::Jet &>(clones_arrays().Jet(JetNumber));
        switch (jet_detail) {
        case JetDetail::plain: {
            fastjet::PseudoJet Jet = analysis::PseudoJet(jet.P4());
            Jet.set_user_info(new JetInfo(jet));
            jets.emplace_back(Jet);
        }
        break;
        case JetDetail::tagging: {
            fastjet::PseudoJet Jet = analysis::PseudoJet(jet.P4());
            Jet.set_user_info(new JetInfo(JetId(jet)));
            jets.emplace_back(Jet);
        }
        break;
        case JetDetail::structure:
            jets.emplace_back(StructuredJet(jet, jet_detail));
            break;
        case JetDetail::tagging_structure: {
            jets.emplace_back(StructuredJet(jet, jet_detail));
        }
        break;
        default:
            Error("Delphes Jets", "unhandeled case");
        }
    }
    PrintTruthLevel(Severity::debug);
    return jets;
}

fastjet::PseudoJet Hadrons::StructuredJet(const ::delphes::Jet &jet, const JetDetail jet_detail)
{
    Info("Constituents");
    analysis::Jets constituentJets;
    std::vector<Constituent> constituents;
    JetInfo *jet_info = new JetInfo(bool(jet.BTag), jet.Charge);
    for (const int constituentNumber : Range(jet.Constituents.GetEntriesFast())) {
        if (!jet.Constituents.At(constituentNumber)) continue;
        fastjet::PseudoJet constituent = ConstituentJet(*jet.Constituents.At(constituentNumber), jet_detail);
        jet_info->AddConstituents(constituent.user_info<JetInfo>().constituents());
        constituentJets.emplace_back(constituent);
    }
    fastjet::PseudoJet Jet = fastjet::join(constituentJets);
    Jet.set_user_info(jet_info);
    return Jet;
}

fastjet::PseudoJet Hadrons::ConstituentJet(TObject &object, const analysis::JetDetail jet_detail, const analysis::SubDetector sub_detector)
{
    Debug("Constituent", object.ClassName());
    fastjet::PseudoJet jet;
    JetInfo *jet_info = new JetInfo();
    if (object.IsA() == ::delphes::GenParticle::Class()) {
        ::delphes::GenParticle &particle = static_cast<::delphes::GenParticle &>(object);
        TLorentzVector Position(particle.X, particle.Y, particle.Z, particle.T);
        Constituent constituent(particle.P4(), Position, SubDetector::gen_particle, particle.Charge);
        if (jet_detail == JetDetail::tagging_structure) constituent.SetFamily(BranchFamily(object));
        jet = analysis::PseudoJet(particle.P4());
        jet_info->AddConstituent(constituent);
    } else if (object.IsA() == ::delphes::Track::Class()) {
        ::delphes::Track &track = static_cast<::delphes::Track &>(object);
        TLorentzVector Position(track.X, track.Y, track.Z, track.T);
        Constituent constituent(track.P4(), Position, SubDetector::track, track.Charge);
        if (jet_detail == JetDetail::tagging_structure) constituent.SetFamily(BranchFamily(*track.Particle.GetObject()));
        jet = analysis::PseudoJet(track.P4());
        jet_info->AddConstituent(constituent);
    } else if (object.IsA() == ::delphes::Tower::Class()) {
        ::delphes::Tower &tower = static_cast<::delphes::Tower &>(object);
        std::vector<Constituent> constituents;
        constituents.emplace_back(Constituent(tower.P4()));
        if (jet_detail == JetDetail::tagging_structure) constituents = JetId(tower).constituents();
        for (auto & constituent : constituents) constituent.SetDetector(sub_detector);
        jet = analysis::PseudoJet(tower.P4());
        jet_info->AddConstituents(constituents);
    } else if (object.IsA() == ::delphes::Muon::Class()) {
        ::delphes::Muon &muon = static_cast<::delphes::Muon &>(object);
        Constituent constituent(muon.P4(), SubDetector::muon, muon.Charge);
        if (jet_detail == JetDetail::tagging_structure) constituent.SetFamily(BranchFamily(*muon.Particle.GetObject()));
        jet = analysis::PseudoJet(muon.P4());
        jet_info->AddConstituent(constituent);
    } else {
        Error("Unkonw Jet constituent", object.ClassName());
    }
    jet.set_user_info(jet_info);
    return jet;
}

Jets Hadrons::EFlowJets(const JetDetail jet_detail)
{
    analysis::Jets e_flow_jets;
    Debug("EFlow", clones_arrays().EFlowTrackSum(), Name(jet_detail));
    if (FindInVector(clones_arrays().Branches(), Branch::e_flow_track)) e_flow_jets = Join(e_flow_jets, EFlowTrack(jet_detail));
    Debug("Number of EFlow Jet", e_flow_jets.size());
    if (FindInVector(clones_arrays().Branches(), Branch::e_flow_photon)) e_flow_jets = Join(e_flow_jets, EFlowPhoton(jet_detail));
    if (FindInVector(clones_arrays().Branches(), Branch::e_flow_neutral_hadron)) e_flow_jets = Join(e_flow_jets, EFlowHadron(jet_detail));
    if (FindInVector(clones_arrays().Branches(), Branch::e_flow_muon)) e_flow_jets = Join(e_flow_jets, EFlowMuon(jet_detail));
    Debug("Number of EFlow Jet", e_flow_jets.size());
    PrintTruthLevel(Severity::detailed);
    return e_flow_jets;
}

Jets Hadrons::EFlowTrack(const JetDetail jet_detail)
{
    analysis::Jets e_flow_jets;
    Debug("Track EFlow", clones_arrays().EFlowTrackSum());
    for (const int e_flow_track_number : Range(clones_arrays().EFlowTrackSum())) {
        if (jet_detail == JetDetail::tagging_structure || jet_detail == JetDetail::structure) {
            e_flow_jets.emplace_back(ConstituentJet(clones_arrays().EFlowTrack(e_flow_track_number), jet_detail, SubDetector::track));
            continue;
        }
        ::delphes::Track &e_flow_track = static_cast<::delphes::Track &>(clones_arrays().EFlowTrack(e_flow_track_number));
        if (jet_detail == JetDetail::isolation || jet_detail ==  JetDetail::tagging_isolation) {
            bool Isolated = GetIsolation<::delphes::Electron>(e_flow_track, clones_arrays().ElectronClonesArray());
            if (Isolated) Isolated = GetIsolation<::delphes::Muon>(e_flow_track, clones_arrays().MuonClonesArray());
            if (!Isolated) continue;
        }
        e_flow_jets.emplace_back(analysis::PseudoJet(e_flow_track.P4()));
        if (jet_detail == JetDetail::tagging || jet_detail ==  JetDetail::tagging_isolation) {
            Constituent constituent(e_flow_track.P4(), BranchFamily(*e_flow_track.Particle.GetObject()));
            e_flow_jets.back().set_user_info(new JetInfo(constituent));
            Detail("Track EFlow Id", e_flow_jets.back().user_index());
        }
    }
    Debug("Number of EFlow Jet", e_flow_jets.size());
    return e_flow_jets;
}

Jets Hadrons::EFlowPhoton(const JetDetail jet_detail)
{
    Debug("Photon EFlow", clones_arrays().EFlowPhotonSum());
    analysis::Jets e_flow_jets;
    if (clones_arrays().PhotonSum() > 0) Debug("Number of Photons", clones_arrays().PhotonSum());
    for (const int e_flow_photon_number : Range(clones_arrays().EFlowPhotonSum())) {
        if (jet_detail == JetDetail::tagging_structure || jet_detail == JetDetail::structure) {
            e_flow_jets.emplace_back(ConstituentJet(clones_arrays().EFlowPhoton(e_flow_photon_number), jet_detail, SubDetector::photon));
            continue;
        }
        ::delphes::Tower &e_flow_photon = static_cast<::delphes::Tower &>(clones_arrays().EFlowPhoton(e_flow_photon_number));
        if (jet_detail == JetDetail::isolation || jet_detail == JetDetail::tagging_isolation) {
            bool Isolated = GetIsolation<::delphes::Photon>(e_flow_photon, clones_arrays().PhotonClonesArray());
            if (!Isolated) continue;
        }
        e_flow_jets.emplace_back(analysis::PseudoJet(e_flow_photon.P4()));
        if (jet_detail == JetDetail::tagging || jet_detail ==  JetDetail::tagging_isolation) {
            e_flow_jets.back().set_user_info(new JetInfo(JetId(e_flow_photon)));
            Detail("Photon EFlow Id", e_flow_jets.back().user_index());
        }
    }
    return e_flow_jets;
}

Jets Hadrons::EFlowHadron(const JetDetail jet_detail)
{
    Debug("Hadron EFlow", clones_arrays().EFlowNeutralHadronSum());
    analysis::Jets e_flow_jets;
    for (const int HadronNumber : Range(clones_arrays().EFlowNeutralHadronSum())) {
        if (jet_detail == JetDetail::tagging_structure || jet_detail == JetDetail::structure) {
            e_flow_jets.emplace_back(ConstituentJet(clones_arrays().EFlowNeutralHadron(HadronNumber), jet_detail, SubDetector::tower));
            continue;
        }
        ::delphes::Tower &e_flow_hadron = static_cast<::delphes::Tower &>(clones_arrays().EFlowNeutralHadron(HadronNumber));
        e_flow_jets.emplace_back(analysis::PseudoJet(e_flow_hadron.P4()));
        if (jet_detail == JetDetail::tagging || jet_detail ==  JetDetail::tagging_isolation) {
            e_flow_jets.back().set_user_info(new JetInfo(JetId(e_flow_hadron)));
            Detail("Hadron EFlow Id", e_flow_jets.back().user_index());
        }
    }
    return e_flow_jets;
}

Jets Hadrons::EFlowMuon(const JetDetail jet_detail)
{
    Debug("Muon EFlow", clones_arrays().EFlowMuonSum());
    analysis::Jets e_flow_jets;
    for (const int muon_number : Range(clones_arrays().EFlowMuonSum())) {
        if (jet_detail == JetDetail::tagging_structure || jet_detail == JetDetail::structure) {
//             if (!clones_arrays().GetEFlowMuon(muon_number)) continue;
            e_flow_jets.emplace_back(ConstituentJet(clones_arrays().EFlowMuon(muon_number), jet_detail, SubDetector::muon));
            continue;
        }
        ::delphes::Muon &e_flow_muon = static_cast<::delphes::Muon &>(clones_arrays().EFlowMuon(muon_number));
        if (jet_detail == JetDetail::isolation || jet_detail ==  JetDetail::tagging_isolation) {
            bool Isolated = GetIsolation<::delphes::Muon>(e_flow_muon, clones_arrays().MuonClonesArray());
            if (!Isolated) continue;
        }
        e_flow_jets.emplace_back(analysis::PseudoJet(e_flow_muon.P4()));
        if (jet_detail == JetDetail::tagging || jet_detail ==  JetDetail::tagging_isolation) {
            Constituent constituent(e_flow_muon.P4(), BranchFamily(*e_flow_muon.Particle.GetObject()));
            e_flow_jets.back().set_user_info(new JetInfo(constituent));
            Detail("Muon EFlow Id", e_flow_jets.back().user_index());
        }
    }
    return e_flow_jets;
}

Jets Hadrons::GenJets()
{
    Info("GenJet", clones_arrays().GenJetSum());
    analysis::Jets gen_jets;
    for (const int GenJetNumber : Range(clones_arrays().GenJetSum())) gen_jets.emplace_back(analysis::PseudoJet(static_cast<::delphes::Jet &>(clones_arrays().GenJet(GenJetNumber)).P4()));
    return gen_jets;
}

float Hadrons::ScalarHt()
{
    Info("ScalerHt");
    return static_cast<::delphes::ScalarHT &>(clones_arrays().ScalarHt()).HT;
}

fastjet::PseudoJet Hadrons::MissingEt()
{
    Info("Missing ET");
    return analysis::PseudoJet(static_cast<::delphes::MissingET &>(clones_arrays().MissingEt()).P4());
}

Jets Hadrons::GranulatedJets(const analysis::Jets &e_flow_jets)
{
    if (e_flow_jets.empty()) return e_flow_jets;
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
    fastjet::ClusterSequence &cluster_sequence = *new fastjet::ClusterSequence(GranulatedJets(EFlowJets(JetDetail::structure)), detector_geometry.JetDefinition);
    analysis::Jets jets = fastjet::sorted_by_pt(cluster_sequence.inclusive_jets(detector_geometry.JetMinPt));
    if (jets.empty()) {
        delete &cluster_sequence;
        return jets;
    }
    cluster_sequence.delete_self_when_unused();
    for (auto & jet : jets)  {
        std::vector<Constituent> constituents;
        for (const auto & constituent : jet.constituents()) {
            std::vector<Constituent> jet_constituents = constituent.user_info<JetInfo>().constituents();
            constituents = Join(constituents, jet_constituents);
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
