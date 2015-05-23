# include "Octet62.hh"

Octet62::Octet62(const analysis::Sextet &sextet, const analysis::Doublet &doublet)
{
    sextet_ = sextet;
    doublet_ = doublet;
    SetBdt(sextet_.Bdt(),doublet_.Bdt());
    SetTag(sextet_.Tag(),doublet_.Tag());
}
