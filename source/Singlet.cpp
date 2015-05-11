# include "Singlet.hh"

hanalysis::Singlet::Singlet(const fastjet::PseudoJet &singlet)
{
    Print(HInformation, "Constructor");
    singlet_ = singlet;
}
