#include "Units.hh"
#include <sstream>

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
    string.erase(std::remove_if(string.begin(), string.end(), isspace), string.end());
    return string;
}

int Int(boost::units::quantity< electronvolt::energy > energy)
{
    return energy / GeV;
}

int Float(boost::units::quantity< electronvolt::energy > energy)
{
  return energy / GeV;
}

}
