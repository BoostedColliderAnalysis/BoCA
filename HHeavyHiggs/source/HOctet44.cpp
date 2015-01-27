# include "HOctet44.hh"
# include "HTagPrivate.hh"

HOctet44::HOctet44(const hanalysis::HQuartet31 &NewQuartet1, const hanalysis::HQuartet31 &NewQuartet2)
{
    Quartet1M = NewQuartet1;
    Quartet2M = NewQuartet2;
    TagPrivate->Bdt = Quartet1M.Bdt() * Quartet2M.Bdt();
    TagPrivate->Tag = Quartet1M.Tag() * Quartet2M.Tag();
}


HOctet44::HOctet44(const hanalysis::HQuartet31 &NewQuartet1, const hanalysis::HQuartet31 &NewQuartet2, const HChargedEventStruct &NewEventStruct)
{
  Quartet1M = NewQuartet1;
  Quartet2M = NewQuartet2;
  EventStructM = NewEventStruct;
  TagPrivate->Bdt = Quartet1M.Bdt() * Quartet2M.Bdt();
  TagPrivate->Tag = Quartet1M.Tag() * Quartet2M.Tag();
}
