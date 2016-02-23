#include <boost/range/algorithm/min_element.hpp>

#include "physics/Barn.hh"
#include "physics/Prefixes.hh"

namespace boca
{

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

Crosssection min(std::vector< Crosssection > vector, bool truncate)
{
  if (truncate) vector.erase(std::remove(vector.begin(), vector.end(), 0_fb), vector.end());
  return *boost::range::min_element(vector);
}
std::vector< float > FloatVector(const std::vector< boca::Crosssection >& crosssections)
{
    std::vector<float> values;
    values.reserve(crosssections.size());
    for (auto const & xsec : crosssections) values.emplace_back(float(xsec / fb));
    return values;
}

}
