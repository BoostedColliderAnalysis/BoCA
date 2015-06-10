# include "Quintet.hh"

bool analysis::Quintet::overlap() const
{
    DetectorGeometry detector_geometry;
    if (Doublet().Singlet1().delta_R(Triplet().SingletJet()) < detector_geometry.JetConeSize) return true;
    if (Doublet().Singlet1().delta_R(Triplet().Doublet().Singlet1()) < detector_geometry.JetConeSize) return true;
    if (Doublet().Singlet1().delta_R(Triplet().Doublet().Singlet2()) < detector_geometry.JetConeSize) return true;
    if (Doublet().Singlet2().delta_R(Triplet().SingletJet()) < detector_geometry.JetConeSize) return true;
    if (Doublet().Singlet2().delta_R(Triplet().Doublet().Singlet1()) < detector_geometry.JetConeSize) return true;
    if (Doublet().Singlet2().delta_R(Triplet().Doublet().Singlet2()) < detector_geometry.JetConeSize) return true;
    return false;
}


