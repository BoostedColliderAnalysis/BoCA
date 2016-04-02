/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include <boost/range/algorithm/unique.hpp>
#include "multiplets/Sort.hh"
#include "generic/Vector.hh"

#include "multiplets/Multiplet.hh"
#include "ClusterSequence.hh"

namespace boca
{

template <typename Multiplet_1_, typename Multiplet_2_>
class TwoBody : public Multiplet
{

public:

    TwoBody() {};

    TwoBody(Multiplet_1_ const& multiplet_1, Multiplet_2_ const& multiplet_2) {
        multiplet_1_ = multiplet_1;
        multiplet_2_ = multiplet_2;
        if (multiplet_1.Bdt() != InitialValue() && multiplet_2.Bdt() != InitialValue()) SetBdt(multiplet_1.Bdt(), multiplet_2.Bdt());
        else if (multiplet_1.Bdt() != InitialValue()) SetBdt(multiplet_1.Bdt());
        else if (multiplet_2.Bdt() != InitialValue()) SetBdt(multiplet_2.Bdt());
    }

    template<typename Multiplet_3_, typename Multiplet_4_>
    void Enforce(TwoBody<Multiplet_3_, Multiplet_4_> const& multiplet) {
        multiplet_1_.Enforce(multiplet.Multiplet1());
        multiplet_2_.Enforce(multiplet.Multiplet2());
        SetBdt(multiplet.Bdt());
    }

    void Enforce(boca::Jet const& jet) {
        Enforce(jet, jet.Bdt());
    }

    void Enforce(std::vector<boca::Jet> const& jets) {
        if (jets.empty()) return;
        if (jets.size() == 1) return EnforceJet(jets.front(), jets.front().Bdt());
        multiplet_1_.Enforce(jets.at(0));
        multiplet_2_.Enforce(jets.at(1));
        SetBdt(jets.at(0).Bdt(), jets.at(1).Bdt());
        if (jets.size() > 2) std::cout << "to many jets to enforce a multiplet" << std::endl;
    }

    void Enforce(boca::Jet const& jet, double bdt) {
        if (jet.Constituents().size() < 2) return EnforceJet(jet, bdt);
        ClusterSequence cluster_sequence(jet.Constituents(), DetectorGeometry::SubJetDefinition());
        auto jets = cluster_sequence.ExclusiveJetsUpTo(2);
        if (jets.size() != 2) std::cout << "not the sub-jet number we expected: " << jets.size();
        multiplet_1_.Enforce(jets.at(0), bdt);
        multiplet_2_.Enforce(jets.at(1), bdt);
        SetBdt(bdt);
    }

    void EnforceJet(boca::Jet jet, double bdt) {
        jet.Info().SetSubStructure(false);
        multiplet_1_.Enforce(jet / 2, bdt);
        multiplet_2_.Enforce(jet / 2, bdt);
        SetBdt(bdt);
    }

    Multiplet_1_& Multiplet1() {
        return multiplet_1_;
    }

    Multiplet_1_ const& Multiplet1() const {
        return multiplet_1_;
    }

    Multiplet_2_& Multiplet2() {
        return multiplet_2_;
    }

    Multiplet_2_ const& Multiplet2() const {
        return multiplet_2_;
    }

    template <typename Multiplet_3_>
    bool Overlap(Multiplet_3_ const& multiplet) const {
        return multiplet.Overlap(multiplet_1_) || multiplet.Overlap(multiplet_2_);
    }

    bool Overlap(boca::Singlet const& singlet) const {
        return multiplet_1_.Overlap(singlet) || multiplet_2_.Overlap(singlet);
    }

    bool Overlap(boca::Jet const& jet) const {
        return multiplet_1_.Overlap(jet) || multiplet_2_.Overlap(jet);
    }

    bool Overlap() const {
        return multiplet_1_.Overlap(multiplet_2_);
    }

    std::vector<boca::Jet> Jets() const {
        return Combine(Multiplet1().Jets(), Multiplet2().Jets());
    }

    Momentum DeltaPt() const {
        return Multiplet2().Pt() - Multiplet1().Pt();
    }

