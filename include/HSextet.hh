# ifndef HSextet_hh
# define HSextet_hh

# include "HTriplet.hh"

class HSextetPrivate;

/**
 * @brief A sextet formed from 2 triplets
 *
 */
class hanalysis::HSextet : public HTag
{

public:

    HSextet() {
//         Bdt = -10;
    }

    HSextet(const HTriplet &NewTriple1, const HTriplet &NewTriple2);

    ~HSextet();

    HTriplet Triplet1()const;

    HTriplet Triplet2()const;

    inline fastjet::PseudoJet Triplet1Jet()const {
        return Triplet1().Jet();
    }
    inline fastjet::PseudoJet Triplet2Jet()const {
        return Triplet2().Jet();
    }

    inline fastjet::PseudoJet Jet() const {
        return Triplet1Jet() + Triplet2Jet();
    }

    inline float Ht() const {
        return Triplet1().Ht() + Triplet2().Ht();
    }

    inline float DeltaPt()const {
        return Triplet1Jet().pt() - Triplet2Jet().pt();
    }

    inline float DeltaRap() const {
        return Triplet1Jet().rap() - Triplet2Jet().rap();
    }

    inline float DeltaPhi() const {
        return Triplet1Jet().delta_phi_to(Triplet2Jet());
    }

    inline float DeltaR() const {
        return Triplet1Jet().delta_R(Triplet2Jet());
    }

    inline float GetLargerTripletDeltaR() const {
        return std::max(Triplet1().DeltaR(), Triplet2().DeltaR());
    }

    inline float GetSmallerTripletDeltaR() const {
        return std::min(Triplet1().DeltaR(), Triplet2().DeltaR());
    }

    inline float GetLargerTripletDeltaRap() const {
        return std::max(Triplet1().DeltaRap(), Triplet2().DeltaRap());
    }

    inline float GetSmallerTripletDeltaRap() const {
        return std::min(Triplet1().DeltaRap(), Triplet2().DeltaRap());
    }

    inline float GetLargerTripleDeltaPhi() const {
        return std::max(std::abs(Triplet1().DeltaPhi()), std::abs(Triplet2().DeltaPhi()));
    }

    inline float GetSmallerTripletDeltaPhi() const {
        return std::min(std::abs(Triplet1().DeltaPhi()), std::abs(Triplet2().DeltaPhi()));
    }

    inline float GetBetterTripleMass(const HParticleId ParticleId)const {
        return std::min(Triplet1().GetDeltaMass(ParticleId), Triplet2().GetDeltaMass(ParticleId));
    }

    inline float GetWorseTripleMass(const HParticleId ParticleId)const {
        return std::max(Triplet1().GetDeltaMass(ParticleId), Triplet2().GetDeltaMass(ParticleId));
    }

    inline float GetBetterPairMass(const HParticleId ParticleId)const {
        return std::min(Triplet1().Doublet().MassDifferenceTo(ParticleId), Triplet2().Doublet().MassDifferenceTo(ParticleId));
    }

    inline float GetWorsePairMass(const HParticleId ParticleId)const {
        return std::max(Triplet1().Doublet().MassDifferenceTo(ParticleId), Triplet2().Doublet().MassDifferenceTo(ParticleId));
    }

    inline float GetBetterJetMass(const HParticleId ParticleId)const {
        return std::min(Triplet1().GetJetDeltaMass(ParticleId), Triplet2().GetJetDeltaMass(ParticleId));
    }

    inline float GetWorseJetMass(const HParticleId ParticleId)const {
        return std::max(Triplet1().GetJetDeltaMass(ParticleId), Triplet2().GetJetDeltaMass(ParticleId));
    }

protected:

    HSextet(HSextetPrivate& NewSextetPrivate) ;

    virtual inline std::string ClassName() const {
        return "HSextet";
    }

private:

//     HTriplet Triplet1;

//     HTriplet Triplet2;

};

#endif
