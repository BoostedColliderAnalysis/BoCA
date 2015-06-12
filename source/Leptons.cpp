# include "Leptons.hh"
# include "Predicate.hh"

namespace analysis {

Leptons::Leptons()
{
//   DebugLevel=kDebug;
    Print(kNotification, "Constructor");
}

Leptons::~Leptons()
{
    Print(kNotification, "Destructor");
}

void Leptons::NewEvent(const ClonesArrays &clones_arrays)
{
    Print(kInformation, "New event");
    FourVector::NewEvent(clones_arrays);
}

Jets Leptons::leptons()
{
    Print(kInformation, "Lepton Jets");
    return Join(Electrons(), Muons());
}

}
