/**
 * Copyright (C) 2015 Jan Hajer
 */


#include <sstream>

#include <boost/range/algorithm/remove_if.hpp>
#include <boost/units/systems/si/io.hpp>

#include "physics/ElectronVolt.hh"
#include "physics/Prefixes.hh"

namespace boca
{

namespace electronvolt
{

std::string EnergyBaseUnit::name()
{
    return "electronvolt";
}

std::string EnergyBaseUnit::symbol()
{
    return "eV";
}

}

std::string Name(Energy energy)
{
    std::stringstream stream;
    stream << boost::units::engineering_prefix << energy;
    std::string string = stream.str();
    string.erase(boost::range::remove_if(string, isspace), string.end());
    return string;
}

// Energy operator"" _eV(long double length)
// {
//     return double(length) * eV;
// }
//
// Energy operator"" _GeV(long double length)
// {
//     return double(length) * GeV;
// }
//
// Energy operator"" _TeV(long double length)
// {
//     return double(length) * TeV;
// }

int Int(Momentum energy)
{
    return energy / GeV;
}

float to_float(Energy energy)
{
    return energy / GeV;
}

Energy to_energy(double energy)
{
    return energy * GeV;
}

}
