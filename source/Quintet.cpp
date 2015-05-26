# include "Quintet.hh"

analysis::Quintet::Quintet(const analysis::Triplet &triplet, const analysis::Doublet &doublet)
{
    Print(kInformation, "Constructor");
    doublet_ = doublet;
    triplet_ = triplet;
    SetBdt((doublet_.Bdt() + triplet_.Bdt())/2);
    SetTag(doublet_.Tag() * triplet_.Tag());
}
