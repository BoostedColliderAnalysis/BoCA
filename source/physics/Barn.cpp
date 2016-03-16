#include <boost/range/algorithm/min_element.hpp>
#include <boost/range/algorithm/transform.hpp>

#include "physics/Barn.hh"
#include "physics/Prefixes.hh"

namespace boca
{

double to_double(Crosssection crosssection)
{
  return crosssection / fb;
}

Crosssection to_crosssection(double crosssection)
{
  return crosssection * fb;
}

double to_double(Luminosity luminosity)
{
  return luminosity * fb;
}

Luminosity to_luminosity(double luminosity)
{
  return luminosity / fb;
}

Crosssection min(std::vector< Crosssection > vector, bool truncate)
{
  if (truncate) vector.erase(std::remove(vector.begin(), vector.end(), 0_fb), vector.end());
  return *boost::range::min_element(vector);
}

std::vector< double > FloatVector(const std::vector< boca::Crosssection >& crosssections)
{
    std::vector<double> values;
    values.reserve(crosssections.size());
    for (auto const & crosssection : crosssections) values.emplace_back(crosssection / fb);
//     boost::range::transform(crosssections, std::back_inserter(values), [](boca::Crosssection crosssection) { return crosssection / fb;});
    return values;
}

}
