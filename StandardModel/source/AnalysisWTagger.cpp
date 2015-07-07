#include "AnalysisWTagger.hh"
#include "Debug.hh"

namespace analysis
{

namespace standardmodel
{

std::string WName(const Decay decay)
{
    switch (decay) {
    case Decay::hadronic :
        return "hadronic";
    case Decay::semi :
        return "semi";
    }
}

}

}
