#include "physics/LorentzVectorBase.hh"
#include "Types.hh"
#include "DEBUG.hh"
namespace boca
{
std::string Name(LorentzDimension dimension)
{
    switch (dimension) {
    case LorentzDimension::t : return "t";
    case LorentzDimension::x : return "x";
    case LorentzDimension::y : return "y";
    case LorentzDimension::z : return "z";
        DEFAULT(to_int(dimension), "");
    }
}

std::vector<LorentzDimension> Dimensions3()
{
    return {LorentzDimension::t, LorentzDimension::x, LorentzDimension::y, LorentzDimension::z};
}

}
