# include "Octet44.hh"

bool heavyhiggs::Octet44::overlap() const
{
    analysis::DetectorGeometry detector_geometry;
    if (Quartet1().SingletJet().delta_R(Quartet2().SingletJet()) < detector_geometry.JetConeSize) return true;
    if (Quartet1().SingletJet().delta_R(Quartet2().Triplet().SingletJet()) < detector_geometry.JetConeSize) return true;
    if (Quartet1().SingletJet().delta_R(Quartet2().Triplet().Doublet().Singlet1()) < detector_geometry.JetConeSize) return true;
    if (Quartet1().SingletJet().delta_R(Quartet2().Triplet().Doublet().Singlet2()) < detector_geometry.JetConeSize) return true;
    if (Quartet1().Triplet().SingletJet().delta_R(Quartet2().SingletJet()) < detector_geometry.JetConeSize) return true;
    if (Quartet1().Triplet().SingletJet().delta_R(Quartet2().Triplet().SingletJet()) < detector_geometry.JetConeSize) return true;
    if (Quartet1().Triplet().SingletJet().delta_R(Quartet2().Triplet().Doublet().Singlet1()) < detector_geometry.JetConeSize) return true;
    if (Quartet1().Triplet().SingletJet().delta_R(Quartet2().Triplet().Doublet().Singlet2()) < detector_geometry.JetConeSize) return true;
    if (Quartet1().Triplet().Doublet().Singlet1().delta_R(Quartet2().SingletJet()) < detector_geometry.JetConeSize) return true;
    if (Quartet1().Triplet().Doublet().Singlet1().delta_R(Quartet2().Triplet().SingletJet()) < detector_geometry.JetConeSize) return true;
    if (Quartet1().Triplet().Doublet().Singlet1().delta_R(Quartet2().Triplet().Doublet().Singlet1()) < detector_geometry.JetConeSize) return true;
    if (Quartet1().Triplet().Doublet().Singlet1().delta_R(Quartet2().Triplet().Doublet().Singlet2()) < detector_geometry.JetConeSize) return true;
    if (Quartet1().Triplet().Doublet().Singlet2().delta_R(Quartet2().SingletJet()) < detector_geometry.JetConeSize) return true;
    if (Quartet1().Triplet().Doublet().Singlet2().delta_R(Quartet2().Triplet().SingletJet()) < detector_geometry.JetConeSize) return true;
    if (Quartet1().Triplet().Doublet().Singlet2().delta_R(Quartet2().Triplet().Doublet().Singlet1()) < detector_geometry.JetConeSize) return true;
    if (Quartet1().Triplet().Doublet().Singlet2().delta_R(Quartet2().Triplet().Doublet().Singlet2()) < detector_geometry.JetConeSize) return true;
    return false;
}

bool heavyhiggs::Octet44::overlap(const fastjet::PseudoJet &jet) const
{
    analysis::DetectorGeometry detector_geometry;
    if (jet.delta_R(Quartet1().SingletJet()) < detector_geometry.JetConeSize) return true;
    if (jet.delta_R(Quartet1().Triplet().SingletJet()) < detector_geometry.JetConeSize) return true;
    if (jet.delta_R(Quartet1().Triplet().Doublet().Singlet1()) < detector_geometry.JetConeSize) return true;
    if (jet.delta_R(Quartet1().Triplet().Doublet().Singlet2()) < detector_geometry.JetConeSize) return true;
    if (jet.delta_R(Quartet2().SingletJet()) < detector_geometry.JetConeSize) return true;
    if (jet.delta_R(Quartet2().Triplet().SingletJet()) < detector_geometry.JetConeSize) return true;
    return false;
}
