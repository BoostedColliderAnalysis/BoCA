#pragma once

#include "Singlet.hh"
#include "Multiplets.hh"
#include "DetectorGeometry.hh"
#include "Predicate.hh"

namespace analysis {

template <typename Multiplet_1, typename Multiplet_2, typename Multiplet_3>
class ThreeBody : public Multiplets {

public:

    ThreeBody() {};

    ThreeBody(const Multiplet_1& multiplet_1, const Multiplet_2& multiplet_2, const Multiplet_3& multiplet_3)
    {
        SetTChannels(multiplet_1, multiplet_2,multiplet_3);
    }

    ThreeBody(const fastjet::PseudoJet& jet)
    {
        SetJet(jet);
    }

    void SetTChannels(const Multiplet_1& multiplet_1, const Multiplet_2& multiplet_2,const Multiplet_3& multiplet_3)
    {
        multiplet_1_ = multiplet_1;
        multiplet_2_ = multiplet_2;
        multiplet_3_ = multiplet_3;
        SetBdt((multiplet_1_.Bdt() + multiplet_2_.Bdt() + multiplet_3_.Bdt()) / 3);
    }

    void SetJet(const fastjet::PseudoJet& jet)
    {
        multiplet_1_ = Multiplet_1(jet / 3);
        multiplet_2_ = Multiplet_2(jet / 3);
        multiplet_3_ = Multiplet_3(jet / 3);
        SetBdt((multiplet_1_.Bdt() + multiplet_2_.Bdt() + multiplet_2_.Bdt()) / 3);
    }

    void SetSinglet(){
      singlet_ = Singlet(Jet(Structure::constituents));
    }

    const analysis::Singlet& singlet() const {
      //       return Singlet(Jet(Structure::vertices));
      return singlet_;
    }

    Multiplet_1& Multiplet1() const
    {
        return multiplet_1_;
    }

    Multiplet_2& Multiplet2() const
    {
        return multiplet_2_;
    }

    Multiplet_3& Multiplet3() const
    {
      return multiplet_3_;
    }

    template <typename Multiplet>
    bool Overlap(const Multiplet& multiplet) const
    {
      return (multiplet.Overlap(multiplet_1_) || multiplet.Overlap(multiplet_2_) || multiplet.Overlap(multiplet_3_));
    }

    bool Overlap(const analysis::Singlet& singlet) const
    {
      return (multiplet_1_.Overlap(singlet) || multiplet_2_.Overlap(singlet) || multiplet_3_.Overlap(singlet));
    }

    bool Overlap(const fastjet::PseudoJet& jet) const
    {
      return (multiplet_1_.Overlap(jet) || multiplet_2_.Overlap(jet) || multiplet_3_.Overlap(jet));
    }

    bool Overlap() const
    {
      return multiplet_1_.Overlap(multiplet_2_) || multiplet_1_.Overlap(multiplet_3_) || multiplet_2_.Overlap(multiplet_3_);
    }

    fastjet::PseudoJet Jet(Structure structure) const {
      if (structure == Structure::vertices) structure |= Structure::plain;
      return Multiplets::Jet(Jet12(structure), Multiplet3().Jet(structure), structure);
    }

    fastjet::PseudoJet Jet12(Structure structure) const {
      if (structure == Structure::vertices) structure |= Structure::plain;
      return Multiplets::Jet(Multiplet1().Jet(structure), Multiplet2().Jet(structure), structure);
    }

    fastjet::PseudoJet Jet23(Structure structure) const {
      if (structure == Structure::vertices) structure |= Structure::plain;
      return Multiplets::Jet(Multiplet2().Jet(structure), Multiplet3().Jet(structure), structure);
    }

    fastjet::PseudoJet Jet13(Structure structure) const {
      if (structure == Structure::vertices) structure |= Structure::plain;
      return Multiplets::Jet(Multiplet1().Jet(structure), Multiplet3().Jet(structure), structure);
    }

    fastjet::PseudoJet Jet() const
    {
      return Jet(Structure::plain);
    }
    fastjet::PseudoJet Jet12() const
    {
      return Jet12(Structure::plain);
    }

    fastjet::PseudoJet Jet23() const
    {
      return Jet23(Structure::plain);
    }

    fastjet::PseudoJet Jet13() const
    {
      return Jet13(Structure::plain);
    }

    analysis::Jets Jets() const{
      return Join(Multiplet1().Jets(), Multiplet2().Jets(), Multiplet3().Jets());
    }