    Momentum Ht() const {
        return Multiplet1().Ht() + Multiplet2().Ht();
    }

    Angle DeltaRap() const {
        return Multiplet1().DeltaRapTo(Multiplet2());
    }

    Angle DeltaPhi() const {
        return Multiplet1().DeltaPhiTo(Multiplet2());
    }

    Angle DeltaR() const {
        return Multiplet1().DeltaRTo(Multiplet2());
    }

    boca::Mass DeltaM() const {
        return Multiplet2().Mass() - Multiplet1().Mass();
    }

    Momentum DeltaHt() const {
        return Multiplet2().Ht() - Multiplet1().Ht();
    }

    double Rho() const {
        return Pt() > DetectorGeometry::MinCellPt() && DeltaR() > DetectorGeometry::MinCellResolution() ? double(Mass() / Pt() / DeltaR() * 2_rad) : 0;
    }

    boca::Mass MassDifferenceTo(Id id) const {
        return boost::units::abs(Mass() - MassOf(id));
    }

    int Charge() const {
        return Multiplet1().Charge() + Multiplet2().Charge();
    }

    Angle Pull12() const {
        return Multiplet1().Pull(Multiplet2());
    }

    Angle Pull21() const {
        return Multiplet2().Pull(Multiplet1());
    }

    Line2<Angle> Line() const {
        auto angles_1 = Multiplet1().Angles();
        return {angles_1, Multiplet2().Angles(angles_1)};
    }

    double Dipolarity() const {
        if (Pt() <= at_rest || DeltaR() <= 0_rad) return 0;
        return ConstituentJet().Dipolarity(Line()) / Pt() / sqr(DeltaR());
    }

    template<typename Multiplet_>
    Angle Pull(Multiplet_ const& multiplet) const {
        return ConstituentJet().Pull(DeltaTo(multiplet));
    }

    void Set(Multiplet_1_ const& multiplet_1, Multiplet_2_ const& multiplet_2) {
        multiplet_1_ = multiplet_1;
        multiplet_2_ = multiplet_2;
    }

    std::vector<LorentzVector<Momentum>> LorentzVectors() const {
        return DeltaR() > DetectorGeometry::JetConeSize() ? Combine(Multiplet1().LorentzVectors(), Multiplet2().LorentzVectors()) : std::vector<LorentzVector<Momentum>> {Jet().Vector()};
    }

    boca::EventShapes EventShapes() const {
        return event_shapes_.Get([this]() {
            return boca::EventShapes(Jets());
        });
    }

protected:

    void SetMultiplet1(Multiplet_1_ const& multiplet_1) {
        multiplet_1_ = multiplet_1;
    }

    void SetMultiplet2(Multiplet_2_ const& multiplet_2) {
        multiplet_2_ = multiplet_2;
    }

private:

    boca::Jet GetJet() const override {
        return Join(Multiplet1(), Multiplet2());
    }

    Singlet GetConstituentJet() const override {
        return JoinConstituents(Multiplet1(), Multiplet2());
    }

    Multiplet_1_ multiplet_1_;

    Multiplet_2_ multiplet_2_;

};

template<typename Multiplet_1_, typename Multiplet_2_>
Jet Join(Multiplet_1_ const& multiplet_1, Multiplet_2_ const& multiplet_2)
{
    return Join(multiplet_1.Jet(), multiplet_2.Jet());
}

template<typename Multiplet_1_, typename Multiplet_2_>
boca::Singlet JoinConstituents(Multiplet_1_ const& multiplet_1, Multiplet_2_ const& multiplet_2)
{
    auto constituents = SortedByPt(Combine(multiplet_1.Constituents(), multiplet_2.Constituents()));
    boost::erase(constituents, boost::unique<boost::return_next_end>(constituents));
    return Join(constituents);
}

template<typename Multiplet_>
Jet Join(Jet const& jet, Multiplet_ const& multiplet)
{
    return Join(jet, multiplet.Jet());
}

template<typename Multiplet_>
Jet Join(Multiplet_ const& multiplet, Jet const& jet)
{
    return Join(jet, multiplet.Jet());
}

}

