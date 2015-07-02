#include "fastjet/ClusterSequence.hh"

#include "delphes/Hadrons.hh"
#include "Predicate.hh"
#include "Debug.hh"

namespace analysis
{

namespace delphes
{

Jets Hadrons::DelphesJets(const JetDetail jet_detail) const
{
    Info(clones_arrays().JetSum());
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
            Error("unhandeled case");
        }
    }
//     PrintTruthLevel(Severity::debug);
    return jets;
}

fastjet::PseudoJet Hadrons::StructuredJet(const ::delphes::Jet &jet, const JetDetail jet_detail) const
{
    Info();
    analysis::Jets constituent_jets;
    std::vector<Constituent> constituents;
    JetInfo *jet_info = new JetInfo(bool(jet.BTag), jet.Charge);
    for (const int constituentNumber : Range(jet.Constituents.GetEntriesFast())) {
        if (!jet.Constituents.At(constituentNumber)) continue;
        fastjet::PseudoJet constituent = ConstituentJet(*jet.Constituents.At(constituentNumber), jet_detail);
        jet_info->AddConstituents(constituent.user_info<JetInfo>().constituents());
        constituent_jets.emplace_back(constituent);
    }
    fastjet::PseudoJet Jet = fastjet::join(constituent_jets);
    Jet.set_user_info(jet_info);
    return Jet;
}

fastjet::PseudoJet Hadrons::ConstituentJet(TObject &object, const analysis::JetDetail jet_detail, const analysis::SubDetector sub_detector) const
{
    Debug(object.ClassName());
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

Jets Hadrons::EFlowJets(const JetDetail jet_detail) const
{
    analysis::Jets e_flow_jets;
    Debug(clones_arrays().EFlowTrackSum(), Name(jet_detail));
    if (FindInVector(clones_arrays().Branches(), Branch::e_flow_track)) e_flow_jets = Join(e_flow_jets, EFlowTrack(jet_detail));
    Debug("Number of EFlow Jet", e_flow_jets.size());
    if (FindInVector(clones_arrays().Branches(), Branch::e_flow_photon)) e_flow_jets = Join(e_flow_jets, EFlowPhoton(jet_detail));
    if (FindInVector(clones_arrays().Branches(), Branch::e_flow_neutral_hadron)) e_flow_jets = Join(e_flow_jets, EFlowHadron(jet_detail));
    if (FindInVector(clones_arrays().Branches(), Branch::e_flow_muon)) e_flow_jets = Join(e_flow_jets, EFlowMuon(jet_detail));
    Debug("Number of EFlow Jet", e_flow_jets.size());
//     PrintTruthLevel(Severity::detailed);
    return e_flow_jets;
}

Jets Hadrons::EFlowTrack(const JetDetail jet_detail) const
{
    analysis::Jets e_flow_jets;
    Debug(clones_arrays().EFlowTrackSum());
    for (const int e_flow_track_number : Range(clones_arrays().EFlowTrackSum())) {
        if (jet_detail == JetDetail::tagging_structure || jet_detail == JetDetail::structure) {
            e_flow_jets.emplace_back(ConstituentJet(clones_arrays().EFlowTrack(e_flow_track_number), jet_detail, SubDetector::track));
            continue;
        }
        ::delphes::Track &e_flow_track = static_cast<::delphes::Track &>(clones_arrays().EFlowTrack(e_flow_track_number));
        if (jet_detail == JetDetail::isolation || jet_detail ==  JetDetail::tagging_isolation) {
            bool Isolated = Isolation<::delphes::Electron>(e_flow_track, clones_arrays().ElectronClonesArray());
            if (Isolated) Isolated = Isolation<::delphes::Muon>(e_flow_track, clones_arrays().MuonClonesArray());
            if (!Isolated) continue;
        }
        e_flow_jets.emplace_back(analysis::PseudoJet(e_flow_track.P4()));
        if (jet_detail == JetDetail::tagging || jet_detail ==  JetDetail::tagging_isolation) {
            Constituent constituent(e_flow_track.P4(), BranchFamily(*e_flow_track.Particle.GetObject()));
            e_flow_jets.back().set_user_info(new JetInfo(constituent));
            Detail(e_flow_jets.back().user_index());
        }
    }
    Debug(e_flow_jets.size());
    return e_flow_jets;
}

Jets Hadrons::EFlowPhoton(const JetDetail jet_detail) const
{
    Debug(clones_arrays().EFlowPhotonSum());
    analysis::Jets e_flow_jets;
    if (clones_arrays().PhotonSum() > 0) Debug("Number of Photons", clones_arrays().PhotonSum());
    for (const int e_flow_photon_number : Range(clones_arrays().EFlowPhotonSum())) {
        if (jet_detail == JetDetail::tagging_structure || jet_detail == JetDetail::structure) {
            e_flow_jets.emplace_back(ConstituentJet(clones_arrays().EFlowPhoton(e_flow_photon_number), jet_detail, SubDetector::photon));
            continue;
        }
        ::delphes::Tower &e_flow_photon = static_cast<::delphes::Tower &>(clones_arrays().EFlowPhoton(e_flow_photon_number));
        if (jet_detail == JetDetail::isolation || jet_detail == JetDetail::tagging_isolation) if (!Isolation<::delphes::Photon>(e_flow_photon, clones_arrays().PhotonClonesArray())) continue;
        e_flow_jets.emplace_back(analysis::PseudoJet(e_flow_photon.P4()));
        if (jet_detail == JetDetail::tagging || jet_detail ==  JetDetail::tagging_isolation) {
            e_flow_jets.back().set_user_info(new JetInfo(JetId(e_flow_photon)));
            Detail(e_flow_jets.back().user_index());
        }
    }
    return e_flow_jets;
}

Jets Hadrons::EFlowHadron(const JetDetail jet_detail) const
{
    Debug(clones_arrays().EFlowNeutralHadronSum());
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
            Detail(e_flow_jets.back().user_index());
        }
    }
    return e_flow_jets;
}

