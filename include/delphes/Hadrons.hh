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
    boca::Jets Jets() const final {
        switch (DetectorGeometry::jet_type()) {
        case JetType::jet :
            return DelphesJets(JetDetail::structure | JetDetail::isolation);
        case JetType::gen_jet :
            return GenJets();
        case JetType::e_flow_jet :
            return EFlowJets(JetDetail::structure | JetDetail::isolation);
        }
    }

    float ScalarHt() const final;

    fastjet::PseudoJet MissingEt() const final;


private:

//     boca::Jets UniqueJets() const;

//     boca::Jets UniqueConstituents(TObject& object, const std::vector< TObject* > leptons) const;

//     boca::Jets GranulatedJets(boca::Jets const& jets) const;

    boca::Jets EFlowJets(boca::JetDetail jet_detail) const;

    boca::Jets DelphesJets(JetDetail jet_detail) const;

    boca::Jets EFlow(JetDetail jet_detail) const;

    boca::Jets GenJets() const;

    template <typename Clone>
    std::vector<Constituent> JetId(const Clone& clone) const {
        std::vector<Constituent> constituents;
        for (auto const & particle_number : Range(clone.Particles.GetEntriesFast())) {
            Family family = BranchFamily(*clone.Particles.At(particle_number));
            constituents.emplace_back(Constituent(const_cast<Clone&>(clone).P4(), family));
        }
        return constituents;
    }

//     template<typename Particle, typename EFlow>
//     bool Isolation(const EFlow& e_flow, const TClonesArray& clones_array) const
//     {
//         bool Isolated = true;
//         for (auto const& particle_number = 0; particle_number < clones_array.GetEntriesFast(); ++particle_number) {
//             Particle& particle = static_cast<Particle&>(*clones_array.At(particle_number));
//             Isolated = CheckIsolation(e_flow, particle);
//         }
//         return Isolated;
//     }

    template<typename Particle, typename EFlow>
    bool Isolation(const EFlow& e_flow, Branch branch) const {
        bool isolated = true;
        for (auto const & particle_number : Range(clones_arrays().EntrySum(branch))) {
            Particle& particle = static_cast<Particle&>(clones_arrays().Object(branch, particle_number));
            isolated = CheckIsolation(e_flow, particle);
        }
        return isolated;
    }

//     boca::Jets Constituents(TObject const& object, const TLorentzVector lorentz_vector, const std::vector< TObject* > leptons) const;

    bool Isolated(TObject const& object, std::vector<TObject*> const& leptons) const;

    boca::Jets EFlowTrack(const JetDetail) const;

    boca::Jets EFlowPhoton(const JetDetail) const;

    boca::Jets EFlowHadron(const JetDetail) const;

    boca::Jets EFlowMuon(JetDetail jet_detail) const;

    fastjet::PseudoJet StructuredJet(::delphes::Jet const& delphes_jet, std::vector< TObject* > const& leptons, boca::JetDetail jet_detail) const;

    fastjet::PseudoJet ConstituentJet(TObject& object, JetDetail jet_detail, SubDetector sub_detector = SubDetector::none, const std::vector<TObject*> leptons = {}) const;

};

}

}
