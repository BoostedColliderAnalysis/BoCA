/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "multiplets/MultipletBase.hh"

namespace boca
{

/**
 * @brief Thin wrapper to make Jet behave like a Multiplet.
 *
 */
class Singlet : public boca::Jet, public MultipletBase
{

public:

    using boca::Jet::Jet;

    void Enforce(boca::Jet const& jet) {
        reset(jet);
        ResetInfo(jet.Info());
    }

    boca::Jet Jet() const override {
        return *this;
    }

    std::vector<boca::Jet> Jets() const {
        return {*this};
    }

    boca::Mass Mass() const override {
        boca::Jet::Mass();
    }

    Angle DeltaRTo(boca::PseudoJet const& jet) const override {
        return boca::Jet::DeltaRTo(jet);
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

    Momentum Ht() const override {
        return Jet().Pt();
    }

    using boca::Jet::Pt;
    using boca::Jet::Rap;
    using boca::Jet::Phi;

    void SetBdt(float bdt) override;

    float Bdt() const override;

    int Charge() const override;

    Singlet const& singlet() const override;

    Vector2<AngleSquare> PullVector() const;

//     float BottomBdt() const override {
//         return Bdt();
//     }

private:

    float log(Length length) const;

    Angle Radius(boca::Jet const& jet) const;

    float Spread(boca::Jet const& jet) const;

    // save expensive results in mutable member variables

    mutable Vector2<AngleSquare> pull_;

    mutable bool has_pull_ = false;

};


}

