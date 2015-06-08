# include "Octet44.hh"

heavyhiggs::Octet44::Octet44(const analysis::Quartet31 &quartet_1, const analysis::Quartet31 &quartet_2)
{
    quartet_1_ = quartet_1;
    quartet_2_ = quartet_2;
    SetBdt(quartet_1_.Bdt(), quartet_2_.Bdt());
    SetTag(quartet_1_.Tag(), quartet_2_.Tag());
}

bool heavyhiggs::Octet44::overlap() const
{
    analysis::DetectorGeometry detector_geometry;
    if (quartet_1_.singlet().delta_R(quartet_2_.singlet()) < detector_geometry.JetConeSize) return true;
    if (quartet_1_.singlet().delta_R(quartet_2_.triplet().singlet()) < detector_geometry.JetConeSize) return true;
    if (quartet_1_.singlet().delta_R(quartet_2_.triplet().doublet().Singlet1()) < detector_geometry.JetConeSize) return true;
    if (quartet_1_.singlet().delta_R(quartet_2_.triplet().doublet().Singlet2()) < detector_geometry.JetConeSize) return true;
    if (quartet_1_.triplet().singlet().delta_R(quartet_2_.singlet()) < detector_geometry.JetConeSize) return true;
    if (quartet_1_.triplet().singlet().delta_R(quartet_2_.triplet().singlet()) < detector_geometry.JetConeSize) return true;
    if (quartet_1_.triplet().singlet().delta_R(quartet_2_.triplet().doublet().Singlet1()) < detector_geometry.JetConeSize) return true;
    if (quartet_1_.triplet().singlet().delta_R(quartet_2_.triplet().doublet().Singlet2()) < detector_geometry.JetConeSize) return true;
    if (quartet_1_.triplet().doublet().Singlet1().delta_R(quartet_2_.singlet()) < detector_geometry.JetConeSize) return true;
    if (quartet_1_.triplet().doublet().Singlet1().delta_R(quartet_2_.triplet().singlet()) < detector_geometry.JetConeSize) return true;
    if (quartet_1_.triplet().doublet().Singlet1().delta_R(quartet_2_.triplet().doublet().Singlet1()) < detector_geometry.JetConeSize) return true;
    if (quartet_1_.triplet().doublet().Singlet1().delta_R(quartet_2_.triplet().doublet().Singlet2()) < detector_geometry.JetConeSize) return true;
    if (quartet_1_.triplet().doublet().Singlet2().delta_R(quartet_2_.singlet()) < detector_geometry.JetConeSize) return true;
    if (quartet_1_.triplet().doublet().Singlet2().delta_R(quartet_2_.triplet().singlet()) < detector_geometry.JetConeSize) return true;
    if (quartet_1_.triplet().doublet().Singlet2().delta_R(quartet_2_.triplet().doublet().Singlet1()) < detector_geometry.JetConeSize) return true;
    if (quartet_1_.triplet().doublet().Singlet2().delta_R(quartet_2_.triplet().doublet().Singlet2()) < detector_geometry.JetConeSize) return true;
    return false;
}

bool heavyhiggs::Octet44::overlap(const fastjet::PseudoJet &jet) const
{
    analysis::DetectorGeometry detector_geometry;
    if (jet.delta_R(quartet1().singlet()) < detector_geometry.JetConeSize) return true;
    if (jet.delta_R(quartet1().triplet().singlet()) < detector_geometry.JetConeSize) return true;
    if (jet.delta_R(quartet1().triplet().doublet().Singlet1()) < detector_geometry.JetConeSize) return true;
    if (jet.delta_R(quartet1().triplet().doublet().Singlet2()) < detector_geometry.JetConeSize) return true;
    if (jet.delta_R(quartet2().singlet()) < detector_geometry.JetConeSize) return true;
    if (jet.delta_R(quartet2().triplet().singlet()) < detector_geometry.JetConeSize) return true;
    return false;
}
