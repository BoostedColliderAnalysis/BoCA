# include "Quattuordecuplet.hh"

toppartner::Quattuordecuplet::Quattuordecuplet(const analysis::Quintet &quintet_1, const analysis::Quintet &quintet_2, const analysis::Doublet &doublet_1, const analysis::Doublet &doublet_2)
{
    Print(kInformation, "Constructor");
    quintet_1_ = quintet_1;
    quintet_2_ = quintet_2;
    doublet_1_ = doublet_1;
    doublet_2_ = doublet_2;
    SetBdt((doublet_1_.Bdt() + doublet_2_.Bdt() + quintet_1_.Bdt() + quintet_2_.Bdt()) / 4);
    SetTag(doublet_1_.Tag() * doublet_2_.Tag() * quintet_1_.Tag() * quintet_2_.Tag());
}

bool toppartner::Quattuordecuplet::overlap() const
{
  //TODO find a cleaner way to implement this overlap function

  analysis::DetectorGeometry detector_geometry;
  // doublet doublet
    if (doublet_1_.Singlet1().delta_R(doublet_2_.Singlet1()) < detector_geometry.JetConeSize) return true;
    if (doublet_1_.Singlet2().delta_R(doublet_2_.Singlet1()) < detector_geometry.JetConeSize) return true;

    if (doublet_1_.Singlet1().delta_R(doublet_2_.Singlet2()) < detector_geometry.JetConeSize) return true;
    if (doublet_1_.Singlet1().delta_R(doublet_2_.Singlet2()) < detector_geometry.JetConeSize) return true;

    // doublet quintet
    if (quintet_1_.doublet().Singlet1().delta_R(doublet_1_.Singlet1()) < detector_geometry.JetConeSize) return true;
    if (quintet_1_.doublet().Singlet2().delta_R(doublet_1_.Singlet1()) < detector_geometry.JetConeSize) return true;
    if (quintet_1_.triplet().singlet().delta_R(doublet_1_.Singlet1()) < detector_geometry.JetConeSize) return true;
    if (quintet_1_.triplet().doublet().Singlet1().delta_R(doublet_1_.Singlet1()) < detector_geometry.JetConeSize) return true;
    if (quintet_1_.triplet().doublet().Singlet2().delta_R(doublet_1_.Singlet1()) < detector_geometry.JetConeSize) return true;

    if (quintet_1_.doublet().Singlet1().delta_R(doublet_1_.Singlet2()) < detector_geometry.JetConeSize) return true;
    if (quintet_1_.doublet().Singlet2().delta_R(doublet_1_.Singlet2()) < detector_geometry.JetConeSize) return true;
    if (quintet_1_.triplet().singlet().delta_R(doublet_1_.Singlet2()) < detector_geometry.JetConeSize) return true;
    if (quintet_1_.triplet().doublet().Singlet1().delta_R(doublet_1_.Singlet2()) < detector_geometry.JetConeSize) return true;
    if (quintet_1_.triplet().doublet().Singlet2().delta_R(doublet_1_.Singlet2()) < detector_geometry.JetConeSize) return true;

    if (quintet_1_.doublet().Singlet1().delta_R(doublet_2_.Singlet1()) < detector_geometry.JetConeSize) return true;
    if (quintet_1_.doublet().Singlet2().delta_R(doublet_2_.Singlet1()) < detector_geometry.JetConeSize) return true;
    if (quintet_1_.triplet().singlet().delta_R(doublet_2_.Singlet1()) < detector_geometry.JetConeSize) return true;
    if (quintet_1_.triplet().doublet().Singlet1().delta_R(doublet_2_.Singlet1()) < detector_geometry.JetConeSize) return true;
    if (quintet_1_.triplet().doublet().Singlet2().delta_R(doublet_2_.Singlet1()) < detector_geometry.JetConeSize) return true;

    if (quintet_1_.doublet().Singlet1().delta_R(doublet_2_.Singlet2()) < detector_geometry.JetConeSize) return true;
    if (quintet_1_.doublet().Singlet2().delta_R(doublet_2_.Singlet2()) < detector_geometry.JetConeSize) return true;
    if (quintet_1_.triplet().singlet().delta_R(doublet_2_.Singlet2()) < detector_geometry.JetConeSize) return true;
    if (quintet_1_.triplet().doublet().Singlet1().delta_R(doublet_2_.Singlet2()) < detector_geometry.JetConeSize) return true;
    if (quintet_1_.triplet().doublet().Singlet2().delta_R(doublet_2_.Singlet2()) < detector_geometry.JetConeSize) return true;

    // quintet quintet

    if (quintet_1_.doublet().Singlet1().delta_R(quintet_2_.doublet().Singlet1()) < detector_geometry.JetConeSize) return true;
    if (quintet_1_.doublet().Singlet1().delta_R(quintet_2_.doublet().Singlet2()) < detector_geometry.JetConeSize) return true;
    if (quintet_1_.doublet().Singlet1().delta_R(quintet_2_.triplet().singlet()) < detector_geometry.JetConeSize) return true;
    if (quintet_1_.doublet().Singlet1().delta_R(quintet_2_.triplet().doublet().Singlet1()) < detector_geometry.JetConeSize) return true;
    if (quintet_1_.doublet().Singlet1().delta_R(quintet_2_.triplet().doublet().Singlet2()) < detector_geometry.JetConeSize) return true;

    if (quintet_1_.doublet().Singlet2().delta_R(quintet_2_.doublet().Singlet1()) < detector_geometry.JetConeSize) return true;
    if (quintet_1_.doublet().Singlet2().delta_R(quintet_2_.doublet().Singlet2()) < detector_geometry.JetConeSize) return true;
    if (quintet_1_.doublet().Singlet2().delta_R(quintet_2_.triplet().singlet()) < detector_geometry.JetConeSize) return true;
    if (quintet_1_.doublet().Singlet2().delta_R(quintet_2_.triplet().doublet().Singlet1()) < detector_geometry.JetConeSize) return true;
    if (quintet_1_.doublet().Singlet2().delta_R(quintet_2_.triplet().doublet().Singlet2()) < detector_geometry.JetConeSize) return true;

    if (quintet_1_.triplet().singlet().delta_R(quintet_2_.doublet().Singlet1()) < detector_geometry.JetConeSize) return true;
    if (quintet_1_.triplet().singlet().delta_R(quintet_2_.doublet().Singlet2()) < detector_geometry.JetConeSize) return true;
    if (quintet_1_.triplet().singlet().delta_R(quintet_2_.triplet().singlet()) < detector_geometry.JetConeSize) return true;
    if (quintet_1_.triplet().singlet().delta_R(quintet_2_.triplet().doublet().Singlet1()) < detector_geometry.JetConeSize) return true;
    if (quintet_1_.triplet().singlet().delta_R(quintet_2_.triplet().doublet().Singlet2()) < detector_geometry.JetConeSize) return true;

    if (quintet_1_.triplet().doublet().Singlet1().delta_R(quintet_2_.doublet().Singlet1()) < detector_geometry.JetConeSize) return true;
    if (quintet_1_.triplet().doublet().Singlet1().delta_R(quintet_2_.doublet().Singlet2()) < detector_geometry.JetConeSize) return true;
    if (quintet_1_.triplet().doublet().Singlet1().delta_R(quintet_2_.triplet().singlet()) < detector_geometry.JetConeSize) return true;
    if (quintet_1_.triplet().doublet().Singlet1().delta_R(quintet_2_.triplet().doublet().Singlet1()) < detector_geometry.JetConeSize) return true;
    if (quintet_1_.triplet().doublet().Singlet1().delta_R(quintet_2_.triplet().doublet().Singlet2()) < detector_geometry.JetConeSize) return true;

    if (quintet_1_.triplet().doublet().Singlet2().delta_R(quintet_2_.doublet().Singlet1()) < detector_geometry.JetConeSize) return true;
    if (quintet_1_.triplet().doublet().Singlet2().delta_R(quintet_2_.doublet().Singlet2()) < detector_geometry.JetConeSize) return true;
    if (quintet_1_.triplet().doublet().Singlet2().delta_R(quintet_2_.triplet().singlet()) < detector_geometry.JetConeSize) return true;
    if (quintet_1_.triplet().doublet().Singlet2().delta_R(quintet_2_.triplet().doublet().Singlet1()) < detector_geometry.JetConeSize) return true;
    if (quintet_1_.triplet().doublet().Singlet2().delta_R(quintet_2_.triplet().doublet().Singlet2()) < detector_geometry.JetConeSize) return true;

    return false;
}
