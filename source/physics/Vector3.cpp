#include "physics/Vector3.hh"
#include "Types.hh"
#include "DEBUG.hh"
namespace boca
{
std::string Name(Dimension3 dimension)
{
    switch (dimension) {
    case Dimension3::x : return "x";
    case Dimension3::y : return "y";
    case Dimension3::z : return "z";
        DEFAULT(to_int(dimension), "");
    }
}

std::vector<Dimension3> Dimensions3()
{
    return {Dimension3::x, Dimension3::y, Dimension3::z};
}

}
