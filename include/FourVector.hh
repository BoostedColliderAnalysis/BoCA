#pragma once

#include "ClonesArrays.hh"
#include "JetTag.hh"

namespace analysis
{

enum class Status
{
    none = 0,
    stable = 1,
    unstable = 2,
    generator = 3
};


enum class JetDetail
{
    plain, tagging, isolation, structure, tagging_isolation, tagging_structure
};

std::string Name(const JetDetail jet_detail);

/**
 * @brief converts Clones to LorentzVectors and fastjet::PseudoJets
 *
 */
class FourVector : virtual public Object
{

public:

    /**
     * @brief Constructor
     *
     */
    FourVector();

protected:

    void NewEvent(const ClonesArrays &clones_arrays);

    template<typename Particle>
    TLorentzVector LorentzVectorByEnergy(const Particle &particle) const {
        Print(Severity::debug, "Lorentz Vector by Energy");
        TLorentzVector vector;
        const float Pt = particle.PT;
        const float Eta = particle.Eta;
        const float Phi = particle.Phi;
        const float Energy = particle.E;
        vector.SetPtEtaPhiE(Pt, Eta, Phi, Energy);
        if (check_four_vectors_) {
            if (vector.Pt() - Pt > check_value_) Print(Severity::error, "Pt", Pt, vector.Pt());
            if (vector.Eta() - Eta > check_value_) Print(Severity::error, "Eta", Eta, vector.Eta());
            if (vector.Phi() - Phi > check_value_) Print(Severity::error, "Phi", Phi, vector.Phi());
            if (vector.E() - Energy > check_value_) Print(Severity::error, "Energy", Energy, vector.E());
        }
        return vector;
    }

    template<typename Particle>
    TLorentzVector LorentzVectorByMass(const Particle &particle, const float mass) const {
        Print(Severity::debug, "Lorentz Vector by Mass");
        TLorentzVector LorentzVector;
        const float Pt = particle.PT;
        const float Eta = particle.Eta;
        const float Phi = particle.Phi;
        LorentzVector.SetPtEtaPhiM(Pt, Eta, Phi, mass);
        if (check_four_vectors_) {
            if (LorentzVector.Pt() - Pt > check_value_) Print(Severity::error, "Pt", Pt, LorentzVector.Pt());
            if (LorentzVector.Eta() - Eta > check_value_) Print(Severity::error, "Eta", Eta, LorentzVector.Eta());
            if (LorentzVector.Phi() - Phi > check_value_) Print(Severity::error, "Phi", Phi, LorentzVector.Phi());
        }
        return LorentzVector;
    }

    template<typename Particle>
    TLorentzVector LorentzVectorByMass(const Particle &particle) const {
        Print(Severity::debug, "Lorentz Vector by Mass");
        const float Mass = particle.Mass;
        const TLorentzVector LorentzVector = LorentzVectorByMass(particle, Mass);
        if (check_four_vectors_) {
            if (LorentzVector.M() - Mass > mass_check_value_) Print(Severity::error, "Mass", Mass, LorentzVector.M());
        }
        return LorentzVector;
    }

    template<typename Particle>
    TLorentzVector LorentzVectorByM(const Particle &particle) const {
        Print(Severity::debug, "Lorentz Vector by Mass");
        const float Mass = particle.M;
        const TLorentzVector LorentzVector = LorentzVectorByMass(particle, Mass);
        if (check_four_vectors_) {
            if (LorentzVector.M() - Mass > mass_check_value_) Print(Severity::error, "Mass", Mass, LorentzVector.M());
        }
        return LorentzVector;
    }
//     TLorentzVector LorentzVector(const MissingET *const Particle) const;

    TLorentzVector LorentzVector(const exroot::Electron &Particle) const;
    TLorentzVector LorentzVector(const exroot::GenJet &Particle) const;
    TLorentzVector LorentzVector(const exroot::GenParticle &Particle) const;
    TLorentzVector LorentzVector(const exroot::Jet &Particle) const;
    TLorentzVector LorentzVector(const exroot::LHEFParticle &Particle) const;
    TLorentzVector LorentzVector(const exroot::Muon &Particle) const;
    TLorentzVector LorentzVector(const exroot::Photon &Particle) const;
    TLorentzVector LorentzVector(const exroot::Tau &Particle) const;
    fastjet::PseudoJet PseudoJet(const exroot::Electron &Particle) const;
    fastjet::PseudoJet PseudoJet(const exroot::GenJet &Particle) const;
    fastjet::PseudoJet PseudoJet(const exroot::GenParticle &Particle) const;
    fastjet::PseudoJet PseudoJet(const exroot::Jet &Particle) const;
    fastjet::PseudoJet PseudoJet(const exroot::LHEFParticle &Particle) const;
    fastjet::PseudoJet PseudoJet(const exroot::Muon &Particle) const;
    fastjet::PseudoJet PseudoJet(const exroot::Photon &Particle) const;
    fastjet::PseudoJet PseudoJet(const exroot::Tau &Particle) const;

    Family BranchFamily(const TObject &object);

    Family BranchFamily(Family &BranchId, int Position);
//     fastjet::PseudoJet PseudoJet(const MissingET & Particle) const;

    template<typename TData>
    void PrintCell(TData const Data) const {
        std::cout << std::right << std::setw(9) << std::setfill(' ') << Data;
    }

    void PrintTruthLevel(const Severity severity) const;

    std::string PrintParticle(const int Position) const;

    const ClonesArrays &clones_arrays() const {
        return *clones_arrays_;
    }

    /**
     * @brief Clones Arrays
     *
     */
    const ClonesArrays *clones_arrays_;

    std::vector<Family> topology_;

    int source_;

    JetTag &jet_tag()const {
        return *jet_tag_;
    }

    void set_jet_tag(JetTag &jet_tag) {
        jet_tag_ = &jet_tag;
    }

    const bool check_four_vectors_;

    const float check_value_;

    const float mass_check_value_;

    virtual  std::string ClassName() const {
        return "FourVector";
    }

private:

    JetTag *jet_tag_;

};

}
