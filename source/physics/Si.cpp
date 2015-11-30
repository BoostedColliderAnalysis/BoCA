/**
 * Copyright (C) 2015 Jan Hajer
 */

#include "physics/Si.hh"
#include "physics/Math.hh"
#include "physics/Prefixes.hh"
#include "Debug.hh"

namespace boca
{

// Length operator"" _m(long double length)
// {
//     return double(length) * m;
// }
//
// Length operator"" _mm(long double length)
// {
//   return double(length) * mm;
// }

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

Angle RestrictPhi(Angle phi)
{
    if (std::isnan(phi.value())) {
        Error("function called with NaN");
        return phi;
    }
    while (phi >= M_PI * rad) phi -= M_PI * 2_rad;
    while (phi < -M_PI * rad) phi += M_PI * 2_rad;
    return phi;
}

Angle Wrap(Angle phi)
{
    phi -= sgn(phi) * M_PI * 2_rad;
    return phi;
}

}
