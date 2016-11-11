/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/generic/Mutable.hh"
#include "boca/math/Line2.hh"
#include "boca/fastjet/Jet.hh"

namespace boca
{

using AngleSquareMomentum = ValueProduct<AngleSquare, Momentum>;

/**
 * @brief Wrapper for a Jet in order to make it behave like a Multiplet.
 *
 */
class Singlet : public boca::Jet
{

  template<typename Multiplet_>
  using NotJet = typename std::enable_if < !std::is_same<Multiplet_, boca::Jet>::value && !std::is_same<Multiplet_, boca::PseudoJet>::value >::type;

public:

    using boca::Jet::Jet;

    void Enforce(boca::Jet const& jet);

    void Enforce(boca::Jet const& jet, double bdt);

    Singlet const& ConstituentJet() const;

    boca::Jet Jet() const;

    std::vector<boca::Jet> Jets() const;

    std::vector<boca::LorentzVector<Momentum>> LorentzVectors() const;

    bool Overlap(boca::Jet const& jet) const;

    /**
     * @name B-tagging related variables
     * @{
     */

    /**
     * @brief Logarithm of radial distance of maximal displaced track
     */
    double MaxDisplacement() const;

    /**
     * @brief Logarithm of radial distance of the mean of all displaced tracks
     */
    double MeanDisplacement() const;

    /**
     * @brief Logarithm of radial distance of the sum all all displaced tracks
     */
    double SumDisplacement() const;

    /**
     * @brief Jet radius
     */
    Angle Radius() const;

    /**
     * @brief Jet spread
     */
    double Spread() const;

    /**
     * @brief Radius of jet consisting only of displaced tracks
     */
    Angle VertexRadius() const;

    /**
     * @brief Spread of displaced tracks
     */
    double VertexSpread() const;

    /**
     * @brief Energy fraction of displaced tracks over the whole jet
     */
    double EnergyFraction() const;
    //@}

    /**
     * @name Tau tagging related variables
     * @{
     */

    /**
     * @brief Electromagnetic radius
     */
    Angle EmRadius() const;

    /**
     * @brief Track radius
     */
    Angle TrackRadius() const;

    /**
     * @brief Core energy fraction
     */
    double CoreEnergyFraction() const;

    /**
     * @brief Flight path
     */
    double FlightPath() const;

    /**
     * @brief Trt Ht fraction
     */
    double TrtHtFraction() const;

    /**
     * @brief Energy ratio
     */
    double EnergyRatio() const;

    /**
     * @brief Momentum ratio
     */
    double MomentumRatio() const;
    //@}

    /**
     * @brief Ht
     */
    Momentum Ht() const;

    void SetBdt(double bdt);

    double Bdt() const;

    void SetTag(boca::Tag tag);

    boca::Tag Tag() const;

    int Charge() const;

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
    Angle PullTo(Multiplet_ const& multiplet) const {
        return PullAngle(DeltaTo(multiplet));
    }


    /**
     * @name Sub-structure variables
     * @{
     */

    /**
     * @brief Pull angle towards the reference angel
     */
    Angle PullAngle(Vector2<Angle> const& reference) const;

    /**
     * @brief Pull vector
     */
    Vector2<AngleSquare> PullVector() const;

    /**
     * @brief Sum for Dipolarity calculation
     */
    AngleSquareMomentum DipolaritySum(Line2<Angle> const& line) const;
    //@}

private:

    // save expensive results in mutable member variables

    Mutable<Vector2<AngleSquare>> pull_;

    Mutable<Angle> radius_;

};

}

