#include "boca/tagger/Global.hh"
#include "boca/event/Event.hh"
#include "boca/generic/DEBUG_MACROS.hh"

namespace boca
{

namespace tagger
{

int Global::Train(Event const& event, PreCuts const& , Tag tag)
{
    INFO0;
    auto global = boca::Global{event};
    global.SetTag(tag);
    return SaveEntries({global});
}

std::vector<boca::Global> Global::Multiplets(Event const& event, PreCuts const& , TMVA::Reader const& reader)
{
    INFO0;
    auto global = boca::Global{event};
    global.SetBdt(Bdt(global, reader));
    return {global};
}

std::string Global::Name() const
{
    return "Global";
}

}

}
