# include "Hadrons.hh"

namespace analysis {

Hadrons::Hadrons()
{
//     DebugLevel = kDebug;
    Print(kNotification, "Constructor");
}

void Hadrons::NewEvent(const ClonesArrays &clones_arrays)
{
    Print(kInformation, "New event");
    FourVector::NewEvent(clones_arrays);
}

float Hadrons::ScalarHt()
{
    Print(kError, "Scalar Ht", "No Scalar Ht");
    return 0;
}

fastjet::PseudoJet Hadrons::MissingEt()
{
    Print(kError, "Missing Et", "No Mising Et");
    return fastjet::PseudoJet{};
}

}
