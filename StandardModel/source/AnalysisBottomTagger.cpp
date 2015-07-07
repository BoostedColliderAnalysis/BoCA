#include "AnalysisBottomTagger.hh"
#include "Debug.hh"

namespace analysis
{

namespace standardmodel
{

std::string Name(const Production production_channel)
{
    switch (production_channel) {
    case Associated :
        return "llbb_";
    case DYP :
        return "pp_z_";
    case VBF :
        return "VBF_";
    default:
        return "";
    }
}

}

}
