#include "Leptons.hh"
#include "Predicate.hh"
#include "Debug.hh"

namespace analysis {

Leptons::~Leptons()
{
    Note("Destructor");
}

void Leptons::NewEvent(const ClonesArrays &clones_arrays)
{
    Info("New event");
    FourVector::NewEvent(clones_arrays);
}

Jets Leptons::leptons()
{
    Info("Lepton Jets");
    return Join(Electrons(), Muons());
}

}
