#include "Partons.hh"
#include "Predicate.hh"
#include "Debug.hh"

namespace analysis {

void Partons::NewEvent(const ClonesArrays &clones_arrays) {
    Info();
    FourVector::NewEvent(clones_arrays);
}

}
