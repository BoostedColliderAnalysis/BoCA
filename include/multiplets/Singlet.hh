/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include <boost/range/algorithm/unique.hpp>
#include <boost/range/algorithm_ext/erase.hpp>

#include "Jet.hh"
#include "Sort.hh"
#include "Vector.hh"

namespace boca
{

/**
 * @brief Thin wrapper to make Jet behave like a Multiplet.
 *
 */
class Singlet : public boca::Jet
{

public:

    using boca::Jet::Jet;

    void Enforce(boca::Jet const& jet);

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

    Vector2<AngleSquare> PullVector() const;

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

private:

    double Log(Length length) const;

    Angle Radius(boca::Jet const& jet) const;

    double Spread(boca::Jet const& jet) const;

    // save expensive results in mutable member variables

    mutable Vector2<AngleSquare> pull_;

    mutable bool has_pull_ = false;

};

template<typename Multiplet_1_, typename Multiplet_2_>
boca::Singlet MakeSinglet(Multiplet_1_ const& multiplet_1, Multiplet_2_ const& multiplet_2)
{
    auto constituents = SortedByPt(Combine(multiplet_1.ConstituentJet().Constituents(), multiplet_2.ConstituentJet().Constituents()));
    boost::erase(constituents, boost::unique<boost::return_next_end>(constituents));
    return Join(constituents);
}

}

