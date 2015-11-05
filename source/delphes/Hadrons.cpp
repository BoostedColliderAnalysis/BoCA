/**
 * Copyright (C) 2015 Jan Hajer
 */

#include "fastjet/ClusterSequence.hh"

#include "delphes/Delphes.hh"
#include "delphes/Hadrons.hh"

#include "JetInfo.hh"
#include "InfoRecombiner.hh"
#include "Vector.hh"
#include "Exception.hh"
#include "Debug.hh"

namespace boca
{

namespace delphes
{

Jets Hadrons::Jets() const
{
    switch (DetectorGeometry::jet_type()) {
    case JetType::jet : return DelphesJets(JetDetail::structure | JetDetail::isolation);
    case JetType::gen_jet : return GenJets();
    case JetType::e_flow_jet : return EFlowJets(JetDetail::structure | JetDetail::isolation);
        Default("jet type", {});
    }
}

Jets Hadrons::DelphesJets(JetDetail jet_detail) const
{
    if (jet_detail == JetDetail::tagging) jet_detail |= JetDetail::plain;
    std::vector<TObject*> leptons;
    if (is(jet_detail, JetDetail::isolation)) {
        for (auto const & electron : tree_reader().Objects<::delphes::Electron>(Branch::electron)) leptons.emplace_back(electron.Particle.GetObject());
        for (auto const & muon : tree_reader().Objects<::delphes::Muon>(Branch::muon)) leptons.emplace_back(muon.Particle.GetObject());
    }
    boca::Jets jets;
    for (auto const & delphes_jet : tree_reader().Objects<::delphes::Jet>(Branch::jet)) {
        FlagSwitch(jet_detail, [&](JetDetail jet_detail_int) {
            switch (jet_detail_int) {
            case JetDetail::plain: {
                fastjet::PseudoJet Jet = boca::PseudoJet(delphes_jet.P4());
                Jet.set_user_info(new JetInfo(delphes_jet));
                jets.emplace_back(Jet);
            }
            break;
            case JetDetail::structure :
                try {
                    jets.emplace_back(StructuredJet(delphes_jet, leptons, jet_detail));
                } catch (std::exception const&) {}
                break;
            case JetDetail::tagging :
                static_cast<JetInfo&>(*jets.back().user_info_shared_ptr().get()).SetConstituents(JetId(delphes_jet));
                break;
            case JetDetail::isolation : break;
            default : break;
            }
        });
    }
    return jets;
}

fastjet::PseudoJet Hadrons::StructuredJet(::delphes::Jet const& delphes_jet, std::vector<TObject*> const& leptons, JetDetail jet_detail) const
{
    Info0;
    boca::Jets constituents;
    for (auto const & constituent_number : Range(delphes_jet.Constituents.GetEntriesFast())) {
        if (!delphes_jet.Constituents.At(constituent_number)) continue;
        try {
            constituents.emplace_back(ConstituentJet(*delphes_jet.Constituents.At(constituent_number), jet_detail, SubDetector::none, leptons));
        } catch (std::exception const&) {}
    }
    if (constituents.empty()) throw Empty();
    fastjet::PseudoJet jet = fastjet::join(constituents, InfoRecombiner());
    static_cast<JetInfo&>(*jet.user_info_shared_ptr().get()).SetDelphesTags(delphes_jet);
    return jet;
}

fastjet::PseudoJet Hadrons::ConstituentJet(TObject& object, boca::JetDetail jet_detail, const boca::SubDetector sub_detector, const std::vector< TObject* > leptons) const
{
    Info(object.ClassName(), Name(jet_detail));
    fastjet::PseudoJet jet;
    auto jet_info = new JetInfo();
    if (object.IsA() == ::delphes::GenParticle::Class()) {
        if (is(jet_detail, JetDetail::isolation) && !Isolated(object, leptons)) throw boca::Isolation();
        ::delphes::GenParticle& particle = static_cast<::delphes::GenParticle&>(object);
        boca::LorentzVector position(particle.X, particle.Y, particle.Z, particle.T);
        Constituent constituent(particle.P4(), position, SubDetector::gen_particle, particle.Charge);
//         if (is(jet_detail, JetDetail::tagging)) constituent.SetFamily(BranchFamily(object));
        jet = boca::PseudoJet(particle.P4());
        jet_info->AddConstituent(constituent);
    } else if (object.IsA() == ::delphes::Track::Class()) {
        ::delphes::Track& track = static_cast<::delphes::Track&>(object);
        if (is(jet_detail, JetDetail::isolation) && !Isolated(*track.Particle.GetObject(), leptons)) throw boca::Isolation();
        boca::LorentzVector position(track.X, track.Y, track.Z, track.T);
        Constituent constituent(track.P4(), position, SubDetector::track, track.Charge);
//         if (is(jet_detail, JetDetail::tagging)) constituent.SetFamily(BranchFamily(*track.Particle.GetObject()));
        jet = boca::PseudoJet(track.P4());
        jet_info->AddConstituent(constituent);
    } else if (object.IsA() == ::delphes::Tower::Class()) {
        ::delphes::Tower& tower = static_cast<::delphes::Tower&>(object);
        if (is(jet_detail, JetDetail::isolation)) for (auto const & particle_number : Range(tower.Particles.GetEntriesFast())) if (!Isolated(*tower.Particles.At(particle_number), leptons)) throw boca::Isolation();
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
        jet = boca::PseudoJet(tower.P4());
    } else if (object.IsA() == ::delphes::Muon::Class()) {
        ::delphes::Muon& muon = static_cast<::delphes::Muon&>(object);
        if (is(jet_detail, JetDetail::isolation) && !Isolated(*muon.Particle.GetObject(), leptons)) throw boca::Isolation();
        Constituent constituent(muon.P4(), SubDetector::muon, muon.Charge);
//         if (is(jet_detail, JetDetail::tagging)) constituent.SetFamily(BranchFamily(*muon.Particle.GetObject()));
        jet = boca::PseudoJet(muon.P4());
        jet_info->AddConstituent(constituent);
    } else Error("Unkonw Jet constituent", object.ClassName());
    jet.set_user_info(jet_info);
    return jet;
}

bool Hadrons::Isolated(TObject const& object, std::vector<TObject*> const& leptons) const
{
//   Error0;
    bool isolated = true;
    for (auto const & lepton : leptons) if (&object == lepton) isolated = false;
//     Check(isolated, isolated);
    return isolated;
}

Jets Hadrons::EFlowJets(JetDetail jet_detail) const
{
    fastjet::ClusterSequence& cluster_sequence = *new fastjet::ClusterSequence(EFlow(jet_detail), DetectorGeometry::JetDefinition());
    boca::Jets jets = fastjet::sorted_by_pt(cluster_sequence.inclusive_jets(DetectorGeometry::JetMinPt() / GeV));
    if (jets.empty()) {
        delete &cluster_sequence;
        return jets;
    }
    cluster_sequence.delete_self_when_unused();
    return jets;
}

Jets Hadrons::EFlow(JetDetail jet_detail) const
{
    boca::Jets e_flow_jets;
//     Debug(tree_reader().EFlowTrackSum(), Name(jet_detail));
    if (tree_reader().Has(Branch::e_flow_track)) e_flow_jets = Join(e_flow_jets, EFlowTrack(jet_detail));
    Debug(e_flow_jets.size());
    if (tree_reader().Has(Branch::e_flow_photon)) e_flow_jets = Join(e_flow_jets, EFlowPhoton(jet_detail));
    if (tree_reader().Has(Branch::e_flow_neutral_hadron)) e_flow_jets = Join(e_flow_jets, EFlowHadron(jet_detail));
    if (tree_reader().Has(Branch::e_flow_muon)) e_flow_jets = Join(e_flow_jets, EFlowMuon(jet_detail));
    Debug(e_flow_jets.size());
//     PrintTruthLevel(Severity::detailed);
    return e_flow_jets;
}

Jets Hadrons::EFlowTrack(JetDetail jet_detail) const
{
    boca::Jets e_flow_jets;
//     Debug(tree_reader().EFlowTrackSum());
    for (auto & e_flow_track : tree_reader().Objects<::delphes::Track>(Branch::e_flow_track)) {
        if (is(jet_detail, JetDetail::structure)) {
            try {
                e_flow_jets.emplace_back(ConstituentJet(e_flow_track, jet_detail, SubDetector::track));
            } catch (std::exception const&) {
                continue;
            }
            continue;
        }
//         ::delphes::Track& e_flow_track = static_cast<::delphes::Track&>(tree_reader().EFlowTrack(e_flow_track_number));
        if (is(jet_detail, JetDetail::isolation)) {
//             bool Isolated = Isolation<::delphes::Electron>(e_flow_track, Branch::electron);
//             if (Isolated) Isolated = Isolation<::delphes::Muon>(e_flow_track, Branch::muon);
//             if (!Isolated) continue;
        }
        e_flow_jets.emplace_back(boca::PseudoJet(e_flow_track.P4()));
        if (is(jet_detail, JetDetail::tagging)) {
            Constituent constituent(e_flow_track.P4()/*, BranchFamily(*e_flow_track.Particle.GetObject())*/);
            e_flow_jets.back().set_user_info(new JetInfo(constituent));
            Detail(e_flow_jets.back().user_index());
        }
    }
    Debug(e_flow_jets.size());
    return e_flow_jets;
}

Jets Hadrons::EFlowPhoton(JetDetail jet_detail) const
{
//     Debug(tree_reader().EFlowPhotonSum());
    boca::Jets e_flow_jets;
//     if (tree_reader().PhotonSum() > 0) Debug("Number of Photons", tree_reader().PhotonSum());
    for (auto & e_flow_photon : tree_reader().Objects<::delphes::Tower>(Branch::e_flow_photon)) {
        if (is(jet_detail, JetDetail::structure)) {
            try {
                e_flow_jets.emplace_back(ConstituentJet(e_flow_photon, jet_detail, SubDetector::photon));
            } catch (std::exception const&) {
                continue;
            }
            continue;
        }
//         ::delphes::Tower& e_flow_photon = static_cast<::delphes::Tower&>(tree_reader().EFlowPhoton(e_flow_photon_number));
//         if (is(jet_detail, JetDetail::isolation)) if (!Isolation<::delphes::Photon>(e_flow_photon, Branch::photon)) continue;
        e_flow_jets.emplace_back(boca::PseudoJet(e_flow_photon.P4()));
        if (is(jet_detail, JetDetail::tagging)) {
            e_flow_jets.back().set_user_info(new JetInfo(JetId(e_flow_photon)));
            Detail(e_flow_jets.back().user_index());
        }
    }
    return e_flow_jets;
}

Jets Hadrons::EFlowHadron(JetDetail jet_detail) const
{
//     Debug(tree_reader().EFlowNeutralHadronSum());
    boca::Jets e_flow_jets;
    for (auto & e_flow_hadron : tree_reader().Objects<::delphes::Tower>(Branch::e_flow_neutral_hadron)) {
        if (is(jet_detail, JetDetail::structure)) {
            try {
                e_flow_jets.emplace_back(ConstituentJet(e_flow_hadron, jet_detail, SubDetector::tower));
            } catch (std::exception const&) {
                continue;
            }
            continue;
        }
//         ::delphes::Tower& e_flow_hadron = static_cast<::delphes::Tower&>(tree_reader().EFlowNeutralHadron(hadron_number));
        e_flow_jets.emplace_back(boca::PseudoJet(e_flow_hadron.P4()));
        if (is(jet_detail, JetDetail::tagging)) {
            e_flow_jets.back().set_user_info(new JetInfo(JetId(e_flow_hadron)));
            Detail(e_flow_jets.back().user_index());
        }
    }
    return e_flow_jets;
}

Jets Hadrons::EFlowMuon(JetDetail jet_detail) const
{
//     Debug(tree_reader().EFlowMuonSum());
    boca::Jets e_flow_jets;
    for (auto  & e_flow_muon : tree_reader().Objects<::delphes::Muon>(Branch::e_flow_muon)) {
        if (is(jet_detail, JetDetail::structure)) {
            //             if (!tree_reader().GetEFlowMuon(muon_number)) continue;
            try {
                e_flow_jets.emplace_back(ConstituentJet(e_flow_muon, jet_detail, SubDetector::muon));
            } catch (std::exception const&) {
                continue;
            }
            continue;
        }
//         ::delphes::Muon& e_flow_muon = static_cast<::delphes::Muon&>(tree_reader().EFlowMuon(muon_number));
//         if (is(jet_detail, JetDetail::isolation)) if (!Isolation<::delphes::Muon>(e_flow_muon, Branch::muon)) continue;
        e_flow_jets.emplace_back(boca::PseudoJet(e_flow_muon.P4()));
        if (is(jet_detail, JetDetail::tagging)) {
            Constituent constituent(e_flow_muon.P4()/*, BranchFamily(*e_flow_muon.Particle.GetObject())*/);
            e_flow_jets.back().set_user_info(new JetInfo(constituent));
            Detail(e_flow_jets.back().user_index());
        }
    }
    return e_flow_jets;
}

Jets Hadrons::GenJets() const
{
//     Info(tree_reader().GenJetSum());
    boca::Jets gen_jets;
    for (auto const & jet : tree_reader().Objects<::delphes::Jet>(Branch::gen_jet)) gen_jets.emplace_back(jet.P4());
    return gen_jets;
}

float Hadrons::ScalarHt() const
{
    Info0;
    return tree_reader().Objects<::delphes::ScalarHT>(Branch::scalar_ht).front().HT;
}

fastjet::PseudoJet Hadrons::MissingEt() const
{
    Info0;
    return boca::PseudoJet(tree_reader().Objects<::delphes::MissingET>(Branch::missing_et).front().P4());
}

}

}