Jets Hadrons::EFlowMuon(const JetDetail jet_detail) const
{
    Debug(clones_arrays().EFlowMuonSum());
    analysis::Jets e_flow_jets;
    for (const int muon_number : Range(clones_arrays().EFlowMuonSum())) {
        if (jet_detail == JetDetail::tagging_structure || jet_detail == JetDetail::structure) {
//             if (!clones_arrays().GetEFlowMuon(muon_number)) continue;
            e_flow_jets.emplace_back(ConstituentJet(clones_arrays().EFlowMuon(muon_number), jet_detail, SubDetector::muon));
            continue;
        }
        ::delphes::Muon &e_flow_muon = static_cast<::delphes::Muon &>(clones_arrays().EFlowMuon(muon_number));
        if (jet_detail == JetDetail::isolation || jet_detail ==  JetDetail::tagging_isolation) if (!Isolation<::delphes::Muon>(e_flow_muon, clones_arrays().MuonClonesArray())) continue;
        e_flow_jets.emplace_back(analysis::PseudoJet(e_flow_muon.P4()));
        if (jet_detail == JetDetail::tagging || jet_detail ==  JetDetail::tagging_isolation) {
            Constituent constituent(e_flow_muon.P4(), BranchFamily(*e_flow_muon.Particle.GetObject()));
            e_flow_jets.back().set_user_info(new JetInfo(constituent));
            Detail(e_flow_jets.back().user_index());
        }
    }
    return e_flow_jets;
}

Jets Hadrons::GenJets() const
{
    Info(clones_arrays().GenJetSum());
    analysis::Jets gen_jets;
    for (const int GenJetNumber : Range(clones_arrays().GenJetSum())) gen_jets.emplace_back(analysis::PseudoJet(static_cast<::delphes::Jet &>(clones_arrays().GenJet(GenJetNumber)).P4()));
    return gen_jets;
}

float Hadrons::ScalarHt() const
{
    Info();
    return static_cast<::delphes::ScalarHT &>(clones_arrays().ScalarHt()).HT;
}

fastjet::PseudoJet Hadrons::MissingEt() const
{
    Info();
    return analysis::PseudoJet(static_cast<::delphes::MissingET &>(clones_arrays().MissingEt()).P4());
}

