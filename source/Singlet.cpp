# include "Singlet.hh"

hanalysis::Singlet::Singlet(const fastjet::PseudoJet &singlet)
{
    Print(kInformation, "Constructor");
    singlet_ = singlet;
}
