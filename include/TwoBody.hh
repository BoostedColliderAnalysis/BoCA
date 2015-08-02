#pragma once

#include "Singlet.hh"
#include "Multiplets.hh"
#include "DetectorGeometry.hh"
#include "Predicate.hh"

namespace analysis
{

template <typename Multiplet_1, typename Multiplet_2>
class TwoBody : public Multiplets
{

public:

    TwoBody() {};

    TwoBody(const Multiplet_1& multiplet_1, const Multiplet_2& multiplet_2) {
        SetMultiplets(multiplet_1, multiplet_2);
    }

    TwoBody(const fastjet::PseudoJet& jet) {
        SetJet(jet);
    }

    void SetMultiplets(const Multiplet_1& multiplet_1, const Multiplet_2& multiplet_2) {
        multiplet_1_ = multiplet_1;
        multiplet_2_ = multiplet_2;
        if (multiplet_1.Bdt() != initial_value() && multiplet_2.Bdt() != initial_value()) SetBdt(multiplet_1.Bdt(), multiplet_2.Bdt());
        else if (multiplet_1.Bdt() != initial_value()) SetBdt(multiplet_1.Bdt());
        else if (multiplet_2.Bdt() != initial_value()) SetBdt(multiplet_2.Bdt());
    }

    void SetJet(const fastjet::PseudoJet& jet) {
        multiplet_1_ = Multiplet_1(jet / 2);
        multiplet_2_ = Multiplet_2(jet / 2);
        SetBdt((multiplet_1_.Bdt() + multiplet_2_.Bdt()) / 2);
    }

    void SetSinglet(){
      singlet_ = Singlet(Jet(Structure::constituents));
    }

    Multiplet_1& Multiplet1() const {
        return multiplet_1_;
    }

    Multiplet_2& Multiplet2() const {
        return multiplet_2_;
    }

    template <typename Multiplet3>
    bool Overlap(const Multiplet3& multiplet) const {
        return (multiplet.Overlap(multiplet_1_) || multiplet.Overlap(multiplet_2_));
    }

    bool Overlap(const analysis::Singlet& singlet) const {
        return (multiplet_1_.Overlap(singlet) || multiplet_2_.Overlap(singlet));
    }

    bool Overlap(const fastjet::PseudoJet& jet) const {
        return (multiplet_1_.Overlap(jet) || multiplet_2_.Overlap(jet));
    }

    bool Overlap() const {
        return multiplet_1_.Overlap(multiplet_2_);
    }

    /**
     * @brief join the pieces of the multiplets to one jet
     *
     * @return fastjet::PseudoJet
     */
    fastjet::PseudoJet Jet(Structure structure) const {
        if (structure == Structure::vertices) structure |= Structure::plain;
        return Multiplets::Jet(Multiplet1().Jet(structure),Multiplet2().Jet(structure),structure);
    }

    fastjet::PseudoJet Jet() const {
        return Jet(Structure::plain);
    }

    analysis::Jets Jets() const{
      return Join(Multiplet1().Jets(), Multiplet2().Jets());
    }

    float DeltaPt() const {
        return Multiplet1().Jet().pt() - Multiplet2().Jet().pt();
    }

    float Ht() const {
        return Multiplets::Ht(Multiplet1(), Multiplet2());
    }

    float DeltaRap() const {
      return Multiplets::DeltaRap(Multiplet1(),Multiplet2());
    }

    float DeltaPhi() const {
      return Multiplets::DeltaPhi(Multiplet1(),Multiplet2());
    }

    float DeltaR() const {
      return Multiplets::DeltaR(Multiplet1(),Multiplet2());
    }

    float DeltaM() const {
      return Multiplets::DeltaM(Multiplet1(),Multiplet2());
    }

    float DeltaHt() const {
      return Multiplets::DeltaHt(Multiplet1(),Multiplet2());
    }

    float Rho() const
    {
      return Multiplets::Rho(Multiplet1(),Multiplet2());
    }

    float MassDifferenceTo(Id id) const {
        return std::abs(Jet().m() - Mass(id));
    }

    int Charge() const {
        return sgn(Multiplet1().Charge() + Multiplet2().Charge());
    }

    const analysis::Singlet& singlet() const {
//       return Singlet(Jet(Structure::vertices));
      return singlet_;
    }

    float PullDifference() const {
      return Multiplets::PullDifference(Multiplet1(),Multiplet2());
    }

    float PullSum() const {
      return Multiplets::PullSum(Multiplet1(),Multiplet2());
    }

    float Dipolarity() const {
      return Multiplets::Dipolarity(Multiplet1(),Multiplet2());
    }

    Singlet VertexSinglet() const {
      return Singlet(Jet(Structure::vertices));
    }

protected:

    void SetMultiplet1(const Multiplet_1 multiplet_1) {
        multiplet_1_ = multiplet_1;
    }

    void SetMultiplet2(const Multiplet_2 multiplet_2) {
        multiplet_2_ = multiplet_2;
    }

private:

    mutable Multiplet_1 multiplet_1_;

    mutable Multiplet_2 multiplet_2_;

    mutable Singlet singlet_;

};

}
