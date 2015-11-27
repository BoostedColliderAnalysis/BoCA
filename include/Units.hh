/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

// scale for prefixes
#include <boost/units/scale.hpp>
#include <boost/units/make_scaled_unit.hpp>

// base dimension
#include <boost/units/config.hpp>
#include <boost/units/base_dimension.hpp>

// base unit
#include <boost/units/base_unit.hpp>

// system
#include <boost/units/make_system.hpp>

// derived dimension
#include <boost/units/derived_dimension.hpp>
#include <boost/units/quantity.hpp>

// barn
#include <boost/units/base_units/metric/barn.hpp>

// math and io for units
#include <boost/units/cmath.hpp>
#include <boost/units/systems/si/io.hpp>

#include <boost/units/systems/si/plane_angle.hpp>
#include <boost/units/systems/si/length.hpp>

namespace boca
{

// redefine prefixes in boca namespace
// TODO find a way to import the prefixes into boca namespace without reimplementing them or including the full si namespace
#define BOOST_UNITS_METRIC_PREFIX_2(exponent, name) \
    using name ## _type = boost::units::make_scaled_unit<boost::units::si::dimensionless, boost::units::scale<10, boost::units::static_rational<exponent> > >::type; \
    BOOST_UNITS_STATIC_CONSTANT(name, name ## _type)
BOOST_UNITS_METRIC_PREFIX_2(-24, yocto);
BOOST_UNITS_METRIC_PREFIX_2(-21, zepto);
BOOST_UNITS_METRIC_PREFIX_2(-18, atto);
BOOST_UNITS_METRIC_PREFIX_2(-15, femto);
BOOST_UNITS_METRIC_PREFIX_2(-12, pico);
BOOST_UNITS_METRIC_PREFIX_2(-9, nano);
BOOST_UNITS_METRIC_PREFIX_2(-6, micro);
BOOST_UNITS_METRIC_PREFIX_2(-3, milli);
BOOST_UNITS_METRIC_PREFIX_2(-2, centi);
BOOST_UNITS_METRIC_PREFIX_2(-1, deci);
BOOST_UNITS_METRIC_PREFIX_2(1, deka);
BOOST_UNITS_METRIC_PREFIX_2(2, hecto);
BOOST_UNITS_METRIC_PREFIX_2(3, kilo);
BOOST_UNITS_METRIC_PREFIX_2(6, mega);
BOOST_UNITS_METRIC_PREFIX_2(9, giga);
BOOST_UNITS_METRIC_PREFIX_2(12, tera);
BOOST_UNITS_METRIC_PREFIX_2(15, peta);
BOOST_UNITS_METRIC_PREFIX_2(18, exa);
BOOST_UNITS_METRIC_PREFIX_2(21, zetta);
BOOST_UNITS_METRIC_PREFIX_2(24, yotta);


namespace electronvolt
{

struct EnergyBaseDimension : boost::units::base_dimension<EnergyBaseDimension, 1> {};

#if BOOST_UNITS_HAS_BOOST_TYPEOF
#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()
BOOST_TYPEOF_REGISTER_TYPE(boca::energy_base_dimension)
#endif

using EnergyDimension = EnergyBaseDimension::dimension_type;
struct EnergyBaseUnit : public boost::units::base_unit<EnergyBaseUnit, EnergyDimension, 100> {
    static std::string name();
    static std::string symbol();
};

#if BOOST_UNITS_HAS_BOOST_TYPEOF
#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()
BOOST_TYPEOF_REGISTER_TYPE(boca::energy_base_unit)
#endif

using System  = boost::units::make_system <EnergyBaseUnit>::type;
using Dimensionless = boost::units::unit<boost::units::dimensionless_type, System>;
using Energy = boost::units::unit<EnergyDimension, System>;
}

BOOST_UNITS_STATIC_CONSTANT(ElectronVolt, electronvolt::Energy);
BOOST_UNITS_STATIC_CONSTANT(ElectronVolts, electronvolt::Energy);

/**
 * @brief Mass measured in electronvolt
 *
 */
using Mass = boost::units::quantity<electronvolt::Energy>;

/**
 * @brief Momentum measured in electronvolt
 *
 */
using Momentum = boost::units::quantity<electronvolt::Energy>;

/**
 * @brief Energy measured in electronvolt
 *
 */
using Energy = boost::units::quantity<electronvolt::Energy>;
std::string Name(boost::units::quantity<electronvolt::Energy> energy);
// int to_int(boost::units::quantity<electronvolt::energy> energy);

int Int(Momentum energy);
float to_float(boost::units::quantity<electronvolt::Energy> energy);
boost::units::quantity< electronvolt::Energy > to_energy(double energy);

/**
 * @brief giga electronvolt
 *
 */
static const boost::units::quantity<electronvolt::Energy> GeV(1. * giga* ElectronVolt);

/**
 * @brief Tera electronvolt
 *
 */
static const boost::units::quantity<electronvolt::Energy> TeV(1. * tera* ElectronVolt);
static const Momentum at_rest(0. * ElectronVolt);
static const Mass massless(0. * ElectronVolt);

namespace barn
{
using System = boost::units::make_system<boost::units::metric::barn_base_unit>::type;
using Dimensionless = boost::units::unit<boost::units::dimensionless_type, System>;
using Area = boost::units::unit<boost::units::area_dimension, System>;
using LuminosityDimension = boost::units::derived_dimension < boost::units::length_base_dimension, -2 >::type;
using Luminosity = boost::units::unit<LuminosityDimension, System>;

}

BOOST_UNITS_STATIC_CONSTANT(Barn, barn::Area);
BOOST_UNITS_STATIC_CONSTANT(Barns, barn::Area);

/**
 * @brief Crosssection measured in barn
 *
 */
using Crosssection = boost::units::quantity<barn::Area>;
float to_float(Crosssection crosssection);
Crosssection to_crosssection(float crosssection);

/**
 * @brief Luminosity measured in 1 / barn
 *
 */
using Luminosity = boost::units::quantity<barn::Luminosity>;
float to_float(Luminosity luminosity);
Luminosity to_luminosity(float luminosity);

/**
 * @brief femto barn
 *
 */
static const Crosssection fb(1. * femto* Barn);

/**
 * @brief pico barn
 *
 */
static const Crosssection pb(1. * pico* Barn);

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
 * @brief meter
 *
 */
static const Length m(1. * meter);
/**
 * @brief milli meter
 *
 */
static const Length mm(1. * milli* meter);

// auto operator"" _mm (double val) -> decltype(val * milli * meter)
// {
//   return val * milli * meter;
// }

// Length operator"" _mm(double x)
// {
//     return x * mm;
// }

/**
 * @brief Angle measured in radian
 *
 */
using Angle = boost::units::quantity<boost::units::si::plane_angle>;
float to_float(Angle angle);
Angle to_angle(float angle);

BOOST_UNITS_STATIC_CONSTANT(radian, boost::units::si::plane_angle);
BOOST_UNITS_STATIC_CONSTANT(radians, boost::units::si::plane_angle);

/**
 * @brief radian
 *
 */
static const Angle rad(1. * radian);

}

BOOST_UNITS_DEFINE_CONVERSION_FACTOR(boca::electronvolt::EnergyBaseUnit, boost::units::si::energy, double, 1.602176565e-19);




