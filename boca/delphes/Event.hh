/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/generic/Mutable.hh"
#include "boca/Event.hh"

namespace boca
{

/**
 * @brief Delphes
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

protected:

    std::vector<Jet> GetJets() const override;

    boca::MissingEt GetMissingEt() const override;

    Momentum GetScalarHt() const override;

    std::vector<Jet> GetEFlow(JetDetail jet_detail) const override;

    std::vector<Lepton> GetElectrons() const override;

    std::vector<Lepton> GetMuons() const override;

    std::vector<Photon> GetPhotons() const override;

    std::vector<Particle> GetParticles(Status max_status) const override;

private:

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


