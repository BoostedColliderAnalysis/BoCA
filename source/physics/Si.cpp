/**
 * Copyright (C) 2015-2016 Jan Hajer
 */

#include <boost/math/constants/constants.hpp>
#include "physics/Si.hh"
#include "physics/Math.hh"
#include "physics/Prefixes.hh"
#include "DEBUG.hh"

namespace boca
{

double to_double(Length length)
{
    return (length / mm);
}

Length to_length(double length)
{
    return double(length) * mm;
}

double to_double(Angle angle)
{
    return (angle / rad);
}

Angle to_angle(double angle)
{
    return double(angle) * rad;
}

Angle Pi()
{
    return boost::math::constants::pi<double>() * rad;
}

Angle TwoPi()
{
    return 2. * Pi();
}

Angle RestrictPhi(Angle phi)
{
    if (std::isnan(phi.value())) {
        ERROR("function called with NaN");
        return phi;
    }
    while (phi >= Pi()) phi -= TwoPi();
    while (phi < -Pi()) phi += TwoPi();
    return phi;
}

Angle Wrap(Angle phi)
{
    phi -= double(sgn(phi)) * TwoPi();
    return phi;
}

}
