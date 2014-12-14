# include "HOctet.hh"

HOctet::HOctet(const hanalysis::HSextet &NewSextet, const hanalysis::HDoublet &NewDoublet)
{
    Sextet = NewSextet;
    Doublet = NewDoublet;
    Bdt = Sextet.GetBdt() * Doublet.GetBdt();
    Tag = Sextet.GetTag() * Doublet.GetTag();
}
