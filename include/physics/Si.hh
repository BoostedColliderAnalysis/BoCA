/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include <boost/units/quantity.hpp>
#include <boost/units/systems/si/plane_angle.hpp>
#include <boost/units/systems/si/length.hpp>

namespace boca
{

/**
 * @brief Length measured in meter
 *
 */
using Length = boost::units::quantity<boost::units::si::length>;

BOOST_UNITS_STATIC_CONSTANT(meter, boost::units::si::length);
BOOST_UNITS_STATIC_CONSTANT(meters, boost::units::si::length);
BOOST_UNITS_STATIC_CONSTANT(metre, boost::units::si::length);
BOOST_UNITS_STATIC_CONSTANT(metres, boost::units::si::length);

/**
 * @brief Angle measured in radian
 *
 */
using Angle = boost::units::quantity<boost::units::si::plane_angle>;

using AngleSquare = typename boost::units::multiply_typeof_helper<Angle, Angle>::type;

float to_float(Angle angle);

Angle to_angle(float angle);

BOOST_UNITS_STATIC_CONSTANT(radian, boost::units::si::plane_angle);

BOOST_UNITS_STATIC_CONSTANT(radians, boost::units::si::plane_angle);

// returns phi angle in the interval [-PI,PI)
Angle RestrictPhi(Angle phi);

// Wrap phi around by 2 pi
Angle Wrap(Angle phi);

}

