#include "boca/GlobalTagger.hh"
#include "boca/Event.hh"
#include "boca/generic/DEBUG_MACROS.hh"

namespace boca
{

int GlobalTagger::Train(Event const& event, PreCuts const& , Tag tag)
{
    INFO0;
    GlobalObservables global_observables(event, bottom_reader_.Jets(event));
    global_observables.SetTag(tag);
    return SaveEntries({global_observables});
}

std::vector<GlobalObservables> GlobalTagger::Multiplets(Event const& event, PreCuts const& , TMVA::Reader const& reader)
{
    INFO0;
    GlobalObservables global_observables(event, bottom_reader_.Jets(event));
    global_observables.SetBdt(Bdt(global_observables, reader));
    return {global_observables};
}

std::string GlobalTagger::Name() const
{
    return "Global";
}

}
