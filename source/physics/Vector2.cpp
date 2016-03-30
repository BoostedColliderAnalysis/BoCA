#include "physics/Vector2.hh"
#include "Types.hh"
#include "DEBUG.hh"
namespace boca
{
std::string Name(Dimension2 dimension)
{
    switch (dimension) {
    case Dimension2::x : return "x";
    case Dimension2::y : return "y";
        DEFAULT(to_int(dimension), "");
    }
}

std::vector<Dimension2> Dimensions2()
{
    return {Dimension2::x, Dimension2::y};
}

}
