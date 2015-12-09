/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "Identification.hh"
#include "physics/Units.hh"

namespace boca
{

/**
 * @brief An octet composed of a sextet an a doublet
 *
 */
class CutVariables : public Identification
{

public:

    Momentum Ht() const {
        return ht_;
    };

    Energy EtMiss() const {
        return et_miss_;
    };

    float JetNumber() const {
        return jet_number_;
    };

    float BottomNumber() const {
        return bottom_number_;
    };

    boca::Mass InvariantMass() const {
        return invariant_mass_;
    };

    Angle DeltaR() const {
        return delta_r_;
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
   Momentum leading_pt_ = 0;
   Momentum second_leading_pt_ = 0;
   Momentum bottom_min_pt_ = 0;
   Angle bottom_max_rap_ = 0;

    std::vector<bool> passed_;
    void SetPassed(std::vector<bool> const& passed);

    bool IsNaN() {
        return (Ht() != Ht() || EtMiss() != EtMiss() || JetNumber() != JetNumber() || BottomNumber() != BottomNumber() || InvariantMass() != InvariantMass() || DeltaR() != DeltaR());
    }


};


}
