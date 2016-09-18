/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include <boost/units/base_dimension.hpp>
#include <boost/units/base_unit.hpp>
#include <boost/units/quantity.hpp>
#include <boost/units/systems/si/energy.hpp>

namespace boca
{

namespace units
{

/**
* @brief Electronvolt
*
*/
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
 * @brief Energy measured in electronvolt
 *
 */
using Energy = boost::units::quantity<electronvolt::Energy>;

/**
 * @brief Mass measured in electronvolt
 *
 */
using Mass = Energy;

/**
 * @brief Momentum measured in electronvolt
 *
 */
using Momentum = Energy;
std::string Name(Energy const& energy);

Momentum const at_rest = 0. * ElectronVolt;
Mass const massless = 0. * ElectronVolt;

using EnergySquare = typename boost::units::multiply_typeof_helper<Energy, Energy>::type;
using MassSquare = typename boost::units::multiply_typeof_helper<Mass, Mass>::type;
using MomentumSquare = typename boost::units::multiply_typeof_helper<Momentum, Momentum>::type;

}

using namespace units;

}

BOOST_UNITS_DEFINE_CONVERSION_FACTOR(boca::units::electronvolt::EnergyBaseUnit, boost::units::si::energy, double, 1.602176565e-19);
