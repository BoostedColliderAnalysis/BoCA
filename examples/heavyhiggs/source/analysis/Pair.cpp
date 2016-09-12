#include "heavyhiggs/analysis/Pair.hh"
#include "boca/generic/DEBUG_MACROS.hh"

namespace heavyhiggs
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
