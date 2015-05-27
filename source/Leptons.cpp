# include "Leptons.hh"
# include "Predicate.hh"

analysis::Leptons::Leptons()
{
//   DebugLevel=kDebug;
    Print(kNotification, "Constructor");
}

analysis::Leptons::~Leptons()
{
    Print(kNotification, "Destructor");
}

void analysis::Leptons::NewEvent(const analysis::ClonesArrays &clones_arrays)
{
    Print(kInformation, "New event");
    analysis::FourVector::NewEvent(clones_arrays);
}

analysis::Jets analysis::Leptons::leptons()
{
    Print(kInformation, "Lepton Jets");
    return JoinVectors(Electrons(), Muons());
}

