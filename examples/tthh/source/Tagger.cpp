#include "tthh/Tagger.hh"

namespace tthh {

int Tagger::Train(boca::Event const &event, boca::PreCuts const &, boca::Tag tag)
{
    Observables observables(event);
    observables.SetTag(tag);
    return SaveEntries({observables});
}

std::vector<Observables> Tagger::Multiplets(boca::Event const &event, boca::PreCuts const &, TMVA::Reader const &reader)
{
    Observables observables(event);
    observables.SetBdt(Bdt(observables, reader));
    return {observables};
}

std::string Tagger::Name() const
{
    return "tthh";
}

TMVA::Types::EMVA Tagger::Mva() const
{
    return TMVA::Types::EMVA::kCuts;
    return TMVA::Types::EMVA::kBDT;
}


}
