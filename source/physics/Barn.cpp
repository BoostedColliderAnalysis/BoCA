#include <boost/range/algorithm/min_element.hpp>
#include <boost/range/algorithm_ext/erase.hpp>

#include "boca/physics/Barn.hh"
#include "boca/physics/Prefixes.hh"
#include "boca/generic/Vector.hh"

namespace boca
{

double to_double(Crosssection const& crosssection)
{
    return crosssection / fb;
}

Crosssection to_crosssection(double crosssection)
{
    return crosssection * fb;
}

double to_double(Luminosity const& luminosity)
{
    return luminosity * fb;
}

Luminosity to_luminosity(double luminosity)
{
    return luminosity / fb;
}

Crosssection min(std::vector< Crosssection > vector, bool truncate)
{
    if (truncate) boost::range::remove_erase(vector, 0_fb);
    return *boost::range::min_element(vector);
}

std::vector< double > FloatVector(const std::vector< boca::Crosssection >& crosssections)
{
    return Transform(crosssections, [](Crosssection const & crosssection) -> double {
        return crosssection / fb;
    });
}

}
