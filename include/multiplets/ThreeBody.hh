/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "multiplets/Multiplet.hh"
#include "multiplets/Multiplets.hh"
#include "EventShapes.hh"
#include "Vector.hh"

namespace boca
{

template <typename Multiplet_1_, typename Multiplet_2_, typename Multiplet_3_>
class ThreeBody : public Multiplet
{

public:

    ThreeBody() {};

    ThreeBody(Multiplet_1_ const& multiplet_1, Multiplet_2_ const& multiplet_2, Multiplet_3_ const& multiplet_3) {
        SetMultiplets(multiplet_1, multiplet_2, multiplet_3);
        event_shapes_.Reset(Jets());
    }

    void SetMultiplets(Multiplet_1_ const& multiplet_1, Multiplet_2_ const& multiplet_2, Multiplet_3_ const& multiplet_3) {
        multiplet_1_ = multiplet_1;
        multiplet_2_ = multiplet_2;
        multiplet_3_ = multiplet_3;
        SetBdt((multiplet_1_.Bdt() + multiplet_2_.Bdt() + multiplet_3_.Bdt()) / 3);
    }

    Multiplet_1_ const& Multiplet1() const {
        return multiplet_1_;
    }

    Multiplet_2_ const& Multiplet2() const {
        return multiplet_2_;
    }

    Multiplet_3_ const& Multiplet3() const {
        return multiplet_3_;
    }

    template <typename Multiplet>
    bool Overlap(Multiplet const& multiplet) const {
        return multiplet.Overlap(multiplet_1_) || multiplet.Overlap(multiplet_2_) || multiplet.Overlap(multiplet_3_);
    }

    bool Overlap(boca::Singlet const& singlet) const {
        return multiplet_1_.Overlap(singlet) || multiplet_2_.Overlap(singlet) || multiplet_3_.Overlap(singlet);
    }

    bool Overlap(boca::Jet const& jet) const {
        return multiplet_1_.Overlap(jet) || multiplet_2_.Overlap(jet) || multiplet_3_.Overlap(jet);
    }

    bool Overlap() const {
        return multiplet_1_.Overlap(multiplet_2_) || multiplet_1_.Overlap(multiplet_3_) || multiplet_2_.Overlap(multiplet_3_);
    }

    boca::Singlet ConstituentJet12() const {
        return constituent_jet_12_.Get([this]() {
            return GetConstituentJet12();
        });
    }

    boca::Singlet ConstituentJet23() const {
        return constituent_jet_23_.Get([this]() {
            return GetConstituentJet23();
        });
    }

    boca::Singlet ConstituentJet13() const {
        return constituent_jet_13_.Get([this]() {
            return GetConstituentJet13();
        });
    }

    boca::Jet Jet12() const {
        return jet_12_.Get([this]() {
            return GetJet12();
        });
    }

    boca::Jet Jet23() const {
        return jet_23_.Get([this]() {
            return GetJet23();
        });
    }

    boca::Jet Jet13() const {
        return jet_13_.Get([this]() {
            return GetJet13();
        });
    }

    std::vector<boca::Jet> Jets() const {
        return Combine(Multiplet1().Jets(), Multiplet2().Jets(), Multiplet3().Jets());
    }

    Momentum DeltaPt() const {
        return boca::DeltaPt(Multiplet1(), Multiplet2());
    }

    Momentum DeltaPt23() const {
        return boca::DeltaPt(Multiplet2(), Multiplet3());
    }

    Momentum DeltaPt13() const {
        return boca::DeltaPt(Multiplet1(), Multiplet3());
    }

    Momentum Ht() const {
        return Ht12() + Multiplet3().Ht();
    }

    Momentum Ht12() const {
        return boca::Ht(Multiplet1(), Multiplet2());
    }

    Momentum Ht23() const {
        return boca::Ht(Multiplet2(), Multiplet3());
    }

    Momentum Ht13() const {
        return boca::Ht(Multiplet1(), Multiplet3());
    }

    Angle DeltaRap() const {
        return boca::DeltaRap(Multiplet1(), Multiplet2());
    }

    Angle DeltaRap23() const {
        return boca::DeltaRap(Multiplet2(), Multiplet3());
    }

    Angle DeltaRap13() const {
        return boca::DeltaRap(Multiplet1(), Multiplet3());
    }

    Angle DeltaPhi() const {
        return boca::DeltaPhi(Multiplet1(), Multiplet2());
    }

    Angle DeltaPhi23() const {
        return boca::DeltaPhi(Multiplet2(), Multiplet3());
    }

    Angle DeltaPhi13() const {
        return boca::DeltaPhi(Multiplet1(), Multiplet3());
    }

    Angle DeltaR() const {
        return boca::DeltaR(Multiplet1(), Multiplet2());
    }

