# include "Quattuordecuplet.hh"

toppartner::Quattuordecuplet::Quattuordecuplet(const analysis::Quintet &quintet_1, const analysis::Quintet &quintet_2, const analysis::Doublet & doublet_1, const analysis::Doublet &doublet_2)
{
  Print(kInformation, "Constructor");
  quintet_1_ = quintet_1;
  quintet_2_ = quintet_2;
    doublet_1_ = doublet_1;
    doublet_2_ = doublet_2;
    SetBdt((doublet_1_.Bdt() + doublet_2_.Bdt() + quintet_1_.Bdt() +quintet_2_.Bdt())/4);
    SetTag(doublet_1_.Tag() * doublet_2_.Tag() * quintet_1_.Tag() * quintet_2_.Tag());
}
