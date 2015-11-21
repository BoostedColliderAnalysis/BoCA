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
    std::vector<Jet> Jets() const final;

    float ScalarHt() const final;

    Jet MissingEt() const final;


private:

    std::vector<TObject*> Leptons(JetDetail jet_detail) const;

    std::vector<Jet> EFlowJets(boca::JetDetail jet_detail) const;

    std::vector<Jet> DelphesJets(JetDetail jet_detail) const;

    std::vector<Jet> EFlow(JetDetail jet_detail) const;

    std::vector<Jet> GenJets() const;

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

    std::vector<Jet> EFlowTrack(std::vector< TObject* > const& leptons, JetDetail jet_detail) const;

    std::vector<Jet> EFlowPhoton(std::vector< TObject* > const& leptons, JetDetail jet_detail) const;

    std::vector<Jet> EFlowHadron(std::vector< TObject* > const& leptons, JetDetail jet_detail) const;

    std::vector<Jet> EFlowMuon(std::vector< TObject* > const& leptons, JetDetail jet_detail) const;

    boost::optional<Jet> StructuredJet(::delphes::Jet const& delphes_jet, std::vector< TObject* > const& leptons, boca::JetDetail jet_detail) const;

    boost::optional<Jet> ConstituentJet(TObject& object, std::vector<TObject*> const& leptons, JetDetail jet_detail, SubDetector sub_detector) const;

    boost::optional<Jet> ConstituentGenParticle(TObject& object, std::vector<TObject*> const& leptons, JetDetail jet_detail) const;

    boost::optional<Jet> ConstituentTrack(TObject& object, std::vector<TObject*> const& leptons, JetDetail jet_detail) const;

    boost::optional<Jet> ConstituentTower(TObject& object, std::vector<TObject*> const& leptons, JetDetail jet_detail, SubDetector sub_detector) const;

    boost::optional<Jet> ConstituentMuon(TObject& object, std::vector<TObject*> const& leptons, JetDetail jet_detail) const;

};

}

}
