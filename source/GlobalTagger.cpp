#include "GlobalTagger.hh"
#include "Event.hh"
#include "DEBUG.hh"

namespace boca
{

int GlobalTagger::Train(boca::Event const& event, PreCuts const& , Tag tag) const
{
    INFO0;
    boca::GlobalObservables global_observables(event, bottom_reader_.Jets(event));
    global_observables.SetTag(tag);
    return SaveEntries({global_observables});
}

std::vector<GlobalObservables> GlobalTagger::Multiplets(Event const& event, PreCuts const& , TMVA::Reader const& reader) const
{
    INFO0;
    boca::GlobalObservables global_observables(event, bottom_reader_.Jets(event));
    global_observables.SetBdt(Bdt(global_observables, reader));
    return {global_observables};
}

std::string GlobalTagger::Name() const
{
    return "Global";
}

}
