#pragma once

// base dimension
#include <boost/units/config.hpp>
#include <boost/units/base_dimension.hpp>

// base unit
#include <boost/units/base_unit.hpp>

// system
#include <boost/units/make_system.hpp>

// derived dimension
#include <boost/units/derived_dimension.hpp>


#include <boost/units/make_scaled_unit.hpp>

#include <boost/units/systems/si/area.hpp>
#include <boost/units/systems/si/energy.hpp>
#include <boost/units/systems/si/length.hpp>
#include <boost/units/systems/si/prefixes.hpp>
#include <boost/units/base_units/metric/barn.hpp>
#include <boost/units/scale.hpp>

#include <boost/units/quantity.hpp>

namespace boca
{

// base dimension
struct energy_base_dimension : boost::units::base_dimension<energy_base_dimension, 1> {};

#if BOOST_UNITS_HAS_BOOST_TYPEOF
#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()
BOOST_TYPEOF_REGISTER_TYPE(boca: energy_base_dimension)
#endif

typedef energy_base_dimension::dimension_type energy_dimension;

// base unit

struct energy_base_unit : public boost::units::base_unit<energy_base_unit, energy_dimension, 100> {
    static std::string name() {
        return "electronvolt";
    }
    static std::string symbol() {
        return "eV";
    }
};

#if BOOST_UNITS_HAS_BOOST_TYPEOF
#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()
BOOST_TYPEOF_REGISTER_TYPE(boca::energy_base_unit)
#endif

// system
typedef boost::units::make_system <energy_base_unit>::type system;
typedef boost::units::unit<boost::units::dimensionless_type, system> dimensionless;

// base unit
typedef boost::units::unit<energy_dimension, system> energy;

BOOST_UNITS_STATIC_CONSTANT(electronvolt, energy);
BOOST_UNITS_STATIC_CONSTANT(electronvolts, energy);
typedef boost::units::quantity<energy> Mass;
typedef boost::units::quantity<energy> Momentum;

// derived dimension
// typedef boost::units::derived_dimension < energy_base_dimension, 1 >::type mass_dimension;
// typedef boost::units::derived_dimension < energy_base_dimension, 1 >::type momentum_dimension;
// typedef boost::units::derived_dimension < energy_base_dimension, -1 >::type length_dimension;

// derived unit
// typedef boost::units::unit<length_dimension, system> length;
// BOOST_UNITS_STATIC_CONSTANT(invelectronvolt, length);
// BOOST_UNITS_STATIC_CONSTANT(invelectronvolts, length);


// new SI units




typedef boost::units::make_system<boost::units::metric::barn_base_unit>::type    barnsystem_;
typedef boost::units::unit<boost::units::area_dimension, barnsystem_> barn_area;
typedef boost::units::quantity<barn_area> Crosssection;
BOOST_UNITS_STATIC_CONSTANT(barn, barn_area);
BOOST_UNITS_STATIC_CONSTANT(barns, barn_area);

// typedef boost::units::derived_dimension < boost::units::metric::barn_area, 1 >::type barn_area;
typedef boost::units::derived_dimension < barn_area, -1 >::type luminosity;


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

static Crosssection femto_barn(1. * femto * barn);
static Crosssection pico_barn(1. * pico * barn);

}

BOOST_UNITS_DEFINE_CONVERSION_FACTOR(boca::energy_base_unit, boost::units::si::energy, double, 1.602176565e-19);

