#include "boca/generic/Types.hh"
#include "boca/math/LorentzVectorBase.hh"
#include "boca/generic/DEBUG.hh"
namespace boca
{
std::string Name(LorentzDim dimension)
{
    switch (dimension) {
    case LorentzDim::x : return "x";
    case LorentzDim::y : return "y";
    case LorentzDim::z : return "z";
    case LorentzDim::t : return "t";
        DEFAULT(to_int(dimension), "");
    }
}

std::vector<LorentzDim> LorentzDimensions()
{
    return {LorentzDim::x, LorentzDim::y, LorentzDim::z, LorentzDim::t};
}

}
