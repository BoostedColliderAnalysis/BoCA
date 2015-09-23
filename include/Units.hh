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


namespace boca
{

// redefine prefixes in boca namespace
#define BOOST_UNITS_METRIC_PREFIX_2(exponent, name) \
    typedef boost::units::make_scaled_unit<boost::units::si::dimensionless, boost::units::scale<10, boost::units::static_rational<exponent> > >::type name ## _type;\
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

// base dimension
struct energy_base_dimension : boost::units::base_dimension<energy_base_dimension, 1> {};

#if BOOST_UNITS_HAS_BOOST_TYPEOF
#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()
BOOST_TYPEOF_REGISTER_TYPE(boca::energy_base_dimension)
#endif

typedef energy_base_dimension::dimension_type energy_dimension;

// base unit

struct energy_base_unit : public boost::units::base_unit<energy_base_unit, energy_dimension, 100> {
    static std::string name();
    static std::string symbol();
};

#if BOOST_UNITS_HAS_BOOST_TYPEOF
#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()
BOOST_TYPEOF_REGISTER_TYPE(boca::energy_base_unit)
#endif

// system
typedef boost::units::make_system <energy_base_unit>::type system;
typedef boost::units::unit<boost::units::dimensionless_type, system> dimensionless;

// unit
typedef boost::units::unit<energy_dimension, system> energy;

}

BOOST_UNITS_STATIC_CONSTANT(ElectronVolt, electronvolt::energy);
BOOST_UNITS_STATIC_CONSTANT(ElectronVolts, electronvolt::energy);
// quantity
typedef boost::units::quantity<electronvolt::energy> Mass;
typedef boost::units::quantity<electronvolt::energy> Momentum;
typedef boost::units::quantity<electronvolt::energy> Energy;
std::string Name(boost::units::quantity<electronvolt::energy> energy);
int Int(boost::units::quantity<electronvolt::energy> energy);
int Float(boost::units::quantity<electronvolt::energy> energy);

/**
 * @brief One giga electronvolt
 *
 */
static const boost::units::quantity<electronvolt::energy> GeV(1. * giga* ElectronVolt);
static const boost::units::quantity<electronvolt::energy> at_rest(0. * ElectronVolt);
static const boost::units::quantity<electronvolt::energy> massless(0. * ElectronVolt);

namespace barn
{

// system
typedef boost::units::make_system<boost::units::metric::barn_base_unit>::type system;
typedef boost::units::unit<boost::units::dimensionless_type, system> dimensionless;
// unit
typedef boost::units::unit<boost::units::area_dimension, system> area;
typedef boost::units::derived_dimension < boost::units::length_base_dimension, -2 >::type luminosity_dimension;
typedef boost::units::unit<luminosity_dimension, system> inv_barn_area;

}

// quantity
typedef boost::units::quantity<barn::area> Crosssection;
typedef boost::units::quantity<barn::inv_barn_area> Luminosity;

BOOST_UNITS_STATIC_CONSTANT(Barn, barn::area);
BOOST_UNITS_STATIC_CONSTANT(Barns, barn::area);
/**
 * @brief One femto barn
 *
 */
static const Crosssection fb(1. * femto* Barn);

/**
 * @brief One pico barn
 *
 */
static const Crosssection pb(1. * pico* Barn);

}

BOOST_UNITS_DEFINE_CONVERSION_FACTOR(boca::electronvolt::energy_base_unit, boost::units::si::energy, double, 1.602176565e-19);

