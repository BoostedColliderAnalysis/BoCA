/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "../Hadrons.hh"
#include "delphes/Forward.hh"
#include "Constituent.hh"

namespace boca
{

/**
 * @brief Delphes object extraction
 *
 */
namespace delphes
{

/**
 * @brief Delphes jets
 *
 */
class Hadrons : public boca::Hadrons
{

public:

    Hadrons(boca::TreeReader const& tree_reader);

    std::vector<Jet> Jets() const override;

    Momentum ScalarHt() const override;

    boca::MissingEt MissingEt() const override;

    std::vector<Jet> EFlow(JetDetail jet_detail) const;

private:

    std::vector<TObject*> Leptons(JetDetail jet_detail) const;

    std::vector<Jet> EFlowJets(JetDetail jet_detail) const;

    std::vector<Jet> DelphesJets(JetDetail jet_detail) const;

    std::vector<Jet> GenJets() const;

    bool Isolated(TObject const& object, std::vector<TObject*> const& leptons) const;

    std::vector<Jet> EFlowTrack(std::vector< TObject* > const& leptons, JetDetail jet_detail) const;

    std::vector<Jet> EFlowPhoton(std::vector< TObject* > const& leptons, JetDetail jet_detail) const;

    std::vector<Jet> EFlowHadron(std::vector< TObject* > const& leptons, JetDetail jet_detail) const;

    std::vector<Jet> EFlowMuon(std::vector< TObject* > const& leptons, JetDetail jet_detail) const;

    boost::optional<Jet> StructuredJet(::delphes::Jet const& delphes_jet, std::vector< TObject* > const& leptons, JetDetail jet_detail) const;

    boost::optional<Jet> ConstituentJet(TObject& object, std::vector<TObject*> const& leptons, JetDetail jet_detail, DetectorPart detector_part) const;

    boost::optional<Jet> ConstituentGenParticle(TObject& object, std::vector<TObject*> const& leptons, JetDetail jet_detail) const;

    boost::optional<Jet> ConstituentTrack(TObject& object, std::vector<TObject*> const& leptons, JetDetail jet_detail) const;

    boost::optional<Jet> ConstituentTower(TObject& object, std::vector<TObject*> const& leptons, JetDetail jet_detail, DetectorPart detector_part) const;

    boost::optional<Jet> ConstituentMuon(TObject& object, std::vector<TObject*> const& leptons, JetDetail jet_detail) const;

};

}

}


