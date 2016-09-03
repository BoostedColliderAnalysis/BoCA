#include "toppartner/tagger/EventPair.hh"
// #define DEBUGGING
#include "boca/generic/DEBUG_MACROS.hh"

namespace toppartner
{

namespace tagger
{

std::string EventPair::Name() const
{
    return "EventPair";
}

latex::String EventPair::LatexName() const
{
    return {"T_{h} T_{l}", true};
}

}

}
