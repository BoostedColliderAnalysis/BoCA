/**
 * Copyright (C) 2015 Jan Hajer
 */

#include "physics/Si.hh"
#include "Debug.hh"

namespace boca
{

float to_float(Length length)
{
    return (length / mm);
}

Length to_length(float length)
{
    return double(length) * mm;
}

float to_float(Angle angle)
{
    return (angle / rad);
}

Angle to_angle(float angle)
{
    return double(angle) * rad;
}

boca::Angle RestrictPhi(boca::Angle x)
{
    if (std::isnan(x.value())) {
        Error("function called with NaN");
        return x;
    }
    while (x >= M_PI * rad) x -= 2 * M_PI * rad;
    while (x < -M_PI * rad) x += 2 * M_PI * rad;
    return x;
}

}
