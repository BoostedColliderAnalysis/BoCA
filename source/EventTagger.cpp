#include "EventTagger.hh"
#include "Event.hh"
#include "Debug.hh"

namespace boca
{

int EventTagger::Train(boca::Event const& event, PreCuts const& , Tag tag) const
{
    INFO0;
    boca::GlobalObservables global_observables(event);
    global_observables.SetJets(bottom_reader_.Jets(event));
    global_observables.SetTag(tag);
    return SaveEntries({global_observables});
}

std::vector<GlobalObservables> EventTagger::Multiplets(Event const& event, PreCuts const& , TMVA::Reader const& reader) const
{
    INFO0;
    boca::GlobalObservables global_observables(event);
    global_observables.SetJets(bottom_reader_.Jets(event));
    global_observables.SetBdt(Bdt(global_observables, reader));
    return {global_observables};
}

std::string EventTagger::Name() const
{
    return "GlobalObservables";
}

}
