/**
 * Copyright (C) 2015-2016 Jan Hajer
 */

#include <boost/math/constants/constants.hpp>

#include "boca/math/Math.hh"
#include "boca/physics/Si.hh"
#include "boca/physics/Prefixes.hh"

#include "boca/generic/DEBUG_MACROS.hh"

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
    phi -= static_cast<double>(sgn(phi)) * TwoPi();
    return phi;
}

}

}
