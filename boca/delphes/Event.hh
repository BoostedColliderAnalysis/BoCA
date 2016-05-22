/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/generic/Mutable.hh"
#include "boca/Event.hh"

namespace boca
{

/**
 * @brief Delphes classes
 *
 */
namespace delphes
{

/**
 * @brief Delphes events
 *
 */
class Event : public boca::Event
{

public:

    using boca::Event::Event;

    std::vector<Jet> Jets() const override;

    Momentum ScalarHt() const override;

    boca::MissingEt MissingEt() const override;

    std::vector<Jet> EFlow(JetDetail jet_detail) const override;

    std::vector<Lepton> Electrons() const override;

    std::vector<Lepton> Muons() const override;

    std::vector<Lepton> Photons() const override;

private:

    std::vector<Particle> Particles(Status max_status) const;

    std::vector<Jet> EFlowJets(JetDetail jet_detail) const;

    std::vector<Jet> DelphesJets(JetDetail jet_detail) const;

    std::vector<Jet> GenJets() const;

    bool IsLepton(TObject const& object, JetDetail jet_detail) const;

    boca::Family Family(TObject & object) const;

    std::vector<Jet> EFlowTrack(JetDetail jet_detail) const;

    std::vector<Jet> EFlowPhoton(JetDetail jet_detail) const;

    std::vector<Jet> EFlowHadron(JetDetail jet_detail) const;

    std::vector<Jet> EFlowMuon(JetDetail jet_detail) const;

    boost::optional<Jet> StructuredJet(::delphes::Jet const& delphes_jet, JetDetail jet_detail) const;

    boost::optional<Jet> ConstituentJet(TObject& object, JetDetail jet_detail) const;

    boost::optional<Jet> ConstituentGenParticle(TObject& object, JetDetail jet_detail) const;

    boost::optional<Jet> ConstituentTrack(TObject& object, JetDetail jet_detail) const;

    boost::optional<Jet> ConstituentTower(TObject& object, JetDetail jet_detail) const;

    boost::optional<Jet> ConstituentMuon(TObject& object, JetDetail jet_detail) const;

    std::vector<TObject*> LeptonsObjects() const;

    Mutable<std::vector<TObject*>> lepton_objects_;

};

}

}


