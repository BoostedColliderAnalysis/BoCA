/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "multiplets/MultipletBase.hh"
#include "Jet.hh"

namespace boca
{

/**
 * @brief Thin wrapper to make Jet behave like a Multiplet.
 *
 */
class Singlet : public MultipletBase, public boca::Jet
{

public:

    using boca::Jet::Jet;

    boca::Jet Jet() const {
        return *this;
    }

    std::vector<boca::Jet> Jets() const {
        return {*this};
    }

    bool Overlap(boca::Jet const& jet) const;

    bool Overlap(Singlet const& singlet) const;

    float MaxDisplacement() const {
        return log(Info().MaxDisplacement());
    }

    float MeanDisplacement() const {
        return log(Info().MeanDisplacement());
    }

    float SumDisplacement() const {
        return log(Info().SumDisplacement());
    }

    Angle Radius() const {
        return Radius(Jet());
    }

    float Spread() const {
        return Spread(Jet());
    }

    Angle VertexRadius() const {
        return Radius(Info().VertexJet());
    }

    float VertexSpread() const {
        return Spread(Info().VertexJet());
    }

    float EnergyFraction() const {
        return Info().VertexEnergy() / Jet().Energy();
    }

    Angle EmRadius() const {
        return Info().ElectroMagneticRadius(Jet());
    }

    Angle TrackRadius() const {
        return Info().TrackRadius(Jet());
    }

    float CoreEnergyFraction() const {
        return Info().CoreEnergyFraction(Jet());
    }

    float FlightPath() const {
        return log(Info().MeanDisplacement());
    }

    float TrtHtFraction() const {
        return Spread(Info().VertexJet());
    }

    Momentum Ht() const {
        return Jet().Pt();
    }

    using boca::Jet::Pt;
    using boca::Jet::Rap;
    using boca::Jet::Phi;

    void SetBdt(float bdt) final;

    float Bdt() const final;

    int Charge() const;

    Singlet const& singlet() const;

    Vector2<AngleSquare> PullVector() const;

    float BottomBdt() const final {
        return Bdt();
    }

private:

    float log(Length length) const;

    Angle Radius(boca::Jet const& jet) const;

    float Spread(boca::Jet const& jet) const;

    // save expensive results in mutable member variables

    mutable Vector2<AngleSquare> pull_;

    mutable bool has_pull_ = false;

};


}

