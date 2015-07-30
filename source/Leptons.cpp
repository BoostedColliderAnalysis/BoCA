#include "Leptons.hh"
#include "Predicate.hh"
#include "Debug.hh"

namespace analysis {

Leptons::~Leptons()
{
  Info();
}

void Leptons::NewEvent(const ClonesArrays& clones_arrays)
{
    Info();
    FourVector::NewEvent(clones_arrays);
}

Jets Leptons::leptons() const
{
    Info();
    return Join(Electrons(), Muons());
}

}
