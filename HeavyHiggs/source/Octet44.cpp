# include "Octet44.hh"
//# include "HTagPrivate.hh"

Octet44::Octet44(const analysis::Quartet31 &quartet_1, const analysis::Quartet31 &quartet_2)
{
    quartet_1_ = quartet_1;
    quartet_2_ = quartet_2;
    SetBdt(quartet_1_.Bdt(), quartet_2_.Bdt());
    SetTag(quartet_1_.Tag(), quartet_2_.Tag());
}


Octet44::Octet44(const analysis::Quartet31 &quartet_1, const analysis::Quartet31 &quartet_2, const EventStructCharged &global_observables)
{
    Octet44(quartet_1, quartet_2);
    global_observables_ = global_observables;
}
