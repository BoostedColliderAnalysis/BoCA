/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include <iomanip>
#include <iostream>

#include "fastjet/PseudoJet.hh"

#include "JetTag.hh"
#include "Flag.hh"
// #include "ClonesArrays.hh"
#include "TreeReader.hh"

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

namespace boca {

typedef std::vector<fastjet::PseudoJet> Jets;

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
    plain = 1 << 0,
    structure = 1 << 1,
    tagging = 1 << 2,
    isolation = 1 << 3,
};

template<>
struct Flag<JetDetail> {
  static const bool enable = true;
};

enum class Severity {
  error,
  notification,
  information,
  debug,
  detailed
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

    void NewEvent(TreeReader const& tree_reader);

    template<typename Particle>
    boca::LorentzVector LorentzVectorByEnergy(const Particle& particle) const
    {
//         Debug("Lorentz Vector by Energy");
        boca::LorentzVector vector;
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
    boca::LorentzVector LorentzVectorByMass(const Particle& particle, Mass mass) const
    {
//         Debug("Lorentz Vector by Mass");
        boca::LorentzVector LorentzVector;
        float Pt = particle.PT;
        float Eta = particle.Eta;
        float Phi = particle.Phi;
        LorentzVector.SetPtEtaPhiM(Pt, Eta, Phi, mass / GeV);
// //         if (check_four_vectors_) {
// //             if (LorentzVector.Pt() - Pt > check_value_) Error(Pt, LorentzVector.Pt());
// //             if (LorentzVector.Eta() - Eta > check_value_) Error(Eta, LorentzVector.Eta());
// //             if (LorentzVector.Phi() - Phi > check_value_) Error(Phi, LorentzVector.Phi());
// //         }
        return LorentzVector;
    }

    template<typename Particle>
    boca::LorentzVector LorentzVectorByMass(const Particle& particle) const
    {
//         Debug("Lorentz Vector by Mass");
        Mass mass(particle.Mass * GeV);
        const boca::LorentzVector LorentzVector = LorentzVectorByMass(particle, mass);
        if (check_four_vectors_) {
//             if (LorentzVector.M() - Mass > mass_check_value_) Error(Mass, LorentzVector.M());
        }
        return LorentzVector;
    }

    template<typename Particle>
    boca::LorentzVector LorentzVectorByM(const Particle& particle) const
    {
//         Debug("Lorentz Vector by Mass");
        Mass mass(particle.M * GeV);
        const boca::LorentzVector LorentzVector = LorentzVectorByMass(particle, mass);
        if (check_four_vectors_) {
//             if (LorentzVector.M() - Mass > mass_check_value_) Error(Mass, LorentzVector.M());
        }
        return LorentzVector;
    }
//     boca::LorentzVector LorentzVector(const MissingET *const Particle) const;

    boca::LorentzVector LorentzVector(const exroot::Electron& Particle) const;
    boca::LorentzVector LorentzVector(const exroot::GenJet& Particle) const;
    boca::LorentzVector LorentzVector(const exroot::GenParticle& Particle) const;
    boca::LorentzVector LorentzVector(const exroot::Jet& Particle) const;
    boca::LorentzVector LorentzVector(const exroot::LHEFParticle& Particle) const;
    boca::LorentzVector LorentzVector(const exroot::Muon& Particle) const;
    boca::LorentzVector LorentzVector(const exroot::Photon& Particle) const;
    boca::LorentzVector LorentzVector(const exroot::Tau& Particle) const;
    fastjet::PseudoJet PseudoJet(const exroot::Electron& Particle) const;
    fastjet::PseudoJet PseudoJet(const exroot::GenJet& Particle) const;
    fastjet::PseudoJet PseudoJet(const exroot::GenParticle& Particle) const;
    fastjet::PseudoJet PseudoJet(const exroot::Jet& Particle) const;
    fastjet::PseudoJet PseudoJet(const exroot::LHEFParticle& Particle) const;
    fastjet::PseudoJet PseudoJet(const exroot::Muon& Particle) const;
    fastjet::PseudoJet PseudoJet(const exroot::Photon& Particle) const;
    fastjet::PseudoJet PseudoJet(const exroot::Tau& Particle) const;

//     Family BranchFamily(TObject const& object) const;

//     Family BranchFamily(Family& BranchId, int Position) const;
//     fastjet::PseudoJet PseudoJet(const MissingET & Particle) const;

    template<typename Data>
    void PrintCell(Data const data) const
    {
        std::cout << std::right << std::setw(9) << std::setfill(' ') << data;
    }

    void PrintTruthLevel(Severity severity) const;

    std::string PrintParticle(int Position) const;

    TreeReader const& tree_reader() const
    {
        return *tree_reader_;
    }

    /**
     * @brief Clones Arrays
     *
     */
    const TreeReader* tree_reader_;

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