    float DeltaPt() const
    {
        return Multiplets::DeltaPt(Multiplet1(),Multiplet2());
    }

    float DeltaPt23() const
    {
      return Multiplets::DeltaPt(Multiplet2(),Multiplet3());
    }

    float DeltaPt13() const
    {
      return Multiplets::DeltaPt(Multiplet1(),Multiplet3());
    }

    float Ht() const
    {
      return Ht12() + Multiplet3().Ht();
    }

    float Ht12() const
    {
      return Multiplets::Ht(Multiplet1(), Multiplet2());
    }

    float Ht23() const
    {
      return Multiplets::Ht(Multiplet2(), Multiplet3());
    }

    float Ht13() const
    {
      return Multiplets::Ht(Multiplet1(), Multiplet3());
    }

    float DeltaRap() const
    {
      return Multiplets::DeltaRap(Multiplet1(),Multiplet2());
    }

    float DeltaPhi() const
    {
      return Multiplets::DeltaPhi(Multiplet1(),Multiplet2());
    }

    float DeltaPhi23() const
    {
      return Multiplets::DeltaPhi(Multiplet2(),Multiplet3());
    }

    float DeltaPhi13() const
    {
      return Multiplets::DeltaPhi(Multiplet1(),Multiplet3());
    }

    float DeltaR() const
    {
      return Multiplets::DeltaR(Multiplet1(),Multiplet2());
    }

    float DeltaR23() const
    {
      return Multiplets::DeltaR(Multiplet2(),Multiplet3());
    }

    float DeltaR13() const
    {
      return Multiplets::DeltaR(Multiplet1(),Multiplet3());
    }

    float DeltaM() const
    {
      return Multiplets::DeltaM(Multiplet1(),Multiplet2());
    }

    float DeltaM23() const
    {
      return Multiplets::DeltaM(Multiplet2(),Multiplet3());
    }

    float DeltaM13() const
    {
      return Multiplets::DeltaM(Multiplet1(),Multiplet3());
    }

    float DeltaHt() const
    {
      return Multiplets::DeltaHt(Multiplet1(),Multiplet2());
    }

    float DeltaHt23() const
    {
      return Multiplets::DeltaHt(Multiplet2(),Multiplet3());
    }

    float DeltaHt13() const
    {
      return Multiplets::DeltaHt(Multiplet1(),Multiplet3());
    }

    float Rho() const
    {
      return Multiplets::Rho(Multiplet1(),Multiplet2());
    }

    float Rho23() const
    {
      return Multiplets::Rho(Multiplet2(),Multiplet3());
    }

    float Rho13() const
    {
      return Multiplets::Rho(Multiplet1(),Multiplet3());
    }

    int Charge() const
    {
      return sgn(Multiplet1().Charge() + Multiplet2().Charge() + Multiplet3().Charge());
    }

    const analysis::Singlet &singlet(Structure) const {
//       return Singlet(Jet(structure));
    }

    float PullDifference() const {
      return Multiplets::PullDifference(Multiplet1(),Multiplet2());
    }

    float PullSum() const {
      return Multiplets::PullSum(Multiplet1(),Multiplet2());
    }


    float PullSum23() const {
      return Multiplets::PullSum(Multiplet2(),Multiplet3());
    }

    float PullDifference23() const {
      return Multiplets::PullDifference(Multiplet2(),Multiplet3());
    }

    float PullSum13() const {
      return Multiplets::PullSum(Multiplet1(),Multiplet3());
    }

    float PullDifference13() const {
      return Multiplets::PullDifference(Multiplet1(),Multiplet3());
    }

    float Dipolarity() const {
      return Multiplets::Dipolarity(Multiplet1(),Multiplet2());
    }

    float Dipolarity23() const {
      return Multiplets::Dipolarity(Multiplet2(),Multiplet3());
    }

    float Dipolarity13() const {
      return Multiplets::Dipolarity(Multiplet1(),Multiplet3());
    }

protected:

    void SetMultiplet1(const Multiplet_1 multiplet_1)
    {
        multiplet_1_ = multiplet_1;
    }

    void SetMultiplet2(const Multiplet_2 multiplet_2)
    {
        multiplet_2_ = multiplet_2;
    }

    void SetMultiplet3(const Multiplet_3 multiplet_3)
    {
      multiplet_3_ = multiplet_3;
    }

private:

    mutable Multiplet_1 multiplet_1_;

    mutable Multiplet_2 multiplet_2_;

    mutable Multiplet_3 multiplet_3_;

    mutable Singlet singlet_;

};

}
