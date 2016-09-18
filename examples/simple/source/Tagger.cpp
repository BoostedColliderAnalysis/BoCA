#include "simple/Tagger.hh"

namespace simple
{

int Tagger::Train(boca::Event const &event, boca::PreCuts const &, boca::Tag tag)
{
    // Create one object of the the Observables and pass it the full event information
    Observables observables(event);
    // save also weather the Tag is signal or background
    observables.SetTag(tag);
    // Save the observables to the root file and return the number of saved objects (in this case always one)
    return SaveEntries({observables});
}

std::vector<Observables> Tagger::Multiplets(boca::Event const &event, boca::PreCuts const &, TMVA::Reader const &reader)
{
    // Create one object of the the Observables and pass it the full event information
    Observables observables(event);
    // save also the BDT response to this object
    observables.SetBdt(Bdt(observables, reader));
    // return all objects (in this case only one)
    return {observables};
}

std::string Tagger::Name() const
{
    return "Simple";
}

}
