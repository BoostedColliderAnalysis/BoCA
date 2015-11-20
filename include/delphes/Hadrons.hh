#pragma once

#include "../Hadrons.hh"
#include "DetectorGeometry.hh"
#include "Constituent.hh"

class Jet;
namespace delphes
{
typedef ::Jet Jet;
}

namespace analysis
{

namespace delphes
{

/**
 * @brief Delphes jets
 *
 */
class Hadrons : public analysis::Hadrons
{

public:
  analysis::Jets Jets() const final {
        switch (DetectorGeometry::jet_type()) {
        case JetType::jet :
            return DelphesJets(JetDetail::structure | JetDetail::isolation);
//                return DelphesJets(JetDetail::structure);
        case JetType::gen_jet :
            return GenJets();
        case JetType::e_flow_jet :
            return EFlowJets(JetDetail::structure | JetDetail::isolation);
//            return EFlowJets(JetDetail::structure);
        }
    }

    float ScalarHt() const final;

    fastjet::PseudoJet MissingEt() const final;


private:

//     analysis::Jets UniqueJets() const;

//     analysis::Jets UniqueConstituents(TObject& object, const std::vector< TObject* > leptons) const;

//     analysis::Jets GranulatedJets(const analysis::Jets& jets) const;

    analysis::Jets EFlowJets(analysis::JetDetail jet_detail) const;

    analysis::Jets DelphesJets(JetDetail jet_detail) const;

    analysis::Jets EFlow(JetDetail jet_detail) const;
    
    analysis::Jets GranulatedJets(const analysis::Jets &NewEFlowJets) const;

    analysis::Jets GenJets() const;

    template <typename Clone>
    std::vector<Constituent> JetId(const Clone& clone) const {
        std::vector<Constituent> constituents;
        for (const auto& particle_number : Range(clone.Particles.GetEntriesFast())) {
            Family family = BranchFamily(*clone.Particles.At(particle_number));
            constituents.emplace_back(Constituent(const_cast<Clone&>(clone).P4(), family));
        }
        return constituents;
    }

//     template<typename Particle, typename EFlow>
//     bool Isolation(const EFlow& e_flow, const TClonesArray& clones_array) const
//     {
//         bool Isolated = true;
//         for (const auto& particle_number = 0; particle_number < clones_array.GetEntriesFast(); ++particle_number) {
//             Particle& particle = static_cast<Particle&>(*clones_array.At(particle_number));
//             Isolated = CheckIsolation(e_flow, particle);
//         }
//         return Isolated;
//     }

    template<typename Particle, typename EFlow>
    bool Isolation(const EFlow& e_flow, Branch branch) const {
        bool isolated = true;
        for (const auto& particle_number : Range(clones_arrays().EntrySum(branch))) {
            Particle& particle = static_cast<Particle&>(clones_arrays().Object(branch, particle_number));
            isolated = CheckIsolation(e_flow, particle);
        }
        return isolated;
    }

//     analysis::Jets Constituents(const TObject& object, const TLorentzVector lorentz_vector, const std::vector< TObject* > leptons) const;

    bool Isolated(const TObject& object, const std::vector<TObject*> leptons) const;

    analysis::Jets EFlowTrack(const JetDetail, std::vector<TObject*> &  leptons) const;

    analysis::Jets EFlowPhoton(const JetDetail, std::vector<TObject*> &  leptons) const;

    analysis::Jets EFlowHadron(const JetDetail, std::vector<TObject*> &  leptons) const;

    analysis::Jets EFlowMuon(JetDetail jet_detail) const;

    fastjet::PseudoJet StructuredJet(const ::delphes::Jet& delphes_jet, const std::vector<TObject*> leptons, analysis::JetDetail jet_detail) const;

    fastjet::PseudoJet ConstituentJet(TObject& object, JetDetail jet_detail, const SubDetector sub_detector = SubDetector::none, const std::vector<TObject*> leptons = {}) const;

};

}

}
