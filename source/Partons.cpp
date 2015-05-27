# include "Partons.hh"
# include "Predicate.hh"

analysis::Partons::Partons()
{
    Print(kNotification,"Constructor");
}

void analysis::Partons::NewEvent(const ClonesArrays &clones_arrays) {
    Print(kInformation,"New event");
    analysis::FourVector::NewEvent(clones_arrays);
}
