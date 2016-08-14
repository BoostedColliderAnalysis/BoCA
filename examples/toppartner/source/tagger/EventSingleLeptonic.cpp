#include "include/tagger/EventSingleLeptonic.hh"
#include "boca/generic/DEBUG_MACROS.hh"

namespace toppartner
{

namespace tagger
{

std::string EventSingleLeptonic::Name() const
{
    return "EventSingleLep";
}
latex::String EventSingleLeptonic::LatexName() const
{
    return "T_{l}t_{h}h";
}

}

}
