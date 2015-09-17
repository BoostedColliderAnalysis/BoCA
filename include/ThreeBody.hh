/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "Singlet.hh"
#include "Multiplet.hh"

namespace boca
{

template <typename Multiplet_1, typename Multiplet_2, typename Multiplet_3>
class ThreeBody : public Multiplet
{

public:

    ThreeBody() {};

    ThreeBody(Multiplet_1 const& multiplet_1, Multiplet_2 const& multiplet_2, const Multiplet_3& multiplet_3) {
        SetMultiplets(multiplet_1, multiplet_2, multiplet_3);
    }

    ThreeBody(fastjet::PseudoJet const& jet) {
        SetJet(jet);
    }

    void SetMultiplets(Multiplet_1 const& multiplet_1, Multiplet_2 const& multiplet_2, const Multiplet_3& multiplet_3) {
        multiplet_1_ = multiplet_1;
        multiplet_2_ = multiplet_2;
        multiplet_3_ = multiplet_3;
        SetBdt((multiplet_1_.Bdt() + multiplet_2_.Bdt() + multiplet_3_.Bdt()) / 3);
    }

    void SetJet(fastjet::PseudoJet const& jet) {
        static_cast<JetInfo&>(*jet.user_info_shared_ptr().get()).SetSubStructure(false);
        multiplet_1_ = Multiplet_1(jet / 3);
        multiplet_2_ = Multiplet_2(jet / 3);
        multiplet_3_ = Multiplet_3(jet / 3);
        SetBdt((multiplet_1_.Bdt() + multiplet_2_.Bdt() + multiplet_2_.Bdt()) / 3);
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

    bool Overlap(fastjet::PseudoJet const& jet) const {
        return multiplet_1_.Overlap(jet) || multiplet_2_.Overlap(jet) || multiplet_3_.Overlap(jet);
    }

    bool Overlap() const {
        return multiplet_1_.Overlap(multiplet_2_) || multiplet_1_.Overlap(multiplet_3_) || multiplet_2_.Overlap(multiplet_3_);
    }

    void SetSinglet() const override {
      Multiplet::SetSinglet(Multiplet::Singlet(Singlet12(), Multiplet3().singlet()));
    }

    boca::Singlet const& Singlet12() const {
      if (!has_singlet_12_) SetSinglet12(Multiplet::Singlet(Multiplet1().singlet(), Multiplet2().singlet()));
      return singlet_12_;
    }

    boca::Singlet const& Singlet23() const {
      if (!has_singlet_23_) SetSinglet23(Multiplet::Singlet(Multiplet2().singlet(), Multiplet3().singlet()));
      return singlet_23_;
    }

    boca::Singlet const& Singlet13() const {
      if (!has_singlet_13_) SetSinglet13(Multiplet::Singlet(Multiplet1().singlet(), Multiplet3().singlet()));
      return singlet_13_;
    }

    void SetPlainJet() const override {
        Multiplet::SetPlainJet(Multiplet::Jet(Jet12(), Multiplet3().Jet()));
    }

    fastjet::PseudoJet const& Jet12() const {
      if (!has_jet_12_) SetJet12(Multiplet::Jet(Multiplet1().Jet(), Multiplet2().Jet()));
      return jet_12_;
    }

    fastjet::PseudoJet const& Jet23() const {
      if (!has_jet_23_) SetJet23(Multiplet::Jet(Multiplet2().Jet(), Multiplet3().Jet()));
      return jet_23_;
    }

    fastjet::PseudoJet const& Jet13() const {
      if (!has_jet_13_) SetJet13(Multiplet::Jet(Multiplet1().Jet(), Multiplet3().Jet()));
      return jet_13_;
    }

    boca::Jets Jets() const override {
        return Join(Multiplet1().Jets(), Multiplet2().Jets(), Multiplet3().Jets());
    }

    float DeltaPt() const {
        return Multiplet::DeltaPt(Multiplet1(), Multiplet2());
    }

    float DeltaPt23() const {
        return Multiplet::DeltaPt(Multiplet2(), Multiplet3());
    }

    float DeltaPt13() const {
        return Multiplet::DeltaPt(Multiplet1(), Multiplet3());
    }

    float Ht() const override {
        return Ht12() + Multiplet3().Ht();
    }

    float Ht12() const {
        return Multiplet::Ht(Multiplet1(), Multiplet2());
    }

    float Ht23() const {
        return Multiplet::Ht(Multiplet2(), Multiplet3());
    }

    float Ht13() const {
        return Multiplet::Ht(Multiplet1(), Multiplet3());
    }

    float DeltaRap() const {
        return Multiplet::DeltaRap(Multiplet1(), Multiplet2());
    }

    float DeltaRap23() const {
        return Multiplet::DeltaRap(Multiplet2(), Multiplet3());
    }

    float DeltaRap13() const {
        return Multiplet::DeltaRap(Multiplet1(), Multiplet3());
    }

    float DeltaPhi() const {
        return Multiplet::DeltaPhi(Multiplet1(), Multiplet2());
    }

    float DeltaPhi23() const {
        return Multiplet::DeltaPhi(Multiplet2(), Multiplet3());
    }

    float DeltaPhi13() const {
        return Multiplet::DeltaPhi(Multiplet1(), Multiplet3());
    }

    float DeltaR() const {
        return Multiplet::DeltaR(Multiplet1(), Multiplet2());
    }

    float DeltaR23() const {
        return Multiplet::DeltaR(Multiplet2(), Multiplet3());
    }

    float DeltaR13() const {
        return Multiplet::DeltaR(Multiplet1(), Multiplet3());
    }

    float DeltaM() const {
        return Multiplet::DeltaM(Multiplet1(), Multiplet2());
    }

    float DeltaM23() const {
        return Multiplet::DeltaM(Multiplet2(), Multiplet3());
    }

    float DeltaM13() const {
        return Multiplet::DeltaM(Multiplet1(), Multiplet3());
    }

    float DeltaHt() const {
        return Multiplet::DeltaHt(Multiplet1(), Multiplet2());
    }

    float DeltaHt23() const {
        return Multiplet::DeltaHt(Multiplet2(), Multiplet3());
    }

    float DeltaHt13() const {
        return Multiplet::DeltaHt(Multiplet1(), Multiplet3());
    }

    float Rho() const {
        return Multiplet::Rho(Multiplet1(), Multiplet2(), Jet12());
    }

    float Rho23() const {
        return Multiplet::Rho(Multiplet2(), Multiplet3(), Jet23());
    }

    float Rho13() const {
        return Multiplet::Rho(Multiplet1(), Multiplet3(), Jet13());
    }

    int Charge() const override {
        return Multiplet::Charge(Multiplet1(), Multiplet2());
    }

    float PullDifference() const {
        return Multiplet::PullDifference(Multiplet1(), Multiplet2());
    }

    float PullSum() const {
        return Multiplet::PullSum(Multiplet1(), Multiplet2());
    }


    float PullSum23() const {
        return Multiplet::PullSum(Multiplet2(), Multiplet3());
    }

    float PullDifference23() const {
        return Multiplet::PullDifference(Multiplet2(), Multiplet3());
    }

    float PullSum13() const {
        return Multiplet::PullSum(Multiplet1(), Multiplet3());
    }

    float PullDifference13() const {
        return Multiplet::PullDifference(Multiplet1(), Multiplet3());
    }

    float Dipolarity() const {
        return Multiplet::Dipolarity(Multiplet1(), Multiplet2(), Jet12());
    }

    float Dipolarity23() const {
        return Multiplet::Dipolarity(Multiplet2(), Multiplet3(), Jet23());
    }

    float Dipolarity13() const {
        return Multiplet::Dipolarity(Multiplet1(), Multiplet3(), Jet13());
    }

    float BottomBdt() const final{
      return (Multiplet1().BottomBdt() + Multiplet2().BottomBdt() + Multiplet3().BottomBdt()) / 3;
    };

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

    Multiplet_1 multiplet_1_;

    Multiplet_2 multiplet_2_;

    Multiplet_3 multiplet_3_;

    void SetJet12(fastjet::PseudoJet const& jet) const {
        jet_12_ = jet;
        has_jet_12_ = true;
    }

    void SetJet23(fastjet::PseudoJet const& jet) const {
        jet_23_ = jet;
        has_jet_23_ = true;
    }

    void SetJet13(fastjet::PseudoJet const& jet) const {
        jet_13_ = jet;
        has_jet_13_ = true;
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

//     mutable fastjet::PseudoJet constiuent_jet_;

    mutable fastjet::PseudoJet jet_12_;

    mutable fastjet::PseudoJet jet_23_;

    mutable fastjet::PseudoJet jet_13_;

    mutable boca::Singlet singlet_12_;

    mutable boca::Singlet singlet_23_;

    mutable boca::Singlet singlet_13_;

//     mutable bool has_singlet_ = false;

    mutable bool has_jet_12_ = false;

    mutable bool has_jet_23_ = false;

    mutable bool has_jet_13_ = false;

    mutable bool has_singlet_12_ = false;

    mutable bool has_singlet_23_ = false;

    mutable bool has_singlet_13_ = false;

};

}
