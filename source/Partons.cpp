# include "Partons.hh"
# include "Predicate.hh"

namespace analysis {

Partons::Partons()
{
    Print(Severity::notification,"Constructor");
}

void Partons::NewEvent(const ClonesArrays &clones_arrays) {
    Print(Severity::information,"New event");
    FourVector::NewEvent(clones_arrays);
}

}
