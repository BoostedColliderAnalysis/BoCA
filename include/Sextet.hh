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

    Triplet & Triplet1() const;

    Triplet & Triplet2() const;

     float HardTopPt() const {
        return std::max(Triplet1().Jet().pt(), Triplet2().Jet().pt());
    }

     float SoftTopPt() const {
        return std::min(Triplet1().Jet().pt(), Triplet2().Jet().pt());
    }

     float GetLargertripletDeltaR() const {
        return std::max(Triplet1().DeltaR(), Triplet2().DeltaR());
    }

     float GetSmallertripletDeltaR() const {
        return std::min(Triplet1().DeltaR(), Triplet2().DeltaR());
    }

     float GetLargertripletDeltaRap() const {
        return std::max(Triplet1().DeltaRap(), Triplet2().DeltaRap());
    }

     float GetSmallertripletDeltaRap() const {
        return std::min(Triplet1().DeltaRap(), Triplet2().DeltaRap());
    }

     float GetLargerTripleDeltaPhi() const {
        return std::max(std::abs(Triplet1().DeltaPhi()), std::abs(Triplet2().DeltaPhi()));
    }

     float GetSmallertripletDeltaPhi() const {
        return std::min(std::abs(Triplet1().DeltaPhi()), std::abs(Triplet2().DeltaPhi()));
    }

     float GetBetterTripleMass(const ParticleId particle_id)const {
        return std::min(Triplet1().MassDifferenceTo(particle_id), Triplet2().MassDifferenceTo(particle_id));
    }

     float GetWorseTripleMass(const ParticleId particle_id)const {
        return std::max(Triplet1().MassDifferenceTo(particle_id), Triplet2().MassDifferenceTo(particle_id));
    }

     float GetBetterPairMass(const ParticleId particle_id)const {
        return std::min(Triplet1().Doublet().MassDifferenceTo(particle_id), Triplet2().Doublet().MassDifferenceTo(particle_id));
    }

     float GetWorsePairMass(const ParticleId particle_id)const {
        return std::max(Triplet1().Doublet().MassDifferenceTo(particle_id), Triplet2().Doublet().MassDifferenceTo(particle_id));
    }

     float GetBetterJetMass(const ParticleId particle_id)const {
        return std::min(Triplet1().MassDifferenceTo(particle_id), Triplet2().MassDifferenceTo(particle_id));
    }

     float GetWorseJetMass(const ParticleId particle_id)const {
        return std::max(Triplet1().MassDifferenceTo(particle_id), Triplet2().MassDifferenceTo(particle_id));
    }

protected:

    virtual  std::string ClassName() const {
        return "Sextet";
    }

private:

};

}
