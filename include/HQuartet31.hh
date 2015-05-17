# ifndef HQuartet31_hh
# define HQuartet31_hh

# include "Triplet.hh"

namespace analysis{
  class HQuartet31Private;
}

class analysis::HQuartet31 : public HTag
{

public:

    HQuartet31();

    HQuartet31(const analysis::Triplet& Newtriplet, const fastjet::PseudoJet& NewSinglet);

    ~HQuartet31();

    Triplet triplet() const;

    fastjet::PseudoJet singlet() const;

    inline fastjet::PseudoJet tripletJet()const{
      return triplet().Jet();
    }

    inline fastjet::PseudoJet Jet() const {
        return (triplet().Jet() + singlet());
    }

    inline float MassDifferenceTo(const HParticleId ParticleId) const {
      return std::abs(Jet().m() - GetParticleMass(ParticleId));
    }

    inline float Ht() const {
      return (triplet().Ht() + singlet().pt());
    }

    inline float DeltaPt() const {
      return (triplet().Jet().pt() - singlet().pt());
    }

    inline float DeltaHt() const {
      return (triplet().Ht() - singlet().pt());
    }

    inline float DeltaR() const {
        return triplet().Jet().delta_R(singlet());
    }
    inline float DeltaRap() const {
        return (triplet().Jet().rap() - singlet().rap());
    }

    inline float DeltaPhi() const {
        return triplet().Jet().delta_phi_to(singlet());
    }

    inline float DeltaM() const {
      return (triplet().Jet().m() - singlet().m());
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
