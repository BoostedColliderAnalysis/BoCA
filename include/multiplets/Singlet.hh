/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "Jet.hh"
#include "Mutable.hh"
#include "Line2.hh"

namespace boca
{

using AngleSquareMomentum = ValueProduct<AngleSquare, Momentum>;

/**
 * @brief Thin wrapper to make Jet behave like a Multiplet.
 *
 */
class Singlet : public boca::Jet
{

public:

    using boca::Jet::Jet;

    void Enforce(boca::Jet const& jet);

    void Enforce(boca::Jet const& jet, double bdt);

    boca::Jet Jet() const;

    std::vector<boca::Jet> Jets() const;

    bool Overlap(boca::Jet const& jet) const;

    double MaxDisplacement() const;

    double MeanDisplacement() const;

    double SumDisplacement() const;

    Angle Radius() const;

    double Spread() const;

    Angle VertexRadius() const;

    double VertexSpread() const;

    double EnergyFraction() const;

    Angle EmRadius() const;

    Angle TrackRadius() const;

    double CoreEnergyFraction() const;

    double FlightPath() const;

    double TrtHtFraction() const;

    Momentum Ht() const;

    void SetBdt(double bdt);

    double Bdt() const;

    void SetTag(boca::Tag tag);

    boca::Tag Tag() const;

    int Charge() const;

    Singlet const& ConstituentJet() const;

    Vector2<AngleSquare> Pull() const;

    template<typename Multiplet_>
    using NotJet = typename std::enable_if < !std::is_same<Multiplet_, boca::Jet>::value && !std::is_same<Multiplet_, boca::PseudoJet>::value >::type;

    template <typename Multiplet_, typename = NotJet<Multiplet_>>
    Angle DeltaPhiTo(Multiplet_ const& jet) const {
        return Jet().DeltaPhiTo(jet.Jet());
    }

    using PseudoJet::DeltaPhiTo;

    template <typename Multiplet_, typename = NotJet<Multiplet_>>
    Angle DeltaRTo(Multiplet_ const& jet) const {
        return Jet().DeltaRTo(jet.Jet());
    }

    using PseudoJet::DeltaRTo;

    template <typename Multiplet_, typename = NotJet<Multiplet_>>
    Angle DeltaRapTo(Multiplet_ const& jet) const {
        return Jet().DeltaRapTo(jet.Jet());
    }

    using PseudoJet::DeltaRapTo;

    template <typename Multiplet_, typename = NotJet<Multiplet_>>
    Vector2<Angle> DeltaTo(Multiplet_ const& jet) const {
        return Jet().DeltaTo(jet.Jet());
    }

    using PseudoJet::DeltaTo;

    template<typename Multiplet_>
    Angle Pull(Multiplet_ const& multiplet) const {
        return Pull(DeltaTo(multiplet));
    }

    Angle Pull(Vector2<Angle> const& reference) const;

    AngleSquareMomentum Dipolarity(Line2<Angle> const& line) const;

private:

    Angle GetRadius() const;

    Vector2<AngleSquare> GetPull() const;

    double Log(Length length) const;

    // save expensive results in mutable member variables

    Mutable<Vector2<AngleSquare>> pull_;

    Mutable<Angle> radius_;

};

}

