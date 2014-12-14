# ifndef HSextet_hh
# define HSextet_hh

# include "HTriplet.hh"

/**
 * @brief A sextet formed from 2 triplets
 *
 */
class hanalysis::HSextet : public HTag
{

public:

    HSextet() {Bdt = -10;}

    HSextet(const HTriplet &NewTriple1, const HTriplet &NewTriple2);

    ~HSextet();

    inline float GetBetterTripleMass(const HParticleId ParticleId)const {
        return std::min(Triplet1.GetTripleMassDifference(ParticleId), Triplet2.GetTripleMassDifference(ParticleId));
    }

    inline float GetWorseTripleMass(const HParticleId ParticleId)const {
        return std::max(Triplet1.GetTripleMassDifference(ParticleId), Triplet2.GetTripleMassDifference(ParticleId));
    }

    inline float GetBetterPairMass(const HParticleId ParticleId)const {
        return std::min(Triplet1.GetDoubletMassDifference(ParticleId), Triplet2.GetDoubletMassDifference(ParticleId));
    }

    inline float GetWorsePairMass(const HParticleId ParticleId)const {
        return std::max(Triplet1.GetDoubletMassDifference(ParticleId), Triplet2.GetDoubletMassDifference(ParticleId));
    }

    inline float GetBetterJetMass(const HParticleId ParticleId)const {
        return std::min(Triplet1.GetJetMassDifference(ParticleId), Triplet2.GetJetMassDifference(ParticleId));
    }

    inline float GetWorseJetMass(const HParticleId ParticleId)const {
        return std::max(Triplet1.GetJetMassDifference(ParticleId), Triplet2.GetJetMassDifference(ParticleId));
    }

    inline float GetLargerTripletDeltaR() const {
        return std::max(Triplet1.GetDeltaR(), Triplet2.GetDeltaR());
    }

    inline float GetSmallerTripletDeltaR() const {
        return std::min(Triplet1.GetDeltaR(), Triplet2.GetDeltaR());
    }

    inline float GetLargerTripletDeltaRap() const {
        return std::max(Triplet1.GetDeltaRap(), Triplet2.GetDeltaRap());
    }

    inline float GetSmallerTripletDeltaRap() const {
        return std::min(Triplet1.GetDeltaRap(), Triplet2.GetDeltaRap());
    }

    inline float GetLargerTripleDeltaPhi() const {
        return std::max(std::abs(Triplet1.GetDeltaPhi()), std::abs(Triplet2.GetDeltaPhi()));
    }

    inline float GetSmallerTripletDeltaPhi() const {
        return std::min(std::abs(Triplet1.GetDeltaPhi()), std::abs(Triplet2.GetDeltaPhi()));
    }

    inline fastjet::PseudoJet GetSextetJet() const {
        return (Triplet1.GetTripletJet() + Triplet2.GetTripletJet());
    }

    inline float GetDeltaRap() const {
        return (std::abs(Triplet1.GetTripletJet().rap() - Triplet2.GetTripletJet().rap()));
    }

    inline float GetDeltaPhi() const {
        return (Triplet1.GetTripletJet().delta_phi_to(Triplet2.GetTripletJet()));
    }

    inline float GetDeltaR() const {
        return Triplet1.GetTripletJet().delta_R(Triplet2.GetTripletJet());
    }

    inline HTriplet GetTriplet1()const {
        return Triplet1;
    }

    inline HTriplet GetTriplet2()const {
        return Triplet2;
    }

protected:

    virtual inline std::string ClassName() const {
        return "Sextet";
    }

private:

    HTriplet Triplet1;

    HTriplet Triplet2;

};

#endif
