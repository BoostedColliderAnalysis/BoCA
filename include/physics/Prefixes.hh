/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include <boost/units/scale.hpp>
#include <boost/units/make_scaled_unit.hpp>
#include <boost/units/systems/si/dimensionless.hpp>

#include "Si.hh"
#include "Barn.hh"
#include "ElectronVolt.hh"

namespace boca
{

// Boost.Units - A C++ library for zero-overhead dimensional analysis and
// unit/quantity manipulation and conversion
//
// Copyright (C) 2003-2008 Matthias Christian Schabel
// Copyright (C) 2007-2008 Steven Watanabe
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


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

// Copyright (c) 2013 Andrew Gascoyne-Cecil
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the Software
// is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


#define BOOST_UNITS_LITERAL(suffix, unit, val, prefix, multiplier) \
    inline boost::units::quantity<unit, double> operator "" _##prefix##suffix(long double x) \
    { \
        return boost::units::quantity<unit, double>(x * multiplier * val); \
    } \
    inline boost::units::quantity<unit, unsigned > operator "" _##prefix##suffix(unsigned long long x) \
    { \
        return boost::units::quantity<unit, unsigned >(x * multiplier * val); \
    } \
    static const boost::units::quantity<unit, double> prefix##suffix(1. * multiplier * val); \

#define BOOST_UNITS_LITERAL_SET(suffix, unit, val) \
    BOOST_UNITS_LITERAL(suffix, unit, val, Y, 1000000000000000000000000.0) \
    BOOST_UNITS_LITERAL(suffix, unit, val, Z, 1000000000000000000000.0) \
    BOOST_UNITS_LITERAL(suffix, unit, val, E, 1000000000000000000.0) \
    BOOST_UNITS_LITERAL(suffix, unit, val, P, 1000000000000000.0) \
    BOOST_UNITS_LITERAL(suffix, unit, val, T, 1000000000000.0) \
    BOOST_UNITS_LITERAL(suffix, unit, val, G, 1000000000.0) \
    BOOST_UNITS_LITERAL(suffix, unit, val, M, 1000000.0) \
    BOOST_UNITS_LITERAL(suffix, unit, val, k, 1000.0) \
    BOOST_UNITS_LITERAL(suffix, unit, val, h, 100.0) \
    BOOST_UNITS_LITERAL(suffix, unit, val, da, 10.0) \
    BOOST_UNITS_LITERAL(suffix, unit, val, , 1.0) \
    BOOST_UNITS_LITERAL(suffix, unit, val, d, 0.1) \
    BOOST_UNITS_LITERAL(suffix, unit, val, c, 0.01) \
    BOOST_UNITS_LITERAL(suffix, unit, val, m, 0.001) \
    BOOST_UNITS_LITERAL(suffix, unit, val, u, 0.000001) \
    BOOST_UNITS_LITERAL(suffix, unit, val, n, 0.00000001) \
    BOOST_UNITS_LITERAL(suffix, unit, val, p, 0.00000000001) \
    BOOST_UNITS_LITERAL(suffix, unit, val, f, 0.00000000000001) \
    BOOST_UNITS_LITERAL(suffix, unit, val, a, 0.00000000000000001) \
    BOOST_UNITS_LITERAL(suffix, unit, val, z, 0.00000000000000000001) \
    BOOST_UNITS_LITERAL(suffix, unit, val, y, 0.00000000000000000000001)

BOOST_UNITS_LITERAL_SET(m, boost::units::si::length, boost::units::si::metre)
// BOOST_UNITS_LITERAL_SET(g, mass, 0.001 * kilogram)
// BOOST_UNITS_LITERAL_SET(s, time, second)
// BOOST_UNITS_LITERAL_SET(A, current, ampere)
// BOOST_UNITS_LITERAL_SET(K, temperature, kelvin)
// BOOST_UNITS_LITERAL_SET(mol, amount, mole)
// BOOST_UNITS_LITERAL_SET(cd, luminous_intensity, candela)
// BOOST_UNITS_LITERAL_SET(Hz, frequency, hertz)
BOOST_UNITS_LITERAL_SET(rad, boost::units::si::plane_angle, boost::units::si::radian)
// BOOST_UNITS_LITERAL_SET(sr, solid_angle, steradian)
// BOOST_UNITS_LITERAL_SET(N, force, newton)
// BOOST_UNITS_LITERAL_SET(Pa, pressure, pascal)
// BOOST_UNITS_LITERAL_SET(J, energy, joule)
// BOOST_UNITS_LITERAL_SET(W, power, watt)
// BOOST_UNITS_LITERAL_SET(C, electric_charge, coulomb)
// BOOST_UNITS_LITERAL_SET(V, electric_potential, volt)
// BOOST_UNITS_LITERAL_SET(F, capacitance, farad)
// BOOST_UNITS_LITERAL_SET(ohm, resistance, ohm)
// BOOST_UNITS_LITERAL_SET(S, conductance, siemens)
// BOOST_UNITS_LITERAL_SET(Wb, magnetic_flux, weber)
// BOOST_UNITS_LITERAL_SET(T, magnetic_flux_density, tesla)
// BOOST_UNITS_LITERAL_SET(H, inductance, henry)
// BOOST_UNITS_LITERAL_SET(degC, temperature, kelvin + 273.15 * kelvin)
// BOOST_UNITS_LITERAL_SET(lm, luminous_flux, lumen)
// BOOST_UNITS_LITERAL_SET(lx, illuminance, lux)
// BOOST_UNITS_LITERAL_SET(Bq, activity, becquerel)
// BOOST_UNITS_LITERAL_SET(Gy, absorbed_dose, gray)
// BOOST_UNITS_LITERAL_SET(Sv, dose_equivalent, sievert)
// BOOST_UNITS_LITERAL_SET(kat, catalytic_activity, katal)
// BOOST_UNITS_LITERAL_SET(min, time, 60.0 * second)
// BOOST_UNITS_LITERAL_SET(h, time, 60.0 * 60.0 * second)
// BOOST_UNITS_LITERAL_SET(day, time, 60.0 * 60.0 * 24.0 * second)
// BOOST_UNITS_LITERAL_SET(deg, plane_angle, M_PI / 180.0 * radian)
// BOOST_UNITS_LITERAL_SET(l, volume, 0.001 * cubic_meter)
// BOOST_UNITS_LITERAL_SET(L, volume, 0.001 * cubic_meter)
// BOOST_UNITS_LITERAL_SET(t, mass, 1000.0 * kilogram)
BOOST_UNITS_LITERAL_SET(eV, electronvolt::Energy, ElectronVolt)
BOOST_UNITS_LITERAL_SET(b, barn::Area, Barn)


}
