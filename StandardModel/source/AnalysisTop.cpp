#include "AnalysisTop.hh"
#include "Debug.hh"

namespace analysis
{

namespace standardmodel
{

std::string Name(const Decay decay)
{
    switch (decay) {
    case Decay::hadronic :
        return "hadronic";
    case Decay::leptonic :
        return "leptonic";
    case Decay::semi :
        return "semi";
    }
}

}

}
