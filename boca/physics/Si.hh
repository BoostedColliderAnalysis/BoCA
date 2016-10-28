/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include <boost/units/quantity.hpp>
#include <boost/units/systems/si/plane_angle.hpp>
#include <boost/units/systems/si/length.hpp>

#include <boost/units/cmath.hpp>

namespace boca
{

namespace units
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

BOOST_UNITS_STATIC_CONSTANT(radian, boost::units::si::plane_angle);

BOOST_UNITS_STATIC_CONSTANT(radians, boost::units::si::plane_angle);

/**
* @brief \f$\pi\f$
*/
Angle Pi();

/**
* @brief \f$2 \pi\f$
*/
Angle TwoPi();

/**
* @brief restrict an angle to the interval \f$[-\pi,\pi]\f$)
*/
Angle Restrict(Angle phi);

/**
* @brief Wrap an angle by \f$2 \pi\f$
*/
Angle Wrap(Angle phi);

}

using namespace units;

}
