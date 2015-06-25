# include "Hadrons.hh"

namespace analysis {

Hadrons::Hadrons()
{
//     DebugLevel = Severity::Debug;
    Print(Severity::Notification, "Constructor");
}

void Hadrons::NewEvent(const ClonesArrays &clones_arrays)
{
    Print(Severity::Information, "New event");
    FourVector::NewEvent(clones_arrays);
}

float Hadrons::ScalarHt()
{
    Print(Severity::Error, "Scalar Ht", "No Scalar Ht");
    return 0;
}

fastjet::PseudoJet Hadrons::MissingEt()
{
    Print(Severity::Error, "Missing Et", "No Mising Et");
    return fastjet::PseudoJet{};
}

}
