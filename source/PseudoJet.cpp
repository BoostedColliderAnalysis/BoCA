/**
 * Copyright (C) 2015 Jan Hajer
 */

#include "PseudoJet.hh"
#include "TLorentzVector.h"
#include "physics/Particles.hh"
#include "Debug.hh"

namespace boca
{

PseudoJet::PseudoJet() : fastjet::PseudoJet() {}

PseudoJet::PseudoJet(TLorentzVector const& vector) : fastjet::PseudoJet(vector.Px(), vector.Py(), vector.Pz(), vector.E()) {}

PseudoJet::PseudoJet(LorentzVector<Momentum> const& vector) : fastjet::PseudoJet(vector.Px() / GeV, vector.Py() / GeV, vector.Pz() / GeV, vector.E() / GeV) {}

Momentum PseudoJet::Pt() const
{
    return pt() * GeV;
}

Mass PseudoJet::Mass() const
{
    return m() * GeV;
}

Angle PseudoJet::DeltaRTo(const fastjet::PseudoJet& jet) const
{
    if (delta_R(jet) == fastjet::pseudojet_invalid_rap) return 0_rad;
    if (delta_R(jet) > 100) {
        Error("invalid delta_r", delta_R(jet));
        return 0_rad;
    }
    return delta_R(jet) * rad;
}

Angle PseudoJet::DeltaPhiTo(const fastjet::PseudoJet& jet) const
{
    return delta_phi_to(jet) * rad;
}


Angle PseudoJet::Rap() const
{
    if (rap() == fastjet::pseudojet_invalid_rap) return 0_rad;
    if (rap() > 100) {
        Error("invalid rap", rap());
        return 0_rad;
    }
    return rap() * rad;
}

Angle PseudoJet::Phi() const
{
    return phi_std() * rad;
}

Energy PseudoJet::Energy() const
{
    return e() * GeV;
}


}

