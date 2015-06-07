# pragma once

# include "Quintet.hh"

namespace toppartner
{

class Quattuordecuplet : public analysis::Identification
{

public:

    Quattuordecuplet() {}

    Quattuordecuplet(const analysis::Quintet &quintet_1, const analysis::Quintet &quintet_2, const analysis::Doublet & doublet_1, const analysis::Doublet &doublet_2);

    inline analysis::Doublet Doublet_1()const {
        return doublet_1_;
    }

    inline analysis::Doublet Doublet_2()const {
        return doublet_2_;
    }

    inline analysis::Quintet Quintet_1()const {
      return quintet_1_;
    }

    inline analysis::Quintet Quintet_2()const {
      return quintet_2_;
    }

    inline fastjet::PseudoJet Jet() const {
        return doublet_1_.Jet() + doublet_2_.Jet() + quintet_1_.Jet() + quintet_2_.Jet();
    }

    inline float Ht() const {
        return doublet_1_.Ht() + doublet_2_.Ht() + quintet_1_.Ht() + quintet_2_.Ht();
    }

    inline float DeltaHt() const {
      //TODO implement a more meaningfull variable
      return doublet_2_.Ht() - doublet_1_.Ht();
    }

    inline float DeltaPt() const {
      //TODO implement a more meaningfull variable
        return doublet_2_.Jet().pt() - doublet_1_.Jet().pt();
    }

    inline float DeltaRap() const {
      //TODO implement a more meaningfull variable
        return std::abs(doublet_2_.Jet().rap() - doublet_1_.Jet().rap());
    }

    inline float DeltaPhi() const {
      //TODO implement a more meaningfull variable
        return doublet_2_.Jet().delta_phi_to(doublet_1_.Jet());
    }

    inline float DeltaR() const {
      //TODO implement a more meaningfull variable
      return doublet_2_.Jet().delta_R(doublet_1_.Jet());
    }

    inline float DeltaM() const {
      //TODO implement a more meaningfull variable
      return doublet_2_.Jet().m() - doublet_1_.Jet().m();
    }

    inline float MassDifferenceTo(const ParticleId particle_id) const {
        return std::abs(Jet().m() - Mass(particle_id));
    }

    bool overlap() const;

    //FIXME only two bdt, not four !!
    analysis::Quintet SubMultiplet1() const {
      return quintet_1_;
    }

    analysis::Quintet SubMultiplet2() const {
      return quintet_2_;
    }

protected:

    virtual inline std::string ClassName() const {
        return "Quattuordecuplet";
    }

private:

  analysis::Doublet doublet_1_;

  analysis::Doublet doublet_2_;

  analysis::Quintet quintet_1_;

  analysis::Quintet quintet_2_;

};

}
