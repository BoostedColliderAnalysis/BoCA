#include "generic/Types.hh"
#include "math/LorentzVectorBase.hh"
#include "generic/DEBUG.hh"
namespace boca
{
std::string Name(LorentzDim dimension)
{
    switch (dimension) {
    case LorentzDim::t : return "t";
    case LorentzDim::x : return "x";
    case LorentzDim::y : return "y";
    case LorentzDim::z : return "z";
        DEFAULT(to_int(dimension), "");
    }
}

std::vector<LorentzDim> LorentzDimensions()
{
    return {LorentzDim::t, LorentzDim::x, LorentzDim::y, LorentzDim::z};
}

}
