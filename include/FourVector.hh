# pragma once

# include "Object.hh"
# include "ClonesArrays.hh"
# include "JetTag.hh"
# include "JetInfo.hh"

# include "delphes/Delphes.hh"
# include "exroot/ExRootAnalysis.hh"

namespace analysis {

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

    void NewEvent(const ClonesArrays &NewClonesArrays);

    template<typename Particle>
    TLorentzVector LorentzVectorByEnergy(const Particle &particle) const {
        Print(kDebug, "Get Lorentz Vector by Energy");
        TLorentzVector vector;
        const float Pt = particle.PT;
        const float Eta = particle.Eta;
        const float Phi = particle.Phi;
        const float Energy = particle.E;
        vector.SetPtEtaPhiE(Pt, Eta, Phi, Energy);
        if (check_four_vectors_) {
            if (vector.Pt() - Pt > check_value_) Print(kError, "Pt", Pt, vector.Pt());
            if (vector.Eta() - Eta > check_value_) Print(kError, "Eta", Eta, vector.Eta());
            if (vector.Phi() - Phi > check_value_) Print(kError, "Phi", Phi, vector.Phi());
            if (vector.E() - Energy > check_value_) Print(kError, "Energy", Energy, vector.E());
        }
        return vector;
    }

    template<typename Particle>
    TLorentzVector LorentzVectorByMass(const Particle &particle, const float mass) const {
        Print(kDebug, "Get Lorentz Vector by Mass");
        TLorentzVector LorentzVector;
        const float Pt = particle.PT;
        const float Eta = particle.Eta;
        const float Phi = particle.Phi;
        LorentzVector.SetPtEtaPhiM(Pt, Eta, Phi, mass);
        if (check_four_vectors_) {
            if (LorentzVector.Pt() - Pt > check_value_) Print(kError, "Pt", Pt, LorentzVector.Pt());
            if (LorentzVector.Eta() - Eta > check_value_) Print(kError, "Eta", Eta, LorentzVector.Eta());
            if (LorentzVector.Phi() - Phi > check_value_) Print(kError, "Phi", Phi, LorentzVector.Phi());
        }
        return LorentzVector;
    }

    template<typename Particle>
    TLorentzVector LorentzVectorByMass(const Particle &particle) const {
        Print(kDebug, "Get Lorentz Vector by Mass");
        const float Mass = particle.Mass;
        const TLorentzVector LorentzVector = LorentzVectorByMass(particle, Mass);
        if (check_four_vectors_) {
            if (LorentzVector.M() - Mass > mass_check_value_) Print(kError, "Mass", Mass, LorentzVector.M());
        }
        return LorentzVector;
    }

    template<typename Particle>
    TLorentzVector LorentzVectorByM(const Particle &particle) const {
        Print(kDebug, "Get Lorentz Vector by Mass");
        const float Mass = particle.M;
        const TLorentzVector LorentzVector = LorentzVectorByMass(particle, Mass);
        if (check_four_vectors_) {
            if (LorentzVector.M() - Mass > mass_check_value_) Print(kError, "Mass", Mass, LorentzVector.M());
        }
        return LorentzVector;
    }
//     TLorentzVector LorentzVector(const MissingET *const Particle) const;

    TLorentzVector LorentzVector(const TRootElectron &Particle) const;
    TLorentzVector LorentzVector(const TRootGenJet &Particle) const;
    TLorentzVector LorentzVector(const TRootGenParticle &Particle) const;
    TLorentzVector LorentzVector(const TRootJet &Particle) const;
    TLorentzVector LorentzVector(const TRootLHEFParticle &Particle) const;
    TLorentzVector LorentzVector(const TRootMuon &Particle) const;
    TLorentzVector LorentzVector(const TRootPhoton &Particle) const;
    TLorentzVector LorentzVector(const TRootTau &Particle) const;
    fastjet::PseudoJet PseudoJet(const TRootElectron &Particle) const;
    fastjet::PseudoJet PseudoJet(const TRootGenJet &Particle) const;
    fastjet::PseudoJet PseudoJet(const TRootGenParticle &Particle) const;
    fastjet::PseudoJet PseudoJet(const TRootJet &Particle) const;
    fastjet::PseudoJet PseudoJet(const TRootLHEFParticle &Particle) const;
    fastjet::PseudoJet PseudoJet(const TRootMuon &Particle) const;
    fastjet::PseudoJet PseudoJet(const TRootPhoton &Particle) const;
    fastjet::PseudoJet PseudoJet(const TRootTau &Particle) const;

    Family GetBranchFamily(const TObject &object);

    Family GetBranchFamily(Family &BranchId, int Position);
//     fastjet::PseudoJet PseudoJet(const MissingET & Particle) const;

    template<typename TData>
    void PrintCell(TData const Data) const {
        std::cout << std::right << std::setw(9) << std::setfill(' ') << Data;
    }

    void PrintTruthLevel(const int severity) const;

    std::string PrintParticle(const int Position) const;

    const ClonesArrays& clones_arrays() const {
        return *clones_arrays_;
    }

    /**
     * @brief Clones Arrays
     *
     */
    const ClonesArrays *clones_arrays_;

    std::vector<Family> topology_;

    int source_;

    JetTag &jet_tag()const{return *jet_tag_;}

    void set_jet_tag(JetTag &jet_tag){jet_tag_ = &jet_tag;}

    enum JetDetail {kPlain, kTagging, kIsolation, kStructure, kTaggingIsolation, kTaggingStructure};

    const bool check_four_vectors_;

    const float check_value_;

    const float mass_check_value_;

    virtual inline std::string ClassName() const {
        return "FourVector";
    }

private:

  JetTag *jet_tag_;

};

}
