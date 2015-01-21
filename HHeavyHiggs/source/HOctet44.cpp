# include "HOctet44.hh"
# include "HTagPrivate.hh"

HOctet44::HOctet44(const hanalysis::HQuartet31 &NewQuartet1, const hanalysis::HQuartet31 &NewQuartet2)
{
    Quartet1 = NewQuartet1;
    Quartet2 = NewQuartet2;
    TagPrivate->Bdt = Quartet1.Bdt() * Quartet2.Bdt();
    TagPrivate->Tag = Quartet1.Tag() * Quartet2.Tag();
}
