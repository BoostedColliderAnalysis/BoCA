# include "HOctet44.hh"

HOctet44::HOctet44(const hanalysis::HQuartet31 &NewQuartet1, const hanalysis::HQuartet31 &NewQuartet2)
{
    Quartet1 = NewQuartet1;
    Quartet2 = NewQuartet2;
    Bdt = Quartet1.GetBdt() * Quartet2.GetBdt();
    Tag = Quartet1.GetTag() * Quartet2.GetTag();
}
