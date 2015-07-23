#pragma once

#include <iomanip>
#include <iostream>
#include "ClonesArrays.hh"
#include "JetTag.hh"

namespace analysis {

enum class Status {
    none = 0,
    stable = 1,
    unstable = 2,
    generator = 3
};


enum class JetDetail {
    plain, tagging, isolation, structure, tagging_isolation, tagging_structure
};

std::string Name(const JetDetail jet_detail);

/**
 * @brief converts Clones to LorentzVectors and fastjet::PseudoJets
 *
 */
class FourVector {

public:

    /**
     * @brief Constructor
     *
     */
    FourVector();

protected:

    void NewEvent(const ClonesArrays& clones_arrays);

    template<typename Particle>
    analysis::LorentzVector LorentzVectorByEnergy(const Particle& particle) const
    {
//         Debug("Lorentz Vector by Energy");
        analysis::LorentzVector vector;
        const float Pt = particle.PT;
        const float Eta = particle.Eta;
        const float Phi = particle.Phi;
        const float Energy = particle.E;
        vector.SetPtEtaPhiE(Pt, Eta, Phi, Energy);
//         if (check_four_vectors_) {
//             if (vector.Pt() - Pt > check_value_) Error(Pt, vector.Pt());
//             if (vector.Eta() - Eta > check_value_) Error(Eta, vector.Eta());
//             if (vector.Phi() - Phi > check_value_) Error(Phi, vector.Phi());
//             if (vector.E() - Energy > check_value_) Error(Energy, vector.E());
//         }
        return vector;
    }

    template<typename Particle>
    analysis::LorentzVector LorentzVectorByMass(const Particle& particle, const float mass) const
    {
//         Debug("Lorentz Vector by Mass");
        analysis::LorentzVector LorentzVector;
        const float Pt = particle.PT;
        const float Eta = particle.Eta;
        const float Phi = particle.Phi;
        LorentzVector.SetPtEtaPhiM(Pt, Eta, Phi, mass);
// //         if (check_four_vectors_) {
// //             if (LorentzVector.Pt() - Pt > check_value_) Error(Pt, LorentzVector.Pt());
// //             if (LorentzVector.Eta() - Eta > check_value_) Error(Eta, LorentzVector.Eta());
// //             if (LorentzVector.Phi() - Phi > check_value_) Error(Phi, LorentzVector.Phi());
// //         }
        return LorentzVector;
    }

    template<typename Particle>
    analysis::LorentzVector LorentzVectorByMass(const Particle& particle) const
    {
//         Debug("Lorentz Vector by Mass");
        const float Mass = particle.Mass;
        const analysis::LorentzVector LorentzVector = LorentzVectorByMass(particle, Mass);
        if (check_four_vectors_) {
//             if (LorentzVector.M() - Mass > mass_check_value_) Error(Mass, LorentzVector.M());
        }
        return LorentzVector;
    }

    template<typename Particle>
    analysis::LorentzVector LorentzVectorByM(const Particle& particle) const
    {
//         Debug("Lorentz Vector by Mass");
        const float Mass = particle.M;
        const analysis::LorentzVector LorentzVector = LorentzVectorByMass(particle, Mass);
        if (check_four_vectors_) {
//             if (LorentzVector.M() - Mass > mass_check_value_) Error(Mass, LorentzVector.M());
        }
        return LorentzVector;
    }
//     analysis::LorentzVector LorentzVector(const MissingET *const Particle) const;

    analysis::LorentzVector LorentzVector(const exroot::Electron& Particle) const;
    analysis::LorentzVector LorentzVector(const exroot::GenJet& Particle) const;
    analysis::LorentzVector LorentzVector(const exroot::GenParticle& Particle) const;
    analysis::LorentzVector LorentzVector(const exroot::Jet& Particle) const;
    analysis::LorentzVector LorentzVector(const exroot::LHEFParticle& Particle) const;
    analysis::LorentzVector LorentzVector(const exroot::Muon& Particle) const;
    analysis::LorentzVector LorentzVector(const exroot::Photon& Particle) const;
    analysis::LorentzVector LorentzVector(const exroot::Tau& Particle) const;
    fastjet::PseudoJet PseudoJet(const exroot::Electron& Particle) const;
    fastjet::PseudoJet PseudoJet(const exroot::GenJet& Particle) const;
    fastjet::PseudoJet PseudoJet(const exroot::GenParticle& Particle) const;
    fastjet::PseudoJet PseudoJet(const exroot::Jet& Particle) const;
    fastjet::PseudoJet PseudoJet(const exroot::LHEFParticle& Particle) const;
    fastjet::PseudoJet PseudoJet(const exroot::Muon& Particle) const;
    fastjet::PseudoJet PseudoJet(const exroot::Photon& Particle) const;
    fastjet::PseudoJet PseudoJet(const exroot::Tau& Particle) const;

    Family BranchFamily(const TObject& object) const;

    Family BranchFamily(Family& BranchId, int Position) const;
//     fastjet::PseudoJet PseudoJet(const MissingET & Particle) const;

    template<typename Data>
    void PrintCell(Data const data) const
    {
        std::cout << std::right << std::setw(9) << std::setfill(' ') << data;
    }

    void PrintTruthLevel(const Severity severity) const;

    std::string PrintParticle(int Position) const;

    const ClonesArrays& clones_arrays() const
    {
        return *clones_arrays_;
    }

    /**
     * @brief Clones Arrays
     *
     */
    const ClonesArrays* clones_arrays_;

//     std::vector<Family> topology_;

    int source_;

    JetTag& jet_tag() const
    {
        return *jet_tag_;
    }

    void set_jet_tag(JetTag& jet_tag)
    {
        jet_tag_ = &jet_tag;
    }

    const bool check_four_vectors_;

    const float check_value_;

    const float mass_check_value_;

private:

    JetTag* jet_tag_;

};

}