    Angle DeltaR23() const {
        return boca::DeltaR(Multiplet2(), Multiplet3());
    }

    Angle DeltaR13() const {
        return boca::DeltaR(Multiplet1(), Multiplet3());
    }

    boca::Mass DeltaM() const {
        return boca::DeltaM(Multiplet1(), Multiplet2());
    }

    boca::Mass DeltaM23() const {
        return boca::DeltaM(Multiplet2(), Multiplet3());
    }

    boca::Mass DeltaM13() const {
        return boca::DeltaM(Multiplet1(), Multiplet3());
    }

    Momentum DeltaHt() const {
        return boca::DeltaHt(Multiplet1(), Multiplet2());
    }

    Momentum DeltaHt23() const {
        return boca::DeltaHt(Multiplet2(), Multiplet3());
    }

    Momentum DeltaHt13() const {
        return boca::DeltaHt(Multiplet1(), Multiplet3());
    }

    double Rho() const {
        return boca::Rho(Multiplet1(), Multiplet2(), Jet12());
    }

    double Rho23() const {
        return boca::Rho(Multiplet2(), Multiplet3(), Jet23());
    }

    double Rho13() const {
        return boca::Rho(Multiplet1(), Multiplet3(), Jet13());
    }

    int Charge() const {
        return Charge12() + Multiplet3().Charge();
    }

    int Charge12() const {
        return boca::Charge(Multiplet1(), Multiplet2());
    }

    int Charge23() const {
        return boca::Charge(Multiplet2(), Multiplet3());
    }

    int Charge13() const {
        return boca::Charge(Multiplet1(), Multiplet3());
    }

    Angle Pull12() const {
        return boca::Pull(Multiplet1(), Multiplet2());
    }

    Angle Pull21() const {
        return boca::Pull(Multiplet2(), Multiplet1());
    }

    Angle Pull23() const {
        return boca::Pull(Multiplet2(), Multiplet3());
    }

    Angle Pull32() const {
        return boca::Pull(Multiplet3(), Multiplet2());
    }

    Angle Pull13() const {
        return boca::Pull(Multiplet1(), Multiplet3());
    }

    Angle Pull31() const {
        return boca::Pull(Multiplet3(), Multiplet1());
    }

    double Dipolarity() const {
        return boca::Dipolarity(Multiplet1(), Multiplet2(), ConstituentJet12());
    }

    double Dipolarity23() const {
        return boca::Dipolarity(Multiplet2(), Multiplet3(), ConstituentJet23());
    }

    double Dipolarity13() const {
        return boca::Dipolarity(Multiplet1(), Multiplet3(), ConstituentJet13());
    }

    void SetVetoBdt(double bdt) {
        veto_bdt_ = bdt;
    }

    double VetoBdt() const {
        return veto_bdt_;
    }

    boca::EventShapes EventShapes() const {
        return event_shapes_;
    }

protected:

    void SetMultiplet1(Multiplet_1_ const& multiplet_1) {
        multiplet_1_ = multiplet_1;
    }

    void SetMultiplet2(Multiplet_2_ const& multiplet_2) {
        multiplet_2_ = multiplet_2;
    }

    void SetMultiplet3(Multiplet_3_ const& multiplet_3) {
        multiplet_3_ = multiplet_3;
    }

private:

    boca::Jet GetJet() const override {
        return Join(Jet12(), Multiplet3());
    }

    boca::Jet GetJet12() const {
        return Join(Multiplet1(), Multiplet2());
    }

    boca::Jet GetJet23() const {
        return Join(Multiplet2(), Multiplet3());
    }

    boca::Jet GetJet13() const {
        return Join(Multiplet1(), Multiplet3());
    }

    Singlet GetConstituentJet() const override {
        return JoinConstituents(ConstituentJet12(), Multiplet3());
    }

    Singlet GetConstituentJet12() const {
        return JoinConstituents(Multiplet1(), Multiplet2());
    }

    Singlet GetConstituentJet23() const {
        return JoinConstituents(Multiplet2(), Multiplet3());
    }

    Singlet GetConstituentJet13() const {
        return JoinConstituents(Multiplet1(), Multiplet3());
    }

    Mutable<boca::Jet> jet_12_;

    Mutable<boca::Jet> jet_23_;

    Mutable<boca::Jet> jet_13_;

    Mutable<boca::Singlet> constituent_jet_12_;

    Mutable<boca::Singlet> constituent_jet_23_;

    Mutable<boca::Singlet> constituent_jet_13_;

    boca::EventShapes event_shapes_;

    double veto_bdt_;

    Multiplet_1_ multiplet_1_;

    Multiplet_2_ multiplet_2_;

    Multiplet_3_ multiplet_3_;

};

}
