#include "Partons.hh"
#include "Predicate.hh"
#include "Debug.hh"

namespace analysis {

Partons::Partons()
{
    Note("Constructor");
}

void Partons::NewEvent(const ClonesArrays &clones_arrays) {
    Info("New event");
    FourVector::NewEvent(clones_arrays);
}

}
