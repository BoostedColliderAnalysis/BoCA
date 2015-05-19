# include "Quartet22.hh"

analysis::Quartet22::Quartet22(const Doublet &doublet_1, const Doublet &doublet_2)
{
    Print(kInformation, "Constructor");
    doublet_1_ = doublet_1;
    doublet_2_ = doublet_2;
    SetBdt((doublet_1_.Bdt() + doublet_2_.Bdt())/2);
    SetTag(doublet_1_.Tag() * doublet_2_.Tag());
}
