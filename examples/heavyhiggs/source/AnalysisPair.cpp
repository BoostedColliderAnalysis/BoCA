#include "include/analysis/Pair.hh"
#include "boca/generic/DEBUG.hh"

namespace heavyhiggs
{

namespace analysis
{

std::string Name(Production production)
{
    switch (production) {
    case Production::Associated : return "llbb_";
    case Production::DYP : return "pp_z_";
    case Production::VBF : return "VBF_";
    default:
        ERROR("ProductionChannelName", "unhandeld case");
        return "";
    }
}

}

}
