# pragma once

# include "Triplet.hh"

namespace analysis
{

/**
 * @brief A sextet of 2 triplets
 *
 */
class Sextet : public Multiplet<Triplet,Triplet>
{

public:

    using Multiplet<Triplet,Triplet>::Multiplet;

    Triplet Triplet1() const;

    Triplet Triplet2() const;

    inline float HardTopPt() const {
        return std::max(Triplet1().Jet().pt(), Triplet2().Jet().pt());
    }

    inline float SoftTopPt() const {
        return std::min(Triplet1().Jet().pt(), Triplet2().Jet().pt());
    }

    inline float GetLargertripletDeltaR() const {
        return std::max(Triplet1().DeltaR(), Triplet2().DeltaR());
    }

    inline float GetSmallertripletDeltaR() const {
        return std::min(Triplet1().DeltaR(), Triplet2().DeltaR());
    }

    inline float GetLargertripletDeltaRap() const {
        return std::max(Triplet1().DeltaRap(), Triplet2().DeltaRap());
    }

    inline float GetSmallertripletDeltaRap() const {
        return std::min(Triplet1().DeltaRap(), Triplet2().DeltaRap());
    }

    inline float GetLargerTripleDeltaPhi() const {
        return std::max(std::abs(Triplet1().DeltaPhi()), std::abs(Triplet2().DeltaPhi()));
    }

    inline float GetSmallertripletDeltaPhi() const {
        return std::min(std::abs(Triplet1().DeltaPhi()), std::abs(Triplet2().DeltaPhi()));
    }

    inline float GetBetterTripleMass(const ParticleId particle_id)const {
        return std::min(Triplet1().MassDifferenceTo(particle_id), Triplet2().MassDifferenceTo(particle_id));
    }

    inline float GetWorseTripleMass(const ParticleId particle_id)const {
        return std::max(Triplet1().MassDifferenceTo(particle_id), Triplet2().MassDifferenceTo(particle_id));
    }

    inline float GetBetterPairMass(const ParticleId particle_id)const {
        return std::min(Triplet1().Doublet().MassDifferenceTo(particle_id), Triplet2().Doublet().MassDifferenceTo(particle_id));
    }

    inline float GetWorsePairMass(const ParticleId particle_id)const {
        return std::max(Triplet1().Doublet().MassDifferenceTo(particle_id), Triplet2().Doublet().MassDifferenceTo(particle_id));
    }

    inline float GetBetterJetMass(const ParticleId particle_id)const {
        return std::min(Triplet1().MassDifferenceTo(particle_id), Triplet2().MassDifferenceTo(particle_id));
    }

    inline float GetWorseJetMass(const ParticleId particle_id)const {
        return std::max(Triplet1().MassDifferenceTo(particle_id), Triplet2().MassDifferenceTo(particle_id));
    }

protected:

    virtual inline std::string ClassName() const {
        return "Sextet";
    }

private:

};

}
