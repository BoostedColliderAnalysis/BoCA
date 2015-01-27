# ifndef HQuartet31_hh
# define HQuartet31_hh

# include "HTriplet.hh"

namespace hanalysis{
  class HQuartet31Private;
}

class hanalysis::HQuartet31 : public HTag
{

public:

    HQuartet31();

    HQuartet31(const hanalysis::HTriplet& NewTriplet, const fastjet::PseudoJet& NewSinglet);

    ~HQuartet31();

    HTriplet Triplet() const;

    fastjet::PseudoJet Singlet() const;

    inline fastjet::PseudoJet TripletJet()const{
      return Triplet().Jet();
    }

    inline fastjet::PseudoJet Jet() const {
        return (Triplet().Jet() + Singlet());
    }

    inline float MassDifferenceTo(const HParticleId ParticleId) const {
      return std::abs(Jet().m() - GetParticleMass(ParticleId));
    }

    inline float Ht() const {
      return Triplet().Ht() + Singlet().pt();
    }

    inline float DeltaPt() const {
      return Triplet().Jet().pt() - Singlet().pt();
    }

    inline float DeltaR() const {
        return Triplet().Jet().delta_R(Singlet());
    }
    inline float DeltaRap() const {
        return Triplet().Jet().rap() - Singlet().rap();
    }

    inline float DeltaPhi() const {
        return Triplet().Jet().delta_phi_to(Singlet());
    }

    inline float DeltaM() const {
      return Triplet().Jet().m() - Singlet().m();
    }

protected:

    virtual inline std::string ClassName() const {
        return "HQuartet31";
    }

private:

    HQuartet31(HQuartet31Private& NewQuartet31Private);

};

#endif
