# include "Quintet.hh"

// bool analysis::Quintet::Overlap() const
// {
//     DetectorGeometry detector_geometry;
//     if (Doublet().SingletJet1().delta_R(Triplet().SingletJet()) < detector_geometry.JetConeSize) return true;
//     if (Doublet().SingletJet1().delta_R(Triplet().Doublet().SingletJet1()) < detector_geometry.JetConeSize) return true;
//     if (Doublet().SingletJet1().delta_R(Triplet().Doublet().SingletJet2()) < detector_geometry.JetConeSize) return true;
//     if (Doublet().SingletJet2().delta_R(Triplet().SingletJet()) < detector_geometry.JetConeSize) return true;
//     if (Doublet().SingletJet2().delta_R(Triplet().Doublet().SingletJet1()) < detector_geometry.JetConeSize) return true;
//     if (Doublet().SingletJet2().delta_R(Triplet().Doublet().SingletJet2()) < detector_geometry.JetConeSize) return true;
//     return false;
// }
//
//

analysis::Doublet analysis::Quintet::Doublet()const {
  return multiplet_2_;
}

analysis::Triplet analysis::Quintet::Triplet()const {
  return multiplet_1_;
}
