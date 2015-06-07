# include "Quintet.hh"

analysis::Quintet::Quintet(const analysis::Triplet &triplet, const analysis::Doublet &doublet)
{
    Print(kInformation, "Constructor");
    doublet_ = doublet;
    triplet_ = triplet;
    SetBdt((doublet_.Bdt() + triplet_.Bdt())/2);
    SetTag(doublet_.Tag() * triplet_.Tag());
}

bool analysis::Quintet::overlap() const
{
    DetectorGeometry detector_geometry;
    if (doublet_.Singlet1().delta_R(triplet_.singlet()) < detector_geometry.JetConeSize) return true;
    if (doublet_.Singlet1().delta_R(triplet_.doublet().Singlet1()) < detector_geometry.JetConeSize) return true;
    if (doublet_.Singlet1().delta_R(triplet_.doublet().Singlet2()) < detector_geometry.JetConeSize) return true;
    if (doublet_.Singlet2().delta_R(triplet_.singlet()) < detector_geometry.JetConeSize) return true;
    if (doublet_.Singlet2().delta_R(triplet_.doublet().Singlet1()) < detector_geometry.JetConeSize) return true;
    if (doublet_.Singlet2().delta_R(triplet_.doublet().Singlet2()) < detector_geometry.JetConeSize) return true;
    return false;
}


