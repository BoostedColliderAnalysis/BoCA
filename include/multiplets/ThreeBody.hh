/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "multiplets/Multiplet.hh"
#include "multiplets/TwoBody.hh"

namespace boca
{

template <typename Multiplet_1_, typename Multiplet_2_, typename Multiplet_3_>
class ThreeBody : public Multiplet
{

public:

    ThreeBody() {};

    ThreeBody(Multiplet_1_ const& multiplet_1, Multiplet_2_ const& multiplet_2, const Multiplet_3_& multiplet_3) {
        SetMultiplets(multiplet_1, multiplet_2, multiplet_3);
    }

    void SetMultiplets(Multiplet_1_ const& multiplet_1, Multiplet_2_ const& multiplet_2, const Multiplet_3_& multiplet_3) {
        multiplet_1_ = multiplet_1;
        multiplet_2_ = multiplet_2;
        multiplet_3_ = multiplet_3;
        SetBdt((multiplet_1_.Bdt() + multiplet_2_.Bdt() + multiplet_3_.Bdt()) / 3);
    }

    void SetMultiplets12(TwoBody<Multiplet_1_, Multiplet_2_> const& multiplet_12, Multiplet_3_ const& multiplet_3) {
        SetMultiplets(multiplet_12.Multiplet1(), multiplet_12.Multiplet2(), multiplet_3);
    }

    void SetMultiplets23(TwoBody<Multiplet_2_, Multiplet_3_> const& multiplet_23, Multiplet_1_ const& multiplet_1) {
        SetMultiplets(multiplet_1, multiplet_23.Multiplet1(), multiplet_23.Multiplet2());
    }

    void SetMultiplets13(TwoBody<Multiplet_1_, Multiplet_3_> const& multiplet_13, Multiplet_2_ const& multiplet_2) {
        SetMultiplets(multiplet_13.Multiplet1(), multiplet_2, multiplet_13.Multiplet2());
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

    template <typename Multiplet_4_>
    bool Overlap(Multiplet_4_ const& multiplet) const {
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

    std::vector<boca::Jet> Jets() const {
        return Combine(Multiplet1().Jets(), Multiplet2().Jets(), Multiplet3().Jets());
    }

    void SetVetoBdt(double bdt) {
        veto_bdt_ = bdt;
    }

    double VetoBdt() const {
        return veto_bdt_;
    }

    Momentum Ht() const {
        return Multiplet1().Ht() + Multiplet2().Ht() + Multiplet3().Ht();
    }

    int Charge() const {
        return Multiplet1().Charge() + Multiplet2().Charge() + Multiplet3().Charge();
    }

    TwoBody<Multiplet_1_, Multiplet_2_> Multiplet12() const {
        return multiplet_12_.Get([this]() {
            return TwoBody<Multiplet_1_, Multiplet_2_>(Multiplet1(), Multiplet2());
        });
    }

    TwoBody<Multiplet_2_, Multiplet_3_> Multiplet23() const {
        return multiplet_23_.Get([this]() {
            return TwoBody<Multiplet_2_, Multiplet_3_>(Multiplet2(), Multiplet3());
        });
    }

    TwoBody<Multiplet_1_, Multiplet_3_> Multiplet13() const {
        return multiplet_13_.Get([this]() {
            return TwoBody<Multiplet_1_, Multiplet_3_>(Multiplet1(), Multiplet3());
        });
    }

    std::vector<boca::LorentzVector<Momentum>> LorentzVectors() const {
        return Combine(Multiplet1().LorentzVectors(), Multiplet2().LorentzVectors(), Multiplet3().LorentzVectors()) ;
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
        return Join(Multiplet1(), Multiplet2(), Multiplet3());
    }

    Singlet GetConstituentJet() const override {
        return JoinConstituents(Multiplet1(), Multiplet2(), Multiplet3());
    }

    Mutable<TwoBody<Multiplet_1_, Multiplet_2_>> multiplet_12_;

    Mutable<TwoBody<Multiplet_2_, Multiplet_3_>> multiplet_23_;

    Mutable<TwoBody<Multiplet_1_, Multiplet_3_>> multiplet_13_;

    double veto_bdt_;

    Multiplet_1_ multiplet_1_;

    Multiplet_2_ multiplet_2_;

    Multiplet_3_ multiplet_3_;

};

template<typename Multiplet_1_, typename Multiplet_2_, typename Multiplet_3_>
Jet Join(Multiplet_1_ const& multiplet_1, Multiplet_2_ const& multiplet_2, Multiplet_3_ const& multiplet_3)
{
    return Join(multiplet_1.Jet(), multiplet_2.Jet(), multiplet_3.Jet());
}

template<typename Multiplet_1_, typename Multiplet_2_, typename Multiplet_3_>
boca::Singlet JoinConstituents(Multiplet_1_ const& multiplet_1, Multiplet_2_ const& multiplet_2, Multiplet_3_ const& multiplet_3)
{
    auto constituents = SortedByPt(Combine(multiplet_1.Constituents(), multiplet_2.Constituents(), multiplet_3.Constituents()));
    boost::erase(constituents, boost::unique<boost::return_next_end>(constituents));
    return Join(constituents);
}

}
