#include "boca/tagger/Global.hh"
#include "boca/Event.hh"
#include "boca/generic/DEBUG_MACROS.hh"

namespace boca
{

namespace tagger
{

int Global::Train(Event const& event, PreCuts const& , Tag tag)
{
    INFO0;
    auto global_observables = GlobalObservables{event, bottom_reader_.Jets(event)};
    global_observables.SetTag(tag);
    return SaveEntries({global_observables});
}

std::vector<GlobalObservables> Global::Multiplets(Event const& event, PreCuts const& , TMVA::Reader const& reader)
{
    INFO0;
    auto global_observables = GlobalObservables{event, bottom_reader_.Jets(event)};
    global_observables.SetBdt(Bdt(global_observables, reader));
    return {global_observables};
}

std::string Global::Name() const
{
    return "Global";
}

}

}
