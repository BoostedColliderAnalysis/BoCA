#include "Hadrons.hh"
#include "Debug.hh"

namespace analysis {

void Hadrons::NewEvent(const ClonesArrays &clones_arrays)
{
    Info("New event");
    FourVector::NewEvent(clones_arrays);
}

float Hadrons::ScalarHt()
{
    Error("Scalar Ht", "No Scalar Ht");
    return 0;
}

fastjet::PseudoJet Hadrons::MissingEt()
{
    Error("Missing Et", "No Mising Et");
    return fastjet::PseudoJet{};
}

}
