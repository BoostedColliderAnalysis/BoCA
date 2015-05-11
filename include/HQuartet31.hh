# ifndef HQuartet31_hh
# define HQuartet31_hh

# include "Triplet.hh"

namespace hanalysis{
  class HQuartet31Private;
}

class hanalysis::HQuartet31 : public HTag
{

public:

    HQuartet31();

    HQuartet31(const hanalysis::Triplet& Newtriplet, const fastjet::PseudoJet& NewSinglet);

    ~HQuartet31();

    Triplet triplet() const;

    fastjet::PseudoJet Singlet() const;

    inline fastjet::PseudoJet tripletJet()const{
      return triplet().Jet();
    }

    inline fastjet::PseudoJet Jet() const {
        return (triplet().Jet() + Singlet());
    }

    inline float MassDifferenceTo(const HParticleId ParticleId) const {
      return std::abs(Jet().m() - GetParticleMass(ParticleId));
    }

    inline float Ht() const {
      return (triplet().Ht() + Singlet().pt());
    }

    inline float DeltaPt() const {
      return (triplet().Jet().pt() - Singlet().pt());
    }

    inline float DeltaHt() const {
      return (triplet().Ht() - Singlet().pt());
    }

    inline float DeltaR() const {
        return triplet().Jet().delta_R(Singlet());
    }
    inline float DeltaRap() const {
        return (triplet().Jet().rap() - Singlet().rap());
    }

    inline float DeltaPhi() const {
        return triplet().Jet().delta_phi_to(Singlet());
    }

    inline float DeltaM() const {
      return (triplet().Jet().m() - Singlet().m());
    }

protected:

    virtual inline std::string ClassName() const {
        return "HQuartet31";
    }

private:

  //     HQuartet31(HQuartet31Private& NewQuartet31Private);

  void Settriplet(const Triplet &Newtriplet);

  void SetSinglet(const fastjet::PseudoJet &NewSinglet);

  Triplet tripletM;

  fastjet::PseudoJet SingletM;

};

#endif
