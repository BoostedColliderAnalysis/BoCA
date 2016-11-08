/**
 * Copyright (C) 2015-2016 Jan Hajer
 */

#include <sstream>

#include <boost/range/algorithm_ext/erase.hpp>
#include <boost/units/systems/si/io.hpp>

#include "boca/units/ElectronVolt.hh"
#include "boca/units/Prefixes.hh"

namespace boca
{

namespace units
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

std::string Name(Energy const& energy)
{
    std::stringstream stream;
    stream << boost::units::engineering_prefix << energy;
    auto string = stream.str();
    return boost::range::remove_erase_if(string, isspace);
}

}

}
