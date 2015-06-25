# include "Partons.hh"
# include "Predicate.hh"

namespace analysis {

Partons::Partons()
{
    Print(Severity::Notification,"Constructor");
}

void Partons::NewEvent(const ClonesArrays &clones_arrays) {
    Print(Severity::Information,"New event");
    FourVector::NewEvent(clones_arrays);
}

}
