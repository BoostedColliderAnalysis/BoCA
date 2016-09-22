#include <boost/range/algorithm/min_element.hpp>
#include <boost/range/algorithm_ext/erase.hpp>

#include "boca/physics/Barn.hh"
#include "boca/physics/Prefixes.hh"
#include "boca/generic/Vector.hh"

namespace boca
{

namespace units
{

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

}
