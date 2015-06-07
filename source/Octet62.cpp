# include "Octet62.hh"

analysis::Octet62::Octet62(const analysis::Sextet &sextet, const analysis::Doublet &doublet)
{
    sextet_ = sextet;
    doublet_ = doublet;
    SetBdt(sextet_.Bdt(), doublet_.Bdt());
    SetTag(sextet_.Tag(), doublet_.Tag());
}

bool analysis::Octet62::overlap() const
{
    DetectorGeometry detector_geometry;
    if (sextet().triplet1().singlet().delta_R(doublet().Singlet1()) < detector_geometry.JetConeSize) return true;
    if (sextet().triplet1().singlet().delta_R(doublet().Singlet2()) < detector_geometry.JetConeSize) return true;
    if (sextet().triplet2().singlet().delta_R(doublet().Singlet1()) < detector_geometry.JetConeSize) return true;
    if (sextet().triplet2().singlet().delta_R(doublet().Singlet2()) < detector_geometry.JetConeSize) return true;
    if (sextet().triplet2().doublet().Singlet1().delta_R(doublet().Singlet1()) < detector_geometry.JetConeSize) return true;
    if (sextet().triplet2().doublet().Singlet1().delta_R(doublet().Singlet2()) < detector_geometry.JetConeSize) return true;
    if (sextet().triplet2().doublet().Singlet2().delta_R(doublet().Singlet1()) < detector_geometry.JetConeSize) return true;
    if (sextet().triplet2().doublet().Singlet2().delta_R(doublet().Singlet2()) < detector_geometry.JetConeSize) return true;
    if (sextet().triplet2().doublet().Jet().delta_R(doublet().Singlet1()) < detector_geometry.JetConeSize) return true;
    if (sextet().triplet2().doublet().Jet().delta_R(doublet().Singlet2()) < detector_geometry.JetConeSize) return true;
    if (sextet().triplet2().Jet().delta_R(doublet().Singlet1()) < detector_geometry.JetConeSize) return true;
    if (sextet().triplet2().Jet().delta_R(doublet().Singlet2()) < detector_geometry.JetConeSize) return true;
    return false;
}

bool analysis::Octet62::overlap(const fastjet::PseudoJet &jet) const
{
    DetectorGeometry detector_geometry;
    if (jet.delta_R(sextet().triplet1().singlet()) < detector_geometry.JetConeSize) return true;
    if (jet.delta_R(sextet().triplet2().singlet()) < detector_geometry.JetConeSize) return true;
    if (jet.delta_R(sextet().triplet2().doublet().Singlet1()) < detector_geometry.JetConeSize) return true;
    if (jet.delta_R(sextet().triplet2().doublet().Singlet2()) < detector_geometry.JetConeSize) return true;
    if (jet.delta_R(doublet().Singlet1()) < detector_geometry.JetConeSize) return true;
    if (jet.delta_R(doublet().Singlet2()) < detector_geometry.JetConeSize) return true;
    return false;
}
