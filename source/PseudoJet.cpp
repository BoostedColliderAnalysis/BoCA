/**
 * Copyright (C) 2015 Jan Hajer
 */

#include "PseudoJet.hh"
#include "TLorentzVector.h"
#include "Particles.hh"
#include "Debug.hh"

namespace boca
{

PseudoJet::PseudoJet() : fastjet::PseudoJet() {}

PseudoJet::PseudoJet(TLorentzVector const& vector) : fastjet::PseudoJet(vector.Px(), vector.Py(), vector.Pz(), vector.E()) {}

PseudoJet::PseudoJet(LorentzVector const& vector) : fastjet::PseudoJet(vector.Px(), vector.Py(), vector.Pz(), vector.E()) {}

PseudoJet::PseudoJet(const exroot::Electron& Particle) : PseudoJet(LorentzVector(Particle)) {}

PseudoJet::PseudoJet(const exroot::GenJet& Particle) : PseudoJet(LorentzVector(Particle)) {}

PseudoJet::PseudoJet(const exroot::GenParticle& Particle) : PseudoJet(LorentzVector(Particle)) {}

PseudoJet::PseudoJet(const exroot::Jet& Particle) : PseudoJet(LorentzVector(Particle)) {}

PseudoJet::PseudoJet(const exroot::LHEFParticle& Particle) : PseudoJet(LorentzVector(Particle)) {}

PseudoJet::PseudoJet(const exroot::Muon& Particle) : PseudoJet(LorentzVector(Particle)) {}

PseudoJet::PseudoJet(const exroot::Photon& Particle) : PseudoJet(LorentzVector(Particle)) {}

PseudoJet::PseudoJet(const exroot::Tau& Particle) : PseudoJet(LorentzVector(Particle)) {}

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
  if (delta_R(jet) == fastjet::pseudojet_invalid_rap) return 0. * rad;
    if (delta_R(jet) > 100) {
      Error("invalid delta_r", delta_R(jet));
      return 0. * rad;
    }
    return delta_R(jet) * rad;
}

Angle PseudoJet::Rap() const
{
    if (rap() == fastjet::pseudojet_invalid_rap) return 0. * rad;
    if (rap() > 100) {
      Error("invalid rap", rap());
      return 0. * rad;
    }
    return rap() * rad;
}

Angle PseudoJet::Phi() const
{
    return phi_std() * rad;
}


}

