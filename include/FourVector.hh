#pragma once

#include <iomanip>
#include <iostream>

#include "ClonesArrays.hh"
#include "JetTag.hh"
#include "Flag.hh"

class TRootLHEFParticle;
class TRootGenParticle;
class TRootGenJet;
class TRootMissingET;
class TRootPhoton;
class TRootElectron;
class TRootMuon;
class TRootTau;
class TRootJet;

namespace exroot {
  typedef ::TRootLHEFParticle LHEFParticle;
  typedef ::TRootGenParticle GenParticle;
  typedef ::TRootGenJet GenJet;
  typedef ::TRootMissingET MissingET;
  typedef ::TRootPhoton Photon;
  typedef ::TRootElectron Electron;
  typedef ::TRootMuon Muon;
  typedef ::TRootTau Tau;
  typedef ::TRootJet Jet;
}

namespace analysis {

enum class Status {
    none = 0,
    stable = 1,
    unstable = 2,
    generator = 3
};


/**
 * @brief flags defining to which level of detail jets should be analyzed
 *
 */
enum class JetDetail {
    plain = 1,
    structure = 1 << 1,
    tagging = 1 << 2,
    isolation = 1 << 3,
};

template<>
struct Flag<JetDetail> {
  static const bool enable = true;
};

std::string Name(JetDetail jet_detail);

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
        float Pt = particle.PT;
        float Eta = particle.Eta;
        float Phi = particle.Phi;
        float Energy = particle.E;
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
    analysis::LorentzVector LorentzVectorByMass(const Particle& particle, float mass) const
    {
//         Debug("Lorentz Vector by Mass");
        analysis::LorentzVector LorentzVector;
        float Pt = particle.PT;
        float Eta = particle.Eta;
        float Phi = particle.Phi;
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
        float Mass = particle.Mass;
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
        float Mass = particle.M;
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

    bool check_four_vectors_;

    float check_value_;

    float mass_check_value_;

private:

    JetTag* jet_tag_;

};

}
