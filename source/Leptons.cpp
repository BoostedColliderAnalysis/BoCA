# include "Leptons.hh"
# include "Predicate.hh"

namespace analysis {

Leptons::Leptons()
{
//   DebugLevel=Severity::Debug;
    Print(Severity::Notification, "Constructor");
}

Leptons::~Leptons()
{
    Print(Severity::Notification, "Destructor");
}

void Leptons::NewEvent(const ClonesArrays &clones_arrays)
{
    Print(Severity::Information, "New event");
    FourVector::NewEvent(clones_arrays);
}

Jets Leptons::leptons()
{
    Print(Severity::Information, "Lepton Jets");
    return Join(Electrons(), Muons());
}

}
