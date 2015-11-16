/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "../Hadrons.hh"
#include "DetectorGeometry.hh"
#include "Constituent.hh"

class Jet;
namespace delphes
{
typedef ::Jet Jet;
}

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
    boca::Jets Jets() const final;

    float ScalarHt() const final;

    fastjet::PseudoJet MissingEt() const final;


private:

    std::vector<TObject*> Leptons(JetDetail jet_detail) const;

    boca::Jets EFlowJets(boca::JetDetail jet_detail) const;

    boca::Jets DelphesJets(JetDetail jet_detail) const;

    boca::Jets EFlow(JetDetail jet_detail) const;

    boca::Jets GenJets() const;

    template <typename Clone>
    std::vector<Constituent> JetId(Clone& clone) const {
        std::vector<Constituent> constituents;
        for (auto const & particle_number : Range(clone.Particles.GetEntriesFast())) {
//             Family family = BranchFamily(*clone.Particles.At(particle_number));
            constituents.emplace_back(Constituent(clone.P4()/*, family*/));
        }
        return constituents;
    }

    bool Isolated(TObject const& object, std::vector<TObject*> const& leptons) const;

    boca::Jets EFlowTrack(std::vector< TObject* > const& leptons, JetDetail jet_detail) const;

    boca::Jets EFlowPhoton(std::vector< TObject* > const& leptons, JetDetail jet_detail) const;

    boca::Jets EFlowHadron(std::vector< TObject* > const& leptons, JetDetail jet_detail) const;

    boca::Jets EFlowMuon(std::vector< TObject* > const& leptons, JetDetail jet_detail) const;

    boost::optional<fastjet::PseudoJet> StructuredJet(::delphes::Jet const& delphes_jet, std::vector< TObject* > const& leptons, boca::JetDetail jet_detail) const;

    boost::optional<fastjet::PseudoJet> ConstituentJet(TObject& object, std::vector<TObject*> const& leptons, JetDetail jet_detail, SubDetector sub_detector) const;

    boost::optional<fastjet::PseudoJet> ConstituentGenParticle(TObject& object, std::vector<TObject*> const& leptons, JetDetail jet_detail) const;

    boost::optional<fastjet::PseudoJet> ConstituentTrack(TObject& object, std::vector<TObject*> const& leptons, JetDetail jet_detail) const;

    boost::optional<fastjet::PseudoJet> ConstituentTower(TObject& object, std::vector<TObject*> const& leptons, JetDetail jet_detail, SubDetector sub_detector) const;

    boost::optional<fastjet::PseudoJet> ConstituentMuon(TObject& object, std::vector<TObject*> const& leptons, JetDetail jet_detail) const;

};

}

}
