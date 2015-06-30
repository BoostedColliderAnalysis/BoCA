#include "Leptons.hh"
#include "Predicate.hh"

namespace analysis {

Leptons::Leptons()
{
//   DebugLevel=Severity::debug;
    Print(Severity::notification, "Constructor");
}

Leptons::~Leptons()
{
    Print(Severity::notification, "Destructor");
}

void Leptons::NewEvent(const ClonesArrays &clones_arrays)
{
    Print(Severity::information, "New event");
    FourVector::NewEvent(clones_arrays);
}

Jets Leptons::leptons()
{
    Print(Severity::information, "Lepton Jets");
    return Join(Electrons(), Muons());
}

}
