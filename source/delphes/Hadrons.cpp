#include "delphes/Hadrons.hh"

#include "fastjet/ClusterSequence.hh"

#include "delphes/Delphes.hh"
#include "JetInfo.hh"
#include "InfoRecombiner.hh"
#include "Vector.hh"
#include "Debug.hh"

namespace analysis
{

namespace delphes
{

Jets Hadrons::DelphesJets(JetDetail jet_detail) const
{
    Debug(clones_arrays().JetSum(), Name(jet_detail));
    if (jet_detail == JetDetail::tagging) jet_detail |= JetDetail::plain;
    std::vector<TObject*> leptons;
    if (is(jet_detail, JetDetail::isolation)) {
        for (const auto & electron_number : Range(clones_arrays().ElectronSum())) leptons.emplace_back(static_cast<::delphes::Electron&>(clones_arrays().Electron(electron_number)).Particle.GetObject());
        for (const auto & muon_number : Range(clones_arrays().MuonSum())) leptons.emplace_back(static_cast<::delphes::Muon&>(clones_arrays().Muon(muon_number)).Particle.GetObject());
    }
    analysis::Jets jets;
    for (const auto & jet_number : Range(clones_arrays().JetSum())) {
        Detail(jet_number);
        ::delphes::Jet& delphes_jet = static_cast<::delphes::Jet&>(clones_arrays().Jet(jet_number));
        FlagSwitch(jet_detail, [&](JetDetail jet_detail_in) {
            switch (jet_detail_in) {
            case JetDetail::plain: {
                fastjet::PseudoJet Jet = analysis::PseudoJet(delphes_jet.P4());
                Jet.set_user_info(new JetInfo(delphes_jet));
                jets.emplace_back(Jet);
            }
            break;
            case JetDetail::structure:
              try{
                jets.emplace_back(StructuredJet(delphes_jet, leptons, jet_detail));
              }catch(char const*){};
                break;
            case JetDetail::tagging:
                static_cast<JetInfo&>(*jets.back().user_info_shared_ptr().get()).SetConstituents(JetId(delphes_jet));
                break;
            case JetDetail::isolation:
                break;
            default:
                break;
            }
        });
    }    
    return jets;
}

fastjet::PseudoJet Hadrons::StructuredJet(const ::delphes::Jet& delphes_jet, const std::vector<TObject*> leptons, JetDetail jet_detail) const
{
    Info();
    analysis::Jets constituents;
    for (const auto & constituent_number : Range(delphes_jet.Constituents.GetEntriesFast())) {
        if (!delphes_jet.Constituents.At(constituent_number)) continue;
        try {
            fastjet::PseudoJet constituent = ConstituentJet(*delphes_jet.Constituents.At(constituent_number), jet_detail, SubDetector::none, leptons);
            constituents.emplace_back(constituent);
        } catch (const char*) {
            continue;
        }
    }
    if(constituents.empty()) throw "empty jet";
    Debug(constituents.size());
    fastjet::PseudoJet jet = fastjet::join(constituents, InfoRecombiner());
    static_cast<JetInfo&>(*jet.user_info_shared_ptr().get()).SetDelphesTags(delphes_jet);
    return jet;
}

fastjet::PseudoJet Hadrons::ConstituentJet(TObject& object, analysis::JetDetail jet_detail, const analysis::SubDetector sub_detector, const std::vector< TObject* > leptons) const
{
    Debug(object.ClassName(),Name(jet_detail));
    fastjet::PseudoJet jet;
    auto jet_info = new JetInfo();
    if (object.IsA() == ::delphes::GenParticle::Class()) {
        if (is(jet_detail, JetDetail::isolation) && !Isolated(object, leptons)) throw "not isolated";
        ::delphes::GenParticle& particle = static_cast<::delphes::GenParticle&>(object);
        analysis::LorentzVector position(particle.X, particle.Y, particle.Z, particle.T);
        Constituent constituent(particle.P4(), position, SubDetector::gen_particle, particle.Charge);
        if (is(jet_detail, JetDetail::tagging)) constituent.SetFamily(BranchFamily(object));
        jet = analysis::PseudoJet(particle.P4());
        jet_info->AddConstituent(constituent);
    } else if (object.IsA() == ::delphes::Track::Class()) {
        ::delphes::Track& track = static_cast<::delphes::Track&>(object);
        if (is(jet_detail, JetDetail::isolation) && !Isolated(*track.Particle.GetObject(), leptons)) throw "not isolated";
        analysis::LorentzVector position(track.X, track.Y, track.Z, track.T);
        Constituent constituent(track.P4(), position, SubDetector::track, track.Charge);
        if (is(jet_detail, JetDetail::tagging)) constituent.SetFamily(BranchFamily(*track.Particle.GetObject()));
        jet = analysis::PseudoJet(track.P4());
        jet_info->AddConstituent(constituent);
    } else if (object.IsA() == ::delphes::Tower::Class()) {
        ::delphes::Tower& tower = static_cast<::delphes::Tower&>(object);
        if (is(jet_detail, JetDetail::isolation)) for (const auto & particle_number : Range(tower.Particles.GetEntriesFast())) if (!Isolated(*tower.Particles.At(particle_number), leptons)) throw "not isolated";
        if (is(jet_detail, JetDetail::tagging)) {
            std::vector<Constituent> constituents;
            constituents.emplace_back(Constituent(tower.P4()));
            constituents = JetId(tower);
            for (auto & constituent : constituents) constituent.SetDetector(sub_detector);
            jet_info->AddConstituents(constituents);
        } else {
            Constituent constituent(tower.P4(), sub_detector);
            jet_info->AddConstituent(constituent);
        }
        jet = analysis::PseudoJet(tower.P4());
    } else if (object.IsA() == ::delphes::Muon::Class()) {
        ::delphes::Muon& muon = static_cast<::delphes::Muon&>(object);
        if (is(jet_detail, JetDetail::isolation) && !Isolated(*muon.Particle.GetObject(), leptons)) throw "not isolated";
        Constituent constituent(muon.P4(), SubDetector::muon, muon.Charge);
        if (is(jet_detail, JetDetail::tagging)) constituent.SetFamily(BranchFamily(*muon.Particle.GetObject()));
        jet = analysis::PseudoJet(muon.P4());
        jet_info->AddConstituent(constituent);
    } else Error("Unkonw Jet constituent", object.ClassName());
    jet.set_user_info(jet_info);
    return jet;
}

bool Hadrons::Isolated(const TObject& object, const std::vector<TObject*> leptons) const
{
    bool isolated = true;
    for (const auto & lepton : leptons) if (&object == lepton) isolated = false;
//     Check(isolated, isolated);
    return isolated;
}


// Jets Hadrons::UniqueJets() const
// {
//     Info();
//     analysis::Jets jets;
//     std::vector<TObject*> leptons;
//     for (const auto & electron_number : Range(clones_arrays().ElectronSum())) leptons.emplace_back(static_cast<::delphes::Electron&>(clones_arrays().Electron(electron_number)).Particle.GetObject());
//     for (const auto & muon_number : Range(clones_arrays().MuonSum())) leptons.emplace_back(static_cast<::delphes::Muon&>(clones_arrays().Muon(muon_number)).Particle.GetObject());
//     for (const auto & jet_number : Range(clones_arrays().JetSum())) {
//         analysis::Jets constituents;
//         ::delphes::Jet& jet = static_cast<::delphes::Jet&>(clones_arrays().Jet(jet_number));
//         for (const auto & constituent_number : Range(jet.Constituents.GetEntriesFast())) constituents = Join(constituents, UniqueConstituents(*jet.Constituents.At(constituent_number), leptons));
//         jets.emplace_back(fastjet::join(constituents, InfoRecombiner()));
//     }
//     return jets;
// }
//
// analysis::Jets Hadrons::UniqueConstituents(TObject& object, const std::vector<TObject*> leptons) const
// {
//     analysis::Jets constituents;
//     if (object.IsA() == ::delphes::GenParticle::Class()) {
//         ::delphes::GenParticle& particle = static_cast<::delphes::GenParticle&>(object);
//         constituents = Constituents(object, particle.P4(), leptons);
//     } else if (object.IsA() == ::delphes::Track::Class()) {
//         ::delphes::Track& track = static_cast<::delphes::Track&>(object);
//         constituents = Constituents(*track.Particle.GetObject(), track.P4(), leptons);
//     } else if (object.IsA() == ::delphes::Tower::Class()) {
//         ::delphes::Tower& tower = static_cast<::delphes::Tower&>(object);
//         for (const auto & particle_number : Range(tower.Particles.GetEntriesFast())) constituents = UniqueConstituents(*tower.Particles.At(particle_number), leptons);
//     } else if (object.IsA() == ::delphes::Muon::Class()) {
//         ::delphes::Muon& muon = static_cast<::delphes::Muon&>(object);
//         constituents = Constituents(*muon.Particle.GetObject(), muon.P4(), leptons);
//     } else Error("Unkonw Jet constituent", object.ClassName());
//     return constituents;
// }
//
// analysis::Jets Hadrons::Constituents(const TObject& object, const TLorentzVector lorentz_vector, const std::vector<TObject*> leptons) const
// {
//     analysis::Jets constituents;
//     for (const auto & lepton : leptons) if (&object != lepton) constituents.emplace_back(analysis::PseudoJet(lorentz_vector));
//     return constituents;
// }

Jets Hadrons::EFlowJets(JetDetail jet_detail) const
{
    fastjet::ClusterSequence& cluster_sequence = *new fastjet::ClusterSequence(EFlow(jet_detail), DetectorGeometry::JetDefinition());
    analysis::Jets jets = fastjet::sorted_by_pt(cluster_sequence.inclusive_jets(DetectorGeometry::JetMinPt()));
    if (jets.empty()) {
        delete &cluster_sequence;
        return jets;
    }
    cluster_sequence.delete_self_when_unused();
    return jets;
}

Jets Hadrons::EFlow(JetDetail jet_detail) const
{
    analysis::Jets e_flow_jets;
    Debug(clones_arrays().EFlowTrackSum(), Name(jet_detail));
    if (FindInVector(clones_arrays().Branches(), Branch::e_flow_track)) e_flow_jets = Join(e_flow_jets, EFlowTrack(jet_detail));
    Debug(e_flow_jets.size());
    if (FindInVector(clones_arrays().Branches(), Branch::e_flow_photon)) e_flow_jets = Join(e_flow_jets, EFlowPhoton(jet_detail));
    if (FindInVector(clones_arrays().Branches(), Branch::e_flow_neutral_hadron)) e_flow_jets = Join(e_flow_jets, EFlowHadron(jet_detail));
    if (FindInVector(clones_arrays().Branches(), Branch::e_flow_muon)) e_flow_jets = Join(e_flow_jets, EFlowMuon(jet_detail));
    Debug(e_flow_jets.size());
//     PrintTruthLevel(Severity::detailed);
    return e_flow_jets;
}

Jets Hadrons::EFlowTrack(JetDetail jet_detail) const
{
    analysis::Jets e_flow_jets;
    Debug(clones_arrays().EFlowTrackSum());
    for (const auto & e_flow_track_number : Range(clones_arrays().EFlowTrackSum())) {
        if (is(jet_detail, JetDetail::structure)) {
            try {
                e_flow_jets.emplace_back(ConstituentJet(clones_arrays().EFlowTrack(e_flow_track_number), jet_detail, SubDetector::track));
            } catch (const char*) {
                continue;
            }
            continue;
        }
        ::delphes::Track& e_flow_track = static_cast<::delphes::Track&>(clones_arrays().EFlowTrack(e_flow_track_number));
        if (is(jet_detail, JetDetail::isolation)) {
            bool Isolated = Isolation<::delphes::Electron>(e_flow_track, Branch::electron);
            if (Isolated) Isolated = Isolation<::delphes::Muon>(e_flow_track, Branch::muon);
            if (!Isolated) continue;
        }
        e_flow_jets.emplace_back(analysis::PseudoJet(e_flow_track.P4()));
        if (is(jet_detail, JetDetail::tagging)) {
            Constituent constituent(e_flow_track.P4(), BranchFamily(*e_flow_track.Particle.GetObject()));
            e_flow_jets.back().set_user_info(new JetInfo(constituent));
            Detail(e_flow_jets.back().user_index());
        }
    }
    Debug(e_flow_jets.size());
    return e_flow_jets;
}

Jets Hadrons::EFlowPhoton(JetDetail jet_detail) const
{
    Debug(clones_arrays().EFlowPhotonSum());
    analysis::Jets e_flow_jets;
    if (clones_arrays().PhotonSum() > 0)
        Debug("Number of Photons", clones_arrays().PhotonSum());
    for (const auto & e_flow_photon_number : Range(clones_arrays().EFlowPhotonSum())) {
        if (is(jet_detail, JetDetail::structure)) {
            try {
                e_flow_jets.emplace_back(ConstituentJet(clones_arrays().EFlowPhoton(e_flow_photon_number), jet_detail, SubDetector::photon));
            } catch (const char*) {
                continue;
            }
            continue;
        }
        ::delphes::Tower& e_flow_photon = static_cast<::delphes::Tower&>(clones_arrays().EFlowPhoton(e_flow_photon_number));
        if (is(jet_detail, JetDetail::isolation)) if (!Isolation<::delphes::Photon>(e_flow_photon, Branch::photon)) continue;
        e_flow_jets.emplace_back(analysis::PseudoJet(e_flow_photon.P4()));
        if (is(jet_detail, JetDetail::tagging)) {
            e_flow_jets.back().set_user_info(new JetInfo(JetId(e_flow_photon)));
            Detail(e_flow_jets.back().user_index());
        }
    }
    return e_flow_jets;
}

Jets Hadrons::EFlowHadron(JetDetail jet_detail) const
{
    Debug(clones_arrays().EFlowNeutralHadronSum());
    analysis::Jets e_flow_jets;
    for (const auto & hadron_number : Range(clones_arrays().EFlowNeutralHadronSum())) {
        if (is(jet_detail, JetDetail::structure)) {
            try {
                e_flow_jets.emplace_back(ConstituentJet(clones_arrays().EFlowNeutralHadron(hadron_number), jet_detail, SubDetector::tower));
            } catch (const char*) {
                continue;
            }
            continue;
        }
        ::delphes::Tower& e_flow_hadron = static_cast<::delphes::Tower&>(clones_arrays().EFlowNeutralHadron(hadron_number));
        e_flow_jets.emplace_back(analysis::PseudoJet(e_flow_hadron.P4()));
        if (is(jet_detail, JetDetail::tagging)) {
            e_flow_jets.back().set_user_info(new JetInfo(JetId(e_flow_hadron)));
            Detail(e_flow_jets.back().user_index());
        }
    }
    return e_flow_jets;
}

Jets Hadrons::EFlowMuon(JetDetail jet_detail) const
{
    Debug(clones_arrays().EFlowMuonSum());
    analysis::Jets e_flow_jets;
    for (const auto & muon_number : Range(clones_arrays().EFlowMuonSum())) {
        if (is(jet_detail, JetDetail::structure)) {
            //             if (!clones_arrays().GetEFlowMuon(muon_number)) continue;
            try {
                e_flow_jets.emplace_back(ConstituentJet(clones_arrays().EFlowMuon(muon_number), jet_detail, SubDetector::muon));
            } catch (const char*) {
                continue;
            }
            continue;
        }
        ::delphes::Muon& e_flow_muon = static_cast<::delphes::Muon&>(clones_arrays().EFlowMuon(muon_number));
        if (is(jet_detail, JetDetail::isolation)) if (!Isolation<::delphes::Muon>(e_flow_muon, Branch::muon)) continue;
        e_flow_jets.emplace_back(analysis::PseudoJet(e_flow_muon.P4()));
        if (is(jet_detail, JetDetail::tagging)) {
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
    for (const auto & jet_number : Range(clones_arrays().GenJetSum()))
        gen_jets.emplace_back(analysis::PseudoJet(static_cast<::delphes::Jet&>(clones_arrays().GenJet(jet_number)).P4()));
    return gen_jets;
}

float Hadrons::ScalarHt() const
{
    Info();
    return static_cast<::delphes::ScalarHT&>(clones_arrays().ScalarHt()).HT;
}

fastjet::PseudoJet Hadrons::MissingEt() const
{
    Info();
    return analysis::PseudoJet(static_cast<::delphes::MissingET&>(clones_arrays().MissingEt()).P4());
}

}

}
