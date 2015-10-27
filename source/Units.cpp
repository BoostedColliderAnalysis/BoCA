#include "Units.hh"

#include <sstream>

#include <boost/range/algorithm/remove_if.hpp>

namespace boca
{

namespace electronvolt
{

std::string energy_base_unit::name()
{
    return "electronvolt";
}

std::string energy_base_unit::symbol()
{
    return "eV";
}

}

std::string Name(boost::units::quantity< electronvolt::energy > energy)
{
    std::stringstream stream;
    stream << boost::units::engineering_prefix << energy;
    std::string string = stream.str();
    string.erase(boost::range::remove_if(string, isspace), string.end());
    return string;
}

int Int(Momentum energy)
{
    return energy / GeV;
}

float to_float(boost::units::quantity< electronvolt::energy > energy)
{
  return energy / GeV;
}

boost::units::quantity< electronvolt::energy > to_energy(double energy){
  return energy * GeV;
}

float to_float(Crosssection crosssection)
{
  return crosssection / fb;
}

Crosssection to_crosssection(float crosssection)
{
  return double(crosssection) * fb;
}

float to_float(Luminosity luminosity)
{
  return (luminosity * fb);
}

Luminosity to_luminosity(float luminosity)
{
  return double(luminosity) / fb;
}

float to_float(Length length)
{
  return (length / mm);
}

Length to_length(float length)
{
  return double(length) * mm;
}

float to_float(Angle angle)
{
  return (angle / rad);
}

Angle to_angle(float angle)
{
  return double(angle) * rad;
}


}
