# include "HOctet44.hh"
# include "HTagPrivate.hh"

HOctet44::HOctet44(const analysis::HQuartet31 &NewQuartet1, const analysis::HQuartet31 &NewQuartet2)
{
    Quartet1M = NewQuartet1;
    Quartet2M = NewQuartet2;
    SetBdt(Quartet1M.Bdt(),Quartet2M.Bdt());
    SetTag(Quartet1M.Tag(),Quartet2M.Tag());
}


HOctet44::HOctet44(const analysis::HQuartet31 &NewQuartet1, const analysis::HQuartet31 &NewQuartet2, const HChargedeventStruct &NeweventStruct)
{
  Quartet1M = NewQuartet1;
  Quartet2M = NewQuartet2;
  eventStructM = NeweventStruct;
  SetBdt(Quartet1M.Bdt(),Quartet2M.Bdt());
  SetTag(Quartet1M.Tag(),Quartet2M.Tag());
}
