# include "Decuplet.hh"

// bool toppartner::Decuplet::Overlap() const
// {
//   analysis::DetectorGeometry detector_geometry;
//
//   if (Quintet1().Doublet().SingletJet1().delta_R(Quintet2().Doublet().SingletJet1()) < detector_geometry.JetConeSize) return true;
//   if (Quintet1().Doublet().SingletJet1().delta_R(Quintet2().Doublet().SingletJet2()) < detector_geometry.JetConeSize) return true;
//   if (Quintet1().Doublet().SingletJet1().delta_R(Quintet2().Triplet().SingletJet()) < detector_geometry.JetConeSize) return true;
//   if (Quintet1().Doublet().SingletJet1().delta_R(Quintet2().Triplet().Doublet().SingletJet1()) < detector_geometry.JetConeSize) return true;
//   if (Quintet1().Doublet().SingletJet1().delta_R(Quintet2().Triplet().Doublet().SingletJet2()) < detector_geometry.JetConeSize) return true;
//
//   if (Quintet1().Doublet().SingletJet2().delta_R(Quintet2().Doublet().SingletJet1()) < detector_geometry.JetConeSize) return true;
//   if (Quintet1().Doublet().SingletJet2().delta_R(Quintet2().Doublet().SingletJet2()) < detector_geometry.JetConeSize) return true;
//   if (Quintet1().Doublet().SingletJet2().delta_R(Quintet2().Triplet().SingletJet()) < detector_geometry.JetConeSize) return true;
//   if (Quintet1().Doublet().SingletJet2().delta_R(Quintet2().Triplet().Doublet().SingletJet1()) < detector_geometry.JetConeSize) return true;
//   if (Quintet1().Doublet().SingletJet2().delta_R(Quintet2().Triplet().Doublet().SingletJet2()) < detector_geometry.JetConeSize) return true;
//
//   if (Quintet1().Triplet().SingletJet().delta_R(Quintet2().Doublet().SingletJet1()) < detector_geometry.JetConeSize) return true;
//   if (Quintet1().Triplet().SingletJet().delta_R(Quintet2().Doublet().SingletJet2()) < detector_geometry.JetConeSize) return true;
//   if (Quintet1().Triplet().SingletJet().delta_R(Quintet2().Triplet().SingletJet()) < detector_geometry.JetConeSize) return true;
//   if (Quintet1().Triplet().SingletJet().delta_R(Quintet2().Triplet().Doublet().SingletJet1()) < detector_geometry.JetConeSize) return true;
//   if (Quintet1().Triplet().SingletJet().delta_R(Quintet2().Triplet().Doublet().SingletJet2()) < detector_geometry.JetConeSize) return true;
//
//   if (Quintet1().Triplet().Doublet().SingletJet1().delta_R(Quintet2().Doublet().SingletJet1()) < detector_geometry.JetConeSize) return true;
//   if (Quintet1().Triplet().Doublet().SingletJet1().delta_R(Quintet2().Doublet().SingletJet2()) < detector_geometry.JetConeSize) return true;
//   if (Quintet1().Triplet().Doublet().SingletJet1().delta_R(Quintet2().Triplet().SingletJet()) < detector_geometry.JetConeSize) return true;
//   if (Quintet1().Triplet().Doublet().SingletJet1().delta_R(Quintet2().Triplet().Doublet().SingletJet1()) < detector_geometry.JetConeSize) return true;
//   if (Quintet1().Triplet().Doublet().SingletJet1().delta_R(Quintet2().Triplet().Doublet().SingletJet2()) < detector_geometry.JetConeSize) return true;
//
//   if (Quintet1().Triplet().Doublet().SingletJet2().delta_R(Quintet2().Doublet().SingletJet1()) < detector_geometry.JetConeSize) return true;
//   if (Quintet1().Triplet().Doublet().SingletJet2().delta_R(Quintet2().Doublet().SingletJet2()) < detector_geometry.JetConeSize) return true;
//   if (Quintet1().Triplet().Doublet().SingletJet2().delta_R(Quintet2().Triplet().SingletJet()) < detector_geometry.JetConeSize) return true;
//   if (Quintet1().Triplet().Doublet().SingletJet2().delta_R(Quintet2().Triplet().Doublet().SingletJet1()) < detector_geometry.JetConeSize) return true;
//   if (Quintet1().Triplet().Doublet().SingletJet2().delta_R(Quintet2().Triplet().Doublet().SingletJet2()) < detector_geometry.JetConeSize) return true;
//
//   return false;
// }
