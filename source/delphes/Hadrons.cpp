/**
 * Copyright (C) 2015 Jan Hajer
 */

#include<boost/optional.hpp>

#include "delphes/Delphes.hh"
#include "delphes/Hadrons.hh"

#include "ClusterSequence.hh"
#include "Vector.hh"
#include "Sort.hh"
#include "Exception.hh"
// #define DEBUG
#include "Debug.hh"

namespace boca
{

namespace delphes
{

Hadrons::Hadrons(boca::TreeReader const& tree_reader) :
    boca::Hadrons(tree_reader) {}


boca::MissingEt Hadrons::MissingEt() const
{
    Info0;
    return TreeReader().Objects<::delphes::MissingET>(Branch::missing_et).At(0).P4();
}

Momentum Hadrons::ScalarHt() const
{
    Info0;
    return double(TreeReader().Objects<::delphes::ScalarHT>(Branch::scalar_ht).At(0).HT) * GeV;
}

std::vector<Jet> Hadrons::Jets() const
{
    switch (DetectorGeometry::jet_type()) {
    case JetType::jet : return DelphesJets(JetDetail::structure | JetDetail::isolation);
    case JetType::gen_jet : return GenJets();
    case JetType::e_flow_jet : return EFlowJets(JetDetail::structure | JetDetail::isolation);
        Default("jet type", {});
    }
}

std::vector<Jet> Hadrons::GenJets() const
{
    Info0;
    std::vector<Jet> gen_jets;
    for (auto const & jet : TreeReader().Objects<::delphes::Jet>(Branch::gen_jet)) gen_jets.emplace_back(jet.P4());
    return gen_jets;
}

std::vector<TObject*> Hadrons::Leptons(JetDetail jet_detail) const
{
    Info0;
    std::vector<TObject*> leptons;
    if (is(jet_detail, JetDetail::isolation)) {
        for (auto const & electron : TreeReader().Objects<::delphes::Electron>(Branch::electron)) leptons.emplace_back(electron.Particle.GetObject());
        for (auto const & muon : TreeReader().Objects<::delphes::Muon>(Branch::muon)) leptons.emplace_back(muon.Particle.GetObject());
    }
    return leptons;
}

std::vector<Jet> Hadrons::DelphesJets(JetDetail jet_detail) const
{
    std::vector<TObject*> leptons = Leptons(jet_detail);
    std::vector<Jet> jets;
    for (auto const & delphes_jet : TreeReader().Objects<::delphes::Jet>(Branch::jet)) {
        FlagSwitch(jet_detail, [&](JetDetail jet_detail_int) {
            switch (jet_detail_int) {
            case JetDetail::plain: jets.emplace_back(delphes_jet.P4(), delphes_jet);
                break;
            case JetDetail::structure :
                if (boost::optional<Jet> optional = StructuredJet(delphes_jet, leptons, jet_detail)) jets.emplace_back(*optional);
                break;
            case JetDetail::isolation : break;
            default : break;
            }
        });
    }
    return jets;
}

boost::optional<Jet> Hadrons::StructuredJet(::delphes::Jet const& delphes_jet, std::vector<TObject*> const& leptons, JetDetail jet_detail) const
{
    Info0;
    std::vector<Jet> constituents;
    for (auto const & constituent_number : Range(delphes_jet.Constituents.GetEntriesFast())) {
        if (!delphes_jet.Constituents.At(constituent_number)) continue;
        if (boost::optional<Jet> optional = ConstituentJet(*delphes_jet.Constituents.At(constituent_number), leptons, jet_detail, DetectorPart::none)) constituents.emplace_back(*optional);
        else Debug("Constituent is not isolated");
    }
    if (constituents.empty()) return boost::none;
    Jet jet = Join(constituents);
    jet.SetDelphesTags(delphes_jet);
    Debug(jet.m(), jet.rap(), jet.phi_std(), jet.has_user_info());
    Debug(jet.Mass(), jet.Rap(), jet.Phi(), jet.has_user_info());
    return jet;
}

boost::optional<Jet> Hadrons::ConstituentJet(TObject& object, std::vector< TObject* > const& leptons, JetDetail jet_detail, DetectorPart detector_part) const
{
    INFO(object.ClassName(), Name(jet_detail));
    if (object.IsA() == ::delphes::GenParticle::Class()) return ConstituentGenParticle(object, leptons, jet_detail);
    if (object.IsA() == ::delphes::Track::Class()) return ConstituentTrack(object, leptons, jet_detail);
    if (object.IsA() == ::delphes::Tower::Class()) return ConstituentTower(object, leptons, jet_detail, detector_part);
    if (object.IsA() == ::delphes::Muon::Class()) return ConstituentMuon(object, leptons, jet_detail);
    Error("Unkonw Jet constituent", object.ClassName());
    return boost::none;
}

boost::optional<Jet> Hadrons::ConstituentGenParticle(TObject& object, std::vector< TObject* > const& leptons, JetDetail jet_detail) const
{
    INFO(object.ClassName(), Name(jet_detail));
    if (is(jet_detail, JetDetail::isolation) && !Isolated(object, leptons)) return boost::none;
    ::delphes::GenParticle& particle = static_cast<::delphes::GenParticle&>(object);
    Constituent constituent(particle.P4(), LorentzVector<Length>(particle), DetectorPart::gen_particle, particle.Charge);
    return Jet(particle.P4(), constituent);
}

boost::optional<Jet> Hadrons::ConstituentTrack(TObject& object, std::vector< TObject* > const& leptons, JetDetail jet_detail) const
{
    INFO(object.ClassName(), Name(jet_detail));
    ::delphes::Track& track = static_cast<::delphes::Track&>(object);
    if (is(jet_detail, JetDetail::isolation) && !Isolated(*track.Particle.GetObject(), leptons)) return boost::none;
    Constituent constituent(track.P4(), LorentzVector<Length>(track), DetectorPart::track, track.Charge);
    return Jet(track.P4(), constituent);
}

boost::optional<Jet> Hadrons::ConstituentTower(TObject& object, std::vector< TObject* > const& leptons, JetDetail jet_detail, DetectorPart detector_part) const
{
    Info0;
    ::delphes::Tower& tower = static_cast<::delphes::Tower&>(object);
    if (is(jet_detail, JetDetail::isolation)) for (auto const & particle_number : Range(tower.Particles.GetEntriesFast())) if (!Isolated(*tower.Particles.At(particle_number), leptons)) return boost::none;
    return Jet(tower.P4(), Constituent(tower.P4(), detector_part));
}

boost::optional<Jet> Hadrons::ConstituentMuon(TObject& object, std::vector< TObject* > const& leptons, JetDetail jet_detail) const
{
    Info0;
    ::delphes::Muon& muon = static_cast<::delphes::Muon&>(object);
    if (is(jet_detail, JetDetail::isolation) && !Isolated(*muon.Particle.GetObject(), leptons)) return boost::none;
    return Jet(muon.P4(), Constituent(muon.P4(), DetectorPart::muon, muon.Charge));
}

bool Hadrons::Isolated(TObject const& object, std::vector<TObject*> const& leptons) const
{
    Debug0;
    bool isolated = true;
    for (auto const & lepton : leptons) if (&object == lepton) isolated = false;
    DebugCheck(isolated, isolated);
    return isolated;
}

std::vector<Jet> Hadrons::EFlowJets(JetDetail jet_detail) const
{
    Info0;
    ClusterSequence cluster_sequence(EFlow(jet_detail), DetectorGeometry::JetDefinition());
    return cluster_sequence.InclusiveJets(DetectorGeometry::JetMinPt());
}

std::vector<Jet> Hadrons::EFlow(JetDetail jet_detail) const
{
    Info0;
    std::vector<TObject*> leptons = Leptons(jet_detail);
    std::vector<Jet> jets;
    if (TreeReader().Has(Branch::e_flow_track)) jets = Join(jets, EFlowTrack(leptons, jet_detail));
    if (TreeReader().Has(Branch::e_flow_photon)) jets = Join(jets, EFlowPhoton(leptons, jet_detail));
    if (TreeReader().Has(Branch::e_flow_neutral_hadron)) jets = Join(jets, EFlowHadron(leptons, jet_detail));
    if (TreeReader().Has(Branch::e_flow_muon)) jets = Join(jets, EFlowMuon(leptons, jet_detail));
    return jets;
}

std::vector<Jet> Hadrons::EFlowTrack(std::vector< TObject* > const& leptons, JetDetail jet_detail) const
{
    Info0;
    std::vector<Jet> e_flow_jets;
    for (auto & e_flow_track : TreeReader().Objects<::delphes::Track>(Branch::e_flow_track)) {
        if (is(jet_detail, JetDetail::structure)) {
            if (boost::optional<Jet> optional = ConstituentJet(e_flow_track, leptons, jet_detail, DetectorPart::track)) e_flow_jets.emplace_back(*optional);
        } else e_flow_jets.emplace_back(Jet(e_flow_track.P4()));
    }
    Debug(e_flow_jets.size());
    return e_flow_jets;
}

std::vector<Jet> Hadrons::EFlowPhoton(std::vector< TObject* > const& leptons, JetDetail jet_detail) const
{
    Info0;
    std::vector<Jet> e_flow_jets;
    for (auto & e_flow_photon : TreeReader().Objects<::delphes::Tower>(Branch::e_flow_photon)) {
        if (is(jet_detail, JetDetail::structure)) {
            if (boost::optional<Jet> optional = ConstituentJet(e_flow_photon, leptons, jet_detail, DetectorPart::photon)) e_flow_jets.emplace_back(*optional);
        } else e_flow_jets.emplace_back(e_flow_photon.P4());
    }
    return e_flow_jets;
}

std::vector<Jet> Hadrons::EFlowHadron(std::vector< TObject* > const& leptons, JetDetail jet_detail) const
{
    Info0;
    std::vector<Jet> e_flow_jets;
    for (auto & e_flow_hadron : TreeReader().Objects<::delphes::Tower>(Branch::e_flow_neutral_hadron)) {
        if (is(jet_detail, JetDetail::structure)) {
            if (boost::optional<Jet> optional = ConstituentJet(e_flow_hadron, leptons, jet_detail, DetectorPart::tower)) e_flow_jets.emplace_back(*optional);
        } else e_flow_jets.emplace_back(e_flow_hadron.P4());
    }
    return e_flow_jets;
}

std::vector<Jet> Hadrons::EFlowMuon(std::vector< TObject* > const& leptons, JetDetail jet_detail) const
{
    Info0;
    std::vector<Jet> e_flow_jets;
    for (auto  & e_flow_muon : TreeReader().Objects<::delphes::Muon>(Branch::e_flow_muon)) {
        if (is(jet_detail, JetDetail::structure)) {
            if (boost::optional<Jet> optional = ConstituentJet(e_flow_muon, leptons, jet_detail, DetectorPart::muon)) e_flow_jets.emplace_back(*optional);
        } else e_flow_jets.emplace_back(e_flow_muon.P4());
    }
    return e_flow_jets;
}

}

}

