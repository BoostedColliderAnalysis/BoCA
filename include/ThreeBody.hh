#pragma once

#include "Singlet.hh"
#include "Multiplet.hh"
#include "DetectorGeometry.hh"

namespace analysis
{

template <typename Multiplet_1, typename Multiplet_2, typename Multiplet_3>
class ThreeBody : public Multiplet
{

public:

    ThreeBody() {};

    ThreeBody(const Multiplet_1& multiplet_1, const Multiplet_2& multiplet_2, const Multiplet_3& multiplet_3) {
        SetMultiplets(multiplet_1, multiplet_2, multiplet_3);
    }

    ThreeBody(const fastjet::PseudoJet& jet) {
        SetJet(jet);
    }

    void SetMultiplets(const Multiplet_1& multiplet_1, const Multiplet_2& multiplet_2, const Multiplet_3& multiplet_3) {
        multiplet_1_ = multiplet_1;
        multiplet_2_ = multiplet_2;
        multiplet_3_ = multiplet_3;
        SetBdt((multiplet_1_.Bdt() + multiplet_2_.Bdt() + multiplet_3_.Bdt()) / 3);
    }

    void SetJet(const fastjet::PseudoJet& jet) {
        multiplet_1_ = Multiplet_1(jet / 3);
        multiplet_2_ = Multiplet_2(jet / 3);
        multiplet_3_ = Multiplet_3(jet / 3);
        SetBdt((multiplet_1_.Bdt() + multiplet_2_.Bdt() + multiplet_2_.Bdt()) / 3);
    }

    void SetSinglet(const fastjet::PseudoJet& jet) const {
        singlet_ = Singlet(jet);
    }

    const analysis::Singlet& singlet() const {
        if(!has_jet_)SetSinglet(Jet());
        return singlet_;
    }

    const Multiplet_1& Multiplet1() const {
        return multiplet_1_;
    }

    const Multiplet_2& Multiplet2() const {
        return multiplet_2_;
    }

    const Multiplet_3& Multiplet3() const {
        return multiplet_3_;
    }

    template <typename Multiplet>
    bool Overlap(const Multiplet& multiplet) const {
        return (multiplet.Overlap(multiplet_1_) || multiplet.Overlap(multiplet_2_) || multiplet.Overlap(multiplet_3_));
    }

    bool Overlap(const analysis::Singlet& singlet) const {
        return (multiplet_1_.Overlap(singlet) || multiplet_2_.Overlap(singlet) || multiplet_3_.Overlap(singlet));
    }

    bool Overlap(const fastjet::PseudoJet& jet) const {
        return (multiplet_1_.Overlap(jet) || multiplet_2_.Overlap(jet) || multiplet_3_.Overlap(jet));
    }

    bool Overlap() const {
        return multiplet_1_.Overlap(multiplet_2_) || multiplet_1_.Overlap(multiplet_3_) || multiplet_2_.Overlap(multiplet_3_);
    }

    fastjet::PseudoJet Jet() const {
        return Multiplet::Jet(Jet12(), Multiplet3().Jet());
    }

    fastjet::PseudoJet Jet12() const {
        return Multiplet::Jet(Multiplet1().Jet(), Multiplet2().Jet());
    }

    fastjet::PseudoJet Jet23() const {
        return Multiplet::Jet(Multiplet2().Jet(), Multiplet3().Jet());
    }

    fastjet::PseudoJet Jet13() const {
        return Multiplet::Jet(Multiplet1().Jet(), Multiplet3().Jet());
    }

    analysis::Jets Jets() const {
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

    float Ht() const {
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
        return Multiplet::Rho(Multiplet1(), Multiplet2());
    }

    float Rho23() const {
        return Multiplet::Rho(Multiplet2(), Multiplet3());
    }

    float Rho13() const {
        return Multiplet::Rho(Multiplet1(), Multiplet3());
    }

    int Charge() const {
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
        return Multiplet::Dipolarity(Multiplet1(), Multiplet2());
    }

    float Dipolarity23() const {
        return Multiplet::Dipolarity(Multiplet2(), Multiplet3());
    }

    float Dipolarity13() const {
        return Multiplet::Dipolarity(Multiplet1(), Multiplet3());
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

    Multiplet_1 multiplet_1_;

    Multiplet_2 multiplet_2_;

    Multiplet_3 multiplet_3_;

    mutable Singlet singlet_;

    void SetResult(const fastjet::PseudoJet& jet) const {
      jet_ = jet;
      SetSinglet(jet);
      has_jet_ = true;
    }

    void SetResult12(const fastjet::PseudoJet& jet) const {
      jet_12_ = jet;
      has_jet_12_ = true;
    }

    void SetResult23(const fastjet::PseudoJet& jet) const {
      jet_23_ = jet;
      has_jet_23_ = true;
    }

    void SetResult13(const fastjet::PseudoJet& jet) const {
      jet_13_ = jet;
      has_jet_13_ = true;
    }

    mutable fastjet::PseudoJet jet_;

    mutable fastjet::PseudoJet jet_12_;

    mutable fastjet::PseudoJet jet_23_;

    mutable fastjet::PseudoJet jet_13_;

    mutable bool has_jet_ = false;

    mutable bool has_jet_12_ = false;

    mutable bool has_jet_23_ = false;

    mutable bool has_jet_13_ = false;

};

}
