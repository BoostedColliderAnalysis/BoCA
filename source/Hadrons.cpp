# include "Hadrons.hh"

analysis::Hadrons::Hadrons()
{
//     DebugLevel = kDebug;
    Print(kNotification, "Constructor");
}

void analysis::Hadrons::NewEvent(const analysis::ClonesArrays &clones_arrays)
{
    Print(kInformation, "New event");
    analysis::FourVector::NewEvent(clones_arrays);
}

float analysis::Hadrons::ScalarHt()
{
    Print(kError, "Scalar Ht", "No Scalar Ht");
    return 0;
}

fastjet::PseudoJet analysis::Hadrons::MissingEt()
{
    Print(kError, "Missing Et", "No Mising Et");
    return fastjet::PseudoJet{};
}
