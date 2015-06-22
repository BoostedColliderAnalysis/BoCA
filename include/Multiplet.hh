# pragma once

# include "Singlet.hh"

namespace analysis
{

template <typename Multiplet_1, typename Multiplet_2>
class Multiplet : public Identification
{

public:

    Multiplet() {
        empty_ = true;
    };

    Multiplet(const Multiplet_1 &multiplet_1, const Multiplet_2 &multiplet_2) {
        SetMultiplets(multiplet_1, multiplet_2);
    }

    Multiplet(const fastjet::PseudoJet &jet) {
        SetJet(jet);
    }

    void SetMultiplets(const Multiplet_1 &multiplet_1, const Multiplet_2 &multiplet_2) {
        multiplet_1_ = multiplet_1;
        multiplet_2_ = multiplet_2;
        SetBdt((multiplet_1_.Bdt() + multiplet_2_.Bdt()) / 2);
        empty_ = false;
    }

    void SetJet(const fastjet::PseudoJet &jet) {
        multiplet_1_ = Multiplet_1(jet / 2);
        multiplet_2_ = Multiplet_2(jet / 2);
        SetBdt((multiplet_1_.Bdt() + multiplet_2_.Bdt()) / 2);
        empty_ = false;
    }

     Multiplet_1 &Multiplet1() const {
        return multiplet_1_;
    }

     Multiplet_2 &Multiplet2() const {
        return multiplet_2_;
    }

    template <typename Multiplet3>
    bool Overlap(const Multiplet3 &multiplet) const {
        return (multiplet.Overlap(multiplet_1_) | multiplet.Overlap(multiplet_2_));
    }

    bool Overlap(const Singlet &singlet) const {
        return (multiplet_1_.Overlap(singlet) | multiplet_2_.Overlap(singlet));
    }

    bool Overlap(const fastjet::PseudoJet &jet) const {
        return (multiplet_1_.Overlap(jet) | multiplet_2_.Overlap(jet));
    }

    bool Overlap() const {
        return multiplet_1_.Overlap(multiplet_2_);
    }

    bool Coincides(const fastjet::PseudoJet &jet)const {
        return (Jet().delta_R(jet) < DetectorGeometry().JetConeSize);
    }

     fastjet::PseudoJet Jet() const {
        return Multiplet1().Jet() + Multiplet2().Jet();
    }

     float DeltaPt() const {
        return Multiplet1().Jet().pt() - Multiplet2().Jet().pt();
    }

     float Ht() const {
        return Multiplet1().Ht() + Multiplet2().Ht();
    }

     float DeltaRap() const {
        float delta_rap = Multiplet1().Jet().rap() - Multiplet2().Jet().rap();
        if (std::abs(delta_rap) > 100) return 0;
        return delta_rap;
    }

     float DeltaPhi() const {
        return Multiplet1().Jet().delta_phi_to(Multiplet2().Jet());
    }

     float DeltaR() const {
        float delta_r = Multiplet1().Jet().delta_R(Multiplet2().Jet());
        if (std::abs(delta_r) > 100) return 0;
        return delta_r;
    }

     float DeltaM() const {
        return Multiplet1().Jet().m() - Multiplet2().Jet().m();
    }

     float DeltaHt() const {
        return Multiplet1().Ht() - Multiplet2().Ht();
    }

     float Rho() const {
        if (Jet().pt() < DetectorGeometry().MinCellPt || DeltaR() < DetectorGeometry().MinCellResolution) return 0;
        return Jet().m() / Jet().pt() / DeltaR() * 2;
    }

     float MassDifferenceTo(const ParticleId particle_id) const {
        return std::abs(Jet().m() - Mass(particle_id));
    }

     int Charge() const {
        return sgn(Multiplet1().Charge() + Multiplet2().Charge());
    }

    bool IsEmpty() const {
        return empty_;
    }

protected:

    virtual  std::string ClassName() const {
        return "Multiplet";
    }

    void SetMultiplet1(const Multiplet_1 multiplet_1) {
        multiplet_1_ = multiplet_1;
    }

    void SetMultiplet2(const Multiplet_2 multiplet_2) {
        multiplet_2_ = multiplet_2;
    }

private:

    mutable Multiplet_1 multiplet_1_;

    mutable Multiplet_2 multiplet_2_;

    bool empty_ = false;

};

}
