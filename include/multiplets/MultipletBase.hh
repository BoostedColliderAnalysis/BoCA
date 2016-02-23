/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "Jet.hh"

namespace boca
{

class Singlet;

class MultipletBase : public Identification
{

public:

    virtual Singlet const& singlet() const = 0;

    virtual boca::Jet Jet() const = 0;

    virtual Momentum Ht() const = 0;

    virtual int Charge() const = 0;

    virtual float BottomBdt() const = 0;

    boca::Mass Mass() const {
        return Jet().Mass();
    }

    Momentum Pt() const {
        return Jet().Pt();
    }

    Angle Rap() const {
        return Jet().Rap();
    }

    Angle Phi() const {
        return Jet().Phi();
    }

    Angle DeltaRTo(boca::PseudoJet const& jet) const {
        return Jet().DeltaRTo(jet);
    }

    /**
     * @brief calculate Reference vector for other - this
     * @return Vector2<float> reference vector
     *
     */
    Vector2<Angle> Reference(boca::Jet const& jet) const {
        return {jet.Rap() - Jet().Rap(), Jet().DeltaPhiTo(jet)};
    }

};

}
