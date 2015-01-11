# include "HOctet.hh"

HOctet::HOctet(const hanalysis::HSextet &NewSextet, const hanalysis::HDoublet &NewDoublet)
{
    Sextet = NewSextet;
    Doublet = NewDoublet;
    Bdt = Sextet.GetBdt() * Doublet.GetBdt();
    Tag = Sextet.GetTag() * Doublet.GetTag();
}

HOctet::HOctet(const hanalysis::HSextet &NewSextet, const hanalysis::HDoublet &NewDoublet, const HEventStruct &NewEventStruct)
{
  Sextet = NewSextet;
  Doublet = NewDoublet;
  EventStruct = NewEventStruct;
  Bdt = Sextet.GetBdt() * Doublet.GetBdt();
  Tag = Sextet.GetTag() * Doublet.GetTag();
}
