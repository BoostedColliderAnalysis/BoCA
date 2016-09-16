#include "boca/Event.hh"
#include "standardmodel/tagger/Global.hh"
#include "boca/generic/DEBUG_MACROS.hh"

namespace standardmodel
{

namespace tagger
{

int Global::Train(boca::Event const& event, boca::PreCuts const& , boca::Tag tag)
{
    INFO0;
    auto global = boca::Global{event, bottom_reader_.Jets(event)};
    global.SetTag(tag);
    return SaveEntries({global});
}

std::vector<boca::Global> Global::Multiplets(boca::Event const& event, boca::PreCuts const& , TMVA::Reader const& reader)
{
    INFO0;
    auto global = boca::Global{event, bottom_reader_.Jets(event)};
    global.SetBdt(Bdt(global, reader));
    return {global};
}

std::string Global::Name() const
{
    return "Global";
}

}

}
