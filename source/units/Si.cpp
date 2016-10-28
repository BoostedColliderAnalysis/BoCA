/**
 * Copyright (C) 2015-2016 Jan Hajer
 */

#include <boost/math/constants/constants.hpp>

#include "boca/math/Math.hh"
#include "boca/units/Si.hh"
#include "boca/units/Prefixes.hh"

namespace boca
{

namespace units
{

Angle Pi()
{
    return boost::math::constants::pi<double>() * rad;
}

Angle TwoPi()
{
    return 2. * Pi();
}

Angle Restrict(Angle phi)
{
    while (phi >= Pi()) phi -= TwoPi();
    while (phi < -Pi()) phi += TwoPi();
    return phi;
}

Angle Wrap(Angle phi)
{
    return phi - static_cast<double>(sgn(phi)) * TwoPi();
}

}

}
