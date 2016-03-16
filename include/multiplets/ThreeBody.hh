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

template <typename Multiplet_1, typename Multiplet_2, typename Multiplet_3>
class ThreeBody : public Multiplet
{

public:

    ThreeBody() {};

    ThreeBody(Multiplet_1 const& multiplet_1, Multiplet_2 const& multiplet_2, const Multiplet_3& multiplet_3) {
        SetMultiplets(multiplet_1, multiplet_2, multiplet_3);
        event_shapes_.Reset(Jets());
    }

    void SetMultiplets(Multiplet_1 const& multiplet_1, Multiplet_2 const& multiplet_2, const Multiplet_3& multiplet_3) {
        multiplet_1_ = multiplet_1;
        multiplet_2_ = multiplet_2;
        multiplet_3_ = multiplet_3;
        SetBdt((multiplet_1_.Bdt() + multiplet_2_.Bdt() + multiplet_3_.Bdt()) / 3);
    }

    Multiplet_1 const& Multiplet1() const {
        return multiplet_1_;
    }

    Multiplet_2 const& Multiplet2() const {
        return multiplet_2_;
    }

    const Multiplet_3& Multiplet3() const {
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

    boca::Singlet const& Singlet12() const {
        if (!has_singlet_12_) SetSinglet12(MakeSinglet(Multiplet1(), Multiplet2()));
        return singlet_12_;
    }

    boca::Singlet const& Singlet23() const {
        if (!has_singlet_23_) SetSinglet23(MakeSinglet(Multiplet2(), Multiplet3()));
        return singlet_23_;
    }

    boca::Singlet const& Singlet13() const {
        if (!has_singlet_13_) SetSinglet13(MakeSinglet(Multiplet1(), Multiplet3()));
        return singlet_13_;
    }

    boca::Jet const& Jet12() const {
        if (!has_jet_12_) SetJet12(MakeJet(Multiplet1(), Multiplet2()));
        return jet_12_;
    }

    boca::Jet const& Jet23() const {
        if (!has_jet_23_) SetJet23(MakeJet(Multiplet2(), Multiplet3()));
        return jet_23_;
    }

    boca::Jet const& Jet13() const {
        if (!has_jet_13_) SetJet13(MakeJet(Multiplet1(), Multiplet3()));
        return jet_13_;
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
        return boca::Charge(Multiplet1(), Multiplet2());
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
        return boca::Dipolarity(Multiplet1(), Multiplet2(), Jet12());
    }

    double Dipolarity23() const {
        return boca::Dipolarity(Multiplet2(), Multiplet3(), Jet23());
    }

    double Dipolarity13() const {
        return boca::Dipolarity(Multiplet1(), Multiplet3(), Jet13());
    }

    void SetVetoBdt(double bdt) {
        veto_bdt_ = bdt;
    }

    double VetoBdt() const {
        return veto_bdt_;
    }

    boca::EventShapes const& EventShapes() const {
        return event_shapes_;
    }

protected:

    void SetMultiplet1(const Multiplet_1 multiplet_1) {
        multiplet_1_ = multiplet_1;
    }

    void SetMultiplet2(const Multiplet_2 multiplet_2) {
        multiplet_2_ = multiplet_2;
    }

    void SetMultiplet3(const Multiplet_3 multiplet_3) {
        multiplet_3_ = multiplet_3;
    }

private:

    void SetPlainJet() const override {
        Multiplet::SetPlainJet(MakeJet(Jet12(), Multiplet3()));
    }

    void SetJet12(boca::Jet const& jet) const {
        jet_12_ = jet;
        has_jet_12_ = true;
    }

    void SetJet23(boca::Jet const& jet) const {
        jet_23_ = jet;
        has_jet_23_ = true;
    }

    void SetJet13(boca::Jet const& jet) const {
        jet_13_ = jet;
        has_jet_13_ = true;
    }

    void SetSinglet() const override {
        Multiplet::SetSinglet(MakeSinglet(Singlet12(), Multiplet3()));
    }

    void SetSinglet12(boca::Singlet const& singlet) const {
        singlet_12_ = singlet;
        has_singlet_12_ = true;
    }

    void SetSinglet23(boca::Singlet const& singlet) const {
        singlet_23_ = singlet;
        has_singlet_23_ = true;
    }

    void SetSinglet13(boca::Singlet const& singlet) const {
        singlet_13_ = singlet;
        has_singlet_13_ = true;
    }

    mutable boca::Jet jet_12_;

    mutable boca::Jet jet_23_;

    mutable boca::Jet jet_13_;

    mutable boca::Singlet singlet_12_;

    mutable boca::Singlet singlet_23_;

    mutable boca::Singlet singlet_13_;

    mutable bool has_jet_12_ = false;

    mutable bool has_jet_23_ = false;

    mutable bool has_jet_13_ = false;

    mutable bool has_singlet_12_ = false;

    mutable bool has_singlet_23_ = false;

    mutable bool has_singlet_13_ = false;

    boca::EventShapes event_shapes_;

    double veto_bdt_;

    Multiplet_1 multiplet_1_;

    Multiplet_2 multiplet_2_;

    Multiplet_3 multiplet_3_;

};

}
