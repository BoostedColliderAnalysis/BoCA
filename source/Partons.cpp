# include "Partons.hh"
# include "Predicate.hh"

namespace analysis {

Partons::Partons()
{
    Print(kNotification,"Constructor");
}

void Partons::NewEvent(const ClonesArrays &clones_arrays) {
    Print(kInformation,"New event");
    FourVector::NewEvent(clones_arrays);
}

}
