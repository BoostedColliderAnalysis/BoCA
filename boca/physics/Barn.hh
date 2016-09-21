/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include <vector>

#include <boost/units/base_dimension.hpp>
#include <boost/units/base_unit.hpp>
#include <boost/units/quantity.hpp>
#include <boost/units/base_units/metric/barn.hpp>

namespace boca
{

namespace units {

/**
* @brief Barn
*
*/
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

/**
 * @brief Luminosity measured in 1 / barn
 *
 */
using Luminosity = boost::units::quantity<barn::Luminosity>;

Crosssection min(std::vector<Crosssection> vector, bool truncate = false);

std::vector< double > FloatVector(std::vector<Crosssection> const& crosssections);

}

using namespace units;

}
