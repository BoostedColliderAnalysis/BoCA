# pragma once

# include "Identification.hh"

namespace analysis {

template <typename Multiplet1, typename Multiplet2>
class Multiplet : public Identification {

public:

    Multiplet() {};

    Multiplet(const Multiplet1 &multiplet_1, const Multiplet2 &multiplet_2) {
        multiplet_1_ = multiplet_1;
        multiplet_2_ = multiplet_2;
    }

    Multiplet(const fastjet::PseudoJet &jet) {
        multiplet_1_ = Multiplet1(jet/2);
        multiplet_2_ = Multiplet2(jet/2);
    }

    inline Multiplet1 SubMultiplet1()const {
        return multiplet_1_;
    }

    inline Multiplet2 SubMultiplet2()const {
        return multiplet_2_;
    }

    inline fastjet::PseudoJet Jet() const {
        return Multiplet1().Jet() + Multiplet2().Jet();
    }

    inline float GetHt() {
        return multiplet_1_.Ht() + multiplet_2_.Ht();
    }

    inline float DeltaPt() const {
        return Multiplet1().Jet().pt() - Multiplet2().Jet().pt();
    }

    inline float Ht() const {
        return Multiplet1().Ht() + Multiplet2().Ht();
    }

    inline float DeltaRap() const {
        float delta_rap = Multiplet1().Jet().rap() - Multiplet2().Jet().rap();
        if (std::abs(delta_rap) > 100) return 0;
        return delta_rap;
    }

    inline float DeltaPhi() const {
        return Multiplet1().Jet().delta_phi_to(Multiplet2().Jet());
    }

    inline float DeltaR() const {
        float delta_r = Multiplet1().Jet().delta_R(Multiplet2().Jet());
        if (std::abs(delta_r) > 100) return 0;
        return delta_r;
    }

    inline float DeltaM() const {
        return Multiplet1().Jet().m() - Multiplet2().Jet().m();
    }

    inline float DeltaHt() const {
        return Multiplet1().Ht() - Multiplet2().Ht();
    }


    inline float MassDifferenceTo(const ParticleId particle_id) const {
        return std::abs(Jet().m() - Mass(particle_id));
    }

    int Dimension() const {
        multiplet_1_.Dimension() + multiplet_2_.Dimension();
    }

    void SetMultiplets(const Multiplet1 &multiplet) {
        multiplet_1_ = multiplet.Jet() / 2;
        multiplet_2_ = multiplet.Jet() / 2;
    }

    void SetMultiplets(const Multiplet1 &multiplet_1,const Multiplet2 &multiplet_2) {
        multiplet_1_=multiplet_1;
        multiplet_2_=multiplet_2;
    }


    void SetJet(const fastjet::PseudoJet &jet) {
        multiplet_1_ = Multiplet1(jet/2);
        multiplet_2_ = Multiplet2(jet/2);
    }

protected:

    Multiplet1 multiplet_1_;

    Multiplet2 multiplet_2_;

private:

};

}
