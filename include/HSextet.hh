# ifndef HSextet_hh
# define HSextet_hh

# include "Triplet.hh"

/**
 * @brief A sextet of 2 triplets
 *
 */
class analysis::HSextet : public Identification
{

public:

    HSextet();

    HSextet(const Triplet &NewTriple1, const Triplet &NewTriple2);

    ~HSextet();

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

    inline float GetBetterTripleMass(const HParticleId ParticleId)const {
        return std::min(triplet1().GetDeltaMass(ParticleId), triplet2().GetDeltaMass(ParticleId));
    }

    inline float GetWorseTripleMass(const HParticleId ParticleId)const {
        return std::max(triplet1().GetDeltaMass(ParticleId), triplet2().GetDeltaMass(ParticleId));
    }

    inline float GetBetterPairMass(const HParticleId ParticleId)const {
        return std::min(triplet1().doublet().MassDifferenceTo(ParticleId), triplet2().doublet().MassDifferenceTo(ParticleId));
    }

    inline float GetWorsePairMass(const HParticleId ParticleId)const {
        return std::max(triplet1().doublet().MassDifferenceTo(ParticleId), triplet2().doublet().MassDifferenceTo(ParticleId));
    }

    inline float GetBetterJetMass(const HParticleId ParticleId)const {
        return std::min(triplet1().GetJetDeltaMass(ParticleId), triplet2().GetJetDeltaMass(ParticleId));
    }

    inline float GetWorseJetMass(const HParticleId ParticleId)const {
        return std::max(triplet1().GetJetDeltaMass(ParticleId), triplet2().GetJetDeltaMass(ParticleId));
    }

protected:

//     HSextet(HSextetPrivate& NewSextetPrivate) ;

    virtual inline std::string ClassName() const {
        return "HSextet";
    }

private:

  void Settriplet1(const Triplet &Newtriplet1);

  void Settriplet2(const Triplet &Newtriplet2);

  Triplet triplet1M;

  Triplet triplet2M;

};

#endif
