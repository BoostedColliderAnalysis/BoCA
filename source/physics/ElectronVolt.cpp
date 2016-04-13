/**
 * Copyright (C) 2015-2016 Jan Hajer
 */

#include <sstream>

#include <boost/range/algorithm_ext/erase.hpp>
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
    return boost::range::remove_erase_if(string, isspace);
}

int Int(Momentum energy)
{
    return energy / GeV;
}

double to_double(Energy energy)
{
    return energy / GeV;
}

Energy to_energy(double energy)
{
    return energy * GeV;
}
Momentum AtRest() {
    return 0. * ElectronVolt;
}

Mass Massless() {
    return 0. * ElectronVolt;
}

}
