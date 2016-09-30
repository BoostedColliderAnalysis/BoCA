#include "boca/generic/Types.hh"
#include "boca/math/Vector3.hh"
#include "boca/generic/DEBUG_MACROS.hh"

namespace boca
{

std::string Name(Dim3 dimension)
{
    switch (dimension) {
    case Dim3::x :
        return "x";
    case Dim3::y :
        return "y";
    case Dim3::z :
        return "z";
        DEFAULT(to_int(dimension), "");
    }
}

std::vector<Dim3> Dimensions3()
{
    return {Dim3::x, Dim3::y, Dim3::z};
}

Dim3 Third(Dim3 dim_1,  Dim3 dim_2)
{
    switch (dim_1) {
    case Dim3::x :
        return dim_2 == Dim3::y ? Dim3::z : Dim3::y;
    case Dim3::y :
        return dim_2 == Dim3::z ? Dim3::x : Dim3::z;
    case Dim3::z :
        return dim_2 == Dim3::x ? Dim3::y : Dim3::x;
    default :
        return Dim3::last;
    }
}

Dim3 Next(Dim3 dim) {
      switch (dim) {
    case Dim3::x :
        return Dim3::y;
    case Dim3::y :
        return Dim3::z;
    case Dim3::z :
        return Dim3::x;
    default :
        return Dim3::last;
    }
}

}
