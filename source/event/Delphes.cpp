/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "external/delphes/delphes/Classes.hh"

#include "boca/generic/Types.hh"
#include "boca/generic/Vector.hh"
#include "boca/generic/Exception.hh"
#include "boca/fastjet/ClusterSequence.hh"
#include "boca/io/TreeReader.hh"
#include "boca/event/Delphes.hh"
#include "boca/fastjet/Sort.hh"
#include "boca/Settings.hh"
// #define DEBUGGING
#include "boca/generic/DEBUG_MACROS.hh"

namespace boca
{

namespace delphes
{

namespace
{

auto GetFamily(TTreeReaderArray<::delphes::GenParticle>& particles, boca::Family& family, Relative relative, int position)
{
    if (relative == Relative::none) return family;
    if (position == Member::EmptyPosition()) return family;
    family.SetMember( {particles.At(position).PID, position}, relative);
    GetFamily(particles, family, Mother(relative), particles.At(position).M1);
    GetFamily(particles, family, StepMother(relative), particles.At(position).M2);
    return family;
}

auto GetFamily(TTreeReaderArray<::delphes::GenParticle>& particles, int position)
{
    boca::Family family;
    return GetFamily(particles, family, Relative::particle, position);
}

}

std::vector<Particle> Event::GetParticles(Status min_status) const
{
    INFO0;
    auto particles = std::vector<Particle> {};
    auto& gen_particles = TreeReader().Array<::delphes::GenParticle>(Branch::particle);
    auto position = 0;
    for (auto const & particle : gen_particles) {
        if (particle.Status < to_int(min_status)) break;
        particles.emplace_back(Particle(particle.P4(), GetFamily(gen_particles, position)));
        ++position;
    }
    return particles;
}

std::vector<Lepton> Event::GetElectrons() const
{
    INFO0;
    auto electrons = std::vector<Lepton> {};
    for (auto const & electron : TreeReader().Array<::delphes::Electron>(Branch::electron)) electrons.emplace_back(Lepton(electron.P4(), static_cast<int>(electron.Charge)));
    return electrons;
}

std::vector<Lepton> Event::GetMuons() const
{
    INFO0;
    auto muons = std::vector<Lepton> {};
    for (auto const & muon : TreeReader().Array<::delphes::Muon>(Branch::muon)) muons.emplace_back(Lepton(muon.P4(), static_cast<int>(muon.Charge)));
    return muons;
}

std::vector<Photon> Event::GetPhotons() const
{
    INFO0;
    auto photons = std::vector<Photon> {};
    for (auto const & muon : TreeReader().Array<::delphes::Photon>(Branch::photon)) photons.emplace_back(Photon(muon.P4()));
    return photons;
}

boca::MissingEt Event::GetMissingEt() const
{
    INFO0;
    return TreeReader().Array<::delphes::MissingET>(Branch::missing_et).At(0).P4();
}

Momentum Event::GetScalarHt() const
{
    INFO0;
    return static_cast<double>(TreeReader().Array<::delphes::ScalarHT>(Branch::scalar_ht).At(0).HT) * GeV;
}

std::vector<Jet> Event::GetJets() const
{
    switch (Settings::JetType()) {
    case JetType::jet :
        return DelphesJets(JetDetail::structure | JetDetail::isolation);
    case JetType::gen_jet :
        return GenJets();
    case JetType::e_flow_jet :
        return EFlowJets(JetDetail::structure | JetDetail::isolation);
        DEFAULT(Name(Settings::JetType()), {});
    }
}

std::vector<Jet> Event::GenJets() const
{
    INFO0;
    auto gen_jets = std::vector<Jet> {};
    for (auto const & jet : TreeReader().Array<::delphes::Jet>(Branch::gen_jet)) gen_jets.emplace_back(jet.P4());
    return gen_jets;
}

std::vector<Jet> Event::DelphesJets(JetDetail jet_detail) const
{
    INFO0;
    auto jets = std::vector<Jet> {};
    for (auto const & jet : TreeReader().Array<::delphes::Jet>(Branch::jet)) {
        FlagSwitch(jet_detail, [&](JetDetail jet_detail_int) {
            switch (jet_detail_int) {
            case JetDetail::plain:
                jets.emplace_back(jet.P4(), jet);
                break;
            case JetDetail::structure :
                if (auto optional = StructuredJet(jet, jet_detail)) jets.emplace_back(*optional);
                break;
            case JetDetail::isolation :
                break;
                DEFAULT(Name(jet_detail_int));
            }
        });
    }
    return jets;
}

boost::optional<Jet> Event::StructuredJet(::delphes::Jet const& delphes_jet, JetDetail jet_detail) const
{
    INFO(delphes_jet.Constituents.GetEntriesFast());
    auto constituents = std::vector<Jet> {};
    for (auto constituent_number : IntegerRange(delphes_jet.Constituents.GetEntriesFast())) {
        if (!delphes_jet.Constituents.At(constituent_number)) continue;
        if (auto optional = ConstituentJet(*delphes_jet.Constituents.At(constituent_number), jet_detail)) constituents.emplace_back(*optional);
        else DEBUG("Constituent is not isolated");
    }
    if (constituents.empty()) return boost::none;
    auto jet = Join(constituents);
    jet.SetDelphesTags(delphes_jet);
    DEBUG(jet.Mass(), jet.Rap(), jet.Phi());
    return jet;
}

boost::optional<Jet> Event::ConstituentJet(TObject& object, JetDetail jet_detail) const
{
    INFO(object.ClassName(), Name(jet_detail));
    if (object.IsA() == ::delphes::GenParticle::Class()) return ConstituentGenParticle(object, jet_detail);
    if (object.IsA() == ::delphes::Track::Class()) return ConstituentTrack(object, jet_detail);
    if (object.IsA() == ::delphes::Tower::Class()) return ConstituentTower(object, jet_detail);
    if (object.IsA() == ::delphes::Muon::Class()) return ConstituentMuon(object, jet_detail);
    ERROR("Unkonw Jet constituent", object.ClassName());
    return boost::none;
}

boost::optional<Jet> Event::ConstituentGenParticle(TObject& object, JetDetail jet_detail) const
{
    INFO(object.ClassName(), Name(jet_detail));
    if (IsLepton(object, jet_detail)) return boost::none;
    auto& particle = static_cast<::delphes::GenParticle&>(object);
    INFO(particle.PT);
    return Jet(particle.P4(), Constituent(particle.P4(), LorentzVector<Length>(particle), Family(object), DetectorPart::gen_particle, particle.Charge));
}

boost::optional<Jet> Event::ConstituentTrack(TObject& object, JetDetail jet_detail) const
{
    INFO(object.ClassName(), Name(jet_detail));
    auto& track = static_cast<::delphes::Track&>(object);
//     if (IsLepton(*track.Particle.GetObject(), jet_detail)) return boost::none;
//     CHECK(LorentzVector<Length>(track).Rho() < Settings::TrackerDistanceMax(), LorentzVector<Length>(track).Rho(),LorentzVector<Length>(track).Perp() );
    return Jet(track.P4(), Constituent(track.P4(), LorentzVector<Length>(track), Family(*track.Particle.GetObject()), DetectorPart::track, track.Charge));
}

boost::optional<Jet> Event::ConstituentTower(TObject& object, JetDetail jet_detail) const
{
    INFO0;
    auto& tower = static_cast<::delphes::Tower&>(object);
    auto families = std::vector<boca::Family> {};
    for (auto particle_number : IntegerRange(tower.Particles.GetEntriesFast())) {
        auto& object = *tower.Particles.At(particle_number);
        if (IsLepton(object, jet_detail)) return boost::none;
        families.emplace_back(Family(object));
    }
    return Jet(tower.P4(), Constituent(tower.P4(), families, DetectorPart::tower));
}

boost::optional<Jet> Event::ConstituentMuon(TObject& object, JetDetail jet_detail) const
{
    ERROR("muon", "there must have been a change in delphes");
    auto& muon = static_cast<::delphes::Muon&>(object);
    if (IsLepton(*muon.Particle.GetObject(), jet_detail)) return boost::none;
    return Jet(muon.P4(), Constituent(muon.P4(), Family(*muon.Particle.GetObject()), DetectorPart::muon, muon.Charge));
}

bool Event::IsLepton(TObject const& object, JetDetail jet_detail) const
{
    DEBUG0;
    if (!is(jet_detail, JetDetail::isolation)) return true;
    for (auto const & lepton : LeptonsObjects()) if (&object == lepton) return true;
    return false;
}

std::vector<TObject*> Event::LeptonsObjects() const
{
    INFO0;
    return lepton_objects_.Get([&]() {
        auto leptons = std::vector<TObject*> {};
        for (auto const & electron : TreeReader().Array<::delphes::Electron>(Branch::electron)) leptons.emplace_back(electron.Particle.GetObject());
        for (auto const & muon : TreeReader().Array<::delphes::Muon>(Branch::muon)) leptons.emplace_back(muon.Particle.GetObject());
        return leptons;
    });
}

boca::Family Event::Family(TObject& object) const
{
    auto family = boca::Family {};
    auto& particle = static_cast<::delphes::GenParticle&>(object);
    auto& particles = TreeReader().Array<::delphes::GenParticle>(Branch::particle);
    family.SetMember( {particle.PID}, Relative::particle);
    GetFamily(particles, family, Mother(Relative::particle), particle.M1);
    GetFamily(particles, family, StepMother(Relative::particle), particle.M2);
    return family;
}


std::vector<Jet> Event::EFlowJets(JetDetail jet_detail) const
{
    INFO0;
    auto cluster_sequence = ClusterSequence {EFlow(jet_detail), Settings::JetDefinition()};
    return cluster_sequence.InclusiveJets(Settings::JetMinPt());
}

std::vector<Jet> Event::GetEFlow(JetDetail jet_detail) const
{
    INFO0;
    auto jets = std::vector<Jet> {};
    if (TreeReader().Has(Branch::e_flow_track)) Insert(jets, EFlowTrack(jet_detail));
    if (TreeReader().Has(Branch::e_flow_photon)) Insert(jets, EFlowPhoton(jet_detail));
    if (TreeReader().Has(Branch::e_flow_neutral_hadron)) Insert(jets, EFlowHadron(jet_detail));
    if (TreeReader().Has(Branch::e_flow_muon)) Insert(jets, EFlowMuon(jet_detail));
    return jets;
}

std::vector<Jet> Event::EFlowTrack(JetDetail jet_detail) const
{
    INFO0;
    auto e_flow_jets = std::vector<Jet> {};
    for (auto & e_flow_track : TreeReader().Array<::delphes::Track>(Branch::e_flow_track)) {
        if (is(jet_detail, JetDetail::structure)) {
            if (auto optional = ConstituentJet(e_flow_track, jet_detail)) e_flow_jets.emplace_back(*optional);
        } else e_flow_jets.emplace_back(e_flow_track.P4());
    }
    DEBUG(e_flow_jets.size());
    return e_flow_jets;
}

std::vector<Jet> Event::EFlowPhoton(JetDetail jet_detail) const
{
    INFO0;
    auto e_flow_jets = std::vector<Jet> {};
    for (auto & e_flow_photon : TreeReader().Array<::delphes::Tower>(Branch::e_flow_photon)) {
        if (is(jet_detail, JetDetail::structure)) {
            if (auto optional = ConstituentJet(e_flow_photon, jet_detail)) e_flow_jets.emplace_back(*optional);
        } else e_flow_jets.emplace_back(e_flow_photon.P4());
    }
    return e_flow_jets;
}

std::vector<Jet> Event::EFlowHadron(JetDetail jet_detail) const
{
    INFO0;
    auto e_flow_jets = std::vector<Jet> {};
    for (auto & e_flow_hadron : TreeReader().Array<::delphes::Tower>(Branch::e_flow_neutral_hadron)) {
        if (is(jet_detail, JetDetail::structure)) {
            if (auto optional = ConstituentJet(e_flow_hadron, jet_detail)) e_flow_jets.emplace_back(*optional);
        } else e_flow_jets.emplace_back(e_flow_hadron.P4());
    }
    return e_flow_jets;
}

std::vector<Jet> Event::EFlowMuon(JetDetail jet_detail) const
{
    INFO0;
    auto e_flow_jets = std::vector<Jet> {};
    for (auto & e_flow_muon : TreeReader().Array<::delphes::Muon>(Branch::e_flow_muon)) {
        if (is(jet_detail, JetDetail::structure)) {
            if (auto optional = ConstituentJet(e_flow_muon, jet_detail)) e_flow_jets.emplace_back(*optional);
        } else e_flow_jets.emplace_back(e_flow_muon.P4());
    }
    return e_flow_jets;
}

}

}
