# include "HOctet44.hh"
//# include "HTagPrivate.hh"

HOctet44::HOctet44(const analysis::Quartet31 &Newquartet1, const analysis::Quartet31 &Newquartet2)
{
    quartet1M = Newquartet1;
    quartet2M = Newquartet2;
    SetBdt(quartet1M.Bdt(),quartet2M.Bdt());
    SetTag(quartet1M.Tag(),quartet2M.Tag());
}


HOctet44::HOctet44(const analysis::Quartet31 &Newquartet1, const analysis::Quartet31 &Newquartet2, const HChargedevent_struct &Newevent_struct)
{
  quartet1M = Newquartet1;
  quartet2M = Newquartet2;
  event_structM = Newevent_struct;
  SetBdt(quartet1M.Bdt(),quartet2M.Bdt());
  SetTag(quartet1M.Tag(),quartet2M.Tag());
}
