/**
 * Copyright (C) 2015-2016 Jan Hajer
 */


#include "boca/math/Math.hh"
#include "boca/units/Si.hh"
#include "boca/units/Prefixes.hh"

namespace boca
{

namespace units
{

Angle PiRad()
{
    return boost::math::constants::pi<double>() * rad;
}

Angle TwoPiRad()
{
    return TwoPi() * rad;
}

Angle Restrict(Angle phi)
{
    while (phi >= PiRad()) phi -= TwoPiRad();
    while (phi < -PiRad()) phi += TwoPiRad();
    return phi;
}

Angle Wrap(Angle phi)
{
    return phi - static_cast<double>(sgn(phi)) * TwoPiRad();
}

}

}
