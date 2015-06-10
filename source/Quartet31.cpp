# include "Quartet31.hh"

analysis::Triplet analysis::Quartet31::Triplet() const
{
    return multiplet_1_;
}

fastjet::PseudoJet analysis::Quartet31::SingletJet()const
{
    return multiplet_2_.Jet();
}

analysis::Singlet analysis::Quartet31::Singlet()const
{
    return multiplet_2_;
}

// bool analysis::Quartet31::Overlap() const
// {
//   DetectorGeometry detector_geometry;
//   if (Triplet().SingletJet().delta_R(SingletJet()) < detector_geometry.JetConeSize) return true;
//   if (Triplet().Doublet().SingletJet1().delta_R(SingletJet()) < detector_geometry.JetConeSize) return true;
//   if (Triplet().Doublet().SingletJet2().delta_R(SingletJet()) < detector_geometry.JetConeSize) return true;
//   return false;
// }
//
// bool analysis::Quartet31::Overlap(const fastjet::PseudoJet &jet) const
// {
// //   DetectorGeometry detector_geometry;
//
//   if(Triplet().Overlap(jet)) return true;
//   if(Singlet().Overlap(jet)) return true;
// //   if (Triplet().SingletJet().delta_R(SingletJet()) < detector_geometry.JetConeSize) return true;
// //   if (Triplet().Doublet().Singlet1().delta_R(SingletJet()) < detector_geometry.JetConeSize) return true;
// //   if (Triplet().Doublet().Singlet2().delta_R(SingletJet()) < detector_geometry.JetConeSize) return true;
//   return false;
// }
