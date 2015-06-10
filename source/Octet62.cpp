# include "Octet62.hh"

// bool analysis::Octet62::Overlap() const
// {
//     DetectorGeometry detector_geometry;
//     if (Sextet().Triplet1().SingletJet().delta_R(Doublet().SingletJet1()) < detector_geometry.JetConeSize) return true;
//     if (Sextet().Triplet1().SingletJet().delta_R(Doublet().SingletJet2()) < detector_geometry.JetConeSize) return true;
//     if (Sextet().Triplet2().SingletJet().delta_R(Doublet().SingletJet1()) < detector_geometry.JetConeSize) return true;
//     if (Sextet().Triplet2().SingletJet().delta_R(Doublet().SingletJet2()) < detector_geometry.JetConeSize) return true;
//     if (Sextet().Triplet2().Doublet().SingletJet1().delta_R(Doublet().SingletJet1()) < detector_geometry.JetConeSize) return true;
//     if (Sextet().Triplet2().Doublet().SingletJet1().delta_R(Doublet().SingletJet2()) < detector_geometry.JetConeSize) return true;
//     if (Sextet().Triplet2().Doublet().SingletJet2().delta_R(Doublet().SingletJet1()) < detector_geometry.JetConeSize) return true;
//     if (Sextet().Triplet2().Doublet().SingletJet2().delta_R(Doublet().SingletJet2()) < detector_geometry.JetConeSize) return true;
//     if (Sextet().Triplet2().Doublet().Jet().delta_R(Doublet().SingletJet1()) < detector_geometry.JetConeSize) return true;
//     if (Sextet().Triplet2().Doublet().Jet().delta_R(Doublet().SingletJet2()) < detector_geometry.JetConeSize) return true;
//     if (Sextet().Triplet2().Jet().delta_R(Doublet().SingletJet1()) < detector_geometry.JetConeSize) return true;
//     if (Sextet().Triplet2().Jet().delta_R(Doublet().SingletJet2()) < detector_geometry.JetConeSize) return true;
//     return false;
// }
// 
// bool analysis::Octet62::Overlap(const fastjet::PseudoJet &jet) const
// {
//     DetectorGeometry detector_geometry;
//     if (jet.delta_R(Sextet().Triplet1().SingletJet()) < detector_geometry.JetConeSize) return true;
//     if (jet.delta_R(Sextet().Triplet2().SingletJet()) < detector_geometry.JetConeSize) return true;
//     if (jet.delta_R(Sextet().Triplet2().Doublet().SingletJet1()) < detector_geometry.JetConeSize) return true;
//     if (jet.delta_R(Sextet().Triplet2().Doublet().SingletJet2()) < detector_geometry.JetConeSize) return true;
//     if (jet.delta_R(Doublet().SingletJet1()) < detector_geometry.JetConeSize) return true;
//     if (jet.delta_R(Doublet().SingletJet2()) < detector_geometry.JetConeSize) return true;
//     return false;
// }

analysis::Sextet analysis::Octet62::Sextet()const {
  return multiplet_1_;
}

analysis::Doublet analysis::Octet62::Doublet() const {
  return multiplet_2_;
}