Jets Hadrons::GranulatedJets(const analysis::Jets &e_flow_jets) const
{
  if (e_flow_jets.empty()) return e_flow_jets;
    // start of granularization of the hadronic calorimeter to redefine hadrons
    analysis::Jets sorted_jets = sorted_by_pt(e_flow_jets);
    analysis::Jets jets;
    jets.emplace_back(sorted_jets.front());
    for (const auto & e_flow_jet : sorted_jets) {
        bool is_new_jet = false;
        for (std::size_t j = 0; j < jets.size(); ++j) {
            const float cell_diff_rap = std::abs(e_flow_jet.pseudorapidity() - jets[j].pseudorapidity()) / DetectorGeometry().MinCellResolution;
            float cell_diff_phi = std::abs(e_flow_jet.phi() - jets[j].phi());
            if (cell_diff_phi > M_PI) cell_diff_phi = 2 * M_PI - cell_diff_phi;
            cell_diff_phi /= DetectorGeometry().MinCellResolution;
            if (cell_diff_rap < 1 && cell_diff_phi < 1) {
                is_new_jet = true;
                const float total_energy  = e_flow_jet.e() + jets[j].e();
                const float rescale_factor = std::sqrt(std::pow(e_flow_jet.px() + jets[j].px(), 2) + std::pow(e_flow_jet.py() + jets[j].py(), 2) + pow(e_flow_jet.pz() + jets[j].pz(), 2));
                const float rescaled_px = total_energy * (e_flow_jet.px() + jets[j].px()) / rescale_factor;
                const float rescaled_py = total_energy * (e_flow_jet.py() + jets[j].py()) / rescale_factor;
                const float rescaled_pz = total_energy * (e_flow_jet.pz() + jets[j].pz()) / rescale_factor;
                fastjet::PseudoJet combined_jet(rescaled_px, rescaled_py, rescaled_pz, total_energy);
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
    jets = RemoveIfSoft(jets, DetectorGeometry().MinCellPt);
    return jets;
}

Jets Hadrons::ClusteredJets() const
{
    DetectorGeometry detector_geometry;
//     fastjet::ClusterSequence &cluster_sequence = *new fastjet::ClusterSequence(GranulatedJets(EFlowJets(JetDetail::structure)), detector_geometry.JetDefinition);
    fastjet::ClusterSequence &cluster_sequence = *new fastjet::ClusterSequence(EFlowJets(JetDetail::structure), detector_geometry.JetDefinition);
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

Jets Hadrons::UniqueJets() const
{
    Info();
    analysis::Jets jets;

    std::vector<TObject *> leptons;
    for (const int electron_number : Range(clones_arrays().ElectronSum())) leptons.emplace_back(static_cast<::delphes::Electron &>(clones_arrays().Electron(electron_number)).Particle.GetObject());
    for (const int muon_number : Range(clones_arrays().MuonSum())) leptons.emplace_back(static_cast<::delphes::Muon &>(clones_arrays().Muon(muon_number)).Particle.GetObject());
    for (const int jet_number : Range(clones_arrays().JetSum())) {
        analysis::Jets constituents;
        ::delphes::Jet &jet = static_cast<::delphes::Jet &>(clones_arrays().Jet(jet_number));
        for (const int constituent_number : Range(jet.Constituents.GetEntriesFast())) constituents = Join(constituents, UniqueConstituents(*jet.Constituents.At(constituent_number), leptons));
        jets.emplace_back(fastjet::join(constituents));
    }
    return jets;
}

analysis::Jets Hadrons::UniqueConstituents(TObject &object, std::vector<TObject *> leptons) const
{
    analysis::Jets constituents;
    if (object.IsA() == ::delphes::GenParticle::Class()) {
        ::delphes::GenParticle &particle = static_cast<::delphes::GenParticle &>(object);
        for (auto & lepton : leptons) if (&object != lepton) constituents.emplace_back(analysis::PseudoJet(particle.P4()));
    } else if (object.IsA() == ::delphes::Track::Class()) {
        ::delphes::Track &track = static_cast<::delphes::Track &>(object);
        for (auto & lepton : leptons) if (track.Particle.GetObject() != lepton) constituents.emplace_back(analysis::PseudoJet(track.P4()));
    } else if (object.IsA() == ::delphes::Tower::Class()) {
        ::delphes::Tower &tower = static_cast<::delphes::Tower &>(object);
        for (const int particle_number : Range(tower.Particles.GetEntriesFast())) constituents = Join(constituents, UniqueConstituents(*tower.Particles.At(particle_number), leptons));
    } else if (object.IsA() == ::delphes::Muon::Class()) {
        ::delphes::Muon &muon = static_cast<::delphes::Muon &>(object);
        for (auto & lepton : leptons) if (muon.Particle.GetObject() != lepton) constituents.emplace_back(analysis::PseudoJet(muon.P4()));
    } else {
        Error("Unkonw Jet constituent", object.ClassName());
    }
    return constituents;
}




}

}
