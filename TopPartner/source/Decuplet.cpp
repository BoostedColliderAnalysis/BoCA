# include "Decuplet.hh"


bool toppartner::Decuplet::overlap() const
{

  analysis::DetectorGeometry detector_geometry;

  if (Quintet1().Doublet().Singlet1().delta_R(Quintet2().Doublet().Singlet1()) < detector_geometry.JetConeSize) return true;
  if (Quintet1().Doublet().Singlet1().delta_R(Quintet2().Doublet().Singlet2()) < detector_geometry.JetConeSize) return true;
  if (Quintet1().Doublet().Singlet1().delta_R(Quintet2().Triplet().SingletJet()) < detector_geometry.JetConeSize) return true;
  if (Quintet1().Doublet().Singlet1().delta_R(Quintet2().Triplet().Doublet().Singlet1()) < detector_geometry.JetConeSize) return true;
  if (Quintet1().Doublet().Singlet1().delta_R(Quintet2().Triplet().Doublet().Singlet2()) < detector_geometry.JetConeSize) return true;

  if (Quintet1().Doublet().Singlet2().delta_R(Quintet2().Doublet().Singlet1()) < detector_geometry.JetConeSize) return true;
  if (Quintet1().Doublet().Singlet2().delta_R(Quintet2().Doublet().Singlet2()) < detector_geometry.JetConeSize) return true;
  if (Quintet1().Doublet().Singlet2().delta_R(Quintet2().Triplet().SingletJet()) < detector_geometry.JetConeSize) return true;
  if (Quintet1().Doublet().Singlet2().delta_R(Quintet2().Triplet().Doublet().Singlet1()) < detector_geometry.JetConeSize) return true;
  if (Quintet1().Doublet().Singlet2().delta_R(Quintet2().Triplet().Doublet().Singlet2()) < detector_geometry.JetConeSize) return true;

  if (Quintet1().Triplet().SingletJet().delta_R(Quintet2().Doublet().Singlet1()) < detector_geometry.JetConeSize) return true;
  if (Quintet1().Triplet().SingletJet().delta_R(Quintet2().Doublet().Singlet2()) < detector_geometry.JetConeSize) return true;
  if (Quintet1().Triplet().SingletJet().delta_R(Quintet2().Triplet().SingletJet()) < detector_geometry.JetConeSize) return true;
  if (Quintet1().Triplet().SingletJet().delta_R(Quintet2().Triplet().Doublet().Singlet1()) < detector_geometry.JetConeSize) return true;
  if (Quintet1().Triplet().SingletJet().delta_R(Quintet2().Triplet().Doublet().Singlet2()) < detector_geometry.JetConeSize) return true;

  if (Quintet1().Triplet().Doublet().Singlet1().delta_R(Quintet2().Doublet().Singlet1()) < detector_geometry.JetConeSize) return true;
  if (Quintet1().Triplet().Doublet().Singlet1().delta_R(Quintet2().Doublet().Singlet2()) < detector_geometry.JetConeSize) return true;
  if (Quintet1().Triplet().Doublet().Singlet1().delta_R(Quintet2().Triplet().SingletJet()) < detector_geometry.JetConeSize) return true;
  if (Quintet1().Triplet().Doublet().Singlet1().delta_R(Quintet2().Triplet().Doublet().Singlet1()) < detector_geometry.JetConeSize) return true;
  if (Quintet1().Triplet().Doublet().Singlet1().delta_R(Quintet2().Triplet().Doublet().Singlet2()) < detector_geometry.JetConeSize) return true;

  if (Quintet1().Triplet().Doublet().Singlet2().delta_R(Quintet2().Doublet().Singlet1()) < detector_geometry.JetConeSize) return true;
  if (Quintet1().Triplet().Doublet().Singlet2().delta_R(Quintet2().Doublet().Singlet2()) < detector_geometry.JetConeSize) return true;
  if (Quintet1().Triplet().Doublet().Singlet2().delta_R(Quintet2().Triplet().SingletJet()) < detector_geometry.JetConeSize) return true;
  if (Quintet1().Triplet().Doublet().Singlet2().delta_R(Quintet2().Triplet().Doublet().Singlet1()) < detector_geometry.JetConeSize) return true;
  if (Quintet1().Triplet().Doublet().Singlet2().delta_R(Quintet2().Triplet().Doublet().Singlet2()) < detector_geometry.JetConeSize) return true;

  return false;
}
