#include "physics/Vector2.hh"
#include "Types.hh"
#include "DEBUG.hh"
namespace boca
{
std::string Name(Dim2 dimension)
{
    switch (dimension) {
    case Dim2::x : return "x";
    case Dim2::y : return "y";
        DEFAULT(to_int(dimension), "");
    }
}

std::vector<Dim2> Dimensions2()
{
    return {Dim2::x, Dim2::y};
}

}
