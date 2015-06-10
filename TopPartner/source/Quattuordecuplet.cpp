# include "Quattuordecuplet.hh"


bool toppartner::Quattuordecuplet::overlap() const
{
    analysis::DetectorGeometry detector_geometry;
    if (Decuplet().Quintet1().Triplet().Doublet().Singlet1().delta_R(Quartet().Doublet1().Singlet1()) < detector_geometry.JetConeSize) return true;
    if (Decuplet().Quintet1().Triplet().Doublet().Singlet1().delta_R(Quartet().Doublet1().Singlet2()) < detector_geometry.JetConeSize) return true;
    if (Decuplet().Quintet1().Triplet().Doublet().Singlet1().delta_R(Quartet().Doublet2().Singlet1()) < detector_geometry.JetConeSize) return true;
    if (Decuplet().Quintet1().Triplet().Doublet().Singlet1().delta_R(Quartet().Doublet2().Singlet2()) < detector_geometry.JetConeSize) return true;

    if (Decuplet().Quintet1().Triplet().Doublet().Singlet2().delta_R(Quartet().Doublet1().Singlet1()) < detector_geometry.JetConeSize) return true;
    if (Decuplet().Quintet1().Triplet().Doublet().Singlet2().delta_R(Quartet().Doublet1().Singlet2()) < detector_geometry.JetConeSize) return true;
    if (Decuplet().Quintet1().Triplet().Doublet().Singlet2().delta_R(Quartet().Doublet2().Singlet1()) < detector_geometry.JetConeSize) return true;
    if (Decuplet().Quintet1().Triplet().Doublet().Singlet2().delta_R(Quartet().Doublet2().Singlet2()) < detector_geometry.JetConeSize) return true;

    if (Decuplet().Quintet1().Triplet().SingletJet().delta_R(Quartet().Doublet1().Singlet1()) < detector_geometry.JetConeSize) return true;
    if (Decuplet().Quintet1().Triplet().SingletJet().delta_R(Quartet().Doublet1().Singlet2()) < detector_geometry.JetConeSize) return true;
    if (Decuplet().Quintet1().Triplet().SingletJet().delta_R(Quartet().Doublet2().Singlet1()) < detector_geometry.JetConeSize) return true;
    if (Decuplet().Quintet1().Triplet().SingletJet().delta_R(Quartet().Doublet2().Singlet2()) < detector_geometry.JetConeSize) return true;


    if (Decuplet().Quintet1().Doublet().Singlet1().delta_R(Quartet().Doublet1().Singlet1()) < detector_geometry.JetConeSize) return true;
    if (Decuplet().Quintet1().Doublet().Singlet1().delta_R(Quartet().Doublet1().Singlet2()) < detector_geometry.JetConeSize) return true;
    if (Decuplet().Quintet1().Doublet().Singlet1().delta_R(Quartet().Doublet2().Singlet1()) < detector_geometry.JetConeSize) return true;
    if (Decuplet().Quintet1().Doublet().Singlet1().delta_R(Quartet().Doublet2().Singlet2()) < detector_geometry.JetConeSize) return true;



    if (Decuplet().Quintet1().Doublet().Singlet2().delta_R(Quartet().Doublet1().Singlet1()) < detector_geometry.JetConeSize) return true;
    if (Decuplet().Quintet1().Doublet().Singlet2().delta_R(Quartet().Doublet1().Singlet2()) < detector_geometry.JetConeSize) return true;
    if (Decuplet().Quintet1().Doublet().Singlet2().delta_R(Quartet().Doublet2().Singlet1()) < detector_geometry.JetConeSize) return true;
    if (Decuplet().Quintet1().Doublet().Singlet2().delta_R(Quartet().Doublet2().Singlet2()) < detector_geometry.JetConeSize) return true;

    return false;
}
