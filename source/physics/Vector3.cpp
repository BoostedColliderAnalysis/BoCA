#include "physics/Vector3.hh"
#include "Types.hh"
#include "DEBUG.hh"
namespace boca
{
std::string Name(Dim3 dimension)
{
    switch (dimension) {
    case Dim3::x : return "x";
    case Dim3::y : return "y";
    case Dim3::z : return "z";
        DEFAULT(to_int(dimension), "");
    }
}

std::vector<Dim3> Dimensions3()
{
    return {Dim3::x, Dim3::y, Dim3::z};
}

}
