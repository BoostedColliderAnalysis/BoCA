/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "multiplets/MultipletBase.hh"

namespace boca
{

/**
 * @brief An octet composed of a sextet an a doublet
 *
 */
class CutPlet : public MultipletBase
{

public:

    MultipletBase const& singlet() const {
        return *this;
    }

    boca::Jet Jet() const {
        return {};
    }

    Vector2<AngleSquare> Pull() const {
        return {};
    }

    float Ht() const {
        return ht_ / GeV;
    };

    float EtMiss() const {
        return et_miss_ / GeV;
    };

    float JetNumber() const {
        return jet_number_;
    };

    float BottomNumber() const {
        return bottom_number_;
    };

    float InvariantMass() const {
        return invariant_mass_ / GeV;
    };

    float DeltaR() const {
        return delta_r_ / rad;
    };

    int Charge() const {
        return 0;
    }

    float BottomBdt() const {
        return 0;
    }

    Energy ht_ = 0;
    Energy et_miss_ = 0;
    int jet_number_ = 0;
    int bottom_number_ = 0;
    boca::Mass invariant_mass_ = 0;
    Angle delta_r_ = 0;

    std::vector<bool> passed_;
    void SetPassed(std::vector<bool> const& passed);

    bool IsNaN() {
        return (Ht() != Ht() || EtMiss() != EtMiss() || JetNumber() != JetNumber() || BottomNumber() != BottomNumber() || InvariantMass() != InvariantMass() || DeltaR() != DeltaR());
    }


};


}
