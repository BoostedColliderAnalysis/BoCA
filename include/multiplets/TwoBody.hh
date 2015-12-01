/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "multiplets/Singlet.hh"
#include "multiplets/Multiplet.hh"
#include "physics/Particles.hh"

namespace boca
{

template <typename Multiplet_1, typename Multiplet_2>
class TwoBody : public Multiplet
{

public:

    TwoBody() {};

    TwoBody(Multiplet_1 const& multiplet_1, Multiplet_2 const& multiplet_2) {
        SetMultiplets(multiplet_1, multiplet_2);
    }

    TwoBody(boca::Jet const& jet) {
        SetJet(jet);
    }

    void SetMultiplets(Multiplet_1 const& multiplet_1, Multiplet_2 const& multiplet_2) {
        multiplet_1_ = multiplet_1;
        multiplet_2_ = multiplet_2;
        if (multiplet_1.Bdt() != InitialValue() && multiplet_2.Bdt() != InitialValue()) SetBdt(multiplet_1.Bdt(), multiplet_2.Bdt());
        else if (multiplet_1.Bdt() != InitialValue()) SetBdt(multiplet_1.Bdt());
        else if (multiplet_2.Bdt() != InitialValue()) SetBdt(multiplet_2.Bdt());
    }

    void SetJet(boca::Jet jet) {
        jet.Info().SetSubStructure(false);
        multiplet_1_ = Multiplet_1(jet / 2);
        multiplet_2_ = Multiplet_2(jet / 2);
        SetBdt((multiplet_1_.Bdt() + multiplet_2_.Bdt()) / 2);
    }

    Multiplet_1& Multiplet1() {
        return multiplet_1_;
    }

    Multiplet_1 const& Multiplet1() const {
        return multiplet_1_;
    }

    Multiplet_2& Multiplet2() {
        return multiplet_2_;
    }

    Multiplet_2 const& Multiplet2() const {
        return multiplet_2_;
    }

    template <typename Multiplet3>
    bool Overlap(Multiplet3 const& multiplet) const {
        return (multiplet.Overlap(multiplet_1_) || multiplet.Overlap(multiplet_2_));
    }

    bool Overlap(boca::Singlet const& singlet) const {
        return (multiplet_1_.Overlap(singlet) || multiplet_2_.Overlap(singlet));
    }

    bool Overlap(boca::Jet const& jet) const {
        return (multiplet_1_.Overlap(jet) || multiplet_2_.Overlap(jet));
    }

    bool Overlap() const {
        return multiplet_1_.Overlap(multiplet_2_);
    }

    void SetPlainJet() const override {
        Multiplet::SetPlainJet(Multiplet::Jet(Multiplet1().Jet(), Multiplet2().Jet()));
    }

    std::vector<boca::Jet> Jets() const override  {
        return Join(Multiplet1().Jets(), Multiplet2().Jets());
    }

    Momentum DeltaPt() const {
        return (Multiplet1().Pt() - Multiplet2().Pt());
    }

    Momentum Ht() const override {
        return Multiplet::Ht(Multiplet1(), Multiplet2());
    }

    Angle DeltaRap() const {
        return Multiplet::DeltaRap(Multiplet1(), Multiplet2());
    }

    Angle DeltaPhi() const {
        return Multiplet::DeltaPhi(Multiplet1(), Multiplet2());
    }

    Angle DeltaR() const {
        return Multiplet::DeltaR(Multiplet1(), Multiplet2());
    }

    boca::Mass DeltaM() const {
        return Multiplet::DeltaM(Multiplet1(), Multiplet2());
    }

    Momentum DeltaHt() const {
        return Multiplet::DeltaHt(Multiplet1(), Multiplet2());
    }

    float Rho() const {
        return Multiplet::Rho(Multiplet1(), Multiplet2(), Jet());
    }

    boca::Mass MassDifferenceTo(Id id) const {
        return boost::units::abs(Mass() - MassOf(id));
    }

    int Charge() const override {
        return Multiplet::Charge(Multiplet1(), Multiplet2());
    }

    void SetSinglet() const override {
        Multiplet::SetSinglet(Multiplet::Singlet(Multiplet1().singlet(), Multiplet2().singlet()));
    }

    Angle Pull12() const {
        return Multiplet::Pull(Multiplet1(), Multiplet2());
    }

    Angle Pull21() const {
        return Multiplet::Pull(Multiplet2(), Multiplet1());
    }

    float Dipolarity() const {
        return Multiplet::Dipolarity(Multiplet1(), Multiplet2(), singlet());
    }

    float BottomBdt() const final {
        return Multiplet::BottomBdt(Multiplet1(), Multiplet2());
    };

protected:

    void SetMultiplet1(Multiplet_1 const& multiplet_1) {
        multiplet_1_ = multiplet_1;
    }

    void SetMultiplet2(Multiplet_2 const& multiplet_2) {
        multiplet_2_ = multiplet_2;
    }

private:

    Multiplet_1 multiplet_1_;

    Multiplet_2 multiplet_2_;

};

}
