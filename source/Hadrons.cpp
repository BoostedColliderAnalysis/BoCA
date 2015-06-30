#include "Hadrons.hh"

namespace analysis {

Hadrons::Hadrons()
{
//     DebugLevel = Severity::debug;
    Print(Severity::notification, "Constructor");
}

void Hadrons::NewEvent(const ClonesArrays &clones_arrays)
{
    Print(Severity::information, "New event");
    FourVector::NewEvent(clones_arrays);
}

float Hadrons::ScalarHt()
{
    Print(Severity::error, "Scalar Ht", "No Scalar Ht");
    return 0;
}

fastjet::PseudoJet Hadrons::MissingEt()
{
    Print(Severity::error, "Missing Et", "No Mising Et");
    return fastjet::PseudoJet{};
}

}
