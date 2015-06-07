# pragma once

# include "Triplet.hh"

namespace analysis
{

/**
 * @brief A sextet of 2 triplets
 *
 */
class Sextet : public Identification
{

public:

    Sextet();

    Sextet(const Triplet &triplet_1, const Triplet &triplet_2);

    bool overlap() const;

    bool overlap(const fastjet::PseudoJet &jet) const;

    Triplet triplet1()const;

    Triplet triplet2()const;

    inline fastjet::PseudoJet triplet1Jet()const {
        return triplet1().Jet();
    }
    inline fastjet::PseudoJet triplet2Jet()const {
        return triplet2().Jet();
    }

    inline fastjet::PseudoJet Jet() const {
        return triplet1Jet() + triplet2Jet();
    }

    inline float Ht() const {
        return triplet1().Ht() + triplet2().Ht();
    }

    inline float DeltaPt()const {
        return triplet1Jet().pt() - triplet2Jet().pt();
    }

    inline float DeltaHt()const {
        return triplet1().Ht() - triplet2().Ht();
    }

    inline float DeltaM()const {
        return triplet1Jet().m() - triplet2Jet().m();
    }

    inline float DeltaRap() const {
        return triplet1Jet().rap() - triplet2Jet().rap();
    }

    inline float DeltaPhi() const {
        return triplet1Jet().delta_phi_to(triplet2Jet());
    }

    inline float DeltaR() const {
        return triplet1Jet().delta_R(triplet2Jet());
    }

    inline float HardTopPt() const {
        return std::max(triplet1().Jet().pt(), triplet2().Jet().pt());
    }

    inline float SoftTopPt() const {
        return std::min(triplet1().Jet().pt(), triplet2().Jet().pt());
    }

    inline float GetLargertripletDeltaR() const {
        return std::max(triplet1().DeltaR(), triplet2().DeltaR());
    }

    inline float GetSmallertripletDeltaR() const {
        return std::min(triplet1().DeltaR(), triplet2().DeltaR());
    }

    inline float GetLargertripletDeltaRap() const {
        return std::max(triplet1().DeltaRap(), triplet2().DeltaRap());
    }

    inline float GetSmallertripletDeltaRap() const {
        return std::min(triplet1().DeltaRap(), triplet2().DeltaRap());
    }

    inline float GetLargerTripleDeltaPhi() const {
        return std::max(std::abs(triplet1().DeltaPhi()), std::abs(triplet2().DeltaPhi()));
    }

    inline float GetSmallertripletDeltaPhi() const {
        return std::min(std::abs(triplet1().DeltaPhi()), std::abs(triplet2().DeltaPhi()));
    }

    inline float GetBetterTripleMass(const ParticleId particle_id)const {
        return std::min(triplet1().GetDeltaMass(particle_id), triplet2().GetDeltaMass(particle_id));
    }

    inline float GetWorseTripleMass(const ParticleId particle_id)const {
        return std::max(triplet1().GetDeltaMass(particle_id), triplet2().GetDeltaMass(particle_id));
    }

    inline float GetBetterPairMass(const ParticleId particle_id)const {
        return std::min(triplet1().doublet().MassDifferenceTo(particle_id), triplet2().doublet().MassDifferenceTo(particle_id));
    }

    inline float GetWorsePairMass(const ParticleId particle_id)const {
        return std::max(triplet1().doublet().MassDifferenceTo(particle_id), triplet2().doublet().MassDifferenceTo(particle_id));
    }

    inline float GetBetterJetMass(const ParticleId particle_id)const {
        return std::min(triplet1().GetJetDeltaMass(particle_id), triplet2().GetJetDeltaMass(particle_id));
    }

    inline float GetWorseJetMass(const ParticleId particle_id)const {
        return std::max(triplet1().GetJetDeltaMass(particle_id), triplet2().GetJetDeltaMass(particle_id));
    }

    Triplet SubMultiplet1() const {
        return triplet_1;
    }

    Triplet SubMultiplet2() const {
        return triplet_2;
    }

// protected:

    virtual inline std::string ClassName() const {
        return "Sextet";
    }

private:

    void Settriplet1(const Triplet &triplet);

    void Settriplet2(const Triplet &triplet);

    Triplet triplet_1;

    Triplet triplet_2;

};

}
