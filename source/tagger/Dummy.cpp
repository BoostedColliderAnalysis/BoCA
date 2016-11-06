#include "boca/tagger/Dummy.hh"
#include "boca/event/Event.hh"
#include "boca/generic/DEBUG_MACROS.hh"

namespace boca
{

namespace tagger
{

int Dummy::Train(Event const&, PreCuts const& , Tag)
{
    INFO0;
    return 1;
}

std::vector<boca::Global> Dummy::Multiplets(Event const&, PreCuts const& , TMVA::Reader const&)
{
    INFO0;
    return {};
}

std::string Dummy::Name() const
{
    return "Dummy";
}

}

}
