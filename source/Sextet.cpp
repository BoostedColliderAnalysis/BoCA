# include "Sextet.hh"

analysis::Triplet analysis::Sextet::Triplet1() const
{
    return multiplet_1_;
}

analysis::Triplet analysis::Sextet::Triplet2() const
{
    return multiplet_2_;
}

// bool analysis::Sextet::Overlap() const
// {
//     DetectorGeometry detector_geometry;
//     if (Triplet1().SingletJet().delta_R(Triplet2().SingletJet()) < detector_geometry.JetConeSize) return true;
//     if (Triplet1().Doublet().SingletJet1().delta_R(Triplet2().SingletJet()) < detector_geometry.JetConeSize) return true;
//     if (Triplet1().Doublet().SingletJet2().delta_R(Triplet2().SingletJet()) < detector_geometry.JetConeSize) return true;
//     if (Triplet1().SingletJet().delta_R(Triplet2().Doublet().SingletJet1()) < detector_geometry.JetConeSize) return true;
//     if (Triplet1().Doublet().SingletJet1().delta_R(Triplet2().Doublet().SingletJet1()) < detector_geometry.JetConeSize) return true;
//     if (Triplet1().Doublet().SingletJet2().delta_R(Triplet2().Doublet().SingletJet1()) < detector_geometry.JetConeSize) return true;
//     if (Triplet1().SingletJet().delta_R(Triplet2().Doublet().SingletJet2()) < detector_geometry.JetConeSize) return true;
//     if (Triplet1().Doublet().SingletJet1().delta_R(Triplet2().Doublet().SingletJet2()) < detector_geometry.JetConeSize) return true;
//     if (Triplet1().Doublet().SingletJet2().delta_R(Triplet2().Doublet().SingletJet2()) < detector_geometry.JetConeSize) return true;
//     return false;
// }
//
// bool analysis::Sextet::Overlap(const fastjet::PseudoJet &jet) const
// {
//     DetectorGeometry detector_geometry;
//     if (jet.delta_R(Triplet1().SingletJet()) < detector_geometry.JetConeSize) return true;
//     if (jet.delta_R(Triplet2().SingletJet()) < detector_geometry.JetConeSize) return true;
//     if (jet.delta_R(Triplet2().Doublet().SingletJet1()) < detector_geometry.JetConeSize) return true;
//     if (jet.delta_R(Triplet2().Doublet().SingletJet2()) < detector_geometry.JetConeSize) return true;
//     return false;
// }
