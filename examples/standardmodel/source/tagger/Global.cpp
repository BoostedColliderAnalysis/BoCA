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
    auto global_observables = boca::GlobalObservables{event, bottom_reader_.Jets(event)};
    global_observables.SetTag(tag);
    return SaveEntries({global_observables});
}

std::vector<boca::GlobalObservables> Global::Multiplets(boca::Event const& event, boca::PreCuts const& , TMVA::Reader const& reader)
{
    INFO0;
    auto global_observables = boca::GlobalObservables{event, bottom_reader_.Jets(event)};
    global_observables.SetBdt(Bdt(global_observables, reader));
    return {global_observables};
}

std::string Global::Name() const
{
    return "Global";
}

}

}
