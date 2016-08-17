#include "include/Tagger.hh"


int Tagger::Train(boca::Event const &event, boca::PreCuts const &pre_cuts, boca::Tag tag)
{
    Observables observables(event);
    observables.SetTag(tag);
    return SaveEntries({observables});
}

//     using boca::Tagger::Multiplets;

std::vector<Observables> Tagger::Multiplets(boca::Event const &event, boca::PreCuts const &pre_cuts, TMVA::Reader const &reader)
{
    Observables observables(event);
    observables.SetBdt(Bdt(observables, reader));
    return {observables};
}

std::string Tagger::Name() const
{
    return "Simple";
}
