# pragma once

# include "Triplet.hh"



namespace analysis{

class Quartet31 : public Identification
{

public:

    Quartet31(){};

    Quartet31(const analysis::Triplet &triplet, const fastjet::PseudoJet &singlet);

    Triplet triplet() const;

    fastjet::PseudoJet singlet() const;

    bool overlap() const;

    inline fastjet::PseudoJet tripletJet()const{
      return triplet().Jet();
    }

    inline fastjet::PseudoJet Jet() const {
        return (triplet().Jet() + singlet());
    }

    inline float MassDifferenceTo(const ParticleId particle_id) const {
      return std::abs(Jet().m() - Mass(particle_id));
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
        return "Quartet31";
    }

private:

  void Settriplet(const analysis::Triplet &triplet);

  void SetSinglet(const fastjet::PseudoJet &singlet);

  Triplet triplet_;

  fastjet::PseudoJet singlet_;

};

}
