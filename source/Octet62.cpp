# include "Octet62.hh"

bool analysis::Octet62::overlap() const
{
    DetectorGeometry detector_geometry;
    if (Sextet().Triplet1().SingletJet().delta_R(Doublet().Singlet1()) < detector_geometry.JetConeSize) return true;
    if (Sextet().Triplet1().SingletJet().delta_R(Doublet().Singlet2()) < detector_geometry.JetConeSize) return true;
    if (Sextet().Triplet2().SingletJet().delta_R(Doublet().Singlet1()) < detector_geometry.JetConeSize) return true;
    if (Sextet().Triplet2().SingletJet().delta_R(Doublet().Singlet2()) < detector_geometry.JetConeSize) return true;
    if (Sextet().Triplet2().Doublet().Singlet1().delta_R(Doublet().Singlet1()) < detector_geometry.JetConeSize) return true;
    if (Sextet().Triplet2().Doublet().Singlet1().delta_R(Doublet().Singlet2()) < detector_geometry.JetConeSize) return true;
    if (Sextet().Triplet2().Doublet().Singlet2().delta_R(Doublet().Singlet1()) < detector_geometry.JetConeSize) return true;
    if (Sextet().Triplet2().Doublet().Singlet2().delta_R(Doublet().Singlet2()) < detector_geometry.JetConeSize) return true;
    if (Sextet().Triplet2().Doublet().Jet().delta_R(Doublet().Singlet1()) < detector_geometry.JetConeSize) return true;
    if (Sextet().Triplet2().Doublet().Jet().delta_R(Doublet().Singlet2()) < detector_geometry.JetConeSize) return true;
    if (Sextet().Triplet2().Jet().delta_R(Doublet().Singlet1()) < detector_geometry.JetConeSize) return true;
    if (Sextet().Triplet2().Jet().delta_R(Doublet().Singlet2()) < detector_geometry.JetConeSize) return true;
    return false;
}

bool analysis::Octet62::overlap(const fastjet::PseudoJet &jet) const
{
    DetectorGeometry detector_geometry;
    if (jet.delta_R(Sextet().Triplet1().SingletJet()) < detector_geometry.JetConeSize) return true;
    if (jet.delta_R(Sextet().Triplet2().SingletJet()) < detector_geometry.JetConeSize) return true;
    if (jet.delta_R(Sextet().Triplet2().Doublet().Singlet1()) < detector_geometry.JetConeSize) return true;
    if (jet.delta_R(Sextet().Triplet2().Doublet().Singlet2()) < detector_geometry.JetConeSize) return true;
    if (jet.delta_R(Doublet().Singlet1()) < detector_geometry.JetConeSize) return true;
    if (jet.delta_R(Doublet().Singlet2()) < detector_geometry.JetConeSize) return true;
    return false;
}
